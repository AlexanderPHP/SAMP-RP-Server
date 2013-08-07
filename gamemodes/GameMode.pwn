#define FOREACH_NO_BOTS

#include <a_samp>
#include <a_mysql>
#include <foreach>
#include <mxdate>
#include <sscanf2>
#include <gvar>
#include <streamer>
#include <mxINI>
#include <3DMenu>
#include <zcmd>
#include <YSI\y_hooks>	
//#include <file>

#include <Sources\Config>

//==============================================================================


//===========Transport==========
#include <Sources\Transport\Speedo>
#include <Sources\Transport\Command>
	//=========Команды===========	
#include <Sources\Commands\Commands>
#include <Sources\Commands\Dialogs>
#include <Sources\Commands\Functions>
//==========Other=========
#include <Sources\PayDay>
#include <Sources\Objects>
#include <Sources\AutoShow>
#include <Sources\Bank>
#include <Sources\Costume>
#include <Sources\Ammo>
//====================Правила сервер============================================


main()
{
	//print("\n---------------------------------------------\n");
	//print("\t MySQL R8 | By Bellik | Register");
	//print("\n---------------------------------------------\n");
}


//==============================================================================

#define BanEx(%0,%1)        fix_kick(%0, false, %1)

public: DisconnectPlayer(playerid, bool:is_kicked, reason[]){

    if(IsPlayerConnected(playerid))
    if(is_kicked)Kick(playerid);
    else BanEx(playerid, reason);
    return true;
}

stock fix_kick(playerid, bool:is_kicked = true, reason[] = " ")
{
    new fix_ping = GetPlayerPing(playerid) + 25;
    return SetTimerEx("DisconnectPlayer", fix_ping>1000?1000:fix_ping, 0, "dds", playerid, is_kicked, reason);
}

//==============================================================================

public OnGameModeInit()
{
	ManualVehicleEngineAndLights();
	g_CH = mysql_connect(MySQL_HOST, MySQL_USER, MySQL_DATABASE, MySQL_PASS), SetGameModeText("Server123");
	// Menu
 	regskin = CreateMenu("Skin", 1, 50.0, 160.0, 90.0),
	AddMenuItem(regskin, 0, ">~y~ Next"), AddMenuItem(regskin, 0, ">~g~ Okey");
	// Timer's
	SetTimer("PayDay", 1000*60*1, 1);
	SetTimer("OnPlayerUpdateEx", 1000, 1);
	// Load
	LoadMySQL();
	// Other's
 	EnableStuntBonusForAll(0);// Выключенные бонусы за трюки)
	DisableInteriorEnterExits(); // Стандартные пикапы
	Create3DTextLabel("Банковские услуги\nнажмите 'Enter'",COLOR_YELLOW,2308.8201,-13.2660,26.7422,5.0,0,0); // В банке.
	return true;
}

stock BroadCast(color,const string[])
{
	SendClientMessageToAll(color, string);
	return true;
}

stock FixHour(hour)
{
	if (hour < 0)
	{
		hour = hour+24;
	}
	else if (hour > 23)
	{
		hour = hour-24;
	}
	shifthour = hour;
	return true;
}

stock ProxDetector(Float:radi, playerid, string[],col1,col2,col3,col4,col5)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		//radi = 2.0; //Trigger Radius
		foreach (new i : Player)
		{
			if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
			{
				GetPlayerPos(i, posx, posy, posz);
				tempposx = (oldposx -posx);
				tempposy = (oldposy -posy);
				tempposz = (oldposz -posz);
				if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
				{
					SendClientMessage(i, col1, string);
				}
				else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
				{
					SendClientMessage(i, col2, string);
				}
				else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
				{
					SendClientMessage(i, col3, string);
				}
				else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
				{
					SendClientMessage(i, col4, string);
				}
				else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
				{
					SendClientMessage(i, col5, string);
				}
			}
			else
			{
				SendClientMessage(i, col1, string);
			}
		}
	}
	return true;
}

public OnGameModeExit()
{
    foreach(new i : Player) Save_Player(i);
    print("[Сервер] Выключение..."), mysql_close(g_CH);
	return true;
}

public OnPlayerRequestClass(playerid, classid)
{
   // TogglePlayerSpectating(playerid, true);
	return true;
}

