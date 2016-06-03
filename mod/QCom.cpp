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
        ncommand("help", "\f7View command list or command usage. \nUsage: #help for command list and #help <name-of-command> for usage", PRIV_NONE, help_cmd, 1);
        ncommand("me", "\f7Echo your name and message to everyone. Usage: #me <message>", PRIV_NONE, me_cmd, 0);
        ncommand("stats", "\f7View the stats of a player or yourself. Usage: #stats <cn> or #stats", PRIV_NONE, stats_cmd, 1);
        ncommand("localtime", "\f7Get the local time of the Server. Usage: #localtime", PRIV_NONE, localtime_cmd, 0);
        ncommand("getversion", "\f7Get the current QServ Version. Usage: #getversion", PRIV_NONE, getversion_cmd, 0);
        ncommand("uptime", "\f7View how long the server has been up for. Usage: #uptime", PRIV_NONE, uptime_cmd, 0);
        ncommand("invadmin", "\f7Claim invisible administrator. Usage: #invadmin <adminpass>", PRIV_NONE, invadmin_cmd, 1);
        ncommand("cheater", "\f7Accuses someone of cheating and alerts moderators. Usage: #cheater <cn>", PRIV_NONE, cheater_cmd, 1);
        ncommand("info", "\f7View information about a player. Usage: #info <cn>", PRIV_NONE, info_cmd, 1);
        ncommand("time", "\f7View the current time. Usage: #time", PRIV_NONE, time_cmd, 0);
        ncommand("pm", "\f7Send a private message to someone. Usage #pm <cn> <private message>", PRIV_NONE, pm_cmd,2);
        ncommand("callops", "\f7Call all operators on the Internet Relay Chat Server. Usage: #callops", PRIV_NONE, callops_cmd, 0);
        ncommand("mapsucks", "\f7Votes for an intermission to change the map. Usage: #mapsucks", PRIV_NONE, mapsucks_cmd, 0);
        ncommand("forgive", "\f7Forgive a player for teamkilling or just in general. Usage: #forgive <cn>", PRIV_NONE, forgive_cmd, 1);
        ncommand("forceintermission", "\f7Force an intermission. Usage: #forceintermission", PRIV_MASTER, forceintermission_cmd, 0);
        ncommand("echo", "\f7Broadcast a message to all players. Usage: #echo <message>", PRIV_MASTER, echo_cmd, 1);
        ncommand("sendprivs", "\f7Share power with another player. Usage: #sendprivs <cn>", PRIV_MASTER, sendprivs_cmd, 1);
        //ncommand("tournament", "\f7Forces a tournament regardless of mode/etc. Usage: #tournament <mode> <map>", PRIV_MASTER, tournament_cmd, 2);
        ncommand("bunny", "\f7Broadcast a helper message to all players. Usage: #bunny <helpmessage>", PRIV_ADMIN, bunny_cmd, 0);
		ncommand("revokepriv", "\f7Revoke the privileges of a player. Usage: #revokepriv <cn>", PRIV_ADMIN, revokepriv_cmd, 1);
        ncommand("forcespectator", "\f7Forces a player to become a spectator. Usage: #forcespectator <cn>", PRIV_ADMIN, forcespectator_cmd, 1);
        ncommand("unspectate", "\f7Removes a player from spectator mode. Usage: #unspectate <cn>", PRIV_ADMIN, unspectate_cmd, 1);
        ncommand("mute", "\f7Mutes a client. Usage #mute <cn>", PRIV_ADMIN, mute_cmd, 1);
        ncommand("unmute", "\f7Unmutes a client. Usage #mute <cn>", PRIV_ADMIN, unmute_cmd, 1);
        ncommand("editmute", "\f7Stops a client from editing. Usage #editmute <cn>", PRIV_ADMIN, editmute_cmd, 1);
        ncommand("uneditmute", "\f7Allows a client to edit again. Usage #uneditmute <cn>", PRIV_ADMIN, uneditmute_cmd, 1);
        ncommand("togglelockspec", "\f7Forces a client to be locked in spectator mode. Usage #togglelockspec <cn>", PRIV_ADMIN, togglelockspec_cmd, 1);
        ncommand("gban", "\f7Bans a client. Usage: #gban <cn>", PRIV_ADMIN, gban_cmd, 1);
        ncommand("cleargbans", "\f7Clears all server bans stored and issued. Usage: #cleargbans", PRIV_ADMIN, cleargbans_cmd, 0);
        ncommand("teampersist", "\f7Toggle persistant teams on or off. Usage: #teampersist <0/1> (0 for off, 1 for on)", PRIV_ADMIN, teampersist_cmd, 1);
        ncommand("allowmaster", "\f7Allows clients to claim master. Usage: #allowmaster <0/1> (0 for off, 1 for on)", PRIV_ADMIN, allowmaster_cmd, 1);
        ncommand("kill", "\f7Brutally murders a player. Usage: #kill <cn>", PRIV_ADMIN, kill_cmd, 1);
        //ncommand("owords", "View list of offensive words. Usage: #owords",PRIV_NONE, owords_cmd, 0);
        //ncommand("olangfilter", "Turn the offensive language filter on or off. Usage: #olang <off/on> (0/1) and #olang to see if it's activated", PRIV_MASTER, olangfilter_cmd, 1);
    }
    QSERV_CALLBACK teampersist_cmd(p) {
        bool usage = false;
        int togglenum = -1;
        if(CMD_SA) {
            togglenum = atoi(args[1]);
            if(togglenum >= 0 && togglenum <= 1000) {
                //if(!isalpha(cn)) {
                teampersistprocess:
				//int togglenum = atoi(args[1]);
        			if(togglenum==1) {
            			persist = true;
            			clientinfo *ci = qs.getClient(CMD_SENDER);
            			out(ECHO_SERV, "\f7Persistant teams are now \f0enabled");
            			
        			}
        			else if(togglenum==0) {
            			persist = false;
            			out(ECHO_SERV, "\f7Persistant teams are now \f3disabled");
        			}
        	        else if(togglenum==NULL || isalpha(togglenum)) {
        				sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        			}
            } else {
                usage = true;
          }
        } else {
            togglenum = CMD_SENDER;
            goto teampersistprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
     extern void suicide(clientinfo *ci);
     QSERV_CALLBACK kill_cmd(p) {
        bool usage = false;
        int cn = -1;
        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    killprocess:
                    clientinfo *ci = qs.getClient(cn);
                    if(ci != NULL) {
                        if(ci->connected) {
                         	if(cn!=CMD_SENDER && !isalpha(cn) && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL && cn!=CMD_SENDER) {
            				clientinfo *ci = qs.getClient(cn);
            				clientinfo *sender = qs.getClient(CMD_SENDER);
           		 				if(ci->state.state==CS_ALIVE) {
            						suicide(ci);
            						out(ECHO_SERV, "\f0%s \f7has been brutally murdered", colorname(ci));
            						out(ECHO_NOCOLOR, "%s has been brutally murdered by %s", colorname(ci), colorname(sender));
            					}   
                        	}
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
            goto killprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }

      QSERV_CALLBACK allowmaster_cmd(p) {
        bool usage = false;
        int togglenum = -1;
        if(CMD_SA) {
            togglenum = atoi(args[1]);
            if(togglenum >= 0 && togglenum <= 1000) {
                //if(!isalpha(cn)) {
                allowtmaster:
				//int togglenum = atoi(args[1]);
        			if(togglenum==1) {
            			switchallowmaster();
            			clientinfo *ci = qs.getClient(CMD_SENDER);
            			out(ECHO_SERV, "\f7Claiming \f0master \f7with \"/setmaster 1\" is now \f0enabled");
        			}
        			else if(togglenum==0) {
            			switchdisallowmaster();
            			out(ECHO_SERV, "\f7Claiming \f0master \f7with \"/setmaster 1\" is now \f3disabled");
        			}
        	        else if(togglenum==NULL || isalpha(togglenum)) {
        				sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        			}
            } else {
                usage = true;
          }
        } else {
            togglenum = CMD_SENDER;
            goto allowtmaster;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    SVAR(invadminpass, "");
    QSERV_CALLBACK invadmin_cmd(p) {
        if(CMD_SA) {
            clientinfo *ci = qs.getClient(CMD_SENDER);
            if(!strcmp(invadminpass, args[1]) || invadminpass == args[1]) {
                server::setmaster(ci, 0, "", NULL, NULL,PRIV_MASTER,false, false, true);
                ci->privilege = PRIV_ADMIN;
                sendf(ci->clientnum, 1, "ris", N_SERVMSG, "Invisible \f6admin \f7activated");
                out(ECHO_IRC, "%s became an invisible admin", colorname(ci));
                out(ECHO_CONSOLE, "%s became an invisible admin", colorname(ci));
            }
            else sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3Error: Incorrect admin password");
        }
    }
        
    QSERV_CALLBACK cleargbans_cmd(p) {
        server::cleargbans(-1);
        out(ECHO_SERV, "Cleared permanent game bans");
        out(ECHO_NOCOLOR, "[NOTICE]: You need to use clearpbans in server-init.cfg to unban users, uncomment out the line and restart the server");
    }
    
    QSERV_CALLBACK gban_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    gbanprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        
                        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL && cn!=CMD_SENDER) {
            				clientinfo *ci = qs.getClient(cn);
            				disconnect_client(ci->clientnum, DISC_IPBAN);
            				server::addgban(1, ci->ip);
           					 out(ECHO_SERV, "\f0%s \f7has been added to the permanent banlist.", colorname(ci));
            				out(ECHO_NOCOLOR, "%s has been added to the permanent banlist.", colorname(ci));
        				}
                        
                           
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
            goto gbanprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
   
    VAR(votestopassmapsucks, 2, 10, INT_MAX);
    int mapsucksvotes = 0;
    QSERV_CALLBACK mapsucks_cmd(p) {
        clientinfo *ci = qs.getClient(CMD_SENDER);
        
        if(!ci->votedmapsucks) {
            mapsucksvotes++;
            out(ECHO_SERV, "\f0%s \f7thinks this map sucks, use \f2#mapsucks \f7to vote for an intermission to skip it.", colorname(ci));
            ci->votedmapsucks = true;
            
            if(mapsucksvotes>=getvar("votestopassmapsucks")) {
                startintermission();
                out(ECHO_SERV, "\f7Changing map: That map sucked (\f7%d \f7votes to skip)", votestopassmapsucks);
                
                while(mapsucksvotes>=getvar("votestopassmapsucks")) {
                    mapsucksvotes--;
                    mapsucksvotes--;
                    mapsucksvotes--;
                    out(ECHO_SERV,"\f7Clearing votes...");
                }
            }
        }
        else if(ci->votedmapsucks) sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f3Error: You have already voted");
    }
    
    /*    
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
        for(int i = 0; i <= mc; i++)  {
            if(!strcmp(mn, qserv_modenames[i]))  {
                gm = i;
                // use other list to send full name of mode
                changemap(mapname, gm);
                valid = true;
                break;
            }
        }
        	if(valid) {
            defformatstring(f)("\f7Tournament has started: %s on map %s", qserv_modenames[gm], mapname);
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
    */
    
    QSERV_CALLBACK uptime_cmd(p) {
        clientinfo *ci = qs.getClient(CMD_SENDER);
        string msg, buf;
        uint t, months, weeks, days, hours, minutes, seconds;
        copystring(msg,"\f7Server Mod: \f3QServ\f7: \f1https://github.com/deathstar/QServCollect");
        sendf(ci ? ci->clientnum : -1, 1, "ris", N_SERVMSG, msg);
        copystring(msg, "\f7Server Architecture: \f0"
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
        concatstring(msg, "\n\f7Server Uptime:\f6");
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

     QSERV_CALLBACK info_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    sendinfo:
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
                            int connectedtime = totalsecs;
        					string conmsg, buf;
       						uint t, months, weeks, days, hours, minutes, seconds; 
        					t = (int) connectedtime;
        					copystring(conmsg, "\f7Server has been up for:\f6");
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
            concatstring(conmsg, buf);
        }
        
        if(weeks)
        { 
            formatstring(buf)(" %u week%s", weeks, weeks > 1 ? "s" : "");
            concatstring(conmsg, buf);  
        }

        if(days)
        {
            formatstring(buf)(" %u day%s", days, days > 1 ? "s" : "");
            concatstring(conmsg, buf);
        }
        
        if(hours)  
        { 
            formatstring(buf)(" %u hour%s", hours, hours > 1 ? "s" : "");
            concatstring(conmsg, buf);  
        }
          
        if(minutes)   
        {
            formatstring(buf)(" %u minute%s", minutes, minutes > 1 ? "s" : "");
            concatstring(conmsg, buf);  
        }
        
        if(seconds)
        {
            formatstring(buf)(" %u second%s", seconds, seconds > 1 ? "s" : "");
            concatstring(conmsg, buf);    
        }
                            defformatstring(s)("\f7Info for \f0%s \f7(\f7%d\f7): \f7Frags: \f0%i \f7Deaths: \f3%i \f7Teamkills: \f1%i \f7Flag Runs: \f5%i \f7Accuracy: \f3%i%%\n\f7Location: \f2%s",
                                                colorname(ci),
                                                ci->clientnum,
                                                (ci->state.frags)-(ci->state.teamkills/2),
                                                ci->state.deaths,
                                                ci->state.teamkills/2,
                                                ci->state.flags,
                                                accuracy,
                                                lmsg[0]);
                            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, s);
                            sendf(CMD_SENDER,1,"ris", N_SERVMSG, conmsg);
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
            goto sendinfo;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    extern void forcespectator(clientinfo *ci);
    extern void unspectate(clientinfo *ci);
     QSERV_CALLBACK togglelockspec_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    lockspecprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        
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
            goto lockspecprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
      QSERV_CALLBACK forcespectator_cmd(p) {
        bool usage = false;
        int cn = -1;
        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    forcespectatorprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                                if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
        						clientinfo *ci = qs.getClient(cn);
        						forcespectator(ci);
        				}				

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
            goto forcespectatorprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    QSERV_CALLBACK unspectate_cmd(p) {
        bool usage = false;
        int cn = -1;
        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    unspectateprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        	if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
        						clientinfo *ci = qs.getClient(cn);
       						    unspectate(ci);
        				}

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
            goto unspectateprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    QSERV_CALLBACK mute_cmd(p) {
        bool usage = false;
        int cn = -1;
        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    muteprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        	if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            					ci->isMuted = true;
            					defformatstring(mutemsg)("\f0%s \f7has been \f3muted", colorname(ci));
            					sendf(CMD_SENDER, 1, "ris", N_SERVMSG, mutemsg);
        					}
                        }
                    }
                /*} else {
                    usage = true;
                }*/
            } else {
                usage = true;
            }
        } else {
            cn = CMD_SENDER;
            goto muteprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
     QSERV_CALLBACK unmute_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    unmuteprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        	if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            					ci->isMuted = false;
            					defformatstring(unmutemsg)("\f0%s \f7has been \f0unmuted", colorname(ci));
           						 sendf(CMD_SENDER, 1, "ris", N_SERVMSG, unmutemsg);
        					}
							
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
            goto unmuteprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }

	QSERV_CALLBACK editmute_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    editmuteprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        	 if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            					ci->isEditMuted = true;
            					sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f7Your edits \f3will not \f7show up to others.");
           					    defformatstring(mutemsg)("\f0%s\f7's edits have been \f3muted", colorname(ci));
            					sendf(CMD_SENDER, 1, "ris", N_SERVMSG, mutemsg);
       						 }
                                                   
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
            goto editmuteprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    QSERV_CALLBACK uneditmute_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    uneditmuteprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        
                        	if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            					sendf(ci->clientnum, 1, "ris", N_SERVMSG, "\f7Your edits \f0will \f7now show up to others.");
            					ci->isEditMuted = false;
            					out(ECHO_SERV,"\f0%s\f7's edits have been \f0unmuted", colorname(ci));
        					}                         
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
            goto uneditmuteprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    QSERV_CALLBACK forgive_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    forgiveprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        	clientinfo *self = qs.getClient(CMD_SENDER);
        					if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            				defformatstring(forgivemsg)("\f0%s \f7has forgiven \f3%s", colorname(self), colorname(ci));
            				sendf(-1, 1, "ris", N_SERVMSG, forgivemsg);
        			}
                            
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
            goto forgiveprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
    }
    
    SVAR(ircoperators, "");
     QSERV_CALLBACK cheater_cmd(p) {
        bool usage = false;
        int cn = -1;

        if(CMD_SA) {
            cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
                //if(!isalpha(cn)) {
                    cheaterprocess:
                    clientinfo *ci = qs.getClient(cn);

                    if(ci != NULL) {
                        if(ci->connected) {
                        
                        clientinfo *self = qs.getClient(CMD_SENDER);
        				if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && cn != NULL && ci != NULL && ci->connected && args[1]!=NULL) {
        				int accuracy = (ci->state.damage*100)/max(ci->state.shotdamage, 1);
            			privilegemsg(PRIV_MASTER,"\f7Something's fishy! A cheater has been reported.");
             			out(ECHO_SERV, "\f0%s \f7accuses \f3%s \f7(CN: \f6%d \f7| Accuracy: \f6%d%\f7) of cheating.", colorname(self), colorname(ci), ci->clientnum, accuracy);
            			out(ECHO_NOCOLOR, "Attention Operator(s): %s - %s accuses %s (CN: %d | Accuracy: %d%) of cheating.", ircoperators, colorname(self), colorname(ci), ci->clientnum, accuracy);
            			defformatstring(nocolorcheatermsg)("\f3%s \f7has been reported.", colorname(ci));
            			sendf(CMD_SENDER, 1, "ris", N_SERVMSG, nocolorcheatermsg);
        			}		
                           
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
            goto cheaterprocess;
        }

        if(usage) sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
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
        else {defformatstring(operatorunavailable)("\f7Sorry, No operators are available currently. \nEmail: \f1%s \f7for more assistance.",contactemail); sendf(CMD_SENDER, 1, "ris", N_SERVMSG, operatorunavailable);}
    }
    SVAR(qserv_version, "");
    QSERV_CALLBACK getversion_cmd(p) {
    defformatstring(ver)("\f7Running \f3QServ \f7(\f2%s\f7): \f1www.github.com/deathstar/QServCollect", qserv_version);
    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, ver);
    }
    QSERV_CALLBACK forceintermission_cmd(p) {bool intermission = false; if(!intermission){startintermission(); defformatstring(msg)("\f0%s \f7forced an intermission",CMD_SCI.name);sendf(-1, 1, "ris", N_SERVMSG, msg); out(ECHO_IRC,"%s forced an intermission",CMD_SCI.name);}}

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
    
    QSERV_CALLBACK pm_cmd(p) {
        int cn = -1;
        if(args[1] != NULL && strlen(fulltext) > 0) {
            cn = atoi(args[1]);
            clientinfo *ci = qs.getClient(cn);
            if(strlen(fulltext) > 0 && cn!=CMD_SENDER && ci != NULL && cn >= 0 && cn <= 128 && args[1] != NULL) {
                clientinfo *self = qs.getClient(CMD_SENDER);
                if(strlen(fulltext) > 0 && ci->connected && args[1] != NULL && ci != NULL) {
                    defformatstring(recieverpmmsg)("\f7Private message from \f0%s\f7: \f3%s", colorname(self), fulltext);
                    sendf(cn, 1, "ris", N_SERVMSG, recieverpmmsg);
                    defformatstring(senderpmconf)("\f7Sent \f0%s \f7your message: \f3%s", colorname(ci), fulltext);
                    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, senderpmconf);
                }
            }
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    
    QSERV_CALLBACK sendprivs_cmd(p) {
		int cn = -1;
        if(CMD_SA) {
			cn = atoi(args[1]);
            if(cn >= 0 && cn <= 1000) {
				clientinfo *ci = qs.getClient(cn);
				clientinfo *self = qs.getClient(CMD_SENDER);
				
                if(ci != NULL) {
					if(ci->connected) {
					   defformatstring(shareprivsmsg)("\f7Ok, %s\f7. Sharing your privileges with \f0%s\f7. They now have invisible privileges.", colorname(self), colorname(ci));
            		   sendf(CMD_SENDER, 1, "ris", N_SERVMSG, shareprivsmsg);
                       if(self->privilege==PRIV_MASTER) {
                       defformatstring(sendprivsmsg)("\f7You have received invisible \f0master \f7from \f0%s\f7. Relinquish and reclaim to reveal your privileges.", colorname(self));
                       sendf(cn, 1, "ris", N_SERVMSG, sendprivsmsg);
                       ci->privilege=PRIV_MASTER;
                	   self->privilege=PRIV_MASTER;
            		   }
            		   else if(self->privilege==PRIV_ADMIN) {
                       defformatstring(sendprivsmsg)("\f7You have received invisible \f6admin \f7from \f6%s\f7. Relinquish and reclaim to reveal your privileges.", colorname(self));
                       sendf(cn, 1, "ris", N_SERVMSG, sendprivsmsg);
                       ci->privilege=PRIV_ADMIN;
                       self->privilege=PRIV_ADMIN;
                       }

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
    
    QSERV_CALLBACK help_cmd(p) {
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
                    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Command not found. \nUse \f2\"#help\" \f3for a list of commands or \f2\"#help <name-ofcommand>\" \f3for usage.");
                }
            } else {
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Insufficient permissions to view command info");
            }
        } else {
            static char colors[2], commandList[2056] = {0};
            int color = -1;
            strcpy(commandList, "");
            clientinfo *ci = qs.getClient(CMD_SENDER);
            if(ci->privilege==PRIV_ADMIN) {
                sprintf(commandList, "%s", "\f2Commands: \f6");
                for(int i = 0; i < CMD_LAST; i++) {
                    if(CMD_PRIV(i) == PRIV_ADMIN || CMD_PRIV(i) == PRIV_MASTER || CMD_PRIV(i) == PRIV_NONE) {
                        strcat(commandList, CMD_NAME(i));
                        if(i != CMD_LAST-1) {
                            strcat(commandList, " ");
                        }
                    }
                }
            }
            else if(ci->privilege==PRIV_MASTER) {
                sprintf(commandList, "%s", "\f2Commands: \f0");
                for(int i = 0; i < CMD_LAST; i++) {
                    if(CMD_PRIV(i) == PRIV_MASTER || CMD_PRIV(i) == PRIV_NONE) {
                        strcat(commandList, CMD_NAME(i));
                        if(i != CMD_LAST-1) {
                            strcat(commandList, " ");
                        }
                    }
                }
            }
            else if(ci->privilege==PRIV_NONE) {
                sprintf(commandList, "%s", "\f2Commands: \f7");
                for(int i = 0; i < CMD_LAST; i++) {
                    if(CMD_PRIV(i) == PRIV_NONE) {
                        strcat(commandList, CMD_NAME(i));
                        if(i != CMD_LAST-1) {
                            strcat(commandList, " ");
                        }
                    }
                }
                
                /*for(int i = 0; i < CMD_LAST; i++) {
                 if(CMD_PRIV(i) == PRIV_NONE) {
                 color = 7;
                 } else if(CMD_PRIV(i) == PRIV_MASTER) {
                 color = 0;
                 } else if(CMD_PRIV(i) == PRIV_ADMIN) {
                 color = 6;
                 }
                 sprintf(colors, "\f%d", color);
                 strcat(commandList, colors);
                 //strcat(commandList, CMD_NAME(i));
                 }
                 */
            }
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, commandList);
        }
    }
    
    QSERV_CALLBACK localtime_cmd(p) {
    #include <stdio.h>
    #include <time.h>
        struct tm newtime;
        time_t ltime;
        char buf[50];
        ltime=time(&ltime);
        localtime_r(&ltime, &newtime); //localtime__r and asctime_r are both threadsafe
        defformatstring(buffer)("\f4The local date and time is \f1%s", asctime_r(&newtime, buf));
        sendf(-1, 1, "ris", N_SERVMSG, buffer);
    }
    
    #define EST (-4)
    #define CCT (+8)
    #define PST (-7)
    #define ENGLAND (+1)
    #define GERMANY (+2)
    QSERV_CALLBACK time_cmd(p) {
        time_t rawtime;
        struct tm * ptm;
        time ( &rawtime );
        ptm = gmtime (&rawtime); //threadsafe implementation (gmtime_r) causes segfault on mass_spam
        char pst = (ptm->tm_hour+PST)%24;
        char est = (ptm->tm_hour+EST)%24;
        char cct = (ptm->tm_hour+CCT)%24;
        char uk = (ptm->tm_hour+ENGLAND)%24;
        char de = (ptm->tm_hour+GERMANY)%24;
        out(ECHO_SERV, "Los Angeles (U.S./PST): \f2%2d:%02d", pst, ptm->tm_min);
        out(ECHO_SERV, "New York, NY (U.S./EST): \f2%2d:%02d", est, ptm->tm_min);
        out(ECHO_SERV, "Beijing (China/CCT): \f2%2d:%02d", cct, ptm->tm_min);
        out(ECHO_SERV, "England (GMT+1): \f2%2d:%02d", uk, ptm->tm_min);
        out(ECHO_SERV, "Germany (GMT+2): \f2%2d:%02d", de, ptm->tm_min);
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
                            defformatstring(s)("\f7Stats for \f0%s: \f7Frags: \f0%i \f7Deaths: \f3%i \f7Teamkills: \f1%i \f7Flag Runs: \f5%i \f7Accuracy: \f3%i%%\n\f7Location: \f2%s",
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



