# Firex
> Fast and minimalist web framework

[![License: GPL v3](https://img.shields.io/badge/license-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

## Contents
- [Building and Installation](#building-and-installation)
    - [Dependencies](#dependencies)
    - [Building the project](#building-the-project)
    - [Running demo](#running-demo)
    - [Installing](#installing)
- [License](#license)

## Building and Installation

### Dependencies
- C compiler (gcc, clang, etc...)
- cmake (>= 3.20)

These packages can usually be installed through your distributions package manager.

### Building the project
To build the project, we first need to create a separate build directory:
```
mkdir build
```

Now that we've created our build directory (assuming it's created in the project root), we can `cd` into it and run `cmake` and pass the parent directory path to it, which is where the `CMakeLists.txt` file is located:
```
cd build
cmake ..
```

Once `cmake` is done generating makefiles, we can build the library by running `make` inside our build directory:
```
make
```

### Running demo
```
./demo
```

### Installing
To install the framework run:
```
sudo make install
```
By default the libraries and headers will be installed in `/usr/local/lib` and `/usr/local/include` directories.

## License
Firex is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
For more details, see [LICENSE](https://github.com/vstan02/firex/blob/master/LICENSE) file.
