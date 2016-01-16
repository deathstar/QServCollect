#include "QCom.h"

namespace server {
    void initCmds() {
        /**
            @ncommand = New Command
            @Command name
            @Command description and usage
            @Command callback function
            @Command argument count
        **/

        ncommand("me", "\f4Echo your name and message to everyone. Usage: #me <message>", PRIV_NONE, me_cmd, 0);
        ncommand("cmd", "\f4View command list or command usage. Usage: #cmd for command list and #cmd <commandname> for command usage", PRIV_NONE, cmd_cmd, 1);
        ncommand("stats", "\f4View the stats of a player or yourself. Usage: #stats <cn> or #stats", PRIV_NONE, stats_cmd, 1);
        ncommand("localtime", "\f4Get the local time of the Server. Usage: #localtime", PRIV_NONE, localtime_cmd, 0);
        ncommand("time", "\f4View the current time. Usage: #time <zone>", PRIV_NONE, time_cmd, 1);
        ncommand("bunny", "\f4Broadcast a helper message to all players. Usage: #bunny <helpmessage>", PRIV_ADMIN, bunny_cmd, 0);
        ncommand("echo", "\f4Broadcast a message to all players. Usage: #echo <message>", PRIV_MASTER, echo_cmd, 1);
		ncommand("revokepriv", "\f4Revoke the privileges of a player. Usage: #revokepriv <cn>", PRIV_ADMIN, revokepriv_cmd, 1);
        ncommand("forceintermission", "\f4Force an intermission. Usage: #forceintermission", PRIV_MASTER, forceintermission_cmd, 0);
        ncommand("getversion", "\f4Get the current QServ Version. Usage: #getversion", PRIV_NONE, getversion_cmd, 0);
        ncommand("callops", "\f4Call all operators on the Internet Relay Chat Server. Usage: #callops", PRIV_NONE, callops_cmd, 0);
        ncommand("msg", "\f4Send a private message. Usage #msg <cn> <msg>", PRIV_NONE, msg_cmd,2);
        ncommand("sendprivs", "\f4Share power with another player. Usage: #sendprivs <cn>", PRIV_ADMIN, sendprivs_cmd, 1);
        ncommand("forgive", "\f4Forgive a player for teamkilling or just in general. Usage: #forgive <cn>", PRIV_NONE, forgive_cmd, 1);
        ncommand("forcespectator", "\f4Forces a player to become a spectator. Usage: #forcespectator <cn>", PRIV_ADMIN, forcespectator_cmd, 1);
        ncommand("unspectate", "\f4Removes a player from spectator mode. Usage: #unspectate <cn>", PRIV_ADMIN, unspectate_cmd, 1);
        ncommand("mute", "\f4Mutes a client. Usage #mute <cn>", PRIV_ADMIN, mute_cmd, 1);
        ncommand("unmute", "\f4Unmutes a client. Usage #mute <cn>", PRIV_ADMIN, unmute_cmd, 1);
        ncommand("editmute", "\f4Stops a client from editing. Usage #editmute <cn>", PRIV_ADMIN, editmute_cmd, 1);
        ncommand("uneditmute", "\f4Allows a client to edit again. Usage #uneditmute <cn>", PRIV_ADMIN, uneditmute_cmd, 1);
        ncommand("togglelockspec", "\f4Forces a client to be locked in spectator mode. Usage #togglelockspec <cn>", PRIV_ADMIN, togglelockspec_cmd, 1);
        ncommand("uptime", "\f4View how long the server has been up for. Usage: #uptime", PRIV_NONE, uptime_cmd, 0);
        ncommand("info", "\f4View information about a player. Usage: #info <cn>", PRIV_NONE, info_cmd, 1);
        ncommand("tournament", "\f4Forces a tournament regardless of mode/etc. Usage: #tournament <mode> <map>", PRIV_MASTER, tournament_cmd, 2);
        ncommand("help", "\f4Lists the #cmd command and more information. Usage: #help", PRIV_NONE, help_cmd, 0);
        ncommand("cheater", "\f4Accuses someone of cheating and alerts moderators. Usage: #cheater <cn>", PRIV_NONE, cheater_cmd, 1);
        ncommand("mapsucks", "\f4Votes for an intermission to change the map. Usage: #mapsucks", PRIV_NONE, mapsucks_cmd, 0);
        ncommand("gban", "\f4Bans a client. Usage: #gban <cn>", PRIV_ADMIN, gban_cmd, 1);
        ncommand("cleargbans", "\f4Clears all server bans stored and issued. Usage: #cleargbans", PRIV_ADMIN, cleargbans_cmd, 0);
        ncommand("teampersist", "\f4Toggle persistant teams on or off. Usage: #teampersist <0/1> (0 for off, 1 for on)", PRIV_ADMIN, teampersist_cmd, 1);
        ncommand("invadmin", "\f4Claim invisible administrator. Usage: #invadmin <adminpass>", PRIV_ADMIN, invadmin_cmd, 0);
        ncommand("allowmaster", "\f4Allows clients to claim master. Usage: #allowmaster <0/1> (0 for off, 1 for on)", PRIV_ADMIN, allowmaster_cmd, 1);
        //ncommand("owords", "View list of offensive words. Usage: #owords",
        ///         PRIV_NONE, owords_cmd, 0);
        //ncommand("olangfilter", "Turn the offensive language filter on or off. Usage: #olang <off/on> (0/1) and #olang to see if it's activated",
        //         PRIV_MASTER, olangfilter_cmd, 1);
    }
    