public OnPlayerConnect(playerid)
{
	ChangeSkin[playerid] = 0;
    // GetPlayerName(playerid, InfoPlayer[playerid][Name], MAX_PLAYER_NAME), GetPlayerIp(playerid, InfoPlayer[playerid][IP], 32);
	static query_mysql[80];
	f(query_mysql, "SELECT `Name` FROM `"PTG"` WHERE `Name` = '%s'", PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheck", "d", playerid);
	f(query_mysql, "SELECT `Nick` FROM `"BanList"` WHERE Nick = '%s'", PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, true, "CheckBanList", "d", playerid);
	f(query_mysql, "SELECT `IP` FROM `"BanList"` WHERE IP = '%s'", PlayerIP(playerid)), mysql_function_query(g_CH, query_mysql, true, "CheckBanListIp", "d", playerid);
	SetPlayerMapIcon(playerid,47,1414.0972,-1701.0652,13.5395,52,0);//банк
	SetPlayerMapIcon(playerid,47,461.7025,-1500.7941,31.0454,45,0);//Victim
	SetPlayerMapIcon(playerid,47,-1882.5100,866.3918,35.1719,45,0);//Zip
	return true;
}

public OnPlayerDisconnect(playerid, reason)
{
	Save_Player(playerid);
	TextDrawDestroy(CenaSkin[playerid]);
	TextDrawDestroy(SpeedShow[playerid]);
	TextDrawDestroy(FuelShow[playerid]);
	TextDrawDestroy(StatusShow[playerid]);
	TextDrawDestroy(KMShow[playerid]);
	return true;
}

public OnPlayerSpawn(playerid)
{
	TextDrawHideForPlayer(playerid,CenaSkin[playerid]);
	TextDrawHideForPlayer(playerid,Box);
	TextDrawHideForPlayer(playerid,Speed);
	KillTimer(STimer[playerid]);
	TextDrawHideForPlayer(playerid,SpeedShow[playerid]);
	TextDrawHideForPlayer(playerid,LightShow[playerid]);
	TextDrawHideForPlayer(playerid,Fuel);
	TextDrawHideForPlayer(playerid,FuelShow[playerid]);
	TextDrawHideForPlayer(playerid,Status);
	TextDrawHideForPlayer(playerid,StatusShow[playerid]);
	TextDrawHideForPlayer(playerid,KMShow[playerid]);
	SetPlayerSkills(playerid);
	PlayerSpawn(playerid);
	return true;
}
 
public OnPlayerRequestSpawn(playerid)
{
	if(GetPVarInt(playerid, "IsLogged") == 0)
	{
		SendClientMessage(playerid, -1, "Авторизуйся зараза!");
		return false;
	}
	return true;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{

}
public OnPlayerText(playerid, text[])
{
	return true;
}
stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z) 
{ 
    if(IsPlayerConnected(playerid)) 
    { 
     new Float:oldposx, Float:oldposy, Float:oldposz; 
     new Float:tempposx, Float:tempposy, Float:tempposz; 
     GetPlayerPos(playerid, oldposx, oldposy, oldposz); 
     tempposx = (oldposx -x); 
     tempposy = (oldposy -y); 
     tempposz = (oldposz -z); 
     if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) return 1; 
    } 
	return 0; 
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    case Register:
	    {
	        if(!response) return SendMes(playerid, COLOR_RED, "Вы отказались от регистрации !"), fix_kick(playerid);
			if(strlen(inputtext) == 0) return SendClientMessage(playerid, COLOR_WHITE, "Вы не ввели пароль."), RegisterDialog(playerid);
			static query_mysql[160];
			f(query_mysql, "INSERT INTO `"PTG"` (`Name`, `Password`, `IP`) VALUES ('%s', '%s', '%s')", PlayerName(playerid), inputtext, PlayerIP(playerid));
			SendMes(playerid, COLOR_YELLOW, "Ваш пароль: {FF0000}%s {32CD32}", inputtext);
			mysql_function_query(g_CH, query_mysql, true, "OnPlayerRegister", "d", playerid);
		}
	    case Login:
	    {
	        if(!response) return SendMes(playerid, COLOR_RED, "Вы отказались от авторизации !"), fix_kick(playerid);
	        for(new i = strlen(inputtext); i != 0; --i)
			switch(inputtext[i])
			{
			case 'А'..'Я', 'а'..'я', ' ':
				return ShowPlayerDialog(playerid,D_DIALOGS+12,DIALOG_STYLE_MSGBOX,"{FF0000}Ошибка!","{FFFFFF}Смените раскладку клавиатуры с русского на английский","Ок","");
			}
			if(strlen(inputtext) == 0) return SendClientMessage(playerid, COLOR_WHITE, "Вы не ввели пароль."), LoginDialog(playerid);
			static query_mysql[120];
			f(query_mysql, "SELECT * FROM `"PTG"` WHERE `Name` = '%s' AND `Password` = '%s'", PlayerName(playerid), inputtext), mysql_function_query(g_CH, query_mysql, true, "OnPlayerLoginGame", "d", playerid);
		}
   		case D_DIALOGS+1:
	 	{
	 	    if(!response) return SendMes(playerid, COLOR_RED, "Вы отказались от ввода Email !"), fix_kick(playerid);
            static query_mysql[120];
       /*     print("1");
			f(query_mysql, "SELECT * FROM `"PTG"` WHERE `Email` = '%s'", inputtext);
			mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheckEmail", "d", playerid);
			print("2");
			static per;per = GetPVarInt(playerid, "CheckEmail");
			printf("%d\nпер", per);
			//SetPVarInt(playerid,"CheckEmail",0);
			if(GetPVarInt(playerid, "CheckEmail") == 1)
			{*/
			//SpawnPlayer(playerid);
			//new randphone = 10000 + random(899999);
			//mysql_function_query(g_CH, query_mysqll, true, "OnPlayerCheckMobile", "d", playerid);
			f(query_mysql, "UPDATE `"PTG"` SET `Email` = '%s' WHERE `name` = '%s'", inputtext, PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheckMobile", "d", playerid);
			//OnPlayerRegisterInvite
			// mysql_function_query(g_CH, query_mysql, true, "OnPlayerRegisterFinish", "d", playerid);
		//	ShowPlayerDialog(playerid,D_DIALOGS+2,DIALOG_STYLE_LIST,"{FF0000}Выберите пол.","Мужчина\nЖенщина","Ок","Назад");
			SendMes(playerid, COLOR_YELLOW, "Ваш email: {FF0000}%s", inputtext), SetPlayerVirtualWorld(playerid, playerid);
		//	SetSpawnInfo(playerid, 255, playerid, 0, 0, 0, 1.0, -1, -1, -1, -1, -1, -1), SpawnPlayer(playerid), DeletePVar(playerid, "CheckEmail");
			return true;
/*			}
			SendClientMessage(playerid, COLOR_GREEN, "Ошибка при вводе Email, попробуйте еще раз!");
            ShowPlayerDialog(playerid,D_DIALOGS+1,DIALOG_STYLE_INPUT,"{FF0000}Email","{FFFFFF}Введите свой {00FF00}Email{FFFFFF} {FF0000}!","Ок","Назад");*/
		}
		case D_DIALOGS+2:
	 	{
			if(!response) return SendMes(playerid, COLOR_RED, "Вы отказались от выбора скина !"), fix_kick(playerid);
			switch(listitem)
			{
   				case 0: SetPVarInt(playerid, "Sex", 0), SelectSkin(playerid);
				case 1: SetPVarInt(playerid, "Sex", 1), SelectSkin(playerid);
			}
		}
		case D_DIALOGS+3:
		{
		    if(!response) return true;
		    new idx = GetPVarInt(playerid, "PlayerHouse");
 			if(!strcmp(HouseInfo[idx][hOwner],"None",true))
 			{
				if(GetPVarInt(playerid, "Money") < HouseInfo[idx][hPrice]) return SendMes(playerid, COLOR_RED, "У вас нету сколько денег для покупки, вам не хватает: {FFFFFF}%d{0000FF}$", HouseInfo[idx][hPrice]-GetPVarInt(playerid, "Money"));
				oGiveMoney(playerid, -HouseInfo[idx][hPrice]);
				GameTextForPlayer(playerid, "The house was bought", 3000, 5);
				SendMes(playerid, COLOR_WHITE, "Вы купили дом за {FF0000}%d${FFFFFF} долларов. ", HouseInfo[idx][hPrice]);
				HouseInfo[idx][hOwned] = 1, HouseInfo[idx][hLock] = 1;
				SetPVarInt(playerid, "HouseKey", idx);
				strmid(HouseInfo[idx][hOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), MAX_PLAYER_NAME);
				SetPlayerPos(playerid,HouseInfo[idx][hExitX],HouseInfo[idx][hExitY],HouseInfo[idx][hExitZ]);
				SetPlayerInterior(playerid,HouseInfo[idx][hInt]);
				HouseInfo[idx][hIcon] = CreateDynamicMapIcon(HouseInfo[idx][hEnterX], HouseInfo[idx][hEnterY], HouseInfo[idx][hEnterZ], 32, COLOR_WHITE, -1, -1, -1, 400.0);
	 			DestroyPickup(HouseInfo[idx][hPickup]), HouseInfo[idx][hPickup] = CreatePickup(1272, 23, HouseInfo[idx][hEnterX], HouseInfo[idx][hEnterY], HouseInfo[idx][hEnterZ],-1);
				SetPlayerVirtualWorld(playerid, HouseInfo[idx][hVirtualWorld]);
				SaveHouse(), DeletePVar(playerid, "PlayerHouse"), Save_Player(playerid);
				return true;
			}
		}
		case D_DIALOGS+4: // Продажа дома..
	 	{
			if(!response) return true;
			new housee = GetPVarInt(playerid, "HouseKey");
			SetPVarInt(playerid, "HouseKey", -1);
			oGiveMoney(playerid, HouseInfo[housee][hPrice]/2);
			SendMes(playerid, COLOR_YELLOW, "Вы успешно продали дом за {FF0000}%d$", HouseInfo[housee][hPrice]/2);
			strmid(HouseInfo[housee][hOwner], "None", 0, strlen("None"), MAX_PLAYER_NAME);
            DestroyPickup(HouseInfo[housee][hPickup]), HouseInfo[housee][hPickup] = CreatePickup(1274, 23, HouseInfo[housee][hEnterX], HouseInfo[housee][hEnterY], HouseInfo[housee][hEnterZ],-1);
      		HouseInfo[housee][hIcon] = CreateDynamicMapIcon(HouseInfo[housee][hEnterX], HouseInfo[housee][hEnterY], HouseInfo[housee][hEnterZ], 31, COLOR_WHITE, -1, -1, -1, 400.0);
			HouseInfo[housee][hOwned] = 0, HouseInfo[housee][hLock] = 0;
			SaveHouse(), SetPVarInt(playerid, "SetSpawn", 0), Save_Player(playerid);
		}
		case D_DIALOGS+5: // Открыть дом..
	 	{
			if(!response) return true;
			new idx = GetPVarInt(playerid, "HouseKey");
  			HouseInfo[idx][hLock] = 0, GameTextForPlayer(playerid, "~w~Door ~g~Unlocked", 5000, 6), PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		case D_DIALOGS+6:
		{
		    if(!response) return true;
   			switch(listitem)
			{
				case 0: SetPVarInt(playerid, "SetSpawn", 0), SendMes(playerid, COLOR_YELLOW, "Вы установили место спавна {FFFFFF}'{FF0000}Респа{FFFFFF}'");
				case 1:
				{
					if(GetPVarInt(playerid, "HouseKey") == -1) return SendMes(playerid, COLOR_RED, "У вас нету дома !");
					SetPVarInt(playerid, "SetSpawn", 1), SendMes(playerid, COLOR_YELLOW, "Вы установили место спавна в {FFFFFF}'{FF0000}Доме{FFFFFF}'");
				}
			}
		}
		case D_DIALOGS+7: //войти в дом
		{
			if(response)
			{
			    new idx = GetPVarInt(playerid, "PickupIdxHouse");
				if(HouseInfo[idx][hLock] == 1)
				{
	    			if(strcmp(PlayerName(playerid), HouseInfo[idx][hOwner], true) == 0) ShowPlayerDialog(playerid, D_DIALOGS+5, 0, "{FF0000}Дом", "{FFFFFF}Ваш дом закрыт\n\nВы хотите его открыть?", "Да", "Нет");
					SendMes(playerid, COLOR_RED, "Дом закрыт..");
				}
				else
				{
	    			SetPlayerPos(playerid,HouseInfo[idx][hExitX],HouseInfo[idx][hExitY],HouseInfo[idx][hExitZ]);
					SetPlayerInterior(playerid,HouseInfo[idx][hInt]), SetPlayerVirtualWorld(playerid,HouseInfo[idx][hVirtualWorld]);
				}
			}
		}
		case D_DIALOGS+8:
		{
			if(!response) return true;
			SetPlayerPos(playerid, Interior[listitem][vX], Interior[listitem][vY], Interior[listitem][vZ]);
			SendMes(playerid, COLOR_YELLOW, "Вы телепортированы в интерьер: %s | Номер: %d", Interior[listitem][vName], Interior[listitem][vID]);
			SetPlayerInterior(playerid, Interior[listitem][vInt]);
		}
		case D_DIALOGS+9:
	 	{
            static query_mysql[120];
			f(query_mysql, "UPDATE `"PTG"` SET `invite_nick` = '%s' WHERE `name` = '%s'", inputtext, PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, true, "OnPlayerRegisterRules", "d", playerid);
			return true;
		}
        case D_DIALOGS+10:
	 	{
	 	   if(response)
			{
				new rulesdialogg[1000];
				format(rulesdialogg,sizeof(rulesdialogg), "%s%s%s%s%s%s%s%s%s%s%s%s%s",
				RulesMSGG[0],RulesMSGG[1],RulesMSGG[2],RulesMSGG[3],RulesMSGG[4],RulesMSGG[5],RulesMSGG[6],RulesMSGG[7],RulesMSGG[8],RulesMSGG[9],RulesMSGG[10],RulesMSGG[11],RulesMSGG[12]);
				ShowPlayerDialog(playerid,D_DIALOGS+11,DIALOG_STYLE_MSGBOX,"{FFFFFF}Правила сервера BeautifulLife Role Play", rulesdialogg, "Далее", "");
				return true;
			}
			else
			{
				return true;
			}
		}
		case D_DIALOGS+11:
	 	{
			static query_mysql[120];
	 	    f(query_mysql, "UPDATE `"PTG"` SET `Name` = '%s' WHERE `name` = '%s'", PlayerName(playerid), PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, true, "OnPlayerRegisterFinish", "d", playerid);
			ShowPlayerDialog(playerid,D_DIALOGS+2,DIALOG_STYLE_LIST,"{FF0000}Выберите пол.","Мужчина\nЖенщина","Ок","Назад");
			SetSpawnInfo(playerid, 255, playerid, 0, 0, 0, 1.0, -1, -1, -1, -1, -1, -1), SpawnPlayer(playerid);
			InterpolateCameraPos(playerid, 1673.023925, -2006.905151, 90.566871, 1682.506713, -1721.867797, 57.926670, 1000);
			InterpolateCameraLookAt(playerid, 1676.034057, -2003.654541, 88.248970, 1680.283569, -1717.403076, 58.277946, 1000);
		}
		case D_DIALOGS+12:
		{
		    LoginDialog(playerid);
		}
	}
	return true;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
/*	for_c(GetGVarInt("HouseM")-1, -1, idx)
	{
    	if(pickupid == HouseInfo[idx][hPickup])
    	{
    	    SetPVarInt(playerid, "PickupIdxHouse", idx);
    	    static str[200];
			if(HouseInfo[idx][hOwned] == 0) SellHome(str);
			else
	        {
				foreach (new i : Player) if(strcmp(PlayerName(i), HouseInfo[idx][hOwner], true, strlen(HouseInfo[idx][hOwner])) == 0) SetPVarInt(playerid, "PlayerHome", 1);
         		f(str,"{FFFFFF}Адрес: {7CFC00}%s-{FF0000}%d{FFFFFF}\nВладелец: {7CFC00}%s {FF0000}[%s{FF0000}]", HouseInfo[idx][hNameStreet], idx, HouseInfo[idx][hOwner], (GetPVarInt(playerid, "PlayerHome") == 0) ? ("{FF2400}Offline") : ("{3CAA3C}Online"));
			}
			ShowPlayerDialog(playerid, D_DIALOGS+7, 0,"{00CD00}Дом", str, "Войти","Отмена"), DeletePVar(playerid, "PlayerHome");
			return true;
    	}
    }*/
	return true;
}

public OnQueryError(errorid, error[], callback[], query[], connectionHandle) return WriteLog("/MySQL/Errors.txt", error), WriteLog("/MySQL/Errors.txt", callback), WriteLog("/MySQL/Errors.txt", query);

public OnPlayerSelectedMenuRow(playerid, row)
{
    new Menu:Current = GetPlayerMenu(playerid);
	if(Current == regskin)
	{
	    switch(row)
	    {
         	case 0:
		    {
				if(GetPVarInt(playerid, "Sex") == 0)// Мужик
				{
				    if(GetPVarInt(playerid, "ChangeSkin") == 6) SetPVarInt(playerid, "ChangeSkin", 0);
				    else GivePVarInt(playerid, "ChangeSkin", 1);
				    SetPlayerInterior(playerid, 14), oSetSkin(playerid, SpawnInfo[0][fSkin][GetPVarInt(playerid, "ChangeSkin")]);
                    ShowMenuForPlayer(regskin, playerid), SetPVarInt(playerid, "Skin", GetPlayerSkin(playerid));
				}
				if(GetPVarInt(playerid, "Sex") == 1)// Девка
				{
				    if(GetPVarInt(playerid, "ChangeSkin") == 6) SetPVarInt(playerid, "ChangeSkin", 0);
				    else GivePVarInt(playerid, "ChangeSkin", 1);
				    SetPlayerInterior(playerid, 14), oSetSkin(playerid, SpawnInfo[0][fSkinGirl][GetPVarInt(playerid, "ChangeSkin")]);
                    ShowMenuForPlayer(regskin, playerid), SetPVarInt(playerid, "Skin", GetPlayerSkin(playerid));
				}
			}
		 	case 1:
			{	
				SetPVarInt(playerid, "Skin", GetPlayerSkin(playerid));
			    UnFreezePlayer(playerid), SetPlayerFacingAngle(playerid, 280), SetPlayerVirtualWorld(playerid, playerid);
				SetCameraBehindPlayer(playerid), SetPlayerInterior(playerid, SpawnInfo[0][fInt]);
				SetPlayerPos(playerid, SpawnInfo[0][fSpawnX], SpawnInfo[0][fSpawnY], SpawnInfo[0][fSpawnZ]);
			    InterpolateCameraPos(playerid, 1673.023925, -2006.905151, 90.566871, 1682.506713, -1721.867797, 57.926670, 1000);
				InterpolateCameraLookAt(playerid, 1676.034057, -2003.654541, 88.248970, 1680.283569, -1717.403076, 58.277946, 1000);
    			static str[200];
				f(str, "UPDATE `"PTG"` SET `Skin` = %d, `Sex` = %d WHERE `Name` = '%s'", GetPVarInt(playerid, "Skin"), GetPVarInt(playerid, "Sex"), PlayerName(playerid)); mysql_query(str, -1, -1, g_CH);
				LoginDialog(playerid);
			}
		}
		return true;
	}
	return true;
}

stock IsABankomat(playerid)
{
	if(PlayerToPoint(1.0,playerid,1921.5, -1765.8000, 13.2) || PlayerToPoint(1.0,playerid,1831.1999, -1891.6999, 13.1) ||
			PlayerToPoint(1.0,playerid,-1639.5, 12.7, 0.0) || PlayerToPoint(1.0,playerid,1457.9000, -1754.9000, 13.2) ||
			PlayerToPoint(1.0,playerid,-1647.0999, -1171.9000, 23.7) || PlayerToPoint(1.0,playerid,285.8999, -1749.4000, 4.2) ||
			PlayerToPoint(1.0,playerid,-78.1, -1169.0999, 1.8) || PlayerToPoint(1.0,playerid,-2028.6999, -102, 34.8) ||
			PlayerToPoint(1.0,playerid,-1980.5999, 131.8999, 27.3) || PlayerToPoint(1.0,playerid,-1677.1999, 431, 6.8) ||
			PlayerToPoint(1.0,playerid,-262, 1414.9000, 6.7) || PlayerToPoint(1.0,playerid,-1691.4000, 948.4000, 24.5) ||
			PlayerToPoint(1.0,playerid,1142.8994140625,-1764,13.300000190735)){return true;}
	return false;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	
	if((newkeys == 1024)) CallLocalFunction("OnPlayerCommandText", "is", playerid, "/exit");
	if (newkeys == 16)
	{
		if(PlayerToPoint(3.0,playerid,259.2724,-41.4995,1002.0234))
		{
			TogglePlayerControllable(playerid, 0);
			ShowMenuForPlayer(skinshopmagaz,playerid);
		}
	}
	if (newkeys == KEY_LOOK_BEHIND)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			CallLocalFunction("OnPlayerCommandText", "is", playerid, "/en");
		}
	}
	if (newkeys == KEY_ACTION)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			CallLocalFunction("OnPlayerCommandText", "is", playerid, "/light");
		}
	}
	return true;
}

