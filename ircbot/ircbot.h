/**

    header for the IRC bot used in the QServ sauerbraten server mod

**/

#ifndef __IRCBOT_INCLUDED
#define __IRCBOT_INCLUDED

//#include <vector>
#include "game.h"

struct IrcMsg
{
    char nick[32];
    char user[32];
    char host[64];
    char chan[32];
    char message[512];
    int is_ready;
};

class ircBot
{
    public:
        void init(void);
        int getSock();
        int speak(const char *fmt, ...);
        bool checkping(char *buff);
        bool IsCommand(char *buff);
        void join(char *channel);
        void part(char *channel);
        void notice(char *user, const char *message);
        IrcMsg *lastmsg();
        hashtable<char *, int> IRCusers;
		
		bool isConnected();
    private:
        void ParseMessage(char *buff);
        int sock;
        IrcMsg msg;
        bool connected;
};

extern ircBot irc;

enum
{
    ECHO_ALL = 0,
    ECHO_IRC ,
    ECHO_CONSOLE,
    ECHO_SERV,
    ECHO_MASTER,
};

extern void out(int type, const char *fmt, ...);
extern bool isloggedin(bool echo = 1);

extern int tightpussy;

#endif ///__IRCBOT_INCLUDED