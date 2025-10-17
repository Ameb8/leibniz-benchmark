FROM debian:bookworm-slim

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    openjdk-17-jdk \
    python3 \
    golang \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Default command (can be overridden)
CMD ["make"]
