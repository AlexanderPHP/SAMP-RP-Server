//#include <Transport\Benzine>

YCMD:setstat(playerid, params[], help)
{
	if(IsPlayerAdmin(playerid) == 0) return true;
	if(sscanf(params, "uii", params[0], params[1], params[2]))
	{
		SendMes(playerid, COLOR_GREEN, "/setstat [id игрока] [пункт] [значение]");
		SendMes(playerid, COLOR_WHITE, "1-Пол(0,1) 2-Деньги 3-Kills 4-Deaths 5-Skin");
  		return true;
	}
	else
	{
		switch(params[1])
		{
			case 1: SetPVarInt(params[0], "Sex", params[2]);
			case 2: { oGiveMoney(params[0], params[2]); }
  			case 3: SetPVarInt(params[0], "Kills", params[2]);
     		case 4: SetPVarInt(params[0], "Deaths", params[2]);
       		case 5: { oSetSkin(params[0], params[2]); }
		}
	}
	return true;
}

YCMD:stats(playerid, params[], help) return Stats(playerid);

YCMD:mhelp(playerid, params[], help)
{
 SendClientMessageToAll(COLOR_RED, "Епта, работает!");
 return true;
}

YCMD:ban(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 3) return true;
	if(sscanf(params, "uds[50]", params[0], params[1], params[2])) return SendMes(playerid, COLOR_TEST, "Введи: /ban [ид игрока/часть ника] [кол-во дней(2-90)] [причина]");
	if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
	if(params[1] > 90 || params[1] < 2) return SendMes(playerid, COLOR_TEST, "* Минимальное количество дней бана 2, максимальное 90.");
 	if(params[0] == playerid) return MSG_MyID(playerid);
 	static data[16], \
			str[130], query_mysql[200];
	format(str,sizeof(str), "NameServer: %s забанен администратором %s. Причина: %s", PlayerName(params[0]), PlayerName(playerid), params[2]), SendClientMessageToAll(COLOR_RED, str);
	SetPVarInt(playerid, "UnBanDate", gettime() + params[1]*86400), f(data, "%s",date("%dd.%mm.%yyyy",gettime()));
	f(query_mysql, "INSERT INTO `"BanList"` (`Nick`,`Admin`, `IP`, `Date` ,`Reason`,`Days`,`UnbanDate`) VALUES ('%s','%s','%s','%s','%s','%d','%d')", PlayerName(params[0]), PlayerName(playerid), PlayerIP(params[0]), data, params[2], params[1], GetPVarInt(playerid, "UnBanDate"));
	mysql_function_query(g_CH, query_mysql, false, "",""), SetPVarInt(params[0], "Admin", 5), fix_kick(params[0]);
	return true;
}

YCMD:kick(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	if(sscanf(params, "us[50]", params[0], params[1], params[2])) return SendMes(playerid, COLOR_TEST, "Введи: /kick [ид игрока/часть ника] [причина]");
	if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
 	if(params[0] == playerid) return MSG_MyID(playerid);
 	static str[130];
	f(str, "NameServer: %s кикнут администратором %s. Причина: %s", PlayerName(params[0]), PlayerName(playerid), params[2]), SendClientMessageToAll(COLOR_RED, str);
	fix_kick(params[0]);
	return true;
}

YCMD:skick(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 4) return true;
	if(sscanf(params, "u", params[0], params[1], params[2])) return SendMes(playerid, COLOR_TEST, "Введи: /skick [ид игрока/часть ника]");
	if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
 	if(params[0] == playerid) return MSG_MyID(playerid);
	SendMes(playerid, COLOR_YELLOW, "Вы кикнули скрыто игрока: %d", PlayerName(playerid));
	fix_kick(params[0]);
	return true;
}

YCMD:unban(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 3) return true;
	if(sscanf(params, "s[24]", params[0])) return SendMes(playerid, COLOR_WHITE, "Введи: /unban [полный ник игрока]");
    static query_mysql[80];
 	f(query_mysql, "SELECT * FROM `"BanList"` WHERE Nick = '%s'", params[0]), mysql_function_query(g_CH, query_mysql, true, "UnBan", "d", playerid);
	return true;
}

