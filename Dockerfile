FROM debian:bookworm-slim

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    openjdk-17-jdk \
    python3 \
    python3-pip \
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

# Ensure requirements.txt exists in container at build-time
COPY requirements.txt requirements.txt
COPY benchmark_results/requirements.txt benchmark_results/requirements.txt

# Install Python dependencies for NumPy benchmark and plot creation
RUN python3 -m pip install --break-system-packages --no-cache-dir \
    -r requirements.txt \
    -r benchmark_results/requirements.txt

# Default command (can be overridden)
CMD ["make"]
