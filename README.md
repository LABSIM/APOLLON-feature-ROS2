# APOLLON-feature-ROS2

inspired from https://github.com/Unity-Technologies/Unity-Robotics-Hub/blob/v0.7.0/tutorials/ros_unity_integration/README.md

``` powershell
docker build -t apollon-isir-foxy:0.0.1 -f docker/ISIR/Dockerfile .
docker run -it --rm -p 10000:10000 apollon-isir-foxy:0.0.1 /bin/bash
```

OR better ! Podman ! https://podman.io/

``` powershell
podman build -t apollon-isir-foxy:0.0.1 -f docker/ISIR/Dockerfile .
podman run -it --rm -p 10000:10000 apollon-isir-foxy:0.0.1 /bin/bash
```