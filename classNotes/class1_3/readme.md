# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Classes 1–3

> Notes summarizing the welcome lecture, course-structure guide, and the "why/when/what is ROS 2" lecture.

**Instructor:** Edward — software engineer and entrepreneur; built a six-axis robotic arm with ROS from scratch and has taught ROS 2 to tens of thousands of students.

---

## Class 1 — Welcome & Course Overview

### The promise of the course
- Goal: learn ROS 2 from scratch and master its core functionality — without the usual steep learning curve — in order to build powerful, scalable robotics applications.
- Step-by-step and beginner-friendly, with heavy emphasis on practice.
- Covers both the **how** and the **why** of ROS 2 — understanding *why* is presented as the more important half.

### What you will learn
- How to install and set up ROS 2 on **Ubuntu**.
- How to create, build, and use the core building blocks: **Nodes, Topics, Services, Messages, Parameters, Launch files**, and more.
- The most useful **ROS 2 tools** for saving development time.
- **Best practices** for building not just working, but *great* and scalable robotics applications.

### How the practice works
- Lots of hands-on activities: the instructor writes code step by step, explains each part, and sets challenges.
- **All code is shown in both Python and C++.**
- Final project: a complete ROS 2 application built around the **Turtlesim** simulator, pulling together everything covered in the course.

### Prerequisites
- Basic comfort with a terminal.
- Basic programming knowledge.

---

## Class 2 — How to Get the Most Out of This Course

### Overall course structure
1. **Setup** — install ROS 2 and supporting tools, and configure your environment so you're ready to code.
2. **Core concept sections** — one ROS 2 functionality per section, each following the same pattern:
   1. The concept is explained with a real-life analogy.
   2. You write a program using the concept — once in Python, once in C++.
   3. You learn the ROS 2 tools used to work with that concept and the code you just wrote.
   4. You complete a practice **activity** (the goal is given first; the solution is a separate lecture).
   5. A **conclusion** lecture recaps the section and gives you that section's code to download.
3. **Final project** — built on top of an existing ROS 2 package, **Turtlesim**: apply everything learned, and practice working with a package written by someone else.
4. **Wrap-up** — recommendations for what to learn next.

### How to actually get the most out of it
- **Code along, don't just watch.** Pause the video and write the code yourself as it's being written.
- **Attempt every activity solo first.** Each one gives the goal in one lecture and the solution in a separate lecture — do it yourself before watching the solution, then compare your code or see what you missed.
- **Experiment beyond the lessons.** Go further than what's taught if something makes you curious.
- **Re-watch the concept explanation** after finishing a section's practice — it tends to click better the second time.

---

## Class 3 — Why, When, and What is ROS 2?

### ROS 2 vs. ROS 1
- ROS 2 is the **successor to ROS 1**: same goals and core concepts, improved and with more functionality.
- The course (and these notes) use "ROS 2" and "ROS" interchangeably.

### Why does ROS 2 exist?
- The lecture opens with three different robots, all of which are or can be powered by ROS 2 — illustrating how broadly it applies.
- **ROS** = *Robot Operating System*: something between a **middleware** and a **framework**, built specifically for robotics.
- Its purpose: give developers a **standard** they can reuse across different robots.
- Master the core functionality once, and setting up software for a *new* robot becomes fast — skills carry over from robot to robot.
- Guiding philosophy: **"Don't reinvent the wheel."**
  - A very common failure mode in robotics is rebuilding software that already exists, instead of spending time on genuinely new value.
  - ROS 2 gives you a solid software base so you can focus on high-level functionality and use cases, rather than low-level technical plumbing.

### When should you use ROS 2?
- A common trajectory: starting with an Arduino board or custom code, then adding more sensors, actuators, and controllers — complexity grows until everything becomes tangled and every new addition is a headache.
- **Use ROS 2 when:**
  - your application needs a lot of communication between its subprograms, **or**
  - it needs functionality beyond a very simple use case.
- *Probably not needed:* a robot that just opens a door with a servo motor when it detects movement.
- *A good fit:* a mobile robot controlled with a GPS and a camera.

### What is ROS 2, really? (two big ideas)

**1. Reusable code blocks + communication tools**
- ROS 2 lets you split an application into independent, reusable blocks called **nodes**.
- Example — a mobile robot might have separate nodes for the camera, the navigation algorithm, the hardware driver, and the joystick.
- These nodes communicate with each other through ROS 2's communication tools.

**2. Plug-and-play tools and libraries**
- ROS 2 ships with many tools and libraries that save large amounts of development time and help avoid reinventing the wheel.
- Example: computing a trajectory that moves a robot smoothly, avoids obstacles, and coordinates with other robots at the same time would normally take roughly 2 years of studying math, path planning, and algorithms — with ROS 2, it can be closer to **2 days** of installing and learning an existing library.

### Other defining traits
- **Language-agnostic:** different parts of an application can be written in different languages (e.g., Python and C++) because the communication layer doesn't depend on any one language. This course teaches both.
- **Open source**, with an active, growing community — easy to get help, share your work, and contribute.

### Key takeaway
- The big picture of ROS 2 is genuinely hard to grasp all at once — that's expected, not a sign of falling behind.
- It gets easier with practice, and it becomes a major asset for future robotics projects.

---

## Quick Recap

| Class | Focus |
|---|---|
| 1 | Course welcome, instructor's background, what you'll learn, prerequisites |
| 2 | How the course is structured, and how to study it effectively |
| 3 | The why / when / what of ROS 2 — a standard that avoids "reinventing the wheel," nodes + communication tools, plug-and-play libraries, language-agnostic, open source |

**Coming up next:** installing ROS 2 on Ubuntu, then one core concept per section — Nodes, Topics, Services, Messages, Parameters, and Launch files — each with a Python and C++ walkthrough, tool demos, and a hands-on activity.