public OnPlayerUpdate(playerid)
{
    //new Keys,ud,lr;
   // GetPlayerKeys(playerid,Keys,ud,lr);
 //
//	SendMes(playerid, COLOR_WHITE,"%d - key, %d - ud, %d - lr",Keys,ud,lr);
//
   // return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(GetPVarInt(playerid, "Admin") >= 2)
	{
	    if(IsPlayerInAnyVehicle(playerid)) return SendMes(playerid,0xFF0000AA,"Вы в транспорте");
		SetPlayerPosFindZ(playerid, fX, fY, fZ);
		SendMes(playerid, COLOR_GREY, "Вы были телепортированы");
		SetPlayerInterior(playerid, 0), SetPlayerVirtualWorld(playerid, 0);
		return true;
	}
    return false;
}

//Созданые пабликы
public: OnPlayerCheckHouse(mysql_player)
{
	new rows, fields;
    cache_get_data(rows, fields);
	if(rows == 0) SetPVarInt(playerid, "HouseKey", -1), SetPVarInt(playerid, "SetSpawn", 0), Save_Player(playerid);
	return true;
}

public: OnLoadInteriors(mysql_player)
{
	static rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		for_c(rows-1, -1, h)
		{
			Interior[h][vID] = cache_get_field_int(h, "id", g_CH);
			cache_get_field_content(h, "Name", Interior[h][vName], g_CH, 60);
			Interior[h][vX] = cache_get_field_float(h, "x", g_CH);
			Interior[h][vY] = cache_get_field_float(h, "y", g_CH);
			Interior[h][vZ] = cache_get_field_float(h, "z", g_CH);
			Interior[h][vInt] = cache_get_field_int(h, "Int", g_CH);
		 	Interior[h][vPrice_Frac] = cache_get_field_int(h, "Price_Frac", g_CH);
			GiveGVarInt("Inter", 1, 0);
		}
	}
	return true;
}

