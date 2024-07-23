# APOLLON-feature-ROS2

inspired from https://github.com/Unity-Technologies/Unity-Robotics-Hub/blob/v0.7.0/tutorials/ros_unity_integration/README.md

## Build the container 

### Podman :=) 

https://podman.io/ 

```bash
podman build -t apollon-isir-humble:0.0.1 -f docker/ISIR/Dockerfile .
podman network create -d host apollon-net
podman run -it --rm -p 10000:10000 -p 11311:11311 -p 11811:11811 apollon-isir-humble:0.0.1 /bin/bash
```

> see [here](https://github.com/containers) or [there](https://opencontainers.org/) for more info about the open containers initiative.

### Docker :=(
    
https://www.docker.com/

```bash
docker build -t apollon-isir-humble:0.0.1 -f docker/ISIR/Dockerfile .
docker network create -d host apollon-net
docker run -it --rm --network=apollon-net -p 10000:10000 -p 11311:11311 -p 11811:11811 apollon-isir-humble:0.0.1 /bin/bash
```

## Launch ROS2 endpoint in the container 

```bash
export ROS_DISCOVERY_SERVER="<server-ip>:11811"
ros2 launch lexikhum_oat_gateway lexikhum_oat_gateway_container_launch.py
```
