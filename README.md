## Getting started
The [FreeRTOS.org](https://www.freertos.org) website contains a [FreeRTOS Kernel Quick Start Guide](https://www.freertos.org/Documentation/01-FreeRTOS-quick-start/01-Beginners-guide/02-Quick-start-guide), a [list of supported devices and compilers](https://www.freertos.org/RTOS_ports.html), the [API reference](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/00-TaskHandle), and many other resources.

## Cloning this repository
This repo uses [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) to bring in dependent components.

**Note:** If you download the ZIP file provided by the GitHub UI, you will not get the contents of the submodules. (The ZIP file is also not a valid git repository)

If using Windows, because this repository and its submodules contain symbolic links, set `core.symlinks` to true with the following command:
```
git config --global core.symlinks true
```
In addition to this, either enable [Developer Mode](https://docs.microsoft.com/en-us/windows/apps/get-started/enable-your-device-for-development) or, whenever using a git command that writes to the system (e.g. `git pull`, `git clone`, and `git submodule update --init --recursive`), use a console elevated as administrator so that git can properly create symbolic links for this repository. Otherwise, symbolic links will be written as normal files with the symbolic links' paths in them as text. [This](https://blogs.windows.com/windowsdeveloper/2016/12/02/symlinks-windows-10/) gives more explanation.

To clone using HTTPS:
```
git clone https://github.com/djuricicmilos/FreeRTOS-RMS.git --recurse-submodules
```
Using SSH:
```
git clone git@github.com:djuricicmilos/FreeRTOS-RMS.git --recurse-submodules
```

If you have downloaded the repo without using the `--recurse-submodules` argument, you need to run:
```
git submodule update --init --recursive
```

## Repository structure
This repository contains the FreeRTOS Kernel, a number of supplementary libraries including the LTS ones, and a comprehensive set of example projects.  Many libraries (including the FreeRTOS kernel) are included as Git submodules from their own Git repositories.

### Kernel source code and example projects
```FreeRTOS/Source``` contains the FreeRTOS kernel source code (submoduled from https://github.com/FreeRTOS/FreeRTOS-Kernel).

```FreeRTOS/Demo``` contains pre-configured example projects that demonstrate the FreeRTOS kernel executing on different hardware platforms and using different compilers.

The ```FreeRTOS/Demo/Posix_GCC/``` directory contains the RMS algorithm. To run it, you need to navigate to the folder and enter the following commands:
```
make
```

ChatGPT said:

The executable file is located in the build/posix_demo directory and is run using the following command:
```
./build/posix_demo
```