public: OnLoadHouse(mysql_player)
{
	static rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		for_c(rows-1, -1, he)
		{
			HouseInfo[he][hID] = cache_get_field_int(he, "ID", g_CH);
			HouseInfo[he][hEnterX] = cache_get_field_float(he, "EnterX", g_CH);
			HouseInfo[he][hEnterY] = cache_get_field_float(he, "EnterY", g_CH);
			HouseInfo[he][hEnterZ] = cache_get_field_float(he, "EnterZ", g_CH);
			HouseInfo[he][hExitX] = cache_get_field_float(he, "ExitX", g_CH);
			HouseInfo[he][hExitY] = cache_get_field_float(he, "ExitY", g_CH);
			HouseInfo[he][hExitZ] = cache_get_field_float(he, "ExitZ", g_CH);
			HouseInfo[he][hInt] = cache_get_field_int(he, "Int", g_CH);
			HouseInfo[he][hOwned] = cache_get_field_int(he, "Owned", g_CH);
			cache_get_field_content(he, "Owner", HouseInfo[he][hOwner], g_CH, 24);
			cache_get_field_content(he, "NameStreet", HouseInfo[he][hNameStreet], g_CH, 20);
			HouseInfo[he][hPrice] = cache_get_field_int(he, "Price", g_CH);
			HouseInfo[he][hLock] = cache_get_field_int(he, "Lock", g_CH);
			HouseInfo[he][hVirtualWorld] = cache_get_field_int(he, "VirtualWorld", g_CH);
			Create3DTextLabel("Нажмите альт чтобы выйти..", COLOR_AQUA, HouseInfo[he][hExitX], HouseInfo[he][hExitY], HouseInfo[he][hExitZ], 10.0, HouseInfo[he][hVirtualWorld], 1);
			if(HouseInfo[he][hOwned] == 0)
        	{
	            HouseInfo[he][hPickup] = CreatePickup(1274, 23, HouseInfo[he][hEnterX], HouseInfo[he][hEnterY], HouseInfo[he][hEnterZ],-1);
	            HouseInfo[he][hIcon] = CreateDynamicMapIcon(HouseInfo[he][hEnterX], HouseInfo[he][hEnterY], HouseInfo[he][hEnterZ], 31, COLOR_WHITE, -1, -1, -1, 400.0);
			}
	        else if(HouseInfo[he][hOwned] == 1)
	        {
            	HouseInfo[he][hIcon] = CreateDynamicMapIcon(HouseInfo[he][hEnterX], HouseInfo[he][hEnterY], HouseInfo[he][hEnterZ], 32, COLOR_WHITE, -1, -1, -1, 400.0);
            	HouseInfo[he][hPickup] = CreatePickup(1272, 23, HouseInfo[he][hEnterX], HouseInfo[he][hEnterY], HouseInfo[he][hEnterZ],-1);
			}
			GiveGVarInt("HouseM", 1, 0);
		}
	}
	return true;
}

public: OnQueryAdminsInfo(mysql_player)
{
	static rows, fields;
    cache_get_data(rows, fields);
	if(rows)
	{
	    SetPVarInt(playerid, "Admin", cache_get_field_int(0, "AdmLevel", g_CH));
	    SendMes(playerid, COLOR_YELLOW,"Вы вошли как администратор %d уровня", GetPVarInt(playerid, "Admin"));
	}
	return true;
}

