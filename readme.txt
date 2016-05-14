[README]
Thank you for downloading QServ, the most up to date server for Sauerbraten!
We hope you enjoy the modification. A full documentation is included here.
For further assistance, please view the Wiki: https://github.com/deathstar/QServ/wiki
if you still need help, email: gscottmalibu@gmail.com, or join #QServ @ irc.gamesurge.net.

[OVERVIEW]
QServ is a standalone server modification for Cube 2: Sauerbraten. It is completely compatible with Mac OSX and Linux.
Windows support has been implemented with ifdef’s for the os, however QServ has not been tested on recently on Windows.

[DOWNLOAD]
Github offers a zip (link below) or you can git clone the repository from the command line
Direct Download link: https://codeload.github.com/deathstar/QServCollect/zip/master
Terminal Download Command: git clone https://github.com/deathstar/QServCollect

[REQUIREMENTS]

MAC OSX
- xCode: Go to the App Store and download "xCode," or visit: https://developer.apple.com/xcode/download/
- Command Line tools: run: "xcode-select --install" from Terminal after xCode is installed
- Cmake: https://cmake.org/download/

LINUX/WINDOWS
- Cmake: https://cmake.org/download/

[CONFIGURATION]
- Configure general attributes in server-init.cfg
- Configure authkeys in users.cfg
- Flagruns are stored in flagruns.cfg 
Note: you may want to type: "chmod 777 flagruns.cfg" from command line if flagruns aren’t writing (for full file permissions)

[QUICK SETUP]
- download QServ from https://codeload.github.com/deathstar/QServCollect/zip/master
- place the QServCollect folder on your Desktop
- change directories into it: cd Desktop/QServCollect
- Run the check make command: cmake .
- Run the make command: make
- Run the start server command: ./qserv or "nohup ./qserv &" for a background server
- Press Control-C to stop, or use "top" then "kill PID" to kill a background server

[TROUBLESHOOTING]
"command not found: cmake .": cmake is not installed, see below 
"make: *** No targets specified and no makefile found.  Stop.": the cmake . command was not issued before make
"library not found GeoIP": GeoIP is not installed for some reason, download http://dev.maxmind.com/geoip/legacy/geolite/
"No such file or directory": you are changing directories into an invalid folder, make sure QServCollect is the name
"Segmentation fault: 11" on launch: wait for IRC to start! Retry the launch (it will work the second time). 
"Segmentation fault" at a random time after launch: contact DeathStar @ gscottmalibu@gmail.com
QServ IRC not working (incompatable client): Retry the launch (it will work the second time).
QServ IRC not launching at all (excess flood): you either restarted the server too much or flooded IRC, time will fix.
If you are experiencing issues with IRC, simply use the "ircignore 1" command in the server-init.cfg to disable it.
No such file or directory "GeoIP.h": geoIP come precompiled w/ dat, this means some GeoIP file is missing, most likely your download was corrupt.