public: PayDay()
{
	new string[115];
	new tmphour;
	new tmpminute;
	new tmpsecond;
	gettime(tmphour, tmpminute, tmpsecond);
	FixHour(tmphour);
	tmphour = shifthour;
	if (tmpminute == 0)
	{
		format(string, sizeof(string), "::: Сейчас времени %d:00 часов ::: ",tmphour);
		BroadCast(COLOR_WHITE,string);
		foreach (new i : Player)
		{
			if(GetPVarInt(i,"Level") > 0)
			{
				new playername2[MAX_PLAYER_NAME];
				GetPlayerName(i, playername2, sizeof(playername2));
				new exp = GetPVarInt(i,"Exp");
				new nxtlevel = GetPVarInt(i,"Level")+1;
				new expamount = nxtlevel*4;
				SetPVarInt(i,"Exp", GetPVarInt(i,"Exp")+1);
				if(exp == expamount)
				{
					SetPVarInt(i,"Level", GetPVarInt(i,"Level")+1);
					SetPVarInt(i,"Exp", 0);
				}
				PlayerPlayMusic(i);
				new checks = 0;
				format(string, sizeof(string), "~w~PayDay");
				GameTextForPlayer(i, string, 5000, 1);
				//-------------------------- Работам -------------------
				SendClientMessage(i, COLOR_GREY, "----============ [ КЛИЕНТ БАНКА SA ] ============----");
				format(string, sizeof(string), "- Налог государству: 100 долларов");
				SendClientMessage(i, COLOR_LIGHTRED, string);
				SetPVarInt(i,"MoneyBank", GetPVarInt(i,"MoneyBank")-100);
				
				format(string, sizeof(string), "- Зарплата %d долларов", checks);
				SendClientMessage(i, COLOR_WHITE, string);
				SetPVarInt(i,"MoneyBank", GetPVarInt(i,"MoneyBank")-checks);

				format(string, sizeof(string), "- Текущий баланс: %d долларов", GetPVarInt(i,"MoneyBank"));
				SendClientMessage(i, COLOR_WHITE, string);
				SendClientMessage(i,COLOR_GREY,"----=============================================----");
			}
			if(GetPVarInt(i,"Level") >= 2 && GetPVarInt(i,"Exp") == 0)
			{
				SendClientMessage(i, COLOR_ISPOLZUY, "Поздравляем, Ваш уровень повысился!");
			}
			DollahScoreUpdate(i);
			Save_Player(i);
		}
		SetWorldTime(tmphour);
	}
	return true;
}	