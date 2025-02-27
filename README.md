# light-100

## Overview

This project is based on the Zephyr Real-Time Operating System (RTOS).

## Setting up the Dev Environment

The development environment is containerized using docker.

To run the development environment, simply run:

```sh
docker compose up
```

It is recommended to use the VS Code editor, but any IDE of choice will work.

Currently, the only target is the QEMU ARM M3 simulator.
Debugging has been set up using the Cortex-Debug extension.

## Repository Structure

The repository is organized as follows:

```
/workspace
├── README.md           # Project documentation
├── app                 # Application code
│   ├── src             # Application source files (including main.c)
│   ├── prj.conf        # Zephyr project configuration file
|   └── CMakeLists.txt  # CMake build configuration
|
├── docker-compose.yml  # Docker compose file
├── Dockerfile          # Docker image build file
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
