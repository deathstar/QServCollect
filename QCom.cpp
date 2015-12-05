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

        ncommand("me", "\f4Echo your name and message to everyone. Usage: #me <message>",
                 PRIV_NONE, me_cmd, 0);
        ncommand("cmd", "\f4View command list or command usage. Usage: #cmd for command list and #cmd <commandname> for command usage",
                 PRIV_NONE, cmd_cmd, 1);
        ncommand("stats", "\f4View the stats of a player. Usage: #stats <cn>",
                 PRIV_NONE, stats_cmd, 1);
        ncommand("localtime", "\f4Get the local time of the Server. Usage: #localtime",
                 PRIV_NONE, localtime_cmd, 0);
        ncommand("time", "\f4View time. Usage: #time <zone>",
                 PRIV_NONE, time_cmd, 1);
        ncommand("bunny", "\f4Broadcast a helper message to all players. Usage: #bunny <helpmessage>",
                 PRIV_ADMIN, bunny_cmd, 0);
        ncommand("echo", "\f4Broadcast a message to all players. Usage: #echo <message>",
                 PRIV_MASTER, echo_cmd, 1);
		ncommand("revokepriv", "\f4Revoke the privileges of a player. Usage: #revokepriv <cn>",
				PRIV_ADMIN, revokepriv_cmd, 1);
        ncommand("forceintermission", "\f4Force an intermission. Usage: #forceintermission",
                 PRIV_MASTER, forceintermission_cmd, 0);
        ncommand("getversion", "\f4Get the current QServ Version. Usage: #getversion",
                 PRIV_NONE, getversion_cmd, 0);
        ncommand("callops", "\f4Call all operators on the Internet Relay Chat Server. Usage: #callops",
                 PRIV_NONE, callops_cmd, 0);
        ncommand("msg", "\f4Send a private message. Usage #msg <cn> <msg>", PRIV_NONE, msg_cmd,2);
        ncommand("sendprivs", "\f4Share power with another player. Usage: #sendprivs <cn>",
                 PRIV_ADMIN, sendprivs_cmd, 1);
        ncommand("forgive", "\f4Forgive a player for teamkilling or just in general. Usage: #forgive <cn>",
                 PRIV_NONE, forgive_cmd, 1);
        ncommand("forcespectator", "\f4Forces a player to become a spectator. Usage: #forcespectator <cn>", PRIV_ADMIN, forcespectator_cmd, 0);
        ncommand("mute", "\f4Mutes a client. Usage #mute <cn>", PRIV_ADMIN, mute_cmd, 1);
        ncommand("unmute", "\f4Unmutes a client. Usage #mute <cn>", PRIV_ADMIN, unmute_cmd, 1);
        ncommand("togglelockspec", "\f4Forces a client to be locked in spectator mode. Usage #togglelockspec <cn>", PRIV_ADMIN, togglelockspec_cmd, 1);
        ncommand("uptime", "\f4View how long the server has been up for. Usage: #uptime", PRIV_NONE, uptime_cmd, 0);
        ncommand("info", "\f4View information about a player. Usage: #info <cn>", PRIV_NONE, info_cmd, 0);
        ncommand("tournament", "\f4Start a tournament with a timer. Usage: #tournament <mode> <map> ", PRIV_MASTER, tournament_cmd, 2);
        //ncommand("owords", "View list of offensive words. Usage: #owords",
        ///         PRIV_NONE, owords_cmd, 0);
        //ncommand("olangfilter", "Turn the offensive language filter on or off. Usage: #olang <off/on> (0/1) and #olang to see if it's activated",
        //         PRIV_MASTER, olangfilter_cmd, 1);
    }
    
    // restrict modes certain modes only for a tournament, not coop etc.
    char *qserv_modenames[] = {
        "ffa",
        "coop", "teamplay", "insta", "instateam", "effic",
        "efficteam", "tactics", "tacticsteam", "capture",
        "refencapture", "ctf", "instactf", "efficctf", "protect",
        "instaprotect", "efficprotect", "hold", "instahold", "effichold",
        "collect", "instacollect", "efficcollect"
    }; // custom mode names remember to type them like this if you want that mode
    
    int mc = 22;
    
    
    
    extern void changemap(const char *s, int mode);
    extern void pausegame(bool val, clientinfo *ci = NULL);
    
    
    
    int t_timer() {
        int ct = 0;
        
        while(ct > 10000) {
            for(int i = 10; i >= 0; i--) {
                out(ECHO_SERV, "Tournament starting in %d seconds", i);
            }
            
            ct--;
        }
    }

    
    QSERV_CALLBACK tournament_cmd(p) {
        t_timer();
        
        //pausegame(true);
        
        /*const char *mapname = args[2];
        char *mn = args[1];
        if(args[1] != NULL && args[2] != NULL) {
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
            pausegame(false);
            defformatstring(f)("\f4Tournament has started: %s on map %s", qserv_modenames[gm], mapname);
            sendf(-1, 1, "ris", N_SERVMSG, f);
            
        if(!valid) sendf(-1, 1, "ris", N_SERVMSG, "\f7Error: Unknown mode");
        }
        else {
            defformatstring(f)("\f3Error: \f4Invalid mode/mapname provided.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, f);
        }*/
    }
    
    
    int servuptime = 0;
    QSERV_CALLBACK uptime_cmd(p) {
             //broken 
             clientinfo *ci = qs.getClient(CMD_SENDER);
             ci->connectedmillis=(gamemillis/1000)+servuptime-(ci->connectedmillis/1000);
             int ssstime = gamemillis+servuptime;
             int sssdays = ssstime/86400000, sssdaysms=sssdays*86400000;
             int ssshours = (ssstime-sssdaysms)/3600000, ssshoursms=ssshours*3600000;
             int sssminutes = (ssstime-sssdaysms-ssshoursms)/60000;
             int sssseconds = (ssstime-sssdaysms-ssshoursms-sssminutes*60000)/1000;
        
            defformatstring(f)("\f4Server Uptime: \f6%d \f2Day(s)\f4, \f6%d \f2Hour(s)\f4, \f6%d \f2Minute(s)\f4, \f6%d \f2Second(s)", sssdays, ssshours, sssminutes, sssseconds);
            sendf(ci->clientnum, 1, "ris", N_SERVMSG, f);
        
    }
    //Check to see if args 1 is blank, if not causes seg fault on linux when #info is issued
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
                        int milisec = (ci->connectmillis);
                        int sec = (ci->connectmillis/1000);
                        int min = (sec / 60) % 60;
                        defformatstring(s)("\f0%s \f4(\f2%d\f4) [\f1%s\f4] \f4connected for %d minutes %d sec", colorname(ci), ci->clientnum, lmsg[0], min, sec);
                        sendf(CMD_SENDER, 1, "ris", N_SERVMSG, s);
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
    QSERV_CALLBACK mute_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        if(cn!=CMD_SENDER && cn >= 0 && cn <= 1000 && ci != NULL && ci->connected && args[1] != NULL) {
            ci->isMuted = true;
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f0%s \f4has been \f3muted", colorname(ci));

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
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f0%s \f4has been \f0unmuted", colorname(ci));
        }
        else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: \f4Incorrect client number/no cn specified or you're trying to mute yourself.");
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
    // Needs handlers
    QSERV_CALLBACK forcespectator_cmd(p) {
        int cn = atoi(args[1]);
        clientinfo *ci = qs.getClient(cn);
        forcespectator(ci);
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
    SVAR(operators, "");
    QSERV_CALLBACK callops_cmd(p) {VAR(ircignore, 0, 0, 1);if(!getvar("ircignore")) {out(ECHO_IRC, "[Attention operator(s)]: %s: %s is in need of assistance.", operators, CMD_SCI.name); defformatstring(toclient)("You alerted operator(s) %s", irc.lastmsg()->nick); sendf(CMD_SENDER, 1, "ris", N_SERVMSG, toclient);}}
    QSERV_CALLBACK getversion_cmd(p) {
        defformatstring(ver)("\f4Running \f4QServ 11 \f0Collect Edition Beta\f4. Written by Mamasita, DeathStar & Jonlimle.");sendf(CMD_SENDER, 1, "ris", N_SERVMSG, ver);}
    QSERV_CALLBACK forceintermission_cmd(p) {startintermission(); defformatstring(msg)("\f0%s \f4forced an intermission",CMD_SCI.name);sendf(-1, 1, "ris", N_SERVMSG, msg);}

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
                defformatstring(recieverpmmsg)("\f4Private message from \f0%s\f4: \f3%s", colorname(self), fulltext);
                sendf(cn, 1, "ris", N_SERVMSG, recieverpmmsg);
                defformatstring(senderpmconf)("\f4Sent \f0%s \f4your message: \f3%s", colorname(ci), fulltext);
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
            defformatstring(shareprivsmsg)("\f4Ok, %s\f4. Sharing your privileges with \f0%s\f4.", colorname(self), colorname(ci));
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, shareprivsmsg);
            defformatstring(sendprivsmsg)("\f4You have recieved privileges from \f0%s\f4.", colorname(self));
            sendf(cn, 1, "ris", N_SERVMSG, sendprivsmsg);
            if(self->privilege==PRIV_MASTER) {
                ci->privilege=PRIV_MASTER;
            }
            else if(self->privilege==PRIV_ADMIN) {
                ci->privilege=PRIV_ADMIN;
            }
            /*The commented code calls the actual master change message and changes the color of the player, above just changes privileges.
            currentmaster = ci->clientnum;
            sendf(-1, 1, "ri4", N_CURRENTMASTER, currentmaster, currentmaster >= 0 ? cn->privilege : 0, mastermode);*/
        } else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Command variables incorrect or client is not connected/existant.");
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
                    sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Command not found");
                }
            } else {
                sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "\f3Error: Insufficient permissions to view command info");
            }
        } else {
            static char colors[2], commandList[2056] = {0};
            int color = -1;

            strcpy(commandList, "");
            sprintf(commandList, "%s", "\f4Commands: ");

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
                            defformatstring(s)("Stats for \f0%s: \f4Frags: \f0%i \f4Deaths: \f3%i \f4Teamkills: \f1%i \f4Flag Runs: \f2%i \f4Accuracy: \f3%i%%\n\f4Location: \f5%s",
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
					sendf(CMD_SENDER, 1, "ris", N_SERVMSG, "Played not connected");
                } 
			}
		} else {
            sendf(CMD_SENDER, 1, "ris", N_SERVMSG, CMD_DESC(cid));
        }
    }
}



