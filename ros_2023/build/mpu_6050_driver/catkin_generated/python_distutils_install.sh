#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/marco/ros_2023/src/mpu_6050_driver"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/marco/ros_2023/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/marco/ros_2023/install/lib/python2.7/dist-packages:/home/marco/ros_2023/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/marco/ros_2023/build" \
    "/usr/bin/python2" \
    "/home/marco/ros_2023/src/mpu_6050_driver/setup.py" \
     \
    build --build-base "/home/marco/ros_2023/build/mpu_6050_driver" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/marco/ros_2023/install" --install-scripts="/home/marco/ros_2023/install/bin"
