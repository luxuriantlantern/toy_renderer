# toy_renderer

A toy render engine that can render 3D models using a json file.

### .json file's format

```json
{
  "resolution": [2560, 1920],
  "camera": {
    "type": "perspective",
    "fx": 3092,
    "fy":2319,
    "cx": 1280,
    "cy": 1280
  },
  "objects": [
    {
      "file": "../assets/cube.obj",
      "position": [-2, -2, -2],
      "scale": [1, 1, 1],
      "rotation": {
        "type": "euler_xyz",
        "data": [30, 30, 30]
      }
    },
    {
      "file": "../assets/cube2.ply",
      "position": [0, 0, 0],
      "scale": [0.5, 0.5, 0.5],
      "rotation": {
        "type": "quaternion",
        "data": [0, 0, 0, 1]
      }
    }
  ]
}
```

### Clone

This repository contains submodules, so please clone it with:

```bash

# https
git clone https://github.com/luxuriantlantern/toy_renderer.git --recursive
cd toy_renderer

# ssh
git clone git@github.com:luxuriantlantern/toy_renderer.git --recursive
cd toy_renderer
```

### Build

```bash
mkdir build
cd build
cmake ..
make -j
```

### Usage

Using wasd to move up, left, down, right and jk to move forward and backward.

You can also use the mouse to move and rotate the camera.

You need to change the path to the .json file in the main.cpp file right now.


### TODO

Further complete the render engine and imgui.
