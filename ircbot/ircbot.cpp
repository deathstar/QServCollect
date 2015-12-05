//#include "game.h"
#ifndef WIN32
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#endif
#include "ircbot.h"


SVAR(irchost, "irc.gamesurge.net");
VAR(ircport, 0, 6667, 65535);
VAR(ircignore, 0, 0, 1);
SVAR(ircchan, "#QServ");
SVAR(ircbotname, "QServ");
//#include "game.h"
//#include "ircbot.h"

SVAR(ircloginpass, "changeme");

ICOMMAND(login, "s", (char *s), {
    if(isloggedin(0)){
        irc.notice(irc.lastmsg()->nick, "You are already logged in!");
        return;
    }if(!strcmp(s, ircloginpass)){
        irc.IRCusers[irc.lastmsg()->host] = 1;
        irc.speak("%s has logged in", irc.lastmsg()->nick);
		out(ECHO_SERV, "\f0%s \f7has logged in thru IRC (\f4%s \f3%s\f7)", irc.lastmsg()->nick, irchost, ircchan);
    }
    else irc.notice(irc.lastmsg()->nick, "Invalid Password");
});

ICOMMAND(clearbans, "", (), {
	if(isloggedin()) {
        N_CLEARBANS;
        out(ECHO_SERV, "Server bans \f0cleared");
        out(ECHO_CONSOLE, "Server bans cleared");
        out(ECHO_IRC, "All bans cleared");
	}
});

/*ICOMMAND(doscript, "s", (char *s), {
    if(isloggedin()){
        if(fileexists(s, "r"))
            //luaL_dofile(luavm.getState(), s);
        else irc.notice(irc.lastmsg()->nick, "Invalid Script Name");
    }
});*/

ICOMMAND(join, "s", (char *s), {
    if(isloggedin())
        irc.join(s);
});

ICOMMAND(part, "s", (char *s), {
    if(isloggedin())
        irc.part(s);
});

ICOMMAND(kick, "i", (int *i), {
    if(isloggedin())
        disconnect_client(*i, DISC_KICK);
});

/*ICOMMAND(kick, "i", (int *i), {
    if(isloggedin())
        server::banPlayer(*i);
});*/

ircBot irc;

bool isloggedin(bool echo)
{
    /*for(int i = 0; i < irc.IRCusers.size(); i++)
    {
            if(!strcmp(irc.IRCusers[i], irc.lastmsg()->host))
                return true;
    }*/
    if(irc.IRCusers.access(irc.lastmsg()->host))
        return true;
    if(echo)
        irc.notice(irc.lastmsg()->nick, "Insufficient Priveleges");
    return false;
}

bool ircBot::IsCommand(char *buff)
{
    if(!checkping(buff))
    {
        ParseMessage(buff);
        if(msg.message[0] == '#' || msg.message[0] == '@')
        {
            char *c = msg.message;
            c++;
            conoutf(c);
            execute(c);
            return true;
        }return false;
    }return true;
}

int ircBot::getSock()
{
    return sock;
}

int ircBot::speak(const char *fmt, ...){
    char Amsg[1000], k[1000];
    va_list list;
    va_start(list,fmt);
    vsnprintf(k,1000,fmt,list);
    snprintf(Amsg,1000,"PRIVMSG %s :%s\r\n", ircchan, k);
    va_end(list);
	
    return send(sock,Amsg,strlen(Amsg),0);
}

IrcMsg *ircBot::lastmsg(){
    return &msg;
}
void ircBot::join(char *channel){
    defformatstring(joinchan)("JOIN %s\r\n", channel);
    send(sock,joinchan,strlen(joinchan),0);
}

void ircBot::part(char *channel){
    defformatstring(partchan)("PART %s\r\n", channel);
    send(sock,partchan,strlen(partchan),0);
}

void ircBot::notice(char *user, const char *message){
    defformatstring(noticeuser)("NOTICE %s :%s\r\n", user, message);
    send(sock,noticeuser,strlen(noticeuser),0);
}


void ircBot::ParseMessage(char *buff){
    if(sscanf(buff,":%[^!]!%[^@]@%[^ ] %*[^ ] %[^ :] :%[^\r\n]",msg.nick,msg.user,msg.host,msg.chan,msg.message) == 5){
        msg.is_ready = 1;
        if(msg.chan[0] != '#') strcpy(msg.chan,msg.nick);
    } else msg.is_ready = 0;
}

bool ircBot::checkping(char *buff)
{
    printf("%s\n", buff);
    char Pingout[60];
    memset(Pingout,'\0',60);
    if(sscanf(buff,"PING :%s",buff)==1)
    {
        snprintf(Pingout,60,"PONG :%s\r\n",buff);
        send(sock,Pingout,strlen(Pingout),0);
        printf("SENT: %s\n", Pingout);
        return 1;
    }
    return 0;
}

int ircstring = 0;
void ircBot::init()
{
    if(!getvar("ircignore")) {
    int con;
    char mybuffer[1000];

    struct sockaddr_in sa;
    struct hostent *he;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sa.sin_family = AF_INET;
    he = gethostbyname(irchost);
    bcopy(*he->h_addr_list, (char *)&sa.sin_addr.s_addr, sizeof(sa.sin_addr.s_addr));
    sa.sin_port = htons(ircport);
    connected = false;
    con = connect(sock, (struct sockaddr *)&sa, sizeof(sa));

    defformatstring(user)("USER %s 0 * :%s\r\n", ircbotname, ircbotname);
    send(sock, user, strlen(user), 0);
    defformatstring(nick)("NICK %s\r\n", ircbotname);
    send(sock, nick, strlen(nick), 0);
    defformatstring(join)("JOIN %s\r\n", ircchan);
    send(sock, join, strlen(join), 0);
    
    printf("[ OK ] Initalizing IRC...\n");

    
   while(1){

		ircstring = recv(sock, mybuffer, sizeof(mybuffer), 0);
        if(!connected)
        {
            send(sock, join, strlen(join), 0);
            connected = true;
		 } else {
			connected = false;
		 }
		
			if(ircstring) {
			if(!IsCommand(mybuffer)){
			
					defformatstring(toserver)("\f4%s \f3%s \f7- \f0%s\f7: %s", newstring(irchost), newstring(ircchan), msg.nick, msg.message);
					server::sendservmsg(toserver);
			
			}
			} else {
				connected = false;
				break;
			}
			
        memset(mybuffer,'\0',1000);
    }
	connected = false;
}}

void out(int type, const char *fmt, ...)
{
    
    
    char msg[1000];
    va_list list;
    va_start(list,fmt);
    vsnprintf(msg,1000,fmt,list);
    va_end(list);
    
    switch(type)
    {
        case ECHO_ALL:
        {
            server::sendservmsg(msg);
            irc.speak(msg);
            puts(msg);
            break;
        }
        case ECHO_IRC:
        {
            irc.speak(msg);
            break;
        }
        case ECHO_CONSOLE:
        {
            puts(msg);
            break;
        }
        case ECHO_SERV:
        {
            server::sendservmsg(msg);
            break;
        }
        case ECHO_MASTER:
        {
        //sendf(ci, 1, "ris", N_SERVMSG, msg);
            break;
        }
        default:
            break;
    }
}

bool ircBot::isConnected() {
	return connected;
}
