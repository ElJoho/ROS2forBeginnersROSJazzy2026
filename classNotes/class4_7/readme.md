# ROS 2 for Beginners — ROS Jazzy (2026)
### Class Notes — Classes 4–7

**Section:** Installing ROS 2 — choosing your distribution, choosing your OS, and setting up Ubuntu.

---

## Class 4 — Choosing Your ROS 2 Distribution

### Finding the list of distributions
- Before installing ROS 2, check the official list of distributions (search "ROS 2 distributions" in any browser to find the official documentation page).
- On that page, **supported distributions are shown in green**; unsupported ones appear in gray/white.
- A new distribution is released every year on **May 23rd** (consistent since 2021).
- Distributions are named in **alphabetical order** — after the initial Alpha/Beta releases the sequence runs A, B, C, D, E, F… and the current one is **J — Jazzy**. The next one will start with **K**, then **L**, and so on.
- Each distribution technically has two names, but in practice only the short one is used day to day (e.g., just "Jazzy").

### Two things to always check for a distribution
1. **EOL (End Of Life) date**
   - The date after which the distribution is no longer supported.
   - It will still *work* after EOL — it just won't get new updates. Best practice: avoid picking an already-EOL'd distribution.
2. **LTS (Long Term Support) status**
   - Distributions alternate every year between an **LTS** and a **non-LTS** release.
   - **LTS** = supported for **5 years**, generally more stable.
     - *Humble* was the first ROS 2 LTS: May 2022 – May 2027.
     - *Jazzy*: 2024 – 2029.
   - **Non-LTS** = supported for only **~1.5 years**.
     - Example: *Iron* — May 2023 – November 2024.

### Which one should you pick?
- **Recommendation: use the latest LTS version**, as long as it's been out for a few months (time to stabilize and complete its core packages).
- **This course uses ROS 2 Jazzy.**
- If you already have ROS 2 projects when a new LTS comes out: test it, but expect some things won't be ready immediately — a reasonable rule of thumb is to wait **3–6 months** before porting existing code to the new LTS.
- **Avoid non-LTS versions** (e.g., Galactic, Iron) for learning or for real products — they're mainly useful for trying the newest tools/features early, tend to be less stable, and only last 1.5 years.
- Bottom line: for stability, or for an actual product, **stick to LTS releases only**.

---

## Class 5 — Choosing Your Operating System

### Matching an OS to your ROS 2 distribution
- Each distribution needs a specific OS version — check this on its page under **"Supported platforms."**
- **ROS 2 Jazzy → requires Ubuntu 24.04.** (For comparison, the older LTS *Humble* required Ubuntu 22.04 — a different ROS 2 version means a different required Ubuntu version.)

### Which OS to use
- ROS 2 mainly supports three operating systems: **Ubuntu, macOS, and Windows.**
- This course uses **Ubuntu only** — the OS you'll have the fewest setup/tooling problems with.
- Recommendation for beginners: **use Ubuntu.**
  - Windows can work for some people, but tends to cause more issues.
  - macOS is now **Tier 3** support (no longer Tier 1) — not something to rely on.
- Already have Ubuntu 24.04 installed? You can skip straight to the next lesson.

### If you don't have Ubuntu 24.04 yet: two options
1. **Install natively via dual boot** — the best overall option; lets you follow the entire course and every project without limitation.
2. **Use a virtual machine (VM)** — a good fallback if you can't install an OS natively (e.g., a work laptop without admin rights). Enough to learn the ROS 2 basics and complete the course.
- Basic Linux knowledge is assumed as a course prerequisite — you've likely installed Ubuntu (or similar) before.
- If not, plenty of tutorials exist online for installing Ubuntu as a dual boot (steps vary per computer) — recommended to do this before continuing.
- Stuck, or can't install a dual boot? The next class walks through setting up a **virtual machine with Ubuntu 24.04** instead — enough to get started and finish the course.

---

## Class 6 — Installing Ubuntu in a Virtual Machine (VirtualBox)

### 1. Download what you need
- **Ubuntu 24.04 ISO** — search "Ubuntu 24.04 download," go to the official Ubuntu page, and download the **desktop** image. (A trailing version number like ".1" doesn't matter, just make sure it says 24.04. If the page doesn't show 24.04, go to `releases.ubuntu.com` and pick it manually.) Skip any account sign-up prompt.
- **VirtualBox** — go to `virtualbox.org`, click download, and choose your **current/host OS** (e.g., Windows) to get the right installer.
- Together, both downloads total close to **6 GB** — make sure you have a decent internet connection.

### 2. Install VirtualBox
- Run the installer, allow the permissions pop-up, click Next through the menu, accept the license terms, choose an install location (default is fine), accept any missing-dependency prompts, Install, then Finish.

### 3. Create the virtual machine
- In VirtualBox, click **New**.
- Give it a recognizable name (e.g., "Ubuntu 24.04 – ROS2 course").
- Keep the default VM storage folder, or change it if you prefer.
- Point it to the Ubuntu ISO you downloaded (typing "ubuntu" in the name field usually auto-detects **Type: Linux / Version: Ubuntu (64-bit)** — double-check this is correct).
- **Skip "unattended installation"** — this newer VirtualBox feature still has some rough edges; better to run through the Ubuntu installer manually.
- **Hardware settings:**
  - **RAM** — scale it to your machine's total RAM:
    - 16 GB total → allocate 6–8 GB to the VM.
    - 8 GB total → allocate 4 GB.
    - Less than 8 GB → try smaller values (2–3 GB) and see how it performs.
    - Can always be changed later in the VM's settings.
  - **CPUs** — a good rule of thumb is about **half** of your available cores (e.g., 8 cores on the host → assign 4 to the VM).
