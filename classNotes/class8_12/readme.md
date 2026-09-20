# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Classes 8–12

**Section:** Installing ROS 2 *(continued)* — programming tools for the course, installing ROS 2 itself, setting up your environment, a first test run, and the section wrap-up. This closes out the Installation section that began in Classes 4–7.

---

## Class 8 — Programming Tools You'll Use in This Course

Now that Ubuntu is installed (dual boot or VM either way), this lesson covers the tools used to program with ROS 2 in the course. You can use whatever you prefer — this is just so the rest of the course makes sense on-screen. If you have no preference of your own, follow these picks.

### Terminal tools
- Basic terminal use is assumed (open it from Activities/apps, or press the Windows/Command key and type "terminal").
- **Terminator** — lets you split one window into multiple terminals.
  - Install:
    ```bash
    sudo apt install terminator
    ```
  - Shortcuts used in the course:
    | Action | Shortcut |
    |---|---|
    | Split horizontally | `Ctrl+Shift+O` |
    | Split again (horizontal or vertical) | `Ctrl+Shift+E` |
    | Zoom into one terminal / back to all | `Ctrl+Shift+X` |
    | Close a terminal | `Ctrl+Shift+W` |
  - More shortcuts: search "Terminator keyboard shortcuts" online.
  - Not required — plain terminal windows/tabs work just as well.

### Writing code — VS Code
- Chosen because it works well for this kind of project and has good ROS support.
- Install via snap:
  ```bash
  sudo snap install code --classic
  ```
- Launch from a terminal with `code`, or from the Applications menu.
- Extensions to install (Extensions panel):
  - **"ROS"** — the Microsoft extension, valid for both ROS 1 and ROS 2; installing it also pulls in Python and C++ language support.
  - **"CMake"** (by twxs) — syntax highlighting for CMake files.
- That's enough to get started; VS Code project setup (autocompletion for libraries, etc.) is covered again later in the course.
- *(Reminder from the earlier tools note: the standalone "ROS" extension has since been deprecated — install "Robot Developer Extensions for ROS 2" by Ranch Hand Robotics LLC instead; see Class 7.)*

### Editing simple files — gedit
- A very basic text editor for quick edits; `nano` or `vim` work just as well if you prefer them.
- Install if needed (usually already present on Ubuntu):
  ```bash
  sudo apt install gedit
  ```

---

## Class 9 — Installing ROS 2 Jazzy on Ubuntu 24.04

Works the same whether you're on a dual boot or a virtual machine.

- Open a terminal on one side and a browser on the other; search **"install ROS 2 Jazzy"** to reach the official installation docs — make sure the page is specifically for **ROS 2 Jazzy**.
- In the binary packages menu, choose **Deb packages** (the recommended option for Ubuntu).

### Step 1 — System setup (locale)
- Check your locale uses UTF-8:
  ```bash
  locale
  ```
- If it doesn't, run the locale-setup commands given on the docs page, then check again with `locale`.

### Step 2 — Add the ROS 2 package sources
- Needed before `sudo apt install` can find any ROS 2 packages.
- The docs page lists five commands to run — starting with enabling the **Universe** repository, then adding the ROS 2 apt repository itself.
- **The official instructions can change over time** — always follow what the docs page currently shows rather than a fixed list.
- Handy tip: select text with the mouse, then middle-click in the terminal to paste it.

### Step 3 — (Optional but recommended) Install development tools
```bash
sudo apt install ros-dev-tools
```

### Step 4 — Update and upgrade
```bash
sudo apt update
sudo apt upgrade
```
- After adding the sources, `sudo apt update` should show a source like `packages.ros.org/ros2` — confirming the ROS 2 sources were added correctly.
- (25 packages needed upgrading in the walkthrough — your number will vary.)

### Step 5 — Install ROS 2 itself: two options
| Option | Package | What you get |
|---|---|---|
| **ROS base** | `ros-jazzy-ros-base` | Bare minimum to run ROS 2, no graphical tools — a good fit for limited hardware (e.g., a Raspberry Pi) |
| **Desktop** | `ros-jazzy-desktop` | Everything in ROS base **plus** graphical tools, demos, and tutorials — **used in this course** |

- The desktop install pulls in a large number of packages (600+ in the walkthrough) since ROS 2 is really a big collection of packages — confirm with "yes" when prompted.
- Install time depends on your internet speed and computer performance (5–10 minutes in the walkthrough).