public: OnPlayerEnterCheckpoint(playerid) 
{ 
	if(checkpoint[playerid] == 1) // аммо
	{
		new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
		ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
	}
}
public: OnPlayerCheckMobile(mysql_player)
{
	static rows, fields;
	new randphone = 10000 + random(899999);
	static query_mysql[120];
    cache_get_data(rows, fields);
	if(GetPVarInt(playerid,"PhoneCheck") == 0)
	{
		printf("PhoneCheck: %d", GetPVarInt(playerid,"PhoneCheck"));
		SetPVarInt(playerid, "Phone", randphone);
		SetPVarInt(playerid, "PhoneCheck", 1);
		f(query_mysql, "SELECT * FROM `"PTG"` WHERE `phone` = '%d'", randphone);
		mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheckMobile", "d", playerid);
	}
	else
	{
		if(rows)
		{
			SetPVarInt(playerid, "Phone", randphone);
			f(query_mysql, "SELECT * FROM `"PTG"` WHERE `phone` = '%d'", randphone);
			mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheckMobile", "d", playerid);
		}
		else 
		{
			printf("Phone: %d",GetPVarInt(playerid, "Phone"));
			f(query_mysql, "UPDATE `"PTG"` SET `phone` = '%d' WHERE `name` = '%s'", GetPVarInt(playerid, "Phone"), PlayerName(playerid));
			mysql_function_query(g_CH, query_mysql, true, "OnPlayerRegisterInvite", "d", playerid);
		}
	}	
	return true;
}

/*public: OnPlayerCheckEmail(mysql_player)
{
	print("3");
	static rows, fields;
    cache_get_data(rows, fields);
	if(rows)
	{
		printf("4%s\nровс", rows);
		SendMes(playerid, COLOR_RED, "Такой Email - уже указан, у другого игрока !");
		ShowPlayerDialog(playerid,D_DIALOGS+1,DIALOG_STYLE_INPUT,"{FF0000}Email","{FFFFFF}Введите свой {00FF00}Email{FFFFFF} {FF0000}!","Ок","Назад");
	}
	else SetPVarInt(playerid, "CheckEmail", 1);
	return true;
}
*/
public: OnLoadSpawn(mysql_player)
{
	static skin[12], skingirl[7], \
			rows, fields, temp[30];
	cache_get_data(rows, fields);
	if(rows)
	{
		for_c(rows-1, -1, he)
		{
			SpawnInfo[he][fID] = cache_get_field_int(he, "ID", g_CH);
			SpawnInfo[he][fSpawnX] = cache_get_field_float(he, "SpawnX", g_CH);
			SpawnInfo[he][fSpawnY] = cache_get_field_float(he, "SpawnY", g_CH);
			SpawnInfo[he][fSpawnZ] = cache_get_field_float(he, "SpawnZ", g_CH);
			SpawnInfo[he][fVw] = cache_get_field_int(he, "Vw", g_CH);
			SpawnInfo[he][fInt] = cache_get_field_int(he, "Int", g_CH);
			cache_get_field_content(he, "Color", SpawnInfo[he][fColor], g_CH, sizeof(temp));
			cache_get_field_content(he, "Skins", temp, g_CH, sizeof(temp)), sscanf(temp, "p<,>ddddddddddd", skin[1], skin[2], skin[3], skin[4], skin[5], skin[6], skin[7], skin[8], skin[9], skin[10], skin[11]);
            SpawnInfo[he][fSkin][0] = skin[1], SpawnInfo[he][fSkin][1] = skin[2], SpawnInfo[he][fSkin][2] = skin[3], SpawnInfo[he][fSkin][3] = skin[4], SpawnInfo[he][fSkin][4] = skin[5], SpawnInfo[he][fSkin][5] = skin[6], SpawnInfo[he][fSkin][6] = skin[7], SpawnInfo[he][fSkin][7] = skin[8], SpawnInfo[he][fSkin][8] = skin[9], SpawnInfo[he][fSkin][9] = skin[10], SpawnInfo[he][fSkin][10] = skin[11];
            cache_get_field_content(he, "SkinsGirl", temp, g_CH, sizeof(temp)), sscanf(temp, "p<,>ddddddd", skingirl[0], skingirl[1], skingirl[2], skingirl[3], skingirl[4], skingirl[5], skingirl[6]);
			SpawnInfo[he][fSkinGirl][0] = skingirl[0], SpawnInfo[he][fSkinGirl][1] = skingirl[1], SpawnInfo[he][fSkinGirl][2] = skingirl[2], SpawnInfo[he][fSkinGirl][3] = skingirl[3], SpawnInfo[he][fSkinGirl][4] = skingirl[4], SpawnInfo[he][fSkinGirl][5] = skingirl[5], SpawnInfo[he][fSkinGirl][6] = skingirl[6];
		}
	}
	return true;
}

public: OnPlayerCheck(mysql_player)
{
    InterpolateCameraPos(playerid, 1673.023925, -2006.905151, 90.566871, 1682.506713, -1721.867797, 57.926670, 1000);
	InterpolateCameraLookAt(playerid, 1676.034057, -2003.654541, 88.248970, 1680.283569, -1717.403076, 58.277946, 1000);
	static rows, fields;
    cache_get_data(rows, fields);
	if(!rows) SetPVarInt(playerid, "account_Exist", 0), RegisterDialog(playerid);
	else SetPVarInt(playerid, "account_Exist", 1), LoginDialog(playerid);
	return true;
}

public: OnPlayerRegister(mysql_player) return  ShowPlayerDialog(playerid,D_DIALOGS+1,DIALOG_STYLE_INPUT,"{FF0000}Введите Ваш E-Mail.","{FFFFFF}Внимание! Указывайте Ваш настоящий E-Mail адрес, т.к. на него будет выслано письмо с подтверждением!","Ок","Выход");
public: OnPlayerRegisterFinish(mysql_player) return SendClientMessage(playerid, COLOR_YELLOW, "Рекомендуется сделать скриншот. Клавиша: {FF0000}F8"), TogglePlayerSpectating(playerid, false);
public: OnPlayerRegisterInvite(mysql_player) return  ShowPlayerDialog(playerid,D_DIALOGS+9,DIALOG_STYLE_INPUT,"{FF0000}Кто Вас пригласил.","{FF0000}Введите ник игровка пригласившего Вас.","Ок","Пропустить");
public: OnPlayerRegisterRules(mysql_player)
{
	new rulesdialog[1300];
	format(rulesdialog,sizeof(rulesdialog), "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	RulesMSG[0],RulesMSG[1],RulesMSG[2],RulesMSG[3],RulesMSG[4],RulesMSG[5],RulesMSG[6],RulesMSG[7],RulesMSG[8],RulesMSG[9],RulesMSG[10],RulesMSG[11],RulesMSG[12],RulesMSG[13],RulesMSG[14],RulesMSG[15],RulesMSG[16],RulesMSG[17],RulesMSG[18],RulesMSG[19],RulesMSG[20],RulesMSG[21]);
	return ShowPlayerDialog(playerid,D_DIALOGS+10,DIALOG_STYLE_MSGBOX,"{FFFFFF}Правила сервера BeautifulLife Role Play", rulesdialog, "Далее", "");
}

public: OnPlayerLoginGame(mysql_player, extraid, connectionHandle)
{
	static rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		static email[32];
		cache_get_field_content(0, "Email", email, g_CH, sizeof(email));
		SetPVarInt(playerid, "MySQL_ID", cache_get_field_int(0, "ID", g_CH));
		SetPVarInt(playerid, "Kills", cache_get_field_int(0, "Kills", g_CH));
		SetPVarInt(playerid, "Deaths", cache_get_field_int(0, "Deaths", g_CH));
		SetPVarInt(playerid, "Sex", cache_get_field_int(0, "Sex", g_CH));
		SetPVarInt(playerid, "SetSpawn", cache_get_field_int(0, "SetSpawn", g_CH));
		SetPVarInt(playerid, "HouseKey", cache_get_field_int(0, "HouseKey", g_CH));
		SetPVarInt(playerid, "MoneyBank", cache_get_field_int(0, "MoneyBank", g_CH));
		SetPVarInt(playerid, "Money", cache_get_field_int(0, "Money", g_CH));
		SetPVarInt(playerid, "Level", cache_get_field_int(0, "Level", g_CH));
		SetPVarInt(playerid, "Exp", cache_get_field_int(0, "Exp", g_CH));
		SetPVarInt(playerid, "Phone", cache_get_field_int(0, "phone", g_CH));
		SetPVarInt(playerid, "sdpistol", cache_get_field_int(0, "sdpistol", g_CH));
		SetPVarInt(playerid, "deserteagle", cache_get_field_int(0, "deserteagle", g_CH));
		SetPVarInt(playerid, "shotgun", cache_get_field_int(0, "shotgun", g_CH));
		SetPVarInt(playerid, "mp5", cache_get_field_int(0, "mp5", g_CH));
		SetPVarInt(playerid, "ak47", cache_get_field_int(0, "ak47", g_CH));
		SetPVarInt(playerid, "m4", cache_get_field_int(0, "m4", g_CH));
		oSetMoney(playerid, cache_get_field_int(0, "Money", g_CH));
		oSetSkin(playerid, cache_get_field_int(0, "Skin", g_CH));
		SetPVarInt(playerid, "IsLogged", 1), SendClientMessage(playerid, COLOR_WHITE, "Вы успешно вошли."),TogglePlayerSpectating(playerid, false);
		if(strlen(email) == 0)
		{
		    static query_mysql[55];
		    f(query_mysql, "DELETE FROM `"PTG"` WHERE `name`='%s'", PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, false, "","");
	 		SendMes(playerid, COLOR_RED, "Критический сбой, перезайдите."), fix_kick(playerid);
		}
		SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
		//SetSpawnInfo(playerid, 255, playerid, 0, 0, 0, 1.0, -1, -1, -1, -1, -1, -1);
		GoInfo(playerid), Block(playerid), SpawnPlayer(playerid);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "Неправильный пароль.");
    	if(GetPVarInt(playerid, "PassWrong") == 2) SendClientMessage(playerid, COLOR_YELLOW, "Вы ввели неправильный пароль три раза подряд. {FF0000}Вы кикнуты !"), fix_kick(playerid);
     	SetPVarInt(playerid, "PassWrong", GetPVarInt(playerid, "PassWrong") + 1);
	 	new str[300];
		f(str, "{76EE00}Добро пожаловать на Сервер!\n{FF0000}Вы уже зарегистрированы ! Просто введите пароль и нажмите 'Войти'.\n\n{0000FF}Авторизация:{FFC125}\n- Тот же пароль что водили при регистрации\n\n\t\t{FF0000}Неверный пароль{0000FF} (осталось {FF0000}%i{0000FF} из 3)", 3 - GetPVarInt(playerid, "PassWrong"));
		ShowPlayerDialog(playerid, Login, DIALOG_STYLE_INPUT, "Авторизация", str, "Войти", "Отмена");
	}
	return true;
}

