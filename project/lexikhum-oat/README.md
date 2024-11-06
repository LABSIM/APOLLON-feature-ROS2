# LEXIKHUM-OAT

***LEX**ique d'**I**nteraction **K**inesthesique **HU**main-**M**achine - **O**bstacle **A**voidance **T**ask*

## Build

### Docker engine
    
https://www.docker.com/

```bash
docker build -t apollon-isir-humble:0.0.1 -f container/docker/Dockerfile .
docker network create -d host apollon-net
docker run -it --rm --network=apollon-net -p 10000:10000 -p 11311:11311 -p 11811:11811 apollon-isir-humble:0.0.1 /bin/bash
```

### Podman engine

https://podman.io/ 

```bash
podman build -t apollon-isir-humble:0.0.1 -f container/oci/Containerfile .
podman run -it --rm -p 10000:10000 -p 11311:11311 -p 11811:11811 apollon-isir-humble:0.0.1 /bin/bash
```

> see [here](https://github.com/containers) or [there](https://opencontainers.org/) for more info about the open containers initiative.

## Launch

into the first container instance, we lauch the ROS2 discovery server with default options 

```bash
fastdds discovery -i 0
```

usually, as we have launched the discovery server into a container running on the same ISIR "Main ROS2" Host, we run a second container instance (aka. the LEXIKHUM-OAT gateway) :

```bash
export ROS_DISCOVERY_SERVER="<server-ip>:<server-port>"
ros2 launch lexikhum_oat_gateway lexikhum_oat_gateway_container_launch.py
```

with :

- [server-ip]   = 0.0.0.0 
- [server-port] = 11811

> for more informations abour ROS2 & the FastDDS discovery service, see [here](https://fast-dds.docs.eprosima.com/en/latest/fastdds/ros2/discovery_server/ros2_discovery_server.html) or [there](https://fast-dds.docs.eprosima.com/en/latest/fastdds/discovery/discovery_server.html)
