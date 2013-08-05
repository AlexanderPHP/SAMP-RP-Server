Hook:CMD_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(dialogid)
		{
			case DialogSettingMM:
			{
				if(response)
				{
					switch(listitem)
					{
					case 0:{ return true; }
					case 1:{ return true; }
					case 2:{ ShowPlayerDialog(playerid,DialogSexMM,DIALOG_STYLE_LIST,"Меню выбора пола","[0] Мужской\n[1] Женский","Выбрать","Назад"); }
					case 3:
						{
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
							SendClientMessage(playerid, COLOR_GREY, " ");
						}
					case 4: return true;
					}
				}
				else
				{
					new listitems[] = "[1] Команды сервера\n[2] Статистика персонажа\n[3] Репорт\n[4] Правила\t\t\t\t[ {d53e07}Важное{ffffff} ]\n[5] Настройки\n[6] Слив денег\n[7] Безопасность";
					ShowPlayerDialog(playerid, DialogMM, DIALOG_STYLE_LIST, "Личное меню", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DialogSexMM:
			{
				if(response)//Anee ia?ae ia Eaao? eiiieo
				{
					switch(listitem)
					{
					case 0:
						{
							SetPVarInt(playerid, "Sex", 0);
							SendClientMessage(playerid, COLOR_WHITE, "Вы сменили пол на мужской");
							return true;
						}
					case 1:
						{
							SetPVarInt(playerid, "Sex", 1);
							SendClientMessage(playerid, COLOR_WHITE, "Вы сменили пол на женский");
							return true;
						}
					}
				}
				else
				{
					new listitems[] = "[1] Команды сервера\n[2] Статистика персонажа\n[3] Репорт\n[4] Правила\t\t\t\t[ {d53e07}Важное{ffffff} ]\n[5] Настройки\n[6] Слив денег\n[7] Безопасность";
					ShowPlayerDialog(playerid, DialogMM, DIALOG_STYLE_LIST, "Личное меню", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DialogSlivMM:
			{
				if(response)//Anee ia?ae ia Eaao? eiiieo
				{
					new moneys;
					moneys = strval(inputtext);
					if(moneys > 999999999 || moneys < 0) return  SendClientMessage(playerid, COLOR_RED, "Неверная сумма");
					SetPVarInt(playerid, "Money", GetPVarInt(playerid, "Money")-moneys);
					if(GetPVarInt(playerid, "Money") < 0) { SetPVarInt(playerid, "Money", 0);}
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					Save_Player(playerid);
					return true;
				}
				else
				{
					new listitems[] = "[1] Команды сервера\n[2] Статистика персонажа\n[3] Репорт\n[4] Правила\t\t\t\t[ {d53e07}Важное{ffffff} ]\n[5] Настройки\n[6] Слив денег\n[7] Безопасность";
					ShowPlayerDialog(playerid, DialogMM, DIALOG_STYLE_LIST, "Личное меню", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DialogMM:
			{
				if(response)
				{
					switch(listitem)
					{
					case 0: return true;
					case 1: ShowStats(playerid,playerid);
					case 2: return true;
					case 3:
						{
							new rulesdialog[1300];
							format(rulesdialog,sizeof(rulesdialog), "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
							RulesMSG[0],RulesMSG[1],RulesMSG[2],RulesMSG[3],RulesMSG[4],RulesMSG[5],RulesMSG[6],RulesMSG[7],RulesMSG[8],RulesMSG[9],RulesMSG[10],RulesMSG[11],RulesMSG[12],RulesMSG[13],RulesMSG[14],RulesMSG[15],RulesMSG[16],RulesMSG[17],RulesMSG[18],RulesMSG[19],RulesMSG[20],RulesMSG[21]);
							ShowPlayerDialog(playerid,DialogMSGMM,DIALOG_STYLE_MSGBOX,"{FFFFFF}Правила сервера BeautifulLife Role Play", rulesdialog, "Ок", "");
							return true;
						}
					case 4: ShowPlayerDialog(playerid, DialogSettingMM, DIALOG_STYLE_LIST, "Настройки", "[0] Отключить чат семьи\n[1] Включить чат семьи\n[2] Сменить пол\n[3] Очистить чат\n[4] Подать заявку на смену ника\n", "Выбрать", "Назад");
					case 5: ShowPlayerDialog(playerid,DialogSlivMM,DIALOG_STYLE_INPUT,"Слив денег.","Если к Вам попали ворованные/читерские деньги\nОтправьте их администрации сервера.\nИначе Вы будете заблокированы за соучастие.","Слить","Назад");
					case 6: return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
	}
	return true;
}	