public: OnPlayerUpdateEx()
{
    GiveGVarInt("Tick", 1, 0);
	foreach(new i : Player)
	{
		if(GetPVarInt(i, "IsLogged") == 0) return true;
	    if(GetGVarInt("Tick") % 1800 == 0) Save_Player(i);
	  //  if(GetPlayerSkin(i) == 0) SendMes(i, COLOR_YELLOW, "Произошел критический сбой, выберите скин."), SelectSkin(i);
 	}
    return true;
}

static bans_day[3];
public: CheckBanList(mysql_player)
{
	static rows, fields;
    cache_get_data(rows, fields);
	if(rows)
	{
		SetPVarInt(playerid, "BanDate", cache_get_field_int(0, "UnBanDate", g_CH));
		if(gettime() >= GetPVarInt(playerid, "BanDate") && GetPVarInt(playerid, "BanDate") >= 1) SetPVarInt(playerid, "UnBanPlayer", 1);
		timestamp(GetPVarInt(playerid, "BanDate"), bans_day[0], bans_day[1], bans_day[2]), SetPVarInt(playerid, "Block", 1);
		SetPVarInt(playerid, "Bloack_Msg_Year", bans_day[0]); SetPVarInt(playerid, "Bloack_Msg_Month", bans_day[1]); SetPVarInt(playerid, "Bloack_Msg_Day", bans_day[2]);
	}
	return true;
}

public: CheckBanListIp(mysql_player)
{
	static rows, fields;
    cache_get_data(rows, fields);
	if(rows)
	{
		SetPVarInt(playerid, "BanDate", cache_get_field_int(0, "UnBanDate", g_CH));
		if(gettime() >= GetPVarInt(playerid, "BanDate") && GetPVarInt(playerid, "BanDate") >= 1) SetPVarInt(playerid, "UnBanPlayer", 1);
		if(GetPVarInt(playerid, "BanDate") >= 1) timestamp(GetPVarInt(playerid, "BanDate"), bans_day[0], bans_day[1], bans_day[2]);
		SetPVarInt(playerid, "Bloack_Msg_Year", bans_day[0]); SetPVarInt(playerid, "Bloack_Msg_Month", bans_day[1]); SetPVarInt(playerid, "Bloack_Msg_Day", bans_day[2]);
	}
	return true;
}

public: UnBan(mysql_player)
{
	static rows, fields;
    cache_get_data(rows, fields);
    if(rows)
	{
	    static str[24], query_mysql[80];
	    cache_get_field_content(0, "Nick", str, g_CH, sizeof(str));
		SendMes(playerid, COLOR_YELLOW, "Вы успешно разбанили акаунт : {FF0000}%s", str);
		f(query_mysql, "DELETE FROM `"BanList"` WHERE `Nick` = '%s'", str), mysql_function_query(g_CH, query_mysql, false, "","");
	}
	else SendMes(playerid, COLOR_RED,"Игрок не забанен !");
	mysql_free_result();
	return true;
}

public: Info(mysql_player)
{
 	static rows, fields;
    cache_get_data(rows, fields);
    if(rows)
	{
	    new str[100], temp[120];
	    static ip[16], data[16], name[24], admin[24], email[32];
	    if(GetPVarInt(playerid, "IBan") == 1)
	    {
		    cache_get_field_content(0, "Nick", name, g_CH, sizeof(name));
		    cache_get_field_content(0, "IP", ip, g_CH, sizeof(ip));
		    cache_get_field_content(0, "Admin", admin, g_CH, sizeof(admin));
		    cache_get_field_content(0, "Date", data, g_CH, sizeof(data));
		    cache_get_field_content(0, "Reason", email, g_CH, sizeof(email));
	     	SetPVarInt(playerid, "DaysBan", cache_get_field_int(0, "Days", g_CH));
			f(str, "Ник: {FF0000}%s", name), f(temp, "{FFFFFF}Забанил: %s\nЗабанен на: %d дней\nБыл забанен: %s\nIP: %s\nПричина: %s", admin, GetPVarInt(playerid, "DaysBan"), data, ip, email);
			ShowPlayerDialog(playerid, D_NONE, DIALOG_STYLE_MSGBOX, str, temp, "Ok", ""), DeletePVar(playerid, "IBan");
            return true;
		}
  		if(GetPVarInt(playerid, "IGet") == 1)
	    {
		    cache_get_field_content(0, "Name", name, g_CH, sizeof(name));
		    cache_get_field_content(0, "IP", ip, g_CH, sizeof(ip));
		    cache_get_field_content(0, "Email", email, g_CH, sizeof(email));
			f(str, "{FFFFFF}Ник: {FF0000}%s{FFFFFF} | ID: {FF0000}%d", name, cache_get_field_int(0, "ID", g_CH)), f(temp, "{FFFFFF}Денег: %d\nIP: %s\nEmail: %s\nSkin: %d\nПол: %s", cache_get_field_int(0, "Money", g_CH), ip, email, cache_get_field_int(0, "Skin", g_CH), (cache_get_field_int(0, "Sex", g_CH))  ? ("Женский") : ("Мужской"));
			ShowPlayerDialog(playerid, D_NONE, DIALOG_STYLE_MSGBOX, str, temp, "Ok", ""), DeletePVar(playerid, "IGet");
            return true;
		}
		if(GetPVarInt(playerid, "IAdm") == 1)
	    {
		    cache_get_field_content(0, "Name", name, g_CH, sizeof(name));
		    cache_get_field_content(0, "IP", ip, g_CH, sizeof(ip));
		    cache_get_field_content(0, "Admin", email, g_CH, sizeof(email));
		    cache_get_field_content(0, "Date", data, g_CH, sizeof(data));
			f(str, "{FFFFFF}Ник: {FF0000}%s{FFFFFF}", name), f(temp, "{FFFFFF}Назначил: %s\nIP: %s\nДата назначения: %s\nAdm-lvl: %d", email, ip, data, cache_get_field_int(0, "AdmLevel", g_CH));
			ShowPlayerDialog(playerid, D_NONE, DIALOG_STYLE_MSGBOX, str, temp, "Ok", ""), DeletePVar(playerid, "IAdm");
			return true;
		}
	}
	else SendMes(playerid, COLOR_RED, "Данные не найдены.");
	return true;
}

