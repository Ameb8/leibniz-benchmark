FROM debian:bookworm-slim

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    openjdk-17-jdk \
    python3 \
    golang \
    make \
    ca-certificates \
    && curl -fsSL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Create directories for plot data
RUN mkdir -p /app/benchmark_dat /app/plots

# Install Python dependencies for NumPy benchmark and plot creation
RUN pip install --no-cache-dir -r requirements.txt \ 
 && pip install --no-cache-dir -r submodule2/requirements.txt

# Default command (can be overridden)
CMD ["make"]
