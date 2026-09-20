# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Classes 13–16

**Section:** Nodes — Part 1: setting up your workspace, then creating your first Python and C++ packages. Writing the actual node code comes next.

---

## Class 13 — Section Intro: Your First ROS 2 Node

- By the end of this section, you'll be able to write and run your own ROS 2 nodes.
- The plan for setting up a new node:
  1. Create a **ROS 2 workspace** in your home directory.
  2. Create a **package** inside that workspace.
  3. Write a **node** inside the package.
  4. Set it up, **compile** it, and **run** it.
- Every lecture in this section is taught **twice** — once in Python, once in C++ — so you can see both the similarities and the differences between a Python ROS 2 program and a C++ one.
- The complete workspace, with all the code for both languages, is downloadable at the end of the section.
- Recommendation: even if you only plan to use one language, watch the lectures for the other one too — seeing the same concept explained a second way (in a different language) helps it stick.

---

## Class 14 — Creating and Setting Up a ROS 2 Workspace

### What is a workspace?
- The place where you write, install, and compile all the code for a ROS 2 application.
- At its core, a workspace is really just a directory.

### Creating it
```bash
cd ~            # make sure you're in your home directory
mkdir ros2_ws   # create the workspace
cd ros2_ws
mkdir src       # create the "source" directory
```
- Naming is up to you — an app named "ABC" might use `abc_ws`; `ros2_ws` is a common, generic choice to start with.
- That's the whole initial setup: a folder, with a `src` subfolder. **All the code you write for the course goes inside `src`.**

### Building the workspace
- Any time you install new nodes later on, you'll need to (re)build the workspace.
- Always build from the **workspace root** (`ros2_ws`) — never from inside `src`.
  ```bash
  colcon build
  ```
- **Colcon** is ROS 2's build tool. With no packages yet, it finishes almost instantly ("0 packages to build").
- After building, three new folders appear next to `src`: **`build`**, **`install`**, and **`log`** — generated automatically.
- If `colcon` isn't recognized, make sure `ros-dev-tools` is installed: `sudo apt install ros-dev-tools` (from the installation section).

### Sourcing the workspace
- Inside `install/` you'll find `setup.bash` and `local_setup.bash`, among other files:
  - Same idea as `/opt/ros/<distro>/setup.bash` — this `setup.bash` needs to be **sourced** to get access to *this workspace's* functionality.
  - `local_setup.bash` sources just this workspace; `setup.bash` sources both the global ROS 2 install **and** this workspace — the course sticks with `setup.bash` for simplicity.
  ```bash
  source install/setup.bash
  ```

### Making it permanent via `.bashrc`
- Manually sourcing every terminal gets old fast — add it to `~/.bashrc`:
  ```bash
  gedit ~/.bashrc
  ```
- After the existing line that sources the global ROS 2 installation, add:
  ```bash
  source ~/ros2_ws/install/setup.bash
  ```
- **Order matters** — always source the global ROS 2 install *first*, then the workspace.
- Save, close, open a new terminal — both ROS 2 and the workspace are now sourced automatically. Ready to create packages.

### Example terminal session
```
$ mkdir ros2_ws
$ cd ros2_ws/
$ mkdir src
$ ls -a
.  ..  src
$ colcon build
Summary: 0 packages finished [0.12s]
$ ls -a
.  ..  build  install  log  src
$ ls install/
COLCON_IGNORE  local_setup.bash  local_setup.sh  local_setup.zsh  ...
setup.bash     setup.sh          setup.zsh
$ source install/setup.bash
```

---

## Class 15 — Creating a Python Package

### What is a package?
- To create a node, you first need a package.
- Packages split an application into independent, reusable units — e.g., one package for a camera, another for a robot's wheels, another for motion planning.
- In ROS 2, **Python and C++ packages have completely different internal architectures.**

### Creating the package
- Packages live **inside `ros2_ws/src`** — make sure you're in that folder first.
  ```bash
  ros2 pkg create my_py_pkg --build-type ament_python --dependencies rclpy
  ```
  - **Name** — `my_py_pkg` here (e.g., a temperature-monitoring package might be `temperature_sensor`); use underscores between words.
  - **`--build-type ament_python`** — **Ament** is ROS 2's *build system* (Colcon is the *build tool*); `ament_python` marks this as a Python package.
  - **`--dependencies rclpy`** — **`rclpy`** is the Python client library for ROS 2, needed to write Python nodes. More dependencies can be added later directly in the package files.
  - A license warning appears in the output — safe to ignore unless you plan to publish the package publicly (e.g. on GitHub) under an open-source license.

### What gets created
- `my_py_pkg/my_py_pkg/` — a subfolder with the **same name as the package**, containing an empty `__init__.py`. **This is where your Python code goes.**
- `resource/` and `test/` folders — not important for now.
- **`package.xml`** — mandatory for every ROS 2 package. Holds name, version, description, maintainer email, license, build type (`ament_python`), and one `<depend>` tag per dependency (here, `rclpy`) — add one more `<depend>` line per extra dependency.
- **`setup.py`** and **`setup.cfg`** — used later, when installing nodes.

