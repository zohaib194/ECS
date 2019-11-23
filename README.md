# ECS
Idea is to build a graphics framework using a well known code pattern Entity Component System. Using this framework furthur build a sample board game called ludo.

Framework and Game should at minimum have following functionalities:
- The game should follow all basic ludo rules. ```https://www.mastersofgames.com/rules/ludo-rules-instructions-guide.htm```
- Option to play as single player with bot or up to four other player (multiplayer).
- Minimum graphics details.
- Minimum animations.
- Score sytem should be integrated and framework capabilities to create rewarding systems.
- Player must be able to communicate (chat-service).

## Install Guide
### LINUX (OpenSuse)
- Open terminal and run following commands:
    - ```zypper install cmake```
	- ```zypper install gcc-c++```
	- ```zypper install glew-devel```
	- ```zypper install glfw2-devel```
	- ```zypper install doxygen```
	- ```git clone https://github.com/zohaib194/ECS.git```
    - ```cd <path to ECS directory>```
    - ```mkdir build && cd ./build```
    - ```make && ./bin/ECS```


### Windows (Git bash + Chocolatey package manager)

- Install chocolatey
	- Open powershell
	- Run this commanad: ```Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))```
	- Close powershell
- Open Git bash:
	- ```choco install cmake 3.15.5```
	- ```choco install make 4.2.1```
	- ```git clone https://github.com/zohaib194/ECS.git```
	- navigate to the ECS directory
	- Run the following commands:
		- ```mkdir build && cd build```
- Open CMake (cmake-gui) through Start
	- "Where is the source code:" - ```C:/<Path>/ECS```
	- "Where to build the binaries:" - ```C:/<Path>/ECS/build```
- Switch back to Git bash:
    - Run the following commands:
        - ```make```
        - ```./bin/ECS.exe```

### Successful build
![](https://i.imgur.com/KNf14qE.png)

