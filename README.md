# Gazebo DDS Plugins

This repository includes a number of plugins to integrate DDS applications
with the [Gazebo simulator](http://gazebosim.org). These plugins
enable DDS-based robotic systems to leverage Gazebo's simulation capabilities,
such as 3D simulation and computer vision.

In particular, the project provides the following plugins:

* [***API Plugin***](src/api_plugin/README.md) -- This plugin provides a
  number of services that allow DDS applications to manage the simulation
  environment remotely.
* [***Bumper scan***](src/bumper_scan/README.md) -- It publishes information
  generated by a contact sensor.
* [***Camera***](src/camera/README.md) -- It publishes sensor data from cameras
  in Gazebo.
* [***Differential Drive***](src/diff_drive/README.md) -- It allows us to
  manage a differential drive robot and obtain the information it provides.
* [***Elevator***](src/elevator/README.md) -- It allows us to manage an
  elevator.
* [***Imu scan***](src/imu_scan/README.md) -- It publishes information produced
  by an IMU sensor.
* [***Laser scan***](src/laser_scan/README.md) -- It publishes the information
  provided by a laser sensor.
* [***Skid steer drive***](src/skid_steer_drive/README.md) -- It allows us to
 manage a skid steer drive robot and obtain the information it provides.
* [***Stereo camera***](src/stereo_camera/README.md) -- It allows us to manage
  two synchronized cameras and subscribe to the information they produce.

## Cloning Gazebo DDS Plugins Repository

Gazebo DDS Plugins depends on a separate repository that provides the IDL
definition of a number of well-known data types for robotic systems.

Therefore, to clone the Gazebo DDS Plugins you will need to run `git clone` as
follows, cloning the repository providing the types as well:

```bash
git clone --recurse-submodule https://github.com/rticommunity/gazebo-dds-plugins.git
```

## Building Gazebo DDS Plugins

### Preparing your Environment

Before building the Gazebo DDS Plugins, you will need to install Gazebo
and RTI Connext DDS on your system.

#### Installing Gazebo

```bash
# Debian-based systems (e.g., Ubuntu, Debian, or Linux Mint)
sudo apt install gazebo

# Fedora
sudo dnf gazebo gazebo-devel bullet-devel
```

#### Installing RTI Connext DDS

To RTI Connext DDS (host and target), please refer to the
[Core Libraries Getting Started Guide](https://community.rti.com/static/documentation/connext-dds/current/doc/manuals/connext_dds/html_files/RTI_ConnextDDS_CoreLibraries_GettingStarted/Content/GettingStarted/Installing_ConnextDDS.htm).

### Configuring Project with CMake

To configure the build project using CMake, you will need to provide the path
to your RTI Connext DDS installation and the desired target platform using the
`-DCONNEXTDDS_DIR` and `-DCONNEXTDDS_ARCH` arguments, respectively.

Note that in this case, we create a build directory within the source tree
to store the build results.

```bash
cd gazebo-dds-plugins
mkdir build; cd build
cmake -DCONNEXTDDS_DIR=/path/to/rti_connext_dds-x.y.z \
      -DCONNEXTDDS_ARCH=<arch_name> ..
```

### Building Plugins

Once you have configured your build project, simply run `make` to build the
plug-ins.

```bash
make
```

### Shipping Plugins

If you want to install the Gazebo DDS plugins on a well-known location,
provide CMake with the installation path:

```bash
cmake -DCMAKE_INSTALL_PREFIX=/path/to/installation/directory ..
```

And run `make install`:

```bash
make install
```

## Running Gazebo DDS Plugins

For more information on how to use run the plugins, please refer to the
README.md files within the folder of the corresponding plugin.
