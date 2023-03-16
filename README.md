# Example to show how to extend modm library to use my own boards and libraries
This repo use [modm](https://github.com/modm-io/modm) and [lbuild](https://github.com/modm-io/lbuild). You should read more about this two library, if you want to use this repo.   

## Examples

A few examples are provided in the `example` folder:
* Blink - a standard blink led example
* ADC - run and print de values read

Run python to get values from uart:
```
python -m serial /dev/ttyACM0  115200
```

Is possible to run this two examples on two differents boards `["board-a","board-b"]`.
To change the board go to `example/lbuild.xml` and change the extends method `<extends>mcal:board-b</extends>` to use the board wanted.

```

# Compile with SCons 
cd blink
lbuild build
scons build
scons program
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