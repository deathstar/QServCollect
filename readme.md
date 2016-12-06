###README
We hope you enjoy the modification. A full documentation is included here.

For further assistance, please view the Wiki: https://github.com/deathstar/QServCollect/wiki

if you still need help, email: gscottmalibu@gmail.com, join #QServ @ irc.gamesurge.net, or leave an issue on the github page.

##OVERVIEW
QServ is a standalone server modification for Cube 2: Sauerbraten. It is completely compatible with Mac OSX and Linux.

You can download install, configure and start QServ in less than 5 minutes (if you have the prerequisites).

Windows support has been implemented, however, it is not tested.


##DOWNLOAD
Github offers a zip (link below) or you can git clone the repository from the command line

Direct Download link: https://codeload.github.com/deathstar/QServCollect/zip/master

Terminal Download Command: git clone https://github.com/deathstar/QServCollect
(requires git): `sudo apt-get install git-all` or http://sourceforge.net/projects/git-osx-installer/

you can just download the zip from the website and place it on your web server if you do not wish to install git to use the command line code to download QServ.

**Mac Users, simply download and run [this installer](http://techmaster.mooo.com/download/QServ-Installer.zip) to download and install QServ.**

###Requirements

**MAC OSX**

- xCode: Go to the App Store and download "xCode," or visit: https://developer.apple.com/xcode/download/
- Command Line tools: run: `xcode-select --install` from Terminal after xCode is installed
- Cmake: Download a binary release for Mac OSX from https://cmake.org/download/ or run: `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"; brew install cmake` from Terminal

**LINUX**

 - Cmake: Download a binary release for Linux from [https://cmake.org/download/]((download a binary client)) or run `sudo apt-get install cmake` from Terminal
 - install Zlib from Terminal: `sudo apt-get install zlib1g-dev`
 - install compiler from Terminal: `sudo apt-get install build-essential`
 - update from Terminal: `sudo apt-get update`

###QUICK SETUP
1 ) Download QServ by [clicking here](https://codeload.github.com/deathstar/QServCollect/zip/master) 

- `git clone https://github.com/deathstar/QServCollect.git` for command line 
(requires git): `sudo apt-get install git-all` or http://sourceforge.net/projects/git-osx-installer/
you can just download the zip from the website and place it on your web server if you do not wish to install git to use the command line code to download QServ.

2 ) place the QServCollect-master folder on your Desktop and make sure it's named accordingly 

3 ) Open command line and type: `cd Desktop/QServCollect-master`

4 ) Run the cmake command (or select the QServCollect folder from the CMake GUI): `cmake .`

5 ) Run the make command: `make`

6 ) Run the start server command: `./qserv` for a live log, `nohup ./qserv &` for background

Note: if you just use `./qserv` you will need to keep the window open to keep the server running. It is suggested that you always run `nohup ./qserv &` to keep the server up in the background and output the log to nohup.out.

- Press Control-C to stop, or use `top` to get the PID of QServ then use `kill PID` to kill a background server

##CONFIGURATION
- Configure general attributes in config/server-init.cfg
- Add authkeys in config/users.cfg
- Type `chmod 777 config/flagruns.cfg` from command line to give QServ permission to store flagruns. Or, just change the permissions of the config/flagruns.cfg file to Full Access (optional)
- Type `chmod 777 packages; chmod 777 base` from command line to give QServ permission to store maps. Or just change the permissions of the packages/base folder to Full Access (optional)

##TROUBLESHOOTING
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