    QSERV_CALLBACK allowmaster_cmd(p) {
        int togglenum = atoi(args[1]);
        if(togglenum==1) {
            switchallowmaster();
            clientinfo *ci = qs.getClient(CMD_SENDER);
            out(ECHO_SERV, "\f4Claiming \f0master \f4with \"/setmaster 1\" is now \f0enabled");
        }
        else if(togglenum==0) {
            switchdisallowmaster();
            out(ECHO_SERV, "\f4Claiming \f0master \f4is now \f3disabled");
        }
        else if(togglenum==NULL) {
        	sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK invadmin_cmd(p) {
        clientinfo *ci = qs.getClient(CMD_SENDER);
        if(ci->privilege == PRIV_ADMIN) {
            server::setmaster(ci, 0, "", NULL, NULL,PRIV_MASTER,false, false, true);
            ci->privilege = PRIV_ADMIN;
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f4You became an invisible \f6Admin\f4. Relinguish and reclaim to reveal your privilege.");
            out(ECHO_IRC, "%s became an invisible admin", colorname(ci));
            out(ECHO_CONSOLE, "%s became an invisible admin", colorname(ci));
        }
        else {
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3Error: \f7You must first claim admin to go invisible.");
        }
    }
    
    QSERV_CALLBACK teampersist_cmd(p) {
        int togglenum = atoi(args[1]);
        if(togglenum==1) {
            if(!persist) {
                persist = true; out(ECHO_SERV, "\f4Persistant teams are now \f0enabled");
            }
        }
        else if(togglenum==0) {
            if(persist) {
                persist = false; out(ECHO_SERV, "\f4Persistant teams are now \f3disabled");
            }
        }
        else if(togglenum==NULL) {
        	 sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK cleargbans_cmd(p) {
        server::cleargbans();
        out(ECHO_SERV, "\f0All game bans cleared!");
        out(ECHO_NOCOLOR, "All Game bans cleared");
    }
    
    QSERV_CALLBACK gban_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL && cn!=CMD_SENDER) {
            clientinfo *ci = qs.getClient(cn);
            server::addgban(ci->ip);
            disconnect_client(ci->clientnum, DISC_IPBAN);
            out(ECHO_SERV, "\f0%s \f4has been added to the permanent banlist.", colorname(ci));
            out(ECHO_NOCOLOR, "%s has been added to the permanent banlist.", colorname(ci));
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to ban yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
   
    VAR(votestopassmapsucks, 2, 10, INT_MAX);
    int mapsucksvotes = 0;
    QSERV_CALLBACK mapsucks_cmd(p) {
        clientinfo *ci = qs.getClient(CMD_SENDER);
        if(!ci->votedmapsucks) {
            mapsucksvotes++;
            out(ECHO_SERV, "\f0%s \f4thinks this map sucks, use \f2#mapsucks \f4to vote for an intermission to skip it.", colorname(ci));
            ci->votedmapsucks = true;
            if(mapsucksvotes>=getvar("votestopassmapsucks")) {
                startintermission();
                int mapsucksvotes = 0;
                out(ECHO_SERV, "\f4Changing map: That map sucked (\f7%d \f4votes to skip)", votestopassmapsucks);
            }
        }
        else if(ci->votedmapsucks) sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3Error: You have already voted");
    }
    
    QSERV_CALLBACK help_cmd(p) {
        static char colors[2], commandList[2056] = {0};
        int color = -1;
        
        strcpy(commandList, "");
        sprintf(commandList, "%s", "\f1Commands: ");
        
        for(int i = 0; i < CMD_LAST; i++) {
            if(CMD_PRIV(i) == PRIV_NONE) {
                color = 4;
            } else if(CMD_PRIV(i) == PRIV_MASTER) {
                color = 0;
            } else if(CMD_PRIV(i) == PRIV_ADMIN) {
                color = 6;
            }
            
            sprintf(colors, "\f%d", color);
            strcat(commandList, colors);
            strcat(commandList, CMD_NAME(i));
            
            if(i != CMD_LAST-1) {
                strcat(commandList, "\f7, ");
            }
        }
        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, commandList);
        clientinfo *ci = qs.getClient(CMD_SENDER);
        defformatstring(f)("\f1Help\f4: Type \f2#cmd \f4to list commands, or use \f2#cmd <commandname> \f4for information about a specific command.");
        sendf(ci->clientnum, 1, "ris", N_SERVMSG, f);
        }
    
    // restrict modes certain modes only for a tournament, not coop etc.
    char *qserv_modenames[] = {
        "ffa",
        "coop", "teamplay", "insta", "instateam", "effic",
        "efficteam", "tactics", "tacticsteam", "capture",
        "regencapture", "ctf", "instactf", "efficctf", "protect",
        "instaprotect", "efficprotect", "hold", "instahold", "effichold",
        "collect", "instacollect", "efficcollect"
    }; 
    // custom mode names remember to type them like this if you want that mode
    
    int mc = 22;
    
    extern void changemap(const char *s, int mode);
    extern void pausegame(bool val, clientinfo *ci = NULL);
    
    QSERV_CALLBACK tournament_cmd(p) {
        const char *mapname = args[2];
        char *mn = args[1];
        if(args[1] != NULL && args[2] != NULL && *mapname !=NULL && *mn!=NULL) {
        int gm; // default set to current mode td
        bool valid = false;
        
            // intialize this for perf
        for(int i = 0; i < mc; i++)  {
            if(!strcmp(mn, qserv_modenames[i]))  {
                gm = i;
                // use other list to send full name of mode
                changemap(mapname, gm);
                valid = true;
                break;
            }
        }
        	if(valid) {
            defformatstring(f)("\f4Tournament has started: %s on map %s", qserv_modenames[gm], mapname);
            sendf(-1, 1, "ris", N_SERVMSG, f);
            }
            
        if(!valid) {sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Unknown mode");}
        }
        else {
        	bool valid = false;
            defformatstring(f)("\f3Error: Invalid mode/mapname provided");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, f);
        }
    }
    
    QSERV_CALLBACK uptime_cmd(p) {
        clientinfo *ci = qs.getClient(CMD_SENDER);
        string msg, buf;
        uint t, months, weeks, days, hours, minutes, seconds;
        copystring(msg,"\f4Server Mod: \f3QServ\f4: \f1https://github.com/deathstar/QServCollect");
        sendf(ci ? ci->clientnum : -1, 1, "ris", N_SERVMSG, msg);
        copystring(msg, "\f4Server Architecture: \f0"
		/* Firstly determine OS */
		#if !(defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
		/* unix/posix compilant os */
		#   if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
                   "GNU/Linux"
		#   elif defined(__GNU__) || defined(__gnu_hurd__)
                   "GNU/Hurd"
		#   elif defined(__FreeBSD_kernel__) && defined(__GLIBC__)
                   "GNU/FreeBSD"
		#   elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
                   "FreeBSD"
		#   elif defined(__OpenBSD__)
                   "OpenBSD"
		#   elif defined(__NetBSD__)
                   "NetBSD"
		#   elif defined(__sun) || defined(sun)
                   "Solaris"
		#   elif defined(__DragonFly__)
                   "DragonFlyBSD"
		#   elif defined(__MACH__)
		#       if defined(__APPLE__)      
                   "Apple"     
		#       else   
                   "Mach"  
		#       endif  
		#   elif defined(__CYGWIN__)  
                   "Cygwin"  
		#   elif defined(__unix__) || defined(__unix) || defined(unix) || defined(_POSIX_VERSION)  
                   "UNIX"  
		#   else  
                   "unknown"   
		#   endif     
		#else      
                   /* Windows */
                   "Windows"
		#endif
                   " "
                   );
        concatstring(msg, (sizeof(void *) == 8) ? "x86 (64 bit)" : "i386");
        concatstring(msg, "\n\f4Server Uptime:");
        t = totalsecs;
        
        months = t / (30*24*60*60);
        
        t = t % (30*24*60*60);
        
        weeks = t / (7*24*60*60);
        
        t = t % (7*24*60*60);
        
        days = t / (24*60*60);
        
        t = t % (24*60*60);
        
        hours = t / (60*60);
        
        t = t % (60*60);
        
        minutes = t / 60;
        
        t = t % 60;
        
        seconds = t;
    
        if(months)    
        {
            formatstring(buf)(" %u month%s", months, months > 1 ? "s" : "");
            concatstring(msg, buf);
        }
        
        if(weeks)
        { 
            formatstring(buf)(" %u week%s", weeks, weeks > 1 ? "s" : "");
            concatstring(msg, buf);  
        }

        if(days)
        {
            formatstring(buf)(" %u day%s", days, days > 1 ? "s" : "");
            concatstring(msg, buf);
        }
        
        if(hours)  
        { 
            formatstring(buf)(" %u hour%s", hours, hours > 1 ? "s" : "");
            concatstring(msg, buf);  
        }
          
        if(minutes)   
        {
            formatstring(buf)(" %u minute%s", minutes, minutes > 1 ? "s" : "");
            concatstring(msg, buf);  
        }
        
        if(seconds)
        {
            formatstring(buf)(" %u second%s", seconds, seconds > 1 ? "s" : "");
            concatstring(msg, buf);    
        }
        
        sendf(ci ? ci->clientnum : -1, 1, "ris", N_SERVMSG, msg);
    }

    //Check to see if args 1 is blank, if not causes seg fault on linux when #info is issued
    QSERV_CALLBACK info_cmd(p) {
        bool usage = false;
        int cn = -1;
        if(CMD_SA) {
            cn = atoi(args[1]);
             clientinfo *ci = qs.getClient(cn);
            if(cn!=-1 && cn >= 0 && cn <= 1000 && cn != NULL && args[1]!=NULL) {
                //if(!isalpha(cn)) {
            sendinfo:
                
                if(ci != NULL) {
                    if(ci->connected) {
                        char *ip = toip(cn), lmsg[3][255], *location;
                        
                        if(!strcmp("127.0.0.1", ip)) {
                            location = (char*)"localhost";
                        } else {
                            location = qs.congeoip(ip);
                            
                            if(!location) {
                                sprintf(lmsg[1], "%s", "Unknown/Localhost");
                            }
                        }
                        
                        if(location) sprintf(lmsg[1], "%s", location);
                        (CMD_SCI.privilege == PRIV_ADMIN) ? sprintf(lmsg[0], "%s (%s)", lmsg[1], ip) :
                        sprintf(lmsg[0], "%s", lmsg[1]);
                        int sec = (ci->connectmillis/1000) % 60;
                        int min = ((ci->connectmillis/(1000*60)) % 60);
                        int hour = ((ci->connectmillis / (100*60*60)) % 24);
                        int cn = atoi(args[1]);
                        clientinfo *ci = qs.getClient(cn);
                        defformatstring(f)("\f0%s \f4(\f2%d\f4) [\f1%s\f4] \f4Connected for: \f6%d \f2Hour(s)\f4, \f6%d \f2Minute(s)\f4, \f6%d \f2Second(s)", colorname(ci), ci->clientnum,lmsg[0], hour, min, sec);
                        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, f);
                    } else {
                        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "Played not connected");
                    }
                    /*} else {
                     usage = true;
                     }*/
                } else {
                    usage = true;
                }
            } else {
                cn = CMD_SENDER;
                goto sendinfo;
            }
            
            if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
        
    }
    
    extern void forcespectator(clientinfo *ci);
    extern void unspectate(clientinfo *ci);
    QSERV_CALLBACK togglelockspec_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);

        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            if(!ci->isSpecLocked) {
                forcespectator(ci);
                ci->isSpecLocked = true;
                sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3You have been locked in spectator mode.");
            } else if(ci->isSpecLocked) {
                unspectate(ci);
                ci->isSpecLocked = false;
                sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3You are no longer locked in spectator mode.");
            }
            
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to force spectate yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK forcespectator_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
        clientinfo *ci = qs.getClient(cn);
        forcespectator(ci);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to force spectate yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK unspectate_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
        clientinfo *ci = qs.getClient(cn);
        unspectate(ci);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to unspectate spectate yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK mute_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            ci->isMuted = true;
            defformatstring(mutemsg)("\f0%s \f4has been \f3muted", colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, mutemsg);
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to mute yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK unmute_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            ci->isMuted = false;
            defformatstring(unmutemsg)("\f0%s \f4has been \f0unmuted", colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, unmutemsg);
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to unmute yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK editmute_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            ci->isEditMuted = true;
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f4Your edits \f3will not \f4show up to others.");
            defformatstring(mutemsg)("\f0%s\f4's edits have been \f3muted", colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, mutemsg);
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to editmute yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK uneditmute_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f4Your edits \f0will \f4now show up to others.");
            ci->isEditMuted = false;
            out(ECHO_SERV,"\f0%s\f4's edits have been \f0unmuted", colorname(ci));
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to uneditmute yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK forgive_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        clientinfo *self = qs.getClient(CMD_SENDER);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            defformatstring(forgivemsg)("\f0%s \f4has forgiven \f3%s", colorname(self), colorname(ci));
            sendf(-1, 1, "ris", N_SERVMSG, forgivemsg);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to forgive yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    SVAR(ircoperators, "");
    QSERV_CALLBACK cheater_cmd(p) {
    	int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        clientinfo *self = qs.getClient(CMD_SENDER);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && cn != NULL && ci != NULL && ci->connected && args[1]!=NULL) {
        	int accuracy = (ci->state.damage*100)/max(ci->state.shotdamage, 1);
        	//send it to admins and log
            privilegemsg(PRIV_MASTER,"\f4Something's fishy! A cheater has been reported.");
             out(ECHO_SERV, "\f0%s \f4accuses \f3%s \f4(CN: \f6%d \f4| Accuracy: \f6%d%\f4) of cheating.", colorname(self), colorname(ci), ci->clientnum, accuracy);
            out(ECHO_NOCOLOR, "Attention Operator(s): %s - %s accuses %s (CN: %d | Accuracy: %d%) of cheating.", ircoperators, colorname(self), colorname(ci), ci->clientnum, accuracy);
            
            //Acknowledge we got the report
            defformatstring(nocolorcheatermsg)("\f3%s \f4has been reported.", colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, nocolorcheatermsg);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to accuse yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }

    QSERV_CALLBACK olangfilter_cmd(p) {
        if(CMD_SA) {
            int state = atoi(args[1]);

            if(state == 0 or state == 1) {
                qs.setoLang(state);
            } else {
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
            }
        } else {
            defformatstring(msg)("%s", (qs.isLangWarnOn() == 1) ? "On" : "Off");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, msg);
        }
    }
    