- **Hard disk** — create a new virtual disk, **minimum 30 GB** (30–40 GB recommended; the instructor uses 35 GB). Space is allocated dynamically — the VM won't use the full size right away, it grows as needed.
- Click **Finish** to create the VM.

### 4. Adjust a few extra settings before first boot
Select the new VM → **Settings**, then adjust:
- **System → Acceleration:** disable "Enable nested paging."
- **Display:** uncheck "Enable 3D acceleration."
- **Display → Video Memory:** raise it as high as possible (up to 128 MB).
- These help avoid graphical glitches in the VM. If display issues show up later, this is the first place to revisit — every host machine can behave a little differently.

### 5. Install Ubuntu inside the VM
- Start the VM → at the boot menu, use the arrow keys to select **"Try or Install Ubuntu"** → Enter → wait through the startup logs until the installer's welcome screen appears.
- Walk through the installer:
  - Choose your **language** (English, to match the course).
  - Skip the accessibility menu.
  - Choose the **keyboard layout** matching your actual keyboard.
  - Network: choose **"Wired connection"** (uses your host machine's internet connection).
  - If prompted, update the installer itself first — you may need to repeat the language/keyboard steps afterward.
  - Choose **"Interactive installation."**
  - App selection: the **default ("essentials") selection** is enough — just a browser, nothing extra needed.
  - **Check "Install third-party software for graphics and Wi-Fi hardware"** — recommended so you get the correct drivers (especially with Nvidia graphics cards) and avoid errors when starting the VM later.
  - Installation type: since the virtual disk is empty, choose **"Erase disk and install Ubuntu"** — safe for a VM, nothing is lost.
    - *Note:* on a real dual-boot install on physical hardware, you'd instead pick an option like "Install Ubuntu alongside Windows," never erase the whole disk.
  - Create your account: keep the username and computer name simple (e.g., username "ed," computer name "ed-vm"); choose a password (can be simple for a learning VM).
  - Choose your **time zone**.
  - Review the installation summary, then click **Install** and wait (roughly **25 minutes**, as a reference point).
  - When done, click **Restart**, then press Enter at the "remove installation medium" prompt (nothing to actually remove in a VM).
  - Log in with the password you set.
- On first login: click through the welcome menu, **skip the Ubuntu Pro offer**, choose your system-data-sharing preference, and finish. Ubuntu is now installed.

### 6. Post-install setup
- **Update all packages** from a terminal (tip: right-click the terminal in the dock to pin it for quick access later):
  ```bash
  sudo apt update
  sudo apt upgrade
  ```
  (In the walkthrough this pulled in about 200 package upgrades — a normal amount for a fresh install.)
- **Install the Guest Additions** — needed so the VM window resizes properly and so copy/paste works between host and VM (without it, resizing won't change the resolution and the clipboard won't be shared):
  1. Install the required build tools first:
     ```bash
     sudo apt install build-essential gcc make perl dkms
     ```
     (Use Tab autocompletion; some packages may already be installed — accept installing the rest. If asked to restart for something else at this point, you can choose "restart later.")
  2. In the VM window's top menu: **Devices → Insert Guest Additions CD image.**
  3. Open the new CD in the file manager, right-click inside it, and choose **"Open in Terminal"** (optionally run `ls` first to see what's inside).
  4. Run the installer:
     ```bash
     sudo ./VBoxLinuxAdditions.run
     ```
     (Use autocompletion for the exact file name.) Enter your password and wait roughly 1–2 minutes for it to finish.
  5. **Shut down properly** through Ubuntu's own menu (Power Off) — not just by closing the VirtualBox window — then start the VM again from the VirtualBox Manager.
- **After rebooting:**
  - The desktop should now resize correctly (you may need to resize the window once to trigger it).
  - **Eject** the Guest Additions CD (right-click it → Eject) since it's no longer needed.
  - Enable clipboard sharing: **Devices → Shared Clipboard → Bidirectional** (copy/paste now works both ways between host and VM).

### Wrap-up
- The VM is now fully set up and ready for the rest of the course.
- The instructor personally uses a native dual-boot Ubuntu install going forward, but the course can be followed **100%** using this virtual machine instead.

---

## Class 7 — Note: Updated VS Code Extension for ROS 2

- A heads-up tied to the upcoming lecture **"Programming Tools I will use during this course"** (around the 3:15 mark of that video).
- The **"ROS"** extension for VS Code shown in that video is now **deprecated**.
- Instead, search for and install **"Robot Developer Extensions for ROS 2,"** published by **Ranch Hand Robotics LLC**.
- It provides essentially the same functionality — just released under a new name/publisher.

---

## Quick Recap

| Class | Focus |
|---|---|
| 4 | Choosing a ROS 2 distribution — EOL, LTS vs. non-LTS, why this course uses **Jazzy** |
| 5 | Choosing an OS — Ubuntu 24.04 for Jazzy, dual boot vs. virtual machine |
| 6 | Installing Ubuntu 24.04 in a VirtualBox VM — download, create, configure, install, then finish setup (updates, Guest Additions, clipboard) |
| 7 | Note: the VS Code "ROS" extension is deprecated — use "Robot Developer Extensions for ROS 2" (Ranch Hand Robotics LLC) instead |

**Coming up next:** *"Programming Tools I will use during this course."*