### Keeping things updated afterward
- Run `sudo apt update && sudo apt upgrade` regularly — ROS 2 packages typically get an update about once a month.
- If a package doesn't get picked up automatically, you can upgrade it by name directly.
- Clean up anything no longer needed:
  ```bash
  sudo apt autoremove
  ```

---

## Class 10 — Setting Up Your ROS 2 Environment (Sourcing)

ROS 2 is installed, but it isn't usable yet until your shell environment is set up.

- Running `ros2` right after installing gives `ros2: command not found` — this doesn't mean it's not installed, just that the environment isn't sourced yet.
- ROS 2 lives under `/opt/ros/`, inside a folder named after the distribution — e.g., `/opt/ros/jazzy/`.
- That folder contains a `setup.bash` script that needs to be **sourced** to make ROS 2 available in the current terminal:
  ```bash
  source /opt/ros/jazzy/setup.bash
  ```
- After sourcing, running `ros2` again shows a proper usage message instead of "command not found" — confirming it's working (it still needs arguments to actually do anything, which is expected at this point).
- This has to be sourced **in every new terminal** — which gets old fast, so it's better to make it automatic.

### Making it permanent via `.bashrc`
- Open `~/.bashrc` (in your home directory) with a text editor:
  ```bash
  gedit ~/.bashrc
  ```
- `.bashrc` is a script that runs automatically every time a new terminal session starts.
- Go to the very end of the file and add:
  ```bash
  source /opt/ros/jazzy/setup.bash
  ```
- Save, close the file, close all open terminals, then open a new one.
- From now on, `ros2` should work immediately in any new terminal — no manual sourcing needed.

---

## Class 11 — Running Your First ROS 2 Program

Goal: confirm ROS 2 is correctly installed and configured, using two existing example programs — no new code yet, that starts in the next section.

Open two terminals side by side.

**Terminal 1 — the talker**
```bash
ros2 run demo_nodes_cpp talker
```
- (Tab autocompletion works for the package name.)
- Produces logs like "Hello World 1", "Hello World 2", and so on.
- An error here usually means the environment wasn't sourced correctly — revisit Class 10.

**Terminal 2 — the listener**
```bash
ros2 run demo_nodes_cpp listener
```
- Produces logs like "I heard: Hello World X," matching the numbers the talker is publishing in the other terminal — proof the two programs are communicating with each other.

**Stopping the programs**
- Press `Ctrl+C` in a terminal to stop that program.
- Stop the talker and the listener will simply stop receiving anything new (nothing is being published anymore); stop the listener the same way.

**What this confirms**
- Successfully starting and stopping both programs means the installation and environment are working — you're ready for the next section.
- If it doesn't work, go back through the installation/environment lessons and check every step.

---

## Class 12 — Section Conclusion (Recap)

ROS 2 is now installed on Ubuntu and the environment is configured. The installation process isn't the most exciting part of the course, but it's a necessary one — congratulations on getting through it.

### Recap — which ROS 2 version to use
- Use the latest LTS version — currently **ROS 2 Jazzy** (released 2024).
- Already using **Humble**? No problem — it's also an LTS release, supported until mid-2027.
- Sometimes it's worth waiting **6 months to a year** before moving to the newest LTS, if packages you need haven't been ported yet — in that case, keep using the previous ("penultimate") LTS a while longer.

### Recap — non-ROS tools used in the course
- IDE / text editor: **VS Code** and **gedit** — feel free to use whatever you're already comfortable with instead.
- Multiple terminals: **Terminator** on Ubuntu — alternatives are plain terminal windows/tabs, or **tmux**.

### One thing to always remember
- Always source your environment before using ROS 2, or you'll get a "command not found" error:
  ```bash
  source /opt/ros/jazzy/setup.bash
  ```
  (Keep this line in your `~/.bashrc`, swapping "jazzy" for whichever distribution you're actually using.)

### What's next
- Fully set up and ready to start writing your own ROS 2 programs.

---

## Quick Recap

| Class | Focus |
|---|---|
| 8 | Programming tools for the course — Terminator, VS Code (+ ROS/CMake extensions), gedit |
| 9 | Installing ROS 2 Jazzy on Ubuntu 24.04 — locale, sources, dev tools, desktop vs. base install |
| 10 | Setting up your environment — sourcing `setup.bash`, making it permanent via `.bashrc` |
| 11 | Running your first ROS 2 program — talker/listener demo to validate the install |
| 12 | Section conclusion — ROS 2 version recap, tools recap, and the "always source your environment" rule |

**Coming up next:** writing your own ROS 2 programs — the next section of the course.
