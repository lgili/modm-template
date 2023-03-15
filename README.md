# Example to show how to extend modm library to use my own boards and libraries


## Examples

A few examples are provided in the `example` folder:
* Blink - a standard blink led example
* ADC - run and print de values read on the adc

You can use python to get values from uart:
```
python -m serial /dev/ttyACM0  115200
```

You can run this examples on two differents boars `["board-a","board-b"]`.
To change the board go to `example/lbuild.xml` and change the dev_board name `<option name="mcal:dev_board">board-a</option>`

```

# Compile with SCons 
cd mpu_blink
lbuild build
scons build
scons program
```


```
# Compile with SCons or Makefile
cd mpu_adc
lbuild build
scons
make
```
