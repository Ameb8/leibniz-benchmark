# Load required packages
library(tidyverse)

# Read the CSV file
data <- read_csv("../benchmark_data.csv")

# Summarize average Wall-Clock and CPU time by Benchmark
avg_times <- data %>%
  group_by(Benchmark) %>%
  summarise(
    avg_wall = mean(`Wall-Clock Time`),
    avg_cpu = mean(`CPU Time`)
  ) %>%
  pivot_longer(cols = c(avg_wall, avg_cpu), names_to = "Time_Type", values_to = "Average_Time")

# Rename time types for display
avg_times$Time_Type <- recode(avg_times$Time_Type,
                              "avg_wall" = "Wall-Clock Time",
                              "avg_cpu" = "CPU Time")

# Plot the bar chart
benchmark_plot <- ggplot(avg_times, aes(x = reorder(Benchmark, Average_Time), y = Average_Time, fill = Time_Type)) +
    geom_bar(stat = "identity", position = "dodge") +
    coord_flip() +  # Flip for better readability
    labs(title = "Average Benchmark Times",
        x = "Benchmark",
        y = "Average Time (seconds)",
        fill = "Time Type") +
    theme_minimal()

ggsave("benchmark_times.png", plot = benchmark_plot, width = 10, height = 6, dpi = 300)