	VAR(ircignore, 0, 0, 1);
	SVAR(contactemail, "");
    QSERV_CALLBACK callops_cmd(p) {
    	if(!getvar("ircignore")) {
    		out(ECHO_IRC, "[Attention operator(s)]: %s: %s is in need of assistance.", ircoperators, CMD_SCI.name); 
    		defformatstring(toclient)("You alerted operator(s) %s", ircoperators); 
    		sendf(CMD_SENDER, 1, "ris", N_SERVMSG, toclient);
        }
        else {defformatstring(operatorunavailable)("\f4Sorry, No operators are available currently, please email: \f1%s \f4for more assistance.",contactemail); sendf(CMD_SENDER, 1, "ris", N_SERVMSG, operatorunavailable);}
    }
    SVAR(qserv_version, "");
    QSERV_CALLBACK getversion_cmd(p) {
    defformatstring(ver)("\f4Running \f3QServ \f4(\f2%s\f4). Written by DeathStar, Mamasita, Erik & Jonlimle: \f1www.github.com/deathstar/QServCollect", qserv_version);sendf(CMD_SENDER, 1, "ris", N_SERVMSG, ver);
    }
    QSERV_CALLBACK forceintermission_cmd(p) {bool intermission = false; if(!intermission){startintermission(); defformatstring(msg)("\f0%s \f4forced an intermission",CMD_SCI.name);sendf(-1, 1, "ris", N_SERVMSG, msg); out(ECHO_IRC,"%s forced an intermission",CMD_SCI.name);}}

