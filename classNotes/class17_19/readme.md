# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Classes 17–19

**Section:** Nodes — Part 2: what a node actually is, writing and installing your first Python node, then rewriting it with OOP and adding a timer.

---

## Class 17 — What Is a ROS 2 Node?

### Basic definition
- A node is a subpart of an application, coded in a language like Python or C++.
- A node should do **one thing** — a single, well-defined purpose.
- An application is made up of many nodes, grouped into packages, which communicate with each other.

### Real-life example: three packages, several nodes
An empty package does nothing on its own — nodes are what actually fill it with behavior.

**Camera package**
- A **driver** node — programs the camera and grabs frames from it.
- An **image processing** node — takes those frames and processes them.
- Each node can be launched separately (e.g., driver first, then image processing), and they communicate via ROS 2's communication tools (covered later in the course).
- Design judgment call: it isn't always obvious whether related functionality belongs in the *same* package. Here, image processing is treated as specific to this camera (and shares dependencies with the driver) — but it could just as easily be split into its own generic "image processing" package reusable across different cameras. That's a design choice, not a fixed rule.

**Motion planning package**
- A **motion planning** node — computes the robot's movement/trajectories.
- A **path correction** node — adjusts the plan based on external factors.
- Cross-package communication: the camera package's image-processing node sends its analysis of the environment to the path-correction node; path correction then notifies the motion-planning node.

**Hardware control package**
- A **driver** node — runs the motor control loop, using position feedback from the motor encoders for precise control.
- A **state publisher** node — publishes that feedback / hardware status.
- Motion planning sends computed trajectories to the hardware driver; hardware status is published back out, and both motion planning and path correction subscribe to it.

