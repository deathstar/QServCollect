[QServ README]
Thank you for downloading QServ, the most up to date server for Sauerbraten!
We hope you enjoy the modification. A full documentation is included here.
For further assistance, please view the Wiki: https://github.com/deathstar/QServ/wiki
if you still need help, email: gscottmalibu@gmail.com, or join #QServ @ irc.gamesurge.net.

[OVERALL TROUBLESHOOTING]
"command not found: cmake .": cmake is not installed, see below 
"make: *** No targets specified and no makefile found.  Stop.": the cmake . command was not issued before make
"library not found GeoIP": GeoIP is not installed for some reason, download http://dev.maxmind.com/geoip/legacy/geolite/
"No such file or directory": you are changing directories into an invalid folder, make sure QServCollect is the name
"Segmentation fault: 11" on launch: wait for IRC to start! Retry the launch (it will work the second time). 
"Segmentation fault" at a random time after launch: contact DeathStar @ gscottmalibu@gmail.com
QServ IRC not working (incompatable client): Retry the launch (it will work the second time).
QServ IRC not launching at all (excess flood): you either restarted the server too much or flooded IRC, time will fix.
If you are experiencing issues with IRC, simply use the "ircignore 1" command in the server-init.cfg to disable it.

[OVERVIEW]
QServ is a standalone server modification for Cube 2: Sauerbraten. It is developed on a macintosh 
and has been ported to Linux as well. Windows support is here! We just need some testing. If you 
are interested, please contact gscottmalibu@gmail.com with the subject line "QServ"

[DOWNLOAD]
github offers a zip or you can git clone the respitory 
Direct Download link: https://codeload.github.com/deathstar/QServCollect/zip/master
Terminal Download Command: git clone https://github.com/deathstar/QServCollect

[REQUIREMENTS]
you will need cmake, make, xCode, xCode command line tools (geoIP should come precompiled w/ dat) 

xCode: https://developer.apple.com/xcode/download/
Command Line tools: run: "xcode-select --install" from Terminal after xCode is installed
Cmake: https://cmake.org/download/

[CONFIGURATION]
- All the configuration can be done in server-init.cfg

[QUICK SETUP]
- download QServ from https://codeload.github.com/deathstar/QServCollect/zip/master
- place the QServCollect folder on your Desktop
- change directories into it: cd Desktop/QServCollect
- Run the check make command: cmake .
- Run the make command: make
- Run the start server command: ./qserv or "nohup ./qserv &" for a background server
- Press Control-C to stop, or use "top" then "kill PID" to kill a background server

[CUSTOM QSERV TERMINAL COMMANDS]
1) Open your terminal (Applications/Utilities/Terminal)
2) type: nano .profile
3) paste the following lines in the your profile:

alias qlive="cd Desktop/QServCollect"
alias qclean="rm -r cmake_install.cmake CMakeCache.txt"    
alias qstart="./qserv"
alias qall="rm -r cmake_install.cmake CMakeCache.txt; cmake .; make"
alias qnohup="nano nohup.out"
alias qmake="make"
alias qcmake="cmake ."
alias qbgserv="nohup ./qserv &"
alias qserv="./qserv"

4) now you have created a custom profile for QServ to easily issue commands

5) Quit terminal to update the .profile for Terminal (do this or the commands won't work!)

6) Make sure your QServCollect server folder is on your desktop and named "QServCollect" exactly

7) Reopen terminal and type: qlive

8) If this worked, you will have changed directories to QServCollect and should see "Users-MacBook-Pro:QServCollect"

[TROUBLESHOOTING]: make sure you are in the directory just before desktop, use "cd .." to go back a directory

9) type: qcmake;qmake

10) if this worked, you will have compiled QServ sucesfully! You are ready to configure in server-init.cfg and start

[TROUBESHOOTING]: make sure you have cmake installed, you will also need xCode Command Line Tools, possibly GeoIP

11) type: qserv

12) the above command will start a qserv server with the log output live

13) to kill the server hold down Control and C

14) to run the server in the background, use qbgserv

[TROUBESHOOTING]: make sure you are in the QServCollect directory

15) to access the qbgserv logfile, use nano nohup.out, or open the nohup.out file with a text editor 

16) you can stream the logfile from a VPN or SSH connection: ssh -n username@hostname 'tail -f /path/to/nohup.out' &

17) you can stop the server running in the background by running top, finding the PID of QServ, then using: kill PID