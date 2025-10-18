FROM debian:bookworm-slim

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    openjdk-17-jdk \
    python3 \
    python3-numpy \
    golang \
    make \
    ca-certificates \
    curl \
    gnupg \
    software-properties-common \
    libcurl4-openssl-dev \
    libssl-dev \
    libxml2-dev \
    r-base \
    && curl -fsSL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

# Install R packages 
RUN R -e "install.packages(c('tidyverse'), repos='https://cloud.r-project.org')"

# Set working directory
WORKDIR /app

# Default command (can be overridden)
CMD ["make"]