*(This example gets fairly involved — no need to absorb it all immediately. Worth revisiting once you've made more progress in the course.)*

### Node definition, restated
- A node is a subprogram responsible for **one thing** — similar to how a class in object-oriented programming should serve a single purpose (two responsibilities → two classes).
- Nodes are combined into a **graph** and communicate using topics, services, parameters, etc. (covered in upcoming sections).

### Characteristics & benefits of nodes
1. **Reduced code complexity** — correctly splitting an application into packages and nodes makes it far easier to scale. One giant block of code eventually costs more time to fix than it does to extend.
2. **Fault tolerance** — nodes run in separate processes and communicate only through ROS 2, so they aren't directly linked. If one node crashes, it doesn't take the others down with it.
   - Great for debugging.
   - Great for safety: a well-tested, critical hardware node can keep running even if an experimental node you're testing alongside it crashes.
3. **Language-agnostic** — one node can be Python, another C++, and they communicate without any issue. (Python and C++ are the two most common ROS languages; other languages are possible with additional libraries.) Useful for writing most of an app in Python while putting performance-critical nodes in C++.
4. **Naming rule** — two nodes can't share the same name. Running multiple instances of the same node requires renaming them or placing them in different namespaces (covered later).

**Coming up:** creating nodes in both Python and C++, using them via command-line tools, and making them communicate.

---

## Class 18 — Creating Your First Python Node

Goal: write a minimal node, then install and run it. (An improved, object-oriented version — reusable as a template for future nodes — comes in the next lesson.)

### Step 1 — Create the file
Navigate to the inner package folder (the one sharing the package's name) and create the file:
```bash
cd ros2_ws/src/my_py_pkg/my_py_pkg/
touch my_first_node.py
```
Open VS Code from the workspace's `src` folder as usual: `code .`

### Step 2 — Write the minimal node
```python
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

def main(args=None):
    rclpy.init(args=args)
    node = Node("py_test")
    node.get_logger().info("Hello world")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
```
Breaking it down:
- `#!/usr/bin/env python3` — the interpreter line; tells the OS to run this file with Python 3 when executed directly.
- `import rclpy` — the ROS 2 client library for Python, needed in every Python node.
- `from rclpy.node import Node` — imports the `Node` class. *(If autocompletion for these isn't showing in VS Code, double-check the Microsoft "ROS" extension is properly installed, and try restarting VS Code.)*
- Inside `main()`:
  - `rclpy.init(args=args)` — **always the first line** of a ROS 2 program; initializes ROS 2 communications.
  - `node = Node("py_test")` — creates a node named `"py_test"`. Note: **the node lives inside the file — the Python file itself is not the node.**
  - `node.get_logger().info("Hello world")` — logs a message via the node's built-in logger.
  - `rclpy.spin(node)` — **keeps the node alive** (more on `spin` later) until interrupted with `Ctrl+C`. Without this, the node initializes, logs once, and exits immediately.
  - `rclpy.shutdown()` — **always the last line**; shuts everything down.
- `if __name__ == "__main__": main()` — lets the file be run directly and call `main()` automatically.
- **Always save the file** — a very common early mistake is forgetting to. (VS Code shows a dot on an unsaved tab, which turns into a × once saved.)

### Step 3 — Run it directly
```bash
python3 my_first_node.py
# or make it executable first, then run it directly:
chmod +x my_first_node.py
./my_first_node.py
```
- Output looks like: `[INFO] [<timestamp>] [py_test]: Hello world`
- `py_test` in the log is the **node name**, exactly as given in `Node("py_test")`.
- Without `rclpy.spin(node)`, the program logs once and exits every time; with it, the node "hangs" (stays alive) until `Ctrl+C`.

### Step 4 — Install it as an executable
Running the file directly works, but the real goal is to **install** it so it can be started with the `ros2` command from anywhere (and, later, from launch files).

Edit `setup.py` inside the package, in `entry_points` → `console_scripts`:
```python
entry_points={
    'console_scripts': [
        "py_node = my_py_pkg.my_first_node:main"
    ],
},
```
- `py_node` — the **executable name**, your choice.
- `my_py_pkg.my_first_node` — `<package_name>.<file_name_without_.py>`.
- `:main` — the function to call when the executable runs.
- More executables can be added the same way, comma-separated, one per line.

Save the file, then — from the **workspace root** (never from inside `src`) — build just this package:
```bash
colcon build --packages-select my_py_pkg
```
This generates the `py_node` executable inside the `install` folder; you don't need to go find it manually — the `ros2` CLI handles that.

### Step 5 — Run the installed node with `ros2 run`
Something new was installed, so re-source your workspace first (or just open a new terminal, since `.bashrc` already sources it automatically):
```bash
source ~/.bashrc
```
Then run it from anywhere:
```bash
ros2 run my_py_pkg py_node
```
(Both the package name and the executable name support Tab autocompletion.) Stop it with `Ctrl+C` — shown as a harmless "keyboard interrupt."

### Three different names — don't mix them up
| Name | Defined where | Example here |
|---|---|---|
| **File name** | The `.py` file itself | `my_first_node.py` |
| **Node name** | In the code, via `Node("...")` | `py_test` |
| **Executable name** | In `setup.py`'s `console_scripts`, used with `ros2 run` | `py_node` |

These are three genuinely different things, even though in practice they're often given the *same* name for clarity (e.g., a `temperature_sensor.py` file might define a `temperature_sensor` node with a `temperature_sensor` executable). They were deliberately kept different here just to make the distinction clear.

### Progress check
At this point you can: create a node file, write a basic node, run it directly, install it, and run it via `ros2 run`.

### Example terminal session
```
$ cd my_py_pkg/          # into the inner package folder
$ ls
__init__.py
$ touch my_first_node.py
$ cd ../..                # back to src/
$ code .
$ cd my_py_pkg/my_py_pkg/
$ chmod +x my_first_node.py
$ ./my_first_node.py
[INFO] [1733225261.176587423] [py_test]: Hello world
```

---

## Class 19 — Rewriting the Node with OOP, and Adding a Timer

### Why object-oriented programming (OOP)?
- Makes nodes more scalable.
- The **recommended way** to write ROS 2 code, per the official guidelines — virtually all real-world ROS 2 code uses OOP.
- Once built, this becomes a **reusable template** for every node you'll create going forward.

### Turning the node into a class
```python
class MyNode(Node):

    def __init__(self):
        super().__init__("py_test")
```
- Name the class for what it does — `MyNode` here, but e.g. `TemperatureSensorNode` for a temperature sensor.
- **Inherit from `Node`** — this is what gives the class access to all the ROS 2 node functionality from `rclpy`.
- `__init__` is the constructor. Its first line must call the **parent constructor**, `super().__init__("py_test")`, passing the node's name — this is what actually initializes the node.
- That's the minimum code for a class-based node.

### Logging inside the class
- Same idea as before, but now via `self` (since the class inherits from `Node`):
  ```python
  self.get_logger().info("Hello world")
  ```

### Updating `main()`
- Instead of `Node("py_test")`, create an instance of your own class: `node = MyNode()` — no arguments needed, since the name is now set inside the class itself.
- The rest of `main()` is unchanged: initialize ROS 2 → create the node → `rclpy.spin(node)` → shut down.
- The node now gets all its ROS 2 functionality through `self.` inside your own class, rather than directly through a plain `Node` instance.

### Build → source → run (every time)
```bash
colcon build --packages-select my_py_pkg   # from the workspace root
source install/setup.bash                   # or `source ~/.bashrc`, or a new terminal
ros2 run my_py_pkg py_node
```
- **The cycle to remember for any change you make: build, then source, then run — always, in that order.**
- Result should be identical to before, confirming the refactor didn't break anything.

### The reusable node template
- This class-based structure — roughly 20 lines — is the template to reuse for **any** future node.
- To reuse it: keep the structure, just change the node name (and, usually, the class name) to match the new node.

### Adding a Timer
- Motivation: logging "Hello world" once isn't very interesting. What if you want to repeat an action for as long as the node is alive — e.g., reading a sensor at some frequency (10 Hz, say, for a temperature sensor)?
- A **timer** is one of the most important ROS 2 functionalities: "call this function every X amount of time." You'll use timers constantly throughout the course.

**Steps:**
1. Add a method for the repeated work, e.g.:
   ```python
   def timer_callback(self):
       self.get_logger().info("Hello")
   ```
2. In the constructor, create the timer:
   ```python
   self.create_timer(1.0, self.timer_callback)
   ```
   - First argument — the period in seconds (a float): `1.0` = once per second.
   - Second argument — the callback function **itself**, passed **without parentheses** (`self.timer_callback`, not `self.timer_callback()`). Parentheses would call the function immediately; leaving them off just registers a *reference* to it, to be "called back" later — hence "callback."

**How execution actually flows**
- `main()` initializes ROS 2, then creates the node — running the constructor: parent `__init__`, the "Hello world" log, then the timer is *created* (not yet triggered).
- `rclpy.spin(node)` keeps the node alive and lets it process callbacks.
- Because the node is spinning, the timer fires `timer_callback` every second, for as long as the node runs.
- Rebuild → source → run again: now you see "Hello world" once, then "Hello" printed every second until `Ctrl+C`.

### A small addition — and a lesson about build-time vs. run-time errors
- Add a counter as a class attribute (a trailing underscore `_` is this course's naming convention for class attributes):
  ```python
  self.counter_ = 0
  ```
- In `timer_callback`, log it and increment it:
  ```python
  self.get_logger().info("Hello " + str(self.counter_))
  self.counter_ += 1
  ```
- **Demo — a syntax error:** forgetting the `+` when concatenating the strings causes a syntax error.
  - This kind of error shows up **at build time** — `colcon build` fails with an explicit error, so it's caught before you even try to run.
  - Not every error is caught this early, though: an *uncaught exception* raised while the node is running will still let the build succeed — the failure only shows up later, when you actually run the node. Worth keeping in mind.
- Fix the typo, rebuild, source, run again → output is now "Hello 0", "Hello 1", "Hello 2", … once per second.

### Final code for this lesson
```python
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node


class MyNode(Node):

    def __init__(self):
        super().__init__("py_test")
        self.counter_ = 0
        self.get_logger().info("Hello world")
        self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info("Hello " + str(self.counter_))
        self.counter_ += 1

def main(args=None):
    rclpy.init(args=args)
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
```

### Wrap-up
- You now know the correct, OOP-based way to build a ROS 2 node with a class.
- You've also learned about **timers** — a functionality you'll come back to again and again in this course.

---

## Quick Recap

| Class | Focus |
|---|---|
| 17 | What is a ROS 2 node? — single-purpose subprograms, a real-life multi-package example, and the key benefits: reduced complexity, fault tolerance, language-agnostic, unique names |
| 18 | Creating your first Python node — a minimal `rclpy` node, running it directly, installing it via `setup.py`, and running it with `ros2 run` |
| 19 | Rewriting the node with OOP (a reusable class-based template), plus adding a timer to run code repeatedly — and a first look at build-time vs. run-time errors |