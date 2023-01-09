# Muju

-----

A framework to develop mult-board firmware for embedded systems.

**Table of Contents**

- [How to use](#How-to-use)
- [License](#license)

## How to use

This repository can be used in two ways

1. Putting the project to be developed in a folder within it and setting the `PROJECT ` variable in the `makefile` root to point to this folder. The project folder can have different structures as needed

     1. A single `.c` file located in the main project folder (as in the *helloworld* example),
     2. Several `.h` and `.c` files organized in `inc` and `src` folders respectively, both located inside the main project folder

2. Creating the project in a separate folder of this repository. In this case, in the root folder of the project there must be a `makefile` file with the following structure

```makefile
MODULES := # List of module folders used in project
BOARD ?= # Name of target board to compile project
MUJU ?= # Absolute or relative tath to folder with muju framework

include $(MUJU)/module/base/makefile
```

## License

This template is distributed under the terms of the [MIT](https://spdx.org/licenses/MIT.html) license.