    QSERV_CALLBACK me_cmd(p) {
        if(strlen(fulltext) > 0) {
            qs.checkoLang(CMD_SENDER, fulltext);
            defformatstring(msg)("\f0%s \f7%s", CMD_SCI.name, fulltext);
            sendf(-1, 1, "ris", N_SERVMSG, msg);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK echo_cmd(p) {
        if(strlen(fulltext) > 0) {
            qs.checkoLang(CMD_SENDER, fulltext);
            defformatstring(msg)("\f7%s", fulltext);
            sendf(-1, 1, "ris", N_SERVMSG, msg);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    

    QSERV_CALLBACK msg_cmd(p) {
            int cn = atoi(args[1]);
            clientinfo *ci = qs.getClient(cn);
            clientinfo *self = qs.getClient(CMD_SENDER);
            if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && strlen(fulltext) > 0) {
            	const char *privatemessage = fulltext;
                defformatstring(recieverpmmsg)("\f4Private message from \f0%s\f4: \f3%s", colorname(self), privatemessage);
                sendf(cn, 1, "ris", N_SERVMSG, recieverpmmsg);
                defformatstring(senderpmconf)("\f4Sent \f0%s \f4your message: \f3%s", colorname(ci), privatemessage);
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, senderpmconf);
            } else {
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Command variables incorrect or client is not connected/existant.");
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    QSERV_CALLBACK sendprivs_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        clientinfo *self = qs.getClient(CMD_SENDER);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && strlen(fulltext) > 0) {
            defformatstring(shareprivsmsg)("\f4Ok, %s\f4. Sharing your privileges with \f0%s\f4. They now have invisible privileges.", colorname(self), colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, shareprivsmsg);
            if(self->privilege==PRIV_MASTER) {
                defformatstring(sendprivsmsg)("\f4You have recieved \f0master \f4from \f0%s\f4.", colorname(self));
                sendf(cn, 1, "ris", N_SERVMSG, sendprivsmsg);
                ci->privilege=PRIV_MASTER;
                self->privilege=PRIV_ADMIN;
            }
            else if(self->privilege==PRIV_ADMIN) {
                defformatstring(sendprivsmsg)("\f4You have recieved \f6admin from \f6%s\f4.", colorname(self));
                sendf(cn, 1, "ris", N_SERVMSG, sendprivsmsg);
                ci->privilege=PRIV_ADMIN;
                self->privilege=PRIV_ADMIN;
            }
            /*The commented code calls the actual master change message and changes the color of the player, above just changes privileges.*/
            //sendf(-1, 1, "ri4", N_CURRENTMASTER, ci->clientnum, ci->clientnum >= 0 ? self->privilege : 0, mastermode);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Command variables incorrect or client is not connected/existant.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK cmd_cmd(p) {
        if(CMD_SA) {
            int lastcmd = -1;
            char command[50];

            sprintf(command, "%c%s", commandprefix, args[1]);
            if(strlen(command) > 0) {
                for(int i = 0; i < CMD_LAST; i++) {
                    if(!strcmp(CMD_NAME(i), command)) {
                        lastcmd = i;
                        break;
                    }
                }
            }

            if(CMD_SCI.privilege >= qs.getCommandPriv(lastcmd)) {
                if(lastcmd > -1) {
                    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(lastcmd));
                } else {
                    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Command not found. Use \f2\"#cmd\" \f3for a list of commands.");
                }
            } else {
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Insufficient permissions to view command info");
            }
        } else {
            static char colors[2], commandList[2056] = {0};
            int color = -1;

            strcpy(commandList, "");
            sprintf(commandList, "%s", "\f1Commands: ");

            for(int i = 0; i < CMD_LAST; i++) {
                if(CMD_PRIV(i) == PRIV_NONE) {
                    color = 4;
                } else if(CMD_PRIV(i) == PRIV_MASTER) {
                    color = 0;
                } else if(CMD_PRIV(i) == PRIV_ADMIN) {
                    color = 6;
                }

                sprintf(colors, "\f%d", color);
                strcat(commandList, colors);
                strcat(commandList, CMD_NAME(i));

                if(i != CMD_LAST-1) {
                    strcat(commandList, "\f7, ");
                }
            }
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, commandList);
        }
    }
    