YCMD:admins(playerid, params[], help)
{
    if(GetPVarInt(playerid, "Admin") < 1) return true;
    new str_one[1000], str[300];
	foreach(new i : Player)
	{
     	if(GetPVarInt(i, "Admin") < 1) continue;
		new str_two[140];
		f(str_two, "\n\t{FF0000}[ {FFFFFF}%d{FF0000} ] %s [ {0000FF}%d{FF0000} ]\n", i, PlayerName(i), GetPVarInt(i, "Admin"));
		strcat(str_one, str_two), GivePVarInt(playerid, "Admins", 1);
	}
	if(GetPVarInt(playerid, "Admins") == 0) strcat(str_one, "Админов нету, онлайн.");
	f(str, "{FFFFFF}Список администраторов онлайн:\n%s{FFFFFF}\nВсего администраторов онлайн: {FF0000}%d", str_one, GetPVarInt(playerid, "Admins"));
	ShowPlayerDialog(playerid, D_NONE, DIALOG_STYLE_MSGBOX, "{FFFFFF}Онлайн админов.", str, "Закрыть",""), DeletePVar(playerid, "Admins");
	return true;
}

YCMD:goto(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	if(sscanf(params, "u", params[0])) return SendMes(playerid, COLOR_WHITE, "Введите: /goto [id игрока]");
    if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
	static Float:xyz[3];
	GetPlayerPos(params[0], xyz[0], xyz[1], xyz[2]), SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
	SetPos(playerid, xyz[0]+1, xyz[1]+1, xyz[2]);
	SendMes(playerid, COLOR_WHITE, "Вы телепортировались к игроку: {FF0000}%s", PlayerName(params[0]));
	return true;
}

YCMD:gethere(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 3) return true;
	if(sscanf(params, "u", params[0])) return SendMes(playerid, COLOR_WHITE, "Введите: /gethere [id игрока]");
	if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
	static Float:xyz[3];
	GetPlayerPos(params[0], xyz[0], xyz[1], xyz[2]);
	SetPos(params[0], xyz[0]+1, xyz[1]+1, xyz[2]), SetPlayerInterior(params[0], GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));
	SendMes(params[0], COLOR_WHITE, "Вы были телепортированы администратором: {FF0000}%s", PlayerName(playerid));
	return true;
}

YCMD:gotocar(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	if(sscanf(params, "d", params[0])) return SendMes(playerid, COLOR_WHITE, "Введите: /gotocar [id car]");
    static Float:xyz[3];
	GetVehiclePos(params[0], xyz[0], xyz[1], xyz[2]);
	if(xyz[0] == 0 || xyz[1] == 0 || xyz[2] == 0) return SendMes(playerid, COLOR_RED, "С таким id, машины нету !"); // Проверка хрень :D
	SetPlayerPos(playerid, xyz[0], xyz[1]+5, xyz[2]), SendMes(playerid, COLOR_WHITE, "Вы телепортировались к машине(id): {FF0000}%d", params[0]);
	return true;
}

YCMD:atm(playerid, params[], help)
{
	if(IsABankomat(playerid))
	{
		new listitems[] = "- Снять наличные\n- Баланс";
		ShowPlayerDialog(playerid, DialogBankomat, DIALOG_STYLE_LIST, "Терминал приема платежей", listitems, "Далее", "Выход");
	}
	return true;
}

YCMD:veh(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	if(GetPVarInt(playerid,"CARUP") > 0) return SendMes(playerid, COLOR_TEST,"Необходимо удалить прошлый транспорт! Удалить '/vehd' ");
	if(sscanf(params, "ddd", params[0],params[1],params[2])) return SendMes(playerid, COLOR_WHITE, "Введите: /veh [id машины] [цвет 1] [цвет 2]");
	if(params[0] > 611 || params[0] < 400) return SendMes(playerid, COLOR_TEST, "ID транспорта от 400 до 611!");
	if(params[1] > 126 || params[1] < 0) return SendMes(playerid, COLOR_TEST, "ID цвета от 0 до 126!");
	if(params[2] > 126 || params[2] < 0) return SendMes(playerid, COLOR_TEST, "ID цвета от 0 до 126!");
	static Float:xyz[3];
	GetPlayerPos(playerid, xyz[0], xyz[1], xyz[2]), SetPVarInt(playerid, "AddColor1", params[1]), SetPVarInt(playerid, "AddColor2", params[2]);
	new carid = CreateVehicle(params[0], xyz[0], xyz[1], xyz[2], 0.0, params[1], params[2], 60000);
	SetVehicleVirtualWorld(carid, 0), PutPlayerInVehicle(playerid, carid, 0);
	SendMes(playerid, COLOR_WHITE, "Транспорт создан. ID: %d", carid), SetPVarInt(playerid,"CARUP", carid);
	SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), GetPlayerVirtualWorld(playerid));
	new vehicleid = GetPlayerVehicleID(playerid);
	FuelVeh[vehicleid] = 300;
	starting[playerid] = true;
	light_car[playerid] = false;
	return true;
}

