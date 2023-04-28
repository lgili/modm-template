# Example to show how to extend modm library to use my own boards and libraries
This repo use [modm](https://github.com/modm-io/modm) and [lbuild](https://github.com/modm-io/lbuild). You should read more about this two library, if you want to use this repo.   

This is the required software for generating, compiling and programming projects:
* [Python 3](http://www.python.org/).
* [Software Construct](https://www.scons.org/).
* [Library Builder](https://github.com/modm-io/lbuild).
* ARM toolchain: [gcc-arm-toolchain](https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack).
* [OpenOCD](http://openocd.org/) (at least v0.11!) or [Jlink](https://www.segger.com/downloads/jlink/).


### Linux
#### minimal build system 
For Ubuntu 22.04LTS, these commands install the minimal build system:
```bash
sudo apt install python3 python3-pip scons git libncurses5
pip3 install modm lbuild
```
The pip3 command installs executables into ~/.local/bin, which must be added to PATH if it is not already the case. Add the following line to the end of your ~/.bashrc file:
```bash
export PATH="$HOME/.local/bin:$PATH"
```
Ubuntu ≤ 19.10 unfortunately defaults to Python 2, however, our SCons tools require Python 3. For a less intrusive way to run all scons scripts with Python 3 add this to your .bashrc or .zshrc:
```bash
alias scons="/usr/bin/env python3 $(which scons)"
```
#### ARM Cortex-M
Install the ARM toolchain: [gcc-arm-toolchain](https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack) from xpack.

```bash
npm install --location=global xpm@latest
xpm install --global @xpack-dev-tools/arm-none-eabi-gcc@latest --verbose
```
And add to PATH:
```bash
export PATH="$HOME/.local/xPacks/@xpack-dev-tools/arm-none-eabi-gcc/12.2.1-1.2.1/.content/bin:$PATH"
```
#### OpenOCD
Install the OpenOCD tool:
```bash
sudo apt install openocd
```

#### JLink
Got to [Jlink](https://www.segger.com/downloads/jlink/) and download the installer, and do the installation.
And add to PATH:
```bash
export PATH="opt/SEGGER/JLink/:$PATH"
```

#### Hosted
To compile modm for host system targets (x86_64/arm64):
```bash
sudo apt install gcc build-essential libboost-all-dev
```

## Examples

A few examples are provided in the `example` folder:
* Blink - a standard blink led example
* ADC - run and print de values read

Run python to get values from uart:
```
python -m serial /dev/ttyACM0  115200
```

Is possible to run this two examples on three differents boards `["same70_xplained","custom-same70n20","custom-sams70q19"]`.
To change the board go to `example/lbuild.xml` and change the extends method `<extends>mcal:board-b</extends>` to use the board wanted.

```

# Compile with SCons 
cd blink
lbuild build
scons build
scons program
```


```
# Debud with SCons and VS code
lbuild build -m ::vscode  #and open vscode on blink folder
scons build
scons program
# if using jlink change "servertype": "jlink" and "device": "ATSAME70Q20A"
# on vscode press F5 to star debug
```

```
# Compile with SCons or Makefile
cd adc
lbuild build
scons
make
```
## Documentation

To generate documentation of the examples run this inside the folder that has the file `project.xml`:
```
(cd mcal/docs && make)
```

##  (WSL2 with USB Passthrough)[https://devblogs.microsoft.com/commandline/connecting-usb-devices-to-wsl/] 
install ubuntu on wsl
```bash
wsl --install
wsl --update
wsl --install -d Ubuntu-20.04
```
open vs code and the wsl ubuntu terminal and run the
```bash
./tools/scripts/bootstrap.sh
```


windows
Install the latest release of (usbipd-win)[https://github.com/dorssel/usbipd-win/releases].
* on powersheel 
From an administrator command prompt on Windows, run this command. It will list all the USB devices connected to Windows.
```
usbipd wsl list
```

Select the bus ID of the device you’d like to attach to WSL and run this command. You’ll be prompted by WSL for a password to run a sudo command.
```
usbipd wsl attach --busid <busid> --distribution Ubuntu-20.04
```
(wls2)[https://github.com/dorssel/usbipd-win/wiki/WSL-support]
sudo apt install linux-tools-5.4.0-77-generic hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/5.4.0-77-generic/usbip 20

sudo apt install linux-tools-virtual hwdata
sudo update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20