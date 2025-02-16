FROM debian:bookworm-slim

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    cmake \
    ninja-build \
    gperf \
    ccache \
    dfu-util \
    device-tree-compiler \
    wget \
    python3-pip \
    python3-setuptools \
    python3-wheel \
    python3-tk \
    python3-dev \
    python3-venv \
    xz-utils \
    file \
    make gcc gcc-multilib g++-multilib \
    libsdl2-dev libmagic1 \
    && rm -rf /var/lib/apt/lists/*

# Create a new virtual environment
RUN python3 -m venv /opt/zephyrproject/.venv

# Install west
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && pip3 install west"

# Set up Zephyr environment
RUN mkdir -p /opt/zephyrproject
WORKDIR /opt/zephyrproject
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && west init"
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && west update"
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && west zephyr-export"

# Install Zephyr Python dependencies
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && west packages pip --install"

# Install Zephyr SDK
WORKDIR /opt/zephyrproject/zephyr
RUN /bin/bash -c "source /opt/zephyrproject/.venv/bin/activate && west sdk install"

# Set environment variables
ENV ZEPHYR_BASE=/opt/zephyrproject/zephyr
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyrproject/zephyr/zephyr-sdk

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

CMD ["/bin/bash"]