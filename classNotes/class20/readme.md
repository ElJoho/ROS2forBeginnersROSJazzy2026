# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Class 20

**Section:** Nodes — Part 3: creating your first C++ node. Same structure as the Python node lessons — start minimal; the OOP version and a reusable C++ template come next.

---

## Class 20 — Creating a C++ Node

Goal: write a minimal C++ node, compile it, and run it — same approach as with the Python node (Class 18): start minimal now, OOP + a reusable template come in the next lesson.

### Step 1 — Create the file
Inside `my_cpp_pkg` there's an `include` folder and a `src` folder. C++ files go in `src` (currently empty):
```bash
cd ros2_ws/src/my_cpp_pkg/src/
touch my_first_node.cpp
```
Open VS Code from the workspace's `src` folder as usual (`code .`), then find the file inside `my_cpp_pkg`.

### Step 2 — The include
```cpp
#include "rclcpp/rclcpp.hpp"
```
- The only include needed for this minimal node.
- If autocompletion isn't working, check that the Microsoft "ROS" extension is installed, then restart VS Code.
- **Tip:** save the file right after adding an include — otherwise autocompletion for that library's functionality may not kick in properly yet.

### Step 3 — The `main` function structure
```cpp
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    // node code goes here
    rclcpp::shutdown();
    return 0;
}
```
- A standard C++ `main(argc, argv)` — nothing unusual there.
- `rclcpp::init(argc, argv)` — **always the first thing**, initializes ROS 2 communications (the C++ equivalent of Python's `rclpy.init()`), passed `main`'s own arguments.
- `rclcpp::shutdown()` — **always the last thing**, before returning.
- `main` returns an `int`, so finish with `return 0;`.
- All node-related code goes between `init` and `shutdown`.

### Step 4 — Creating the node (pointers!)
```cpp
auto node = std::make_shared<rclcpp::Node>("cpp_test");
```
- Use `auto` for the type — what you actually get back is a **shared pointer** to a node, not the node "directly."
- **Key ROS 2 + C++ pattern: nodes (and most things in ROS 2 C++) are handled through smart pointers** — here, a shared pointer. Smart pointers handle memory allocation/deallocation automatically, so there's no manual memory management to worry about. (If smart pointers are new to you, a quick outside tutorial helps — but the pattern repeats constantly in ROS 2 C++, so it becomes familiar fast.)
- `std::make_shared<rclcpp::Node>("cpp_test")` creates a shared pointer to an `rclcpp::Node`, named `"cpp_test"`.

### Step 5 — Logging
```cpp
RCLCPP_INFO(node->get_logger(), "Hello World");
```
- Since `node` is a pointer, use `->` (arrow), not `.` (dot), to reach the object it points to — `.` would act on the shared-pointer wrapper itself, `->` acts on the actual `Node` object inside it.
- `RCLCPP_INFO(...)` (all uppercase) is the C++ equivalent of Python's `get_logger().info(...)`: first argument is the logger (`node->get_logger()`), second is the message.
- Don't forget the semicolon.

### Step 6 — Building requires `CMakeLists.txt`
- Unlike Python (interpreted — `chmod +x` and run the file directly), **C++ always has to be compiled** before it can run.
- The build/executable rules live in `CMakeLists.txt` (install the "CMake" extension by twxs in VS Code for syntax highlighting, if not already done).

**What's already there (and a bit of cleanup):**
- The minimum required CMake version, plus some compiler options.
- `find_package(...)` calls for dependencies: `ament_cmake` (present because this is a C++ package) and `rclcpp`.
  - Adding a new dependency means declaring it in `package.xml` **and**, if it's needed to compile something, `find_package()`-ing it here too.
- An `if(BUILD_TESTING) ... endif()` block with default testing boilerplate — not needed right now; safe to remove for a cleaner file.
- `ament_package()` — must stay the **last line** of the file.

**Adding an executable** (after the `find_package()` calls, before `ament_package()`):
```cmake
add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)
```
- `add_executable(<name> <path>)` — pick an executable name (`cpp_node` here); the path is relative to the package (`src/my_first_node.cpp`).
- `ament_target_dependencies(<executable-name> <dependencies...>)` — the ament/ROS 2-specific step that links the dependencies your code actually uses (here, `rclcpp`) to this executable. **Skipping this causes a "package not found" error at compile time**, even though `rclcpp` was already found via `find_package()`.

**Installing the executable** (also before `ament_package()`):
```cmake
install(TARGETS
        cpp_node
        DESTINATION lib/${PROJECT_NAME}
)
```
- `TARGETS` — the executable name(s) to install.
- `DESTINATION lib/${PROJECT_NAME}` — installs into a `lib/` folder for this package, inside the workspace's `install` folder. **Watch out for typos in `${PROJECT_NAME}`** — a very common source of "it just doesn't work" bugs.
- For any future executable from this package: duplicate the `add_executable` + `ament_target_dependencies` pair, and add the new executable's name into this same `install(TARGETS ...)` block.

### Step 7 — Building (and a first C++ build error)
From the **workspace root** (never from inside `src`):
```bash
colcon build --packages-select my_cpp_pkg
```
- Demo: creating the node with no name argument (`std::make_shared<rclcpp::Node>()`) produces a classic C++ build error. Fix by passing a name (e.g. `"cpp_test"`), save, and rebuild.
- **`Finished`** in the build output means success; **`Failed`** means there's a build error to fix.

### Step 8 — Running it
Source the workspace (something new was built):
```bash
source install/setup.bash
```
Then run it from anywhere:
```bash
ros2 run my_cpp_pkg cpp_node
```
(Tab autocompletion works for both the package and executable names.) Output: `Hello World`, with the usual info-log format, timestamp, and the node name (`cpp_test`) shown in the log.

### Three different names, again
| Name | Defined where | Example here |
|---|---|---|
| **File name** | The `.cpp` file itself | `my_first_node.cpp` |
| **Node name** | In the code, via `rclcpp::Node("...")` | `cpp_test` |
| **Executable name** | In `CMakeLists.txt`, via `add_executable(...)`, used with `ros2 run` | `cpp_node` |

Same idea as with the Python node: three genuinely different things, even if they're sometimes given the same name in practice.

### Step 9 — Keeping the node alive with `spin`
```cpp
rclcpp::spin(node);
```
- Place this right before `rclcpp::shutdown()`.
- Same role as Python's `rclpy.spin(node)`: keeps the node alive until `Ctrl+C`, instead of printing once and exiting immediately.
- Pass the shared pointer to the node, as with everything else here.
- After any code change: **build, then source, then run** — same cycle as with the Python node.

### Final code for this lesson

`my_first_node.cpp`
```cpp
#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv){
	rclcpp::init(argc,argv);
	auto node = std::make_shared<rclcpp::Node>("cpp_test");
	RCLCPP_INFO(node->get_logger(), "Hello World");
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
```

`CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.20)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)

install(TARGETS 
        cpp_node
        DESTINATION lib/${PROJECT_NAME}
)

ament_package()
```

### Environment note — ROS 2 Lyrical (and later distros): `ament_target_dependencies` is gone

The `ament_target_dependencies()` line above is exactly what the course teaches (it was recorded on Jazzy), and it still works there. But it has a history worth knowing if you're on a newer distro:

- **Kilted** (the distro right after Jazzy): deprecated it — still worked, just printed a CMake warning at build time.
- **Lyrical** (May 2026) and later: **removed it completely.** Using it produces a hard build error, not a warning:
  ```
  CMake Error at CMakeLists.txt:13 (ament_target_dependencies):
    Unknown CMake command "ament_target_dependencies".
  ```

**How to confirm this is what's going on:**
```bash
find /opt/ros/lyrical -iname "*ament_target_dependencies*"
```
If that comes back empty, the macro genuinely isn't installed on your system — no amount of fixing `find_package` order or clearing `build`/`install`/`log` will help, because the command itself no longer exists.

**The fix — replace the macro with modern CMake's `target_link_libraries`:**
```cmake
# Course version (Jazzy) — fails on Lyrical:
ament_target_dependencies(cpp_node rclcpp)

# Lyrical (and later) — use this instead:
target_link_libraries(cpp_node PUBLIC rclcpp::rclcpp)
```
- Syntax: `target_link_libraries(<executable-name> PUBLIC <package>::<package> ...)` — one `<package>::<package>` per dependency, using that package's double-colon target name.
- Everything else in the file stays exactly the same: both `find_package(...)` lines, `add_executable(...)`, the `install(...)` block, and `ament_package()`.
- **This will come up again** for every new C++ executable later in the course: wherever a lesson adds `ament_target_dependencies(<name> <dep1> <dep2> ...)`, swap it for `target_link_libraries(<name> PUBLIC <dep1>::<dep1> <dep2>::<dep2> ...)`.

**Working `CMakeLists.txt` for this environment (Lyrical):**
```cmake
cmake_minimum_required(VERSION 3.20)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)
target_link_libraries(cpp_node PUBLIC rclcpp::rclcpp)

install(TARGETS 
        cpp_node
        DESTINATION lib/${PROJECT_NAME}
)

ament_package()
```

**Coming up next:** the object-oriented version of this same node, plus the reusable C++ node template — the C++ counterpart to Class 19.
