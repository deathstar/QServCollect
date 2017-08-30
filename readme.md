OVERVIEW 
--------

QServ is a highly configurable, compact, fast, extendable, cross-compatible, standalone server modification for Cube 2: Sauerbraten. It is a rather small (approximately 43mb) and only uses about 1% of the CPU with a normal load. 

FEATURES
--------

30+ commands, GeoIP city/region & country, IRC Bot with commands, multi-server chat linkage, smartbot (weather/translator/dictionary/calculator), killing spree messages, server stored maps, longshot/close up kills, beststats, pass-the-flag, command builder, reloadable server configuration/authkeys live without restart, banlist, selective unbanning, banning by ip, chat/server log with time, automatically sent maps with lightmaps, lag detection, instagib on automatically sent maps from the server with lights, no teamkill damage toggle, no damage toggle, stored flagrun times, banner messages, no 1 person private mode toggle, greet clients with name toggle, default gamemode/map option, etc.

DOWNLOAD
--------

Github offers a zip (link below) or you can git clone the repository from the command line
Direct Download link: https://codeload.github.com/deathstar/QServCollect/zip/master

Terminal Download Command: git clone https://github.com/deathstar/QServCollect
(requires git): sudo apt-get install git-all or http://sourceforge.net/projects/git-osx-installer/

REQUIREMENTS
------------

**MAC OSX**

- There is an automatic downloader/installer for QServ, you can use it only if you have the requirements below
- Simply download and run this installer: http://techmaster.mooo.com/download/QServ-Installer.zip 
- xCode: Go to the App Store and download "xCode," or visit: https://developer.apple.com/xcode/download/
- Command Line tools: run: "xcode-select --install" from Terminal after xCode is installed
- Cmake: Download a binary release for Mac OSX from https://cmake.org/download/ or run: "/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"; brew install cmake" from Terminal

**LINUX**

 - Cmake: Download from https://cmake.org/download/ or run "sudo apt-get install cmake" 
 - install Zlib from Terminal: "sudo apt-get install zlib1g-dev"
 - install compiler from Terminal: "sudo apt-get install build-essential"
 - update from Terminal: "sudo apt-get update"
 
**WINDOWS**

- Download and install this version: https://github.com/DragonSlayer87/QServWindows
- Special thanks to BudSpencer for porting QServ to Windows! 

QUICK SETUP
-----------

1) Download QServ by [clicking here](https://codeload.github.com/deathstar/QServCollect/zip/master) 
- OR run "git clone https://github.com/deathstar/QServCollect.git" from command line 
(requires git): "sudo apt-get install git-all" or http://sourceforge.net/projects/git-osx-installer/
you can just download the zip from the website and place it on your web server if you do not wish to install git to use the command line code to download QServ.

2) place the QServCollect folder on your Desktop and make sure it's named accordingly 

3) Open command line and type: "cd Desktop/QServCollect"

4) Run the cmake command (or select the QServCollect folder from the CMake GUI): "cmake ."

5) Run the make command: "make"

6) Run the start server command: "./qserv" for a live log, "nohup ./qserv &" for background

Note: if you just use "./qserv" you will need to keep the window open to keep the server running. It is suggested that you always run "nohup ./qserv &" to keep the server up in the background and output the log to nohup.out.

- Press Control-C to stop, or use "top" to get the PID of QServ then use "kill PID" to kill a background server

CONFIGURATION
-------------

- Configure general attributes in config/server-init.cfg
- Add authkeys in config/users.cfg
- Type "chmod 777 config/
s.cfg" from command line to give QServ permission to store flagruns. Or, just change the permissions of the config/flagruns.cfg file to Full Access (optional)
- Type "chmod 777 packages; chmod 777 base" from command line to give QServ permission to store maps. Or just change the permissions of the packages/base folder to Full Access (optional)

TROUBLESHOOTING
--------------- 

"command not found: cmake .": cmake is not installed, see above for download link.

"make: *** No targets specified and no makefile found.  Stop.": the cmake . command was not issued before make.

"library not found GeoIP": GeoIP is not installed for some reason, download http://dev.maxmind.com/geoip/legacy/geolite/.

"No such file or directory": you are changing directories into an invalid folder, make sure QServCollect is the name

"Segmentation fault: 11" on launch: wait for IRC to start! Retry the launch (it will work the second time).
 
"Segmentation fault" at a random time after launch: contact DeathStar @ gscottmalibu@gmail.com.

QServ IRC not working (incompatable client): Retry the launch (it will work the second time).

QServ IRC not launching at all (excess flood): you either restarted the server too much or flooded IRC, time will fix.

If you are experiencing issues with IRC, simply use the "ircignore 1" command in the server-init.cfg to disable it.

No such file or directory "GeoIP.h": geoIP come precompiled w/ dat, this means some GeoIP file is missing, most likely your download was corrupt.

MORE HELP RESOURCES 
-------------------

For further assistance, please view the Wiki: https://github.com/deathstar/QServCollect/wiki 

If you still need help, you can email the main developer: gscottmalibu@gmail.com