    QSERV_CALLBACK localtime_cmd(p) {
        time_t rawtime;
        #include <stdio.h>      
        #include <time.h>
        struct tm * timeinfo;
        char buffer [80];
        
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        
        strftime (buffer,80,"\f4Local Time \f1%I:%M%p.",timeinfo);
        sendf(-1, 1, "ris", N_SERVMSG, buffer);
    }

    QSERV_CALLBACK time_cmd(p) {
        if(CMD_SA) {
            
            int zone = atoi(args[1]);

            time_t rawtime;
            struct tm *ztm;

            time(&rawtime);
            ztm = gmtime(&rawtime);

            //\n\f7Date: \f0%s, %s, %d, 20%d\n\f7Day of year: \f0%d
            defformatstring(msgtime)("\f7Time:\f0 %2d:%02d:%d",
                                     (ztm->tm_hour+zone)%24, ztm->tm_min, ztm->tm_sec);
                                     /*days[ztm->tm_wday-1],
                                     months[ztm->tm_mon], ztm->tm_mday, ztm->tm_year-100,
                                     ztm->tm_yday);*/
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, msgtime);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }

    QSERV_CALLBACK bunny_cmd(p) {
        if(strlen(fulltext) > 0) {
            
            defformatstring(msg)("%s \f0%s: \f7%s", bunny, "Tip", fulltext);
            sendf(-1, 1, "ris", N_SERVMSG, msg);
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }

    QSERV_CALLBACK owords_cmd(p) {
        char owordList[1024] = "Offensive words (words not to say): ";
        char colors[10];

        for(int i = 0; i < 50; i++) {
            if(strlen(owords[i]) > 0) {
                sprintf(colors, "\f%d", 3);
                strcat(owordList, colors);
                strcat(owordList, owords[i]);
                strcat(owordList, "\f2, ");
            }
        }
        owordList[strlen(owordList)-2] = '\0';
        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, owordList);
    }