### Opening it in VS Code
- Always open VS Code **from the `src` folder** of the workspace:
  ```bash
  code .
  ```
- Doing this consistently avoids autocompletion problems (VS Code can fail to resolve includes/imports if opened from the wrong folder).

### Building it
- From the **workspace root** (`ros2_ws`, not `src`):
  ```bash
  colcon build
  ```
- To build just one package (handy once you have many):
  ```bash
  colcon build --packages-select my_py_pkg
  ```
- The package is now ready to host a Python node.

### Example terminal session
```
$ cd src/
$ ros2 pkg create my_py_pkg --build-type ament_python --dependencies rclpy
going to create a new package
package name: my_py_pkg
build type: ament_python
dependencies: ['rclpy']
creating folder ./my_py_pkg
creating ./my_py_pkg/package.xml
creating folder ./my_py_pkg/my_py_pkg
creating ./my_py_pkg/setup.py
creating ./my_py_pkg/setup.cfg
creating folder ./my_py_pkg/resource
creating ./my_py_pkg/my_py_pkg/__init__.py
creating folder ./my_py_pkg/test
[WARNING]: Unknown license 'TODO: License declaration' — no LICENSE file created (safe to ignore for now).
$ cd ..
$ colcon build --packages-select my_py_pkg
Starting >>> my_py_pkg
Finished <<< my_py_pkg [1.44s]
Summary: 1 package finished [1.58s]
```

---

## Class 16 — Creating a C++ Package

Builds on Class 15 — watch that one first if you haven't. Same starting point: inside `ros2_ws/src`.

### Creating the package
```bash
ros2 pkg create my_cpp_pkg --build-type ament_cmake --dependencies rclcpp
```
- **`--build-type ament_cmake`** — marks this as a **C++** package (vs. `ament_python` for Python).
- **`--dependencies rclcpp`** — **`rclcpp`** is the C++ client library for ROS 2 — the C++ equivalent of `rclpy`. More dependencies can be added later.
- Same license warning as before — same reasoning, safe to ignore for now.

### What gets created (a very different layout from Python)
- **`include/my_cpp_pkg/`** — header files (`.hpp` / `.h`).
- **`src/`** — implementation files (`.cpp`).
- **`CMakeLists.txt`** — the build rules for the package (covered in more depth once the first node is written). This is a fairly standard C++ project layout, just placed inside a ROS 2 package.
- **`package.xml`** — same role as in the Python package, and the one file every ROS 2 package must have: name, version, description, license info, build type (`ament_cmake`), and a `<depend>` tag for `rclcpp`.

### Opening and building it
- Open with `code .` from the `src` folder, same as before.
- **Important — always build from the workspace root, never from `src`.**
  - Running `colcon build` by accident inside `src/` creates stray `build/`, `install/`, and `log/` folders *there too*, on top of the correct ones already in the workspace root — a setup that causes confusing errors later.
  - Fix: remove the stray folders (from inside `src/`, only if you built there by mistake):
    ```bash
    rm -r build install log
    ```
  - Then, from the workspace root:
    ```bash
    colcon build
    # or, to build just this one:
    colcon build --packages-select my_cpp_pkg
    ```
- You now have both a Python package and a C++ package, ready to hold nodes.

### Example terminal session
```
$ cd src/
$ ros2 pkg create my_cpp_pkg --build-type ament_cmake --dependencies rclcpp
going to create a new package
package name: my_cpp_pkg
build type: ament_cmake
dependencies: ['rclcpp']
creating folder ./my_cpp_pkg
creating ./my_cpp_pkg/package.xml
creating source and include folder
creating folder ./my_cpp_pkg/src
creating folder ./my_cpp_pkg/include/my_cpp_pkg
creating ./my_cpp_pkg/CMakeLists.txt
[WARNING]: Unknown license 'TODO: License declaration' — no LICENSE file created (safe to ignore for now).
$ ls
my_cpp_pkg  my_py_pkg
$ cd ..
$ colcon build --packages-select my_cpp_pkg
Starting >>> my_cpp_pkg
Finished <<< my_cpp_pkg [1.28s]
Summary: 1 package finished [1.41s]
```

---

## Quick Recap

| Class | Focus |
|---|---|
| 13 | Section intro — the plan for your first node: workspace → package → node → setup/compile/run, taught in both Python and C++ |
| 14 | Creating and setting up a ROS 2 workspace — `mkdir` + `src`, `colcon build`, sourcing `install/setup.bash` via `.bashrc` |
| 15 | Creating a Python package — `ros2 pkg create ... --build-type ament_python`, package.xml, building with Colcon |
| 16 | Creating a C++ package — `ros2 pkg create ... --build-type ament_cmake`, its different folder layout, and avoiding the "built in the wrong folder" mistake |

**Coming up next:** what a ROS 2 node actually is — and creating your first one.
