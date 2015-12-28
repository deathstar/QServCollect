#ifndef QCOM_H_INCLUDED
#define QCOM_H_INCLUDED

#include "QServ.h"

#define ncommand(name, desc, priv, callback, args) { qs.newcommand(name, desc, priv, callback, args); }
#define QSERV_CALLBACK void
#define p int cid, char **args, int argc
#define CMD_NAME(id) qs.getCommandName(id)
#define CMD_DESC(id) qs.getCommandDesc(id)
#define CMD_PRIV(id) qs.getCommandPriv(id)
#define CMD_LAST     qs.getlastCommand()
#define CMD_SENDER   qs.getSender()
#define CMD_SCI      qs.getlastCI()
#define CMD_SA       qs.getlastSA()
#define fulltext     qs.getFullText()

namespace server {
    extern void initCmds();
    extern QSERV_CALLBACK me_cmd(p);
    extern QSERV_CALLBACK cmd_cmd(p);
    extern QSERV_CALLBACK stats_cmd(p);
    extern QSERV_CALLBACK localtime_cmd(p);
    extern QSERV_CALLBACK time_cmd(p);
    extern QSERV_CALLBACK bunny_cmd(p);
    extern QSERV_CALLBACK owords_cmd(p);
    extern QSERV_CALLBACK olangfilter_cmd(p);
    extern QSERV_CALLBACK echo_cmd(p);
	extern QSERV_CALLBACK revokepriv_cmd(p);
    extern QSERV_CALLBACK forceintermission_cmd(p);
    extern QSERV_CALLBACK getversion_cmd(p);
    extern QSERV_CALLBACK callops_cmd(p);
    extern QSERV_CALLBACK msg_cmd(p);
    extern QSERV_CALLBACK sendprivs_cmd(p);
    extern QSERV_CALLBACK forgive_cmd(p);
    extern QSERV_CALLBACK forcespectator_cmd(p);
    extern QSERV_CALLBACK unspectate_cmd(p);
    extern QSERV_CALLBACK mute_cmd(p);
    extern QSERV_CALLBACK unmute_cmd(p);
    extern QSERV_CALLBACK editmute_cmd(p);
    extern QSERV_CALLBACK uneditmute_cmd(p);
    extern QSERV_CALLBACK togglelockspec_cmd(p);
    extern QSERV_CALLBACK uptime_cmd(p);
    extern QSERV_CALLBACK info_cmd(p);
    extern QSERV_CALLBACK tournament_cmd(p);
    extern QSERV_CALLBACK help_cmd(p);
    extern QSERV_CALLBACK cheater_cmd(p);
    extern QSERV_CALLBACK mapsucks_cmd(p);
}

#endif
