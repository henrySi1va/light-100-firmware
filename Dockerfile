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
    clang-tidy clang-format \
    && rm -rf /var/lib/apt/lists/*

# Install west
RUN pip3 install west --break-system-packages

# Install pre-commit
RUN pip3 install pre-commit --break-system-packages

# Set up Zephyr environment
RUN mkdir -p /opt/zephyrproject
WORKDIR /opt/zephyrproject
RUN west init
RUN west update
RUN west zephyr-export

# Install Zephyr Python dependencies
RUN pip3 install -r /opt/zephyrproject/zephyr/scripts/requirements.txt --break-system-packages

# Install Zephyr SDK
WORKDIR /opt/zephyrproject/zephyr
RUN west sdk install --toolchains arm-zephyr-eabi

# Set environment variables
ENV ZEPHYR_BASE=/opt/zephyrproject/zephyr
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyrproject/zephyr/zephyr-sdk

# Add SDK tools to PATH
ENV PATH="/root/zephyr-sdk-0.17.0/sysroots/x86_64-pokysdk-linux/usr/bin:${PATH}"

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

CMD ["/bin/bash"]