// Стоки
stock PlayerSpawn(playerid)
{
	if(GetPVarInt(playerid, "IsLogged") == 0) return SendMes(playerid, COLOR_RED, "Вы не авторизованы !");
    new idx = GetPVarInt(playerid, "HouseKey");
    switch(GetPVarInt(playerid, "SetSpawn"))
    {
		case 0: SetPlayerPos(playerid,1151.5771,-1772.2440,16.5992);
		case 1: SetPlayerPos(playerid, HouseInfo[idx][hExitX], HouseInfo[idx][hExitY], HouseInfo[idx][hExitZ]), SetPlayerInterior(playerid,HouseInfo[idx][hInt]), SetPlayerVirtualWorld(playerid,HouseInfo[idx][hVirtualWorld]);
	}
	//SetPlayerPos(playerid, SpawnInfo[0][fSpawnX], SpawnInfo[0][fSpawnY], SpawnInfo[0][fSpawnZ]), SetPlayerInterior(playerid, SpawnInfo[0][fInt]), SetPlayerColor(playerid, SpawnInfo[0][fColor]);
	SetPlayerSkin(playerid, GetPVarInt(playerid, "Skin"));
	DollahScoreUpdate(playerid);
	return true;
}

stock DollahScoreUpdate(playerid)
{
	new LevScore;
	foreach (new i : Player)
	{
		LevScore = GetPVarInt(playerid, "Level");
		SetPlayerScore(i, LevScore);
	}
	return true;
}

stock SaveHouse()
{
	static
		query_mysql[200],
		query_mysql_two[400];
	for_c(GetGVarInt("HouseM")-1, -1, i)
    {
	    f(query_mysql, "UPDATE `"PTGH"` SET `EnterX`=%f,`EnterY`=%f,`EnterZ`=%f, `ExitX`=%f,`ExitY`=%f", HouseInfo[i][hEnterX], HouseInfo[i][hEnterY], HouseInfo[i][hEnterZ], HouseInfo[i][hExitX], HouseInfo[i][hExitY]);
	    f(query_mysql_two, "%s,`ExitZ`=%f,`Int`=%d,`Owned`=%d,`Owner`='%s',`Price`=%d,`Lock`=%d WHERE ID = %d", query_mysql, HouseInfo[i][hExitZ], HouseInfo[i][hInt], HouseInfo[i][hOwned], HouseInfo[i][hOwner], HouseInfo[i][hPrice], HouseInfo[i][hLock], HouseInfo[i][hID]);
	    mysql_function_query(g_CH, query_mysql_two, false, "", "");
    }
    return true;
}

stock LoadMySQL()
{
	mysql_set_charset("cp1251_general_ci", g_CH);
 	mysql_function_query(g_CH, "SET NAMES 'cp1251'", false, "", "");
    mysql_function_query(g_CH, "SET CHARACTER SET 'cp1251'", false, "", "");
	printf("\nПодключено к базе данных: %s", (mysql_ping(g_CH)==1 ? ("Успешно"):("Неуспешно")));
	mysql_function_query(g_CH, "SELECT * FROM `"SPA"`", true, "OnLoadSpawn","");
	mysql_function_query(g_CH, "SELECT * FROM `"PTGH"`", true, "OnLoadHouse","");
	mysql_function_query(g_CH, "SELECT * FROM `Interiors`", true, "OnLoadInteriors","");
	return true;
}

stock GoInfo(playerid)
{
	static query_mysql[80];
	f(query_mysql, "SELECT * FROM `AdminsInfo` WHERE Name = '%s'", PlayerName(playerid));
	mysql_function_query(g_CH, query_mysql, true, "OnQueryAdminsInfo", "d", playerid);
	if(GetPVarInt(playerid, "HouseKey") >= 0) f(query_mysql, "SELECT * FROM `"PTGH"` WHERE `Owner` = '%s' AND `ID` = '%d'", PlayerName(playerid), GetPVarInt(playerid, "HouseKey")+1), mysql_function_query(g_CH, query_mysql, true, "OnPlayerCheckHouse", "d", playerid);
	return true;
}

stock SelectSkin(playerid)
{
	SetPlayerPos(playerid, 259.2724,-41.4995,1002.0234), SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerSkin(playerid, (GetPVarInt(playerid, "Sex")) ? (SpawnInfo[0][fSkinGirl][0]) : (SpawnInfo[0][fSkin][0]));
	SetPlayerInterior(playerid, 14), SetPlayerFacingAngle(playerid, 92.6158);
	SetPlayerCameraPos(playerid,257.4099,-41.5846,1002.0234), SetPlayerCameraLookAt(playerid,257.4099,-41.5846,1002.0234);
 	ShowMenuForPlayer(regskin, playerid), FreezePlayer(playerid);
}

stock Block(playerid)
{
    if(GetPVarInt(playerid, "UnBanPlayer") == 1)
    {
        static query_mysql[80];
    	f(query_mysql, "DELETE FROM `"BanList"` WHERE `Nick` = '%s'", PlayerName(playerid)), mysql_function_query(g_CH, query_mysql, false, "","");
		SendMes(playerid, COLOR_YELLOW, "Срок бана вышел, вы разбанены !"), DeletePVar(playerid, "BlockIp"), DeletePVar(playerid, "Block");
		return fix_kick(playerid);
    }
    static str[120];
	if(GetPVarInt(playerid, "BlockIp") == 1)
	{
        if(GetPVarInt(playerid, "BanDate") >= 1) f(str, "{FFFFFF}Ваш Ip заблокирован до: {FF0000}%d{FFFFFF} / {FF0000}%d{FFFFFF} / {FF0000}%d", GetPVarInt(playerid, "Bloack_Msg_Day"), GetPVarInt(playerid, "Bloack_Msg_Month"), GetPVarInt(playerid, "Bloack_Msg_Year")), ShowPlayerDialog(playerid, D_NONE, 0,"{00CD00}Ip заблокирован.", str, "Выход","");
        else ShowPlayerDialog(playerid, D_NONE, 0,"{00CD00}Ip заблокирован.", "{FFFFFF}Ваш Ip заблокирован навсегда !", "Выход","");
		return fix_kick(playerid);
	}
	if(GetPVarInt(playerid, "Block") == 1)
	{
		if(GetPVarInt(playerid, "BanDate") >= 1) f(str, "{FFFFFF}Ваш акаунт заблокирован до: {FF0000}%d{FFFFFF} / {FF0000}%d{FFFFFF} / {FF0000}%d", GetPVarInt(playerid, "Bloack_Msg_Day"), GetPVarInt(playerid, "Bloack_Msg_Month"), GetPVarInt(playerid, "Bloack_Msg_Year")), ShowPlayerDialog(playerid, D_NONE, 0,"{00CD00}Акаунт заблокирован.", str, "Выход","");
        else ShowPlayerDialog(playerid, D_NONE, 0,"{00CD00}Акаунт заблокирован", "{FFFFFF}Ваш акаунт заблокирован навсегда !", "Выход","");
		return fix_kick(playerid);
	}
	return false;
}

stock PlayerPlayMusic(playerid)
{
	SetTimer("StopMusic", 5000, 0);
	PlayerPlaySound(playerid, 1068, 0.0, 0.0, 0.0);
}

stock LoginDialog(playerid)
{
	ShowPlayerDialog(playerid, Login, DIALOG_STYLE_PASSWORD,
		"{76EE00}Вход в аккаунт",
		"\t\t\t{76EE00}Добро пожаловать на Сервер!\n\
		{FF0000}Вы уже зарегистрированы ! Просто введите пароль и нажмите 'Войти'.\n\n\
		{0000FF}Авторизация:{FFC125}\n\
		- Тот же пароль что водили при регистрации",
		"Войти", "Выход"
 	);
  	return true;
}

stock RegisterDialog(playerid) return ShowPlayerDialog(playerid, Register, DIALOG_STYLE_INPUT,
		"{76EE00}Регистрация акаунта !",
		"\t\t\t{76EE00}Добро пожаловать на Сервер!\n\
 		{0000FF}Вы хотите зарегистрироваться ? Введите пароль и нажмите клавишу 'OK'.\n\n\
		{FF0000}Регистрация:{00F5FF}\n\
		- Пароль чувствительный к регистру.\n\
		- В пароле можно использовать символы на кириллице и латинице.",
		"OK", "Выход"
  	);

stock SendMes(playerid, color, fstring[], {Float, _}:...)
{
    static const
    STATIC_ARGS = 3;
    new n = (numargs() - STATIC_ARGS) * BYTES_PER_CELL;
    if (n)
    {
        new message[128], arg_start, arg_end;
        #emit CONST.alt        fstring
        #emit LCTRL          5
        #emit ADD
        #emit STOR.S.pri        arg_start
        #emit LOAD.S.alt        n
        #emit ADD
        #emit STOR.S.pri        arg_end
        do
        {
            #emit LOAD.I
            #emit PUSH.pri
            arg_end -= BYTES_PER_CELL;
            #emit LOAD.S.pri      arg_end
        }
        while (arg_end > arg_start);
        #emit PUSH.S          fstring
        #emit PUSH.C          128
        #emit PUSH.ADR         message
        n += BYTES_PER_CELL * 3;
        #emit PUSH.S          n
        #emit SYSREQ.C         format
        n += BYTES_PER_CELL;
        #emit LCTRL          4
        #emit LOAD.S.alt        n
        #emit ADD
        #emit SCTRL          4
        return SendClientMessage(playerid, color, message);
    }
    else
    {
        return SendClientMessage(playerid, color, fstring);
    }
}

stock WriteLog(const file[],string[])
{
 	new write[256],minute,second,hour,day,month,year;
 	gettime(hour,minute,second);
 	getdate(year,month,day);
 	format(write, sizeof(write), "[Logs]/%s",file);
 	new File:hFile = fopen(write, io_append);
 	format(write, sizeof(write), "[%d.%02d.%02d | %02d:%02d:%02d] %s\r\n",day,month,year,hour,minute,second,string);
	//for_c(strlen(write), 0, i) fputchar(hFile, write[i], false);
 	fwrite(hFile,write);
 	fclose(hFile);
 	return true;
}

stock timestamp (unix_timestamp = 0, & year = 1970, & month = 1, & day  = 1, & hour =  0, & minute = 0, & second = 0)
{
    year = unix_timestamp/31557600, unix_timestamp -= year*31557600, year += 1970;
    if (year % 4 == 0) unix_timestamp -= 21600;
    day = unix_timestamp/86400;
    switch(day)
    {
        case  0..30: second = day, month = 1;
        case  31..58: second = day - 31, month = 2;
        case  59..89: second = day - 59, month = 3;
        case 90..119: second = day - 90, month = 4;
        case 120..150: second = day - 120, month = 5;
        case 151..180: second = day - 151, month = 6;
        case 181..211: second = day - 181, month = 7;
        case 212..242: second = day - 212, month = 8;
        case 243..272: second = day -243, month = 9;
        case 273..303: second = day - 273, month = 10;
        case 304..333: second = day - 304, month = 11;
        case 334..366: second = day - 334, month = 12;
    }
    unix_timestamp -= day*86400, hour = unix_timestamp/3600;
    unix_timestamp -= hour*3600, minute = unix_timestamp/60;
    unix_timestamp -= minute*60, day = second + 1;
    second = unix_timestamp;
}

stock Save_Player(playerid)
{
	if(GetPVarInt(playerid, "IsLogged") == 1)
	{
	    static str[280];
		f(str, "UPDATE `"PTG"` SET \
			`Level` = %d, `Exp` = %d, `Money` = %d, `MoneyBank` = %d, `Kills` = %d, `Deaths` = %d, `Skin` = %d, `Sex` = %d, `HouseKey` = %d, `SetSpawn` = %d, `sdpistol` = %d, `deserteagle` = %d, `shotgun` = %d, `mp5` = %d, `ak47` = %d, `m4` = %d WHERE `ID` = %d",
	 		GetPVarInt(playerid, "Level"), GetPVarInt(playerid, "Exp"), GetPVarInt(playerid, "Money"), GetPVarInt(playerid, "MoneyBank"), GetPVarInt(playerid, "Kills"), GetPVarInt(playerid, "Deaths"), GetPVarInt(playerid, "Skin"), GetPVarInt(playerid, "Sex"), GetPVarInt(playerid, "HouseKey"), GetPVarInt(playerid, "SetSpawn"), 
			GetPVarInt(playerid, "sdpistol"), GetPVarInt(playerid, "deserteagle"), GetPVarInt(playerid, "shotgun"), GetPVarInt(playerid, "mp5"), GetPVarInt(playerid, "ak47"), GetPVarInt(playerid, "m4"), GetPVarInt(playerid, "MySQL_ID")
		); mysql_query(str, -1, -1, g_CH);
	}
	return true;
}

stock Stats(playerid)
{
	static str[300];
	f(str,"\
		 {00FF00}Ваш номер акк \t{FF0000}[{0000FF} %d {FF0000}]{00FF00}\n \
 		Убийств \t\t{FF0000}[{0000FF} %d {FF0000}]{00FF00}\n \
		Смертей \t\t{FF0000}[{0000FF} %d {FF0000}]{00FF00}\n \
		Денег \t\t{FF0000}[{0000FF} %d {FF0000}]{00FF00}\n \
		Пол \t\t\t{FF0000}[{0000FF} %s {FF0000}]{00FF00}"
		,GetPVarInt(playerid, "MySQL_ID"), GetPVarInt(playerid, "Kills"), GetPVarInt(playerid, "Deaths"), GetPVarInt(playerid, "Money"), (GetPVarInt(playerid, "Sex"))  ? ("Женский") : ("Мужской"));
	ShowPlayerDialog(playerid, D_NONE, DIALOG_STYLE_MSGBOX,"Ваша статистика:",str,"Ok","");
	return true;
}

stock SetPos(playerid, Float:x, Float:y, Float:z)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
	else SetPlayerPos(playerid, x, y, z);
	return true;
}

stock PlayerName(playerid)
{
	new name[24];
	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

stock PlayerIP(playerid)
{
	new ip[16];
	GetPlayerIp(playerid,ip,sizeof(ip));
	return ip;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x2, &Float:y2, Float:distance)
{
    new Float:a;

    GetPlayerPos(playerid, x2, y2, a);
    GetPlayerFacingAngle(playerid, a);

    if(GetPlayerVehicleID(playerid))
    {
            GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    }
    x2 += (distance * floatsin(-a, degrees));
    y2 += (distance * floatcos(-a, degrees));
}

public OnPlayerSelect3DMenuBox(playerid,MenuID,boxid)
{
	AS_OnPlayerSelect3DMenuBox(playerid,MenuID,boxid);
	return true;
}