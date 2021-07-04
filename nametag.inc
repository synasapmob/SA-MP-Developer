/*     7/4/2021 16:15 Synasapmob (Mr Son) 
       Nametag Bao gom "Name/ID/Health/Armour"
       ----------------------------------------
	Source Code : Custom Player Nametags
    	----- by Nyzenic -----
    	https://forum.sa-mp.com/showthread.php?p=4004123
*/

#include <YSI\y_hooks>
#include <YSI\y_timers>
#define DTC_NAMETAG 15.0 //distance
new Text3D:Player3DHealth[MAX_PLAYERS];
new Text3D:Player3DArmour[MAX_PLAYERS];
new Text3D:Player3DName[MAX_PLAYERS];
//ShowNameTags(1);
hook TASK_NAMETAG[1000](){
    for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
    {
        if(IsPlayerConnected(i))
        {
			new Float: HP, Float: AR;
			new nametag[128], playername[MAX_PLAYER_NAME];
			GetPlayerName(i, playername, sizeof(playername));
			GetPlayerHealth(i, HP);
			GetPlayerArmour(i, AR);
			format(nametag, sizeof(nametag),
			"{%06x}%s {FFFFFF}(%i)\n{cc0000}%0.2f{FFFFFF}\n{3d3d5c}%0.2f{FFFFFF}",
			GetPlayerColor(i) >>> 8, playername, i, HP, AR);
			UpdateDynamic3DTextLabelText(Player3DName[i], 0xFFFFFFFF, nametag);
    	}
    }
}
hook OnPlayerConnect(playerid)
{
	Player3DName[playerid] = CreateDynamic3DTextLabel("", 0xFFFFFFFF, 0.0, 0.0, 0.2, DTC_NAMETAG, .attachedplayer = playerid, .testlos = 1);
	Player3DHealth[playerid] = CreateDynamic3DTextLabel("", 0xFFFFFFFF, 0.0, 0.0, 0.3, DTC_NAMETAG, .attachedplayer = playerid, .testlos = 1);
	Player3DArmour[playerid] = CreateDynamic3DTextLabel("", 0xFFFFFFFF, 0.0, 0.0, 0.2, DTC_NAMETAG, .attachedplayer = playerid, .testlos = 1);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsValidDynamic3DTextLabel(Player3DName[playerid]))
	{
		DestroyDynamic3DTextLabel(Player3DName[playerid]);
		DestroyDynamic3DTextLabel(Player3DHealth[playerid]);
		DestroyDynamic3DTextLabel(Player3DArmour[playerid]);
		return 1;
	}
    return 1;
}