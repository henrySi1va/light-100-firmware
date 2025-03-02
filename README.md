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

## Updating the Docker Image

After modifying the `Dockerfile` or `docker-compose.yml`, exit the dev container and run `docker compose down` and `docker build .`.
This will make sure the new image is used when opening the development environment.

To update the image on the GitHub Container Registry for CI/CD, run the following:

```
docker tag light-100-firmware-zephyr ghcr.io/YOUR_USERNAME/light-100-firmware-zephyr:latest

docker push ghcr.io/USERNAME/light-100-firmware-zephyr:latest
```

Make sure that you logged in to the GHCR using a personal access token:

```
echo $GHCR_PAT | docker login ghcr.io -u YOUR_USERNAME --password-stdin
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
