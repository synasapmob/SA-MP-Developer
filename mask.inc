/*     7/10/2021 15:08 Synasapmob (Mr Son)
	        System Stranged MASK
		 Random MASK_ID SET Label To Player Changed it to NAME
*/
AntiDeAMX()
{
    new a[][] = {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}
#include <a_samp>
#include <streamer>
#include <YSI\y_hooks>
#include <Pawn.CMD>
enum maskenum{
	pMask,
	pMaskUSE,
	pMask_ID[MAX_PLAYERS],
	Text3D:pMask_3DLabel
};
new PlayerMask_ENUM[MAX_PLAYERS][maskenum];

stock GetName(playerid){
	new szName[MAX_PLAYER_NAME], iPos;
	GetPlayerName(playerid, szName, MAX_PLAYER_NAME);
	while ((iPos = strfind(szName, "_", false, iPos)) != -1) szName[iPos] = ' ';
	return szName;
}

hook OnPlayerSpawn(playerid){
    if(PlayerMask_ENUM[playerid][pMask] == 0){
        PlayerMask_ENUM[playerid][pMask] = 1;
        DestroyDynamic3DTextLabel(PlayerMask_ENUM[playerid][pMask_3DLabel]);
        return 1;
	}
    return true;
}

hook OnPlayerDisconnect(playerid, reason){
    if(IsValidDynamic3DTextLabel(PlayerMask_ENUM[playerid][pMask_3DLabel])){
		DestroyDynamic3DTextLabel(PlayerMask_ENUM[playerid][pMask_3DLabel]);
		return 1;
	}
	return true;
}

hook OnGameModeInit(){
    AntiDeAMX();
    printf("MASK.INC By Mr Son Loading");
    return true;
}
public OnPlayerText(playerid, text[]){
	new
		name[MAX_PLAYER_NAME],
		string[128];
	name = GetName(playerid);

    if(PlayerMask_ENUM[playerid][pMask] == 1 && PlayerMask_ENUM[playerid][pMaskUSE] == 1)
	{
		format(string, sizeof(string), "la mat %d noi: %s", PlayerMask_ENUM[playerid][pMask_ID], text);
		SendClientMessage(playerid, -1, string);
		printf(string);
	}
	else{
		SendClientMessage(playerid, -1, text);
	}
	return 0;
}

cmd:matna(playerid,params[])
{
    new string[128];
	if(PlayerMask_ENUM[playerid][pMask] == 1)
	{
	    if(PlayerMask_ENUM[playerid][pMaskUSE] == 0)
		{
	        PlayerMask_ENUM[playerid][pMaskUSE] = 1;
			format(string, sizeof(string), "la mat ((%d)", PlayerMask_ENUM[playerid][pMask_ID] = random(100000));
			PlayerMask_ENUM[playerid][pMask_3DLabel] = CreateDynamic3DTextLabel(string, 0xFFFFFFFF, 0.0, 0.0, 0.2, 15.0, .attachedplayer = playerid, .testlos = 1);
			UpdateDynamic3DTextLabelText(PlayerMask_ENUM[playerid][pMask_3DLabel], 0xFFFFFFFF, string);
			SendClientMessage(playerid, -1, string);
			ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0, 1);
			for(new i = 0; i < MAX_PLAYERS; i++) ShowPlayerNameTagForPlayer(i, playerid, false);
		}
		else{
		    PlayerMask_ENUM[playerid][pMaskUSE] = 0;
			DestroyDynamic3DTextLabel(PlayerMask_ENUM[playerid][pMask_3DLabel]);
			SendClientMessage(playerid, -1, "ban da thao mat na");
			ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0, 1);
			for(new i = 0; i < MAX_PLAYERS; i++) ShowPlayerNameTagForPlayer(i, playerid, true);
		}
	}
	else SendClientMessage(playerid, -1, "[!] Ban khong co mat na");
    return 1;
}