YCMD:time(playerid, params[], help)
{
	new string[256];
	new sendername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, sendername, sizeof(sendername));
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		ApplyAnimation(playerid,"COP_AMBIENT","Coplook_watch",4.1,0,0,0,0,0,1);
	}
	if(GetPVarInt(playerid,"Sex") == 0)
	{
		format(string, sizeof(string), "%s взглянул на часы", sendername);
		ProxDetector(25.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	else if(GetPVarInt(playerid,"Sex") == 0)
	{
		format(string, sizeof(string), "%s взглянула на часы", sendername);
		ProxDetector(25.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	}
	new mtext[20];
	new year, month,day;
	getdate(year, month, day);
	if (month == 1) {mtext = "January";}
	else if (month == 2) {mtext = "February";}
	else if (month == 3) {mtext = "March";}
	else if (month == 4) {mtext = "April";}
	else if (month == 5) {mtext = "Maya";}
	else if (month == 6) {mtext = "June";}
	else if (month == 7) {mtext = "July";}
	else if (month == 8) {mtext = "August";}
	else if (month == 9) {mtext = "Sentebrya";}
	else if (month == 10) {mtext = "October";}
	else if (month == 11) {mtext = "November";}
	else if (month == 12) {mtext = "December";}
	new hour,minuite,second;
	gettime(hour,minuite,second);
	FixHour(hour);
	hour = shifthour;
	if (minuite < 10)
	{
		/*if (PlayerInfo[playerid][pJailTime] > 0)
		{
			format(string, sizeof(string), "~y~%d ~y~%s~n~~w~%d:0%d~n~ ~g~ concluded ~w~%d", day, mtext, hour, minuite, PlayerInfo[playerid][pJailTime]-10);
		}
		else
		{*/
		format(string, sizeof(string), "~g~Imperial Role Play~n~~y~%d ~y~%s~n~~w~%d:0%d", day, mtext, hour, minuite);
		//}
	}
	else
	{
		/*if (PlayerInfo[playerid][pJailTime] > 0)
		{
			format(string, sizeof(string), "~y~%d ~y~%s~n~~w~%d:%d~n~ ~g~ concluded ~w~%d", day, mtext, hour, minuite, PlayerInfo[playerid][pJailTime]-10);
		}
		else
		{*/
		format(string, sizeof(string), "~g~Imperial Role Play~n~~y~%d ~y~%s~n~~w~%d:%d", day, mtext, hour, minuite);
		//}
	}
	GameTextForPlayer(playerid, string, 4000, 1);
	return true;
}
		
YCMD:mm(playerid, params[], help)
{
	if(GetPVarInt(playerid, "IsLogged") == 1)
	{
		new listitems[] = "[1] Команды сервера\n[2] Статистика персонажа\n[3] Репорт\n[4] Правила\t\t\t\t[ {d53e07}Важное{ffffff} ]\n[5] Настройки\n[6] Слив денег\n[7] Безопасность";
		ShowPlayerDialog(playerid, DialogMM, DIALOG_STYLE_LIST, "Личное меню", listitems, "Выбрать", "Отмена");
	}
	return true;
}

YCMD:me(playerid, params[], help)
{
	new sendername[MAX_PLAYER_NAME];
	new string[48];
	GetPlayerName(playerid, sendername, sizeof(sendername));
	if(GetPVarInt(playerid, "IsLogged") == 0) return SendClientMessage(playerid, COLOR_YELLOW, "Вы не авторизованы!");
	sscanf(params, "s", string);
	if(!strlen(string))  return SendClientMessage(playerid, COLOR_YELLOW, "Введите /me [действие]!");
	format(string, sizeof(string), "%s %s", sendername, string);
	ProxDetector(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	SetPlayerChatBubble(playerid,string,COLOR_PURPLE,30.0,10000);
	return true;
}

YCMD:sms(playerid, params[], help)
{
	new sendername[MAX_PLAYER_NAME];
	new givename[MAX_PLAYER_NAME];
	new string[68];
	new val;
	new result[48];
	GetPlayerName(playerid, sendername, sizeof(sendername));
	if(GetPVarInt(playerid, "IsLogged") == 0) return SendClientMessage(playerid, COLOR_YELLOW, "Вы не авторизованы!");
	sscanf(params, "is",val, result);
	if(!strlen(result))  return SendClientMessage(playerid, COLOR_YELLOW, "Введите /sms [номер телефона/id] [текст сообщения]!");
	if(val>=5)
	{
		foreach(new i : Player)
		{
			if(GetPVarInt(i, "phone") == val)
			{
				val = i;
			}
		}
	}
	GetPlayerName(val, givename, sizeof(givename));
	if (IsPlayerConnected(val))
	{
		if(val != INVALID_PLAYER_ID)
		{
			SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-20);
			format(string, sizeof(string), "SMS: %s. Отправитель: %s[%d]",(result),sendername, playerid);
			SendClientMessage(val, 0xFDE640AA, string);
			PlayerPlaySound(val, 1052, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			format(string, sizeof(string), "SMS: %s. Получатель: %s[%d]",(result), givename, val);
			SendClientMessage(playerid,  0xFDE640AA, string);
			SendClientMessage(playerid,  COLOR_WHITE, "- Сообщение доставлено");
			format(string, sizeof(string), "%s достает мобильный телефон", sendername);
			ProxDetector(5.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			SetPlayerChatBubble(playerid,string,COLOR_PURPLE,30.0,10000);
			return true;
		}
	}
	
	return true;
}

YCMD:myskill(playerid, params[], help)
{
	new stringskill[700];
	new points[6],percent[2] = "%";
	points[0] = 100 - GetPVarInt(playerid,"sdpistol");
	points[1] = 100 - GetPVarInt(playerid,"deserteagle");
	points[2] = 100 - GetPVarInt(playerid,"shotgun");
	points[3] = 100 - GetPVarInt(playerid,"mp5");
	points[4] = 100 - GetPVarInt(playerid,"ak47");
	points[5] = 100 - GetPVarInt(playerid,"m4");
	format(stringskill,sizeof(stringskill),"SDPistol:\t[%s]%d%s\nDeagle:\t[%s]%d%s\nShotGun:\t[%s]%d%s\nMP5\t\t[%s]%d%s\nAK47:\t\t[%s]%d%s\nM4A1:\t\t[%s]%d%s",
	ToDevelopSkills(GetPVarInt(playerid,"sdpistol"),points[0]),GetPVarInt(playerid,"sdpistol"),percent,
	ToDevelopSkills(GetPVarInt(playerid,"deserteagle"),points[1]),GetPVarInt(playerid,"deserteagle"),percent,
	ToDevelopSkills(GetPVarInt(playerid,"shotgun"),points[2]),GetPVarInt(playerid,"shotgun"),percent,
	ToDevelopSkills(GetPVarInt(playerid,"mp5"),points[3]),GetPVarInt(playerid,"mp5"),percent,
	ToDevelopSkills(GetPVarInt(playerid,"ak47"),points[4]),GetPVarInt(playerid,"ak47"),percent,
	ToDevelopSkills(GetPVarInt(playerid,"m4"),points[5]),GetPVarInt(playerid,"m4"),percent);
	ShowPlayerDialog(playerid,43,DIALOG_STYLE_MSGBOX,"Навыки владением оружием",stringskill,"Готово","");
	return 1;
}

YCMD:vehd(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	if(!GetPVarInt(playerid,"CARUP")) return SendMes(playerid, COLOR_TEST,"Необходимо создать транспорт!");
	SendMes(playerid, COLOR_WHITE, "Транспорт удален. ID: %d", GetPVarInt(playerid,"CARUP"));
	DestroyVehicle(GetPVarInt(playerid,"CARUP")), DeletePVar(playerid,"CARUP");
	return true;
}

YCMD:makeadmin(playerid, params[], help)
{
    if(!IsPlayerAdmin(playerid)) return true;
    if(sscanf(params, "d", params[0])) return SendMes(playerid, COLOR_WHITE, "Введите: /makeadmin [id]");
    if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
    if(GetPVarInt(params[0], "Admin") >= 1) return SendMes(playerid, COLOR_RED, "Это администратор !");
	static query_mysql[180], data[16];
	f(data, "%s", date("%dd.%mm.%yyyy",gettime())), SetPVarInt(playerid, "Admin", 1);
	f(query_mysql, "INSERT INTO `AdminsInfo` (`Name`,`Admin`, `IP`, `Date`) VALUES ('%s','%s','%s','%s')", PlayerName(params[0]), PlayerName(playerid), PlayerIP(params[0]), data), mysql_function_query(g_CH, query_mysql, false, "", "");
	SendMes(params[0], COLOR_YELLOW, "Вас назначил администратором: {FF0000}%s", PlayerName(playerid));
	SendMes(playerid, COLOR_YELLOW, "Вы назначили администратора: {FF0000}%s", PlayerName(params[0]));
	return true;
}


YCMD:giveadmin(playerid, params[], help)
{
    if(!IsPlayerAdmin(playerid)) return true;
    if(sscanf(params, "ds[7]", params[0], params[1])) return SendMes(playerid, COLOR_WHITE, "Введите: /giveadmin [id] [+/-/remove]");
    if(GetPVarInt(params[0], "IsLogged") == 0) return MSG_NoneOnlinePlayer(playerid);
    if(GetPVarInt(params[0], "Admin") == 0) return SendMes(playerid, COLOR_RED, "Это не администратор !");
    static query_mysql[80];
	if(strcmp(params[1], "+", true) == 0)
 	{
 	    if(GetPVarInt(params[0], "Admin") >= 5) return SendMes(playerid, COLOR_TEST, "У администратора: %s | Adm Level: %d | В повышении отказано !", PlayerName(params[0]), GetPVarInt(params[0], "Admin"));
 	    SendMes(playerid, COLOR_YELLOW, "Вы повышели администратора: {FF0000}%s", PlayerName(params[0]));
  		SendMes(params[0], COLOR_YELLOW, "Вы повишены администратором: {FF0000}%s", PlayerName(playerid));
  		GivePVarInt(params[0], "Admin", 1), SendMes(params[0], COLOR_YELLOW, "Теперь у вас адм-лвл: {FF0000}%d", GetPVarInt(params[0], "Admin"));
        f(query_mysql, "UPDATE `AdminsInfo` SET `AdmLevel` = '%d' WHERE `Name` = '%s'", GetPVarInt(params[0], "Admin"), PlayerName(params[0]));
	}
    if(strcmp(params[1], "-", true) == 0)
    {
        if(GetPVarInt(params[0], "Admin") <= 1) return SendMes(playerid, COLOR_TEST, "У администратора: %s | Adm Level: %d | В понижении отказано !", PlayerName(params[0]), GetPVarInt(params[0], "Admin"));
    	SendMes(playerid, COLOR_YELLOW, "Вы понизили администратора: {FF0000}%s", PlayerName(params[0]));
  		SendMes(params[0], COLOR_YELLOW, "Вас понизил администратор: {FF0000}%s", PlayerName(playerid));
  		GivePVarInt(params[0], "Admin", -1), SendMes(params[0], COLOR_YELLOW, "Теперь у вас адм-лвл: {FF0000}%d", GetPVarInt(params[0], "Admin"));
        f(query_mysql, "UPDATE `AdminsInfo` SET `AdmLevel` = '%d' WHERE `Name` = '%s'", GetPVarInt(params[0], "Admin"), PlayerName(params[0]));
	}
    if(strcmp(params[1], "remove", true) == 0)
    {
    	SendMes(playerid, COLOR_YELLOW, "Вы сняли администратора: {FF0000}%s", PlayerName(params[0]));
  		SendMes(params[0], COLOR_YELLOW, "Вас сняли с поста администратора: {FF0000}%s", PlayerName(playerid));
  		SetPVarInt(params[0], "Admin", 0), f(query_mysql, "DELETE FROM `AdminsInfo` WHERE `Name`='%s'", PlayerName(params[0]));
	}
	mysql_function_query(g_CH, query_mysql, false, "","");
	return true;
}

YCMD:info(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") < 2) return true;
	static name[24], other[5];
    if(sscanf(params, "s[24]s[5]", name, other)) return SendMes(playerid, COLOR_WHITE, "Введите: /info [name] [get/ban/adm]");
    static query_mysql[80];
    if(strcmp(other, "ban", true) == 0) f(query_mysql, "SELECT * FROM `"BanList"` WHERE `Nick` = '%s'", name), SetPVarInt(playerid, "IBan", 1);
    if(strcmp(other, "get", true) == 0) f(query_mysql, "SELECT * FROM `"PTG"` WHERE `Name` = '%s'", name), SetPVarInt(playerid, "IGet", 1);
    if(strcmp(other, "adm", true) == 0) f(query_mysql, "SELECT * FROM `AdminsInfo` WHERE `Name` = '%s'", name), SetPVarInt(playerid, "IAdm", 1);
    mysql_function_query(g_CH, query_mysql, true, "Info", "d", playerid);
	return true;
}

YCMD:house(playerid, params[], help)
{
    if(GetPVarInt(playerid, "IsLogged") == 0) return true;
    if(GetPVarInt(playerid, "Admin") < 3) return true;
    if(sscanf(params, "ds[24]", params[0], params[1]))
	{
		SendMes(playerid, COLOR_GREEN, "/house [id дома] [пункт] ");
		SendMes(playerid, COLOR_WHITE, "t - Это возле выхода дома..");
		SendMes(playerid, COLOR_WHITE, "e - Это в инте, в том доме..");
		return true;
	}
	if(params[0]+1 > GetGVarInt("HouseM")-1) return SendMes(playerid, COLOR_RED, "Неверный ID дома !");
	if(strcmp(params[1], "e",true) == 0)
	{
		SetPlayerInterior(playerid, HouseInfo[params[0]][hInt]);
		SetPlayerPos(playerid,HouseInfo[params[0]][hExitX],HouseInfo[params[0]][hExitY],HouseInfo[params[0]][hExitZ]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
		SetPlayerVirtualWorld(playerid, HouseInfo[params[0]][hVirtualWorld]);
	}
	if(strcmp(params[1], "t",true) == 0)
	{
	    SetPlayerInterior(playerid, 0);
		SetPlayerPos(playerid,HouseInfo[params[0]][hEnterX],HouseInfo[params[0]][hEnterY],HouseInfo[params[0]][hEnterZ]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
	}
	SaveHouse();
	return true;
}
YCMD:buyhouse(playerid, params[], help)
{
    if(GetPVarInt(playerid, "HouseKey") >= 0) return SendMes(playerid, COLOR_TEST, "У вас уже есть дом !");
	for_c(GetGVarInt("HouseM")-1, -1, idx)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 5.0, HouseInfo[idx][hEnterX], HouseInfo[idx][hEnterY], HouseInfo[idx][hEnterZ]) && GetPlayerVirtualWorld(playerid) == 0)
	    {
	        if(HouseInfo[idx][hOwned] == 1) return SendMes(playerid, COLOR_RED, "Этот дом не продаеться !");
			static str[200];
			SetPVarInt(playerid, "PlayerHouse", idx);
			SellHome(str), ShowPlayerDialog(playerid, D_DIALOGS+3, 0,"{00CD00}Дом", str, "Купить","Отмена"), DeletePVar(playerid, "PlayerHome");
			return true;
		}
 	}
 	SendMes(playerid, COLOR_YELLOW, "Вы далеко от какого-то либо дома !");
	return true;
}

YCMD:open(playerid, params[], help)
{
	if(GetPVarInt(playerid, "HouseKey") == -1) return SendMes(playerid, COLOR_GREEN, "У вас нету дома !");
	new housee = GetPVarInt(playerid, "HouseKey");
	switch(HouseInfo[housee][hLock])
	{
		case 1: HouseInfo[housee][hLock] = 0, GameTextForPlayer(playerid, "~w~Door ~g~Unlocked", 5000, 6), PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		case 0: HouseInfo[housee][hLock] = 1, GameTextForPlayer(playerid, "~w~Door ~r~Locked", 5000, 6), PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	}
	return true;
}

YCMD:exit(playerid, params[], help)
{
	for_c(GetGVarInt("HouseM")-1, -1, i)
	{
		if (IsPlayerInRangeOfPoint(playerid, 5, HouseInfo[i][hExitX], HouseInfo[i][hExitY], HouseInfo[i][hExitZ]) && HouseInfo[i][hVirtualWorld] == GetPlayerVirtualWorld(playerid))
		{
			SetPlayerInterior(playerid,0), SetPlayerVirtualWorld(playerid, 0);
			SetPlayerPos(playerid,HouseInfo[i][hEnterX],HouseInfo[i][hEnterY],HouseInfo[i][hEnterZ]);
		}
	}
	return true;
}

YCMD:sellhome(playerid, params[], help)
{
	if(GetPVarInt(playerid, "HouseKey") == -1) return SendMes(playerid, COLOR_TEST, "У вас нету дома !");
    static str[80];
    f(str,"{FFFFFF}Вы хотите продать дом за: {FF0000}%d$", HouseInfo[GetPVarInt(playerid, "HouseKey")][hPrice]/2);
    ShowPlayerDialog(playerid, D_DIALOGS+4, 0, "Продажа дома !",str,"Да","Выход");
	return true;
}

YCMD:addhouse(playerid, params[], help)
{
	if(GetPVarInt(playerid, "Admin") <= 4) return true;
    static paramsFo;
	if(sscanf(params, "dd", paramsFo, params[1])) return SendMes(playerid, COLOR_AQUA, "Введи: /addhouse [1-%d] [цена]", GetGVarInt("Inter"));
	if(paramsFo < 1 || paramsFo > GetGVarInt("Inter")) return SendMes(playerid, COLOR_TEST, "Неверный интерьер | 1-%d |", GetGVarInt("Inter"));
	if(GetPlayerVirtualWorld(playerid) > 0 || GetPlayerInterior(playerid) > 0) return SendMes(playerid, COLOR_TEST, "Вы в другом виртуальном мире или в интерьере ! Inter: %d, VirtualWorld: %d", GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	GiveGVarInt("HouseM", 1, 0);
	static Float:PosEnter[4],
			query_mysql[350],
				StreetsName[20][] = {"Боровицкая", "Бочкова", "Братеевская", "Брянская", "Вавилова", "Ватутина", "Верземнека", "Большая Молчановка", "Викторенко", "Владимирская", "Воздушная", "Волхонка", "Гаражная", "Гвардейская", "Городская", "Губкина", "Дашков", "Дворцовая", "Деловая", "Дивизионная"};
	GetPlayerPos(playerid, PosEnter[0], PosEnter[1], PosEnter[2]);
	new
		RandomStreet = random(sizeof(StreetsName)),
		HouseM = GetGVarInt("HouseM");
	f(query_mysql, "INSERT INTO `"PTGH"` (`ID`, `EnterX`, `EnterY`, `EnterZ`, `ExitX`, `ExitY`, `ExitZ`,  `Price`, `Int`, `VirtualWorld`, `NameStreet`, `Admin`) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%s', '%s')",
	HouseM, PosEnter[0], PosEnter[1], PosEnter[2], Interior[paramsFo][vX], Interior[paramsFo][vY], Interior[paramsFo][vZ], params[1], Interior[paramsFo][vInt], HouseM, StreetsName[RandomStreet], PlayerName(playerid));
	mysql_function_query(g_CH, query_mysql, false, "","");
	HouseInfo[HouseM][hID] = HouseM;
  	HouseInfo[HouseM][hEnterX] = PosEnter[0], HouseInfo[HouseM][hEnterY] = PosEnter[1], HouseInfo[HouseM][hEnterZ] = PosEnter[2];
    HouseInfo[HouseM][hExitX] = Interior[paramsFo][vX], HouseInfo[HouseM][hExitY] = Interior[paramsFo][vY], HouseInfo[HouseM][hExitZ] = Interior[paramsFo][vZ];
	HouseInfo[HouseM][hPrice] = params[1], HouseInfo[HouseM][hInt] = Interior[paramsFo][vInt], HouseInfo[HouseM][hLock] = 0, HouseInfo[HouseM][hOwned] = 0;
  	strmid(HouseInfo[HouseM][hOwner], "None", 0, strlen("None"), 24);
  	strmid(HouseInfo[HouseM][hNameStreet], StreetsName[RandomStreet], 0, strlen(StreetsName[RandomStreet]), MAX_PLAYER_NAME);
 	SendMes(playerid, COLOR_YELLOW, "Ты добавил новый дом: №%d | Цена: $%d.", HouseM, params[1]);
	Create3DTextLabel("Нажмите альт чтобы выйти..", COLOR_AQUA, HouseInfo[HouseM][hExitX], HouseInfo[HouseM][hExitY], HouseInfo[HouseM][hExitZ], 10.0, HouseInfo[HouseM][hVirtualWorld], 1);
  	HouseInfo[HouseM][hPickup] = CreatePickup(1274, 23, HouseInfo[HouseM][hEnterX], HouseInfo[HouseM][hEnterY], HouseInfo[HouseM][hEnterZ],-1);
   	HouseInfo[HouseM][hIcon] = CreateDynamicMapIcon(HouseInfo[HouseM][hEnterX], HouseInfo[HouseM][hEnterY], HouseInfo[HouseM][hEnterZ], 31, COLOR_WHITE, -1, -1, -1, 400.0);
 	SaveHouse();
	return true;
}

YCMD:inter(playerid, params[], help)
{
    if(GetPVarInt(playerid, "Admin") < 1) return true;
    new str_one[1200];
	for_c(GetGVarInt("Inter")-1, -1, i)
	{
		static str_two[35];
		f(str_two, "[№-%d] %s\n", Interior[i][vID], Interior[i][vName]);
		strcat(str_one, str_two), GivePVarInt(playerid, "Interers", 1);
	}
	if(GetPVarInt(playerid, "Interers") == 0) strcat(str_one, "Интерьеров нету.");
	ShowPlayerDialog(playerid, D_DIALOGS+8, DIALOG_STYLE_LIST, "{FFFFFF}Список интерьеров{FF0000}:", str_one, "Ok","Выход"), DeletePVar(playerid, "Interers");
	return true;
}

YCMD:setspawn(playerid, params[], help) return ShowPlayerDialog(playerid,D_DIALOGS+6,DIALOG_STYLE_LIST,"{FF0000}Смена места спавна..","{FFFFFF}Респа\n{FFFF00}Дом","Выбрать","Отмена");

YCMD:v(playerid, params[], help)
{
	new carid,color1,color2,Float:Pos[4];
	if(sscanf(params, "ddd", carid,color1,color2)) return SendMes(playerid, COLOR_RED, "Введи: /spawnveh [400 < carid < 611] [Color-1] [Color-2]");
	if(carid < 400 || carid > 611) return SendMes(playerid, COLOR_RED, "Введи: /spawnveh [400 < carid < 611] [Color-1] [Color-2]");
	GetPlayerPos(playerid, Pos[0],Pos[1],Pos[2]);
	GetPlayerFacingAngle(playerid, Pos[3]);
	if(IsPlayerInAnyVehicle(playerid)) { DestroyVehicle(GetPlayerVehicleID(playerid)); }
	GetXYInFrontOfPlayer(playerid, Pos[0], Pos[1], 5);
	new PVeh = CreateVehicle(carid, Pos[0], Pos[1], Pos[2], Pos[3]+180, -1, -1, -1);
	LinkVehicleToInterior(PVeh, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(PVeh, GetPlayerVirtualWorld(playerid));
	new query_mysql[140]; 
	f(query_mysql, "INSERT INTO `Cars` (`car_id`,`fuel`, `x`, `y` ,`z`) VALUES ('%d','300','%f','%f','%f')", PVeh, Pos[0], Pos[1], Pos[2]);
	mysql_function_query(g_CH, query_mysql, false, "","");
    return 1;
}
 
 
YCMD:test(playerid,params[],help)
{
	new
	Float:fPX, Float:fPY, Float:fPZ,
	Float:fVX, Float:fVY, Float:fVZ,str[250],
	Float:vPX, Float:vPY, Float:vPZ,
	Float:vZAngl,carid;

	// Change me to change the scale you want. A larger scale increases the distance from the camera.
	carid = GetPlayerVehicleID(playerid);
	GetVehicleZAngle(carid, vZAngl);
	GetVehiclePos(carid,vPX,vPY,vPZ);
	GetPlayerCameraPos(playerid, fPX, fPY, fPZ);
	GetPlayerCameraFrontVector(playerid, fVX, fVY, fVZ);
	format(str,sizeof(str),"Camera Position:%f %f %f\n Camera Front Vector: %f,%f,%f\n Vehicle Position:%f %f %f\n Vehicle ZAngle: %f",fPX, fPY, fPZ,fVX, fVY, fVZ,vPX,vPY,vPZ,vZAngl);
	WriteLog("camera.txt",str);
 	return SendMes(playerid,COLOR_RED,str);
}

/*YCMD:setpos(playerid,params[],help)
{
//new Float:p[4];
//GetPlayerPos(playerid,p[0],p[1],p[2]);
//GetPlayerFacingAngle(playerid,p[3]);
new menu = Create3DMenu(-1654.4026,1209.6061,21.1563,316.1330,4,playerid);
for(new i = 0; i < 4; i++) SetBoxText(menu,i,"Я избранный!",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
Select3DMenu(playerid,menu);
return true;
//

}

YCMD:setpos1(playerid,params[],help)
{
	
	SetPlayerCameraLookAt(playerid,-1664.379150, 1207.728759, 23.454399,2);
	return true;
}

YCMD:setpos2(playerid,params[],help)
{
	//SetPlayerCameraPos(playerid, -1664.379150, 1207.728759, 23.454399);
	SetPlayerCameraLookAt(playerid,-1664.379150 + 1*floatsin(60,degrees),1207.728759 + 2*floatcos(60,degrees),23.454399);
	SetPlayerPos(playerid, -1656.9027,1211.2896,7.2500);
	return true;
	
}*/
YCMD:setp(playerid,params[],help)
{
//	SetPlayerPos(playerid, -1657.2484, 1211.0175, 7.2500);
	SetPlayerPos(playerid, -1967.2998,293.7426,35.2000);
	return true;
	
}

YCMD:setposr(playerid,params[],help)
{
	SetCameraBehindPlayer(playerid);
	SetPlayerVirtualWorld(playerid,0);
	TogglePlayerControllable(playerid,1);	
	return true;
}

YCMD:goauto(playerid,params[],help)
{
	SetPlayerPos(playerid, -1656.9027,1211.2896,7.2500);
	return true;
}

