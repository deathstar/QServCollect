# QServCollect
Cube 2: Sauerbraten Server modification with recode, commands, GeoIP, logs, customization and more!

### Mac Users - watch this video:
http://techmaster.mooo.com/download/howto_install_qserv.mp4

### Windows Users: download/use precompiled binary on QServ website.

### Need more help? 
Visit https://gamesurge.net/chat/ and join channel #QServ, or email gscottmalibu@gmail.com

[[Commands|https://github.com/deathstar/QServ/wiki/Commands/]] |
[[Configuration|https://github.com/deathstar/QServ/wiki/Configuration/]] | 
[[GeoIP Installation|https://github.com/deathstar/QServ/wiki/GeoIP-Installation/]] |
**[[QServ Installation|https://github.com/deathstar/QServ/wiki/QServ-Installation/]]**

## Macintosh 
### What you need
- [CMake](http://www.cmake.org/cmake/resources/software.html)
**When installing CMake, be sure to select "Install Command Line Links"**
- Command Line Tools from xCode
- xCode itself 
- [GeoIP](http://www.maxmind.com/en/installation) for Mac (optional)

If you do not wish to download GeoIP for Mac, it can be turned off from server-init.cfg: look for Miscellaneous and change the variable to: enablegeoip 0

### Installing & Compiling
- Open "Terminal" (Applications/Utilities)
- Type: `git clone git://github.com/deathstar/QServ.git`
- Change directories to the QServ folder (type: `cd QServ`)
- Type: `cmake .; make`

- **You're all set!** Configure your server in "server-init.cfg"  
- To start QServ, use `./qserv`
- If you want to run QServ in the background use: `nohup ./qserv &`, to stop it, run type `top`, find the QServ Process ID number and then type `killall IDNUMBER`

## Windows
### What you need
- [GeoIP](http://www.maxmind.com/en/installation) for Windows (optional)

### Installing 
- Visit the [Downloads](https://github.com/deathstar/QServ/downloads) page and choose a version of QServ.

please note: QServ will be updated for the Collect Edition as a Beta Release. As of now, all of the Windows downloads for QServ are outdated. 

- **You're all set!** Configure your server in "server-init.cfg" 
- To start QServ, open the executable "QServ"

## Linux 
### What you need
- [CMake](http://www.cmake.org/cmake/resources/software.html)
- [GeoIP](http://www.maxmind.com/en/installation) for Linux (optional)

### Installing 
- Open "Terminal" (Search->Terminal)
- Type: `git clone git://github.com/deathstar/QServ.git`
- Change directories to the QServ folder (type: `cd QServ`)
- Type: `cmake .; make`

- **You're all set!** Configure your server in "server-init.cfg"  
- To start QServ, use `./qserv`
- If you want to run QServ in the background use: `nohup ./qserv &`, to stop it, run type `top`, find the QServ Process ID number and then type `killall IDNUMBER`