     QSERV_CALLBACK stats_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    sendstats:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                            char *ip = toip(cn), lmsg[3][255], *location;

                            if(!strcmp("127.0.0.1", ip)) {
                                location = (char*)"localhost";
                            } else {
                                location = qs.congeoip(ip);

                                if(!location) {
                                    sprintf(lmsg[1], "%s", "Unknown Location");
                                }
                            }

                            if(location) sprintf(lmsg[1], "%s", location);
                            (CMD_SCI.privilege == PRIV_ADMIN) ? sprintf(lmsg[0], "%s (%s)", lmsg[1], ip) :
                                                             sprintf(lmsg[0], "%s", lmsg[1]);

                            int accuracy = (ci->state.damage*100)/max(ci->state.shotdamage, 1);
                            defformatstring(s)("\f4Stats for \f0%s: \f4Frags: \f0%i \f4Deaths: \f3%i \f4Teamkills: \f1%i \f4Flag Runs: \f2%i \f4Accuracy: \f3%i%%\n\f4Location: \f5%s",
                                                colorname(ci),
                                                ci->state.frags,
                                                ci->state.deaths,
                                                ci->state.teamkills/2,
                                                ci->state.flags,
                                                accuracy,
                                                lmsg[0]);
                            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, s);
                        }
                    } else {
                        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Player not connected");
                    }
                /*} else {
                    usage = true;
                }*/
            } else {
                usage = true;
            }
        } else {
            cn = CMD_SENDER;
            goto sendstats;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
	
                    
	QSERV_CALLBACK revokepriv_cmd(p) {
		int cn = -1;
	
        if(CMD_SA) {
			cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
				clientinfo *ci = qs.getClient(cn);
				clientinfo *cisender = qs.getClient(CMD_SENDER);
				
                if(ci != NULL) {
					if(ci->connected) {
						server::revokemaster(ci);
							
						defformatstring(msg)("Privileges have been revoked from the specified client \f3%s", colorname(ci));
						sendf(-1, 1, "ris", N_SERVMSG, msg);
						
						setmaster(ci, true, "", NULL, NULL, PRIV_NONE, true, false,
									true);

						//setmaster(clientinfo *ci, bool val, const char *pass = "", const char *authname = NULL, const char *authdesc = NULL, int authpriv = PRIV_MASTER, bool force = false, bool trial = false)
						//loopv(clients) if(ci!=clients[i] && clients[i]->privilege) {
						//	sendf(-1, 1, "ri2", N_CLIENT, clients[i]->privilege);
						//}
						
						/**packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
						putint(p, N_SERVMSG);
						sendstring(msg, p);
						putint(p, N_CURRENTMASTER);
						putint(p, mastermode);
						loopv(clients) if(clients[i]->privilege >= PRIV_MASTER)
						{
							putint(p, clients[i]->clientnum);
							putint(p, clients[i]->privilege);
						}
						putint(p, -1);
						sendpacket(-1, 1, p.finalize());*/
						//scheckpausegame();
					}
				} else {
					sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Player not connected");
                } 
			}
		} else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
}



