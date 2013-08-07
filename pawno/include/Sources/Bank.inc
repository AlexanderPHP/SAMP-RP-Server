new BankPic[2];
new money;

Hook:Bank_OnGameModeInit()
{	
	BankPic[0] = CreatePickup(1318,23,1411.5004,-1699.6112,13.5395);//Aaie aoia
	BankPic[1] = CreatePickup(1318,23,2304.6968,-16.1388,26.7422);//Aaie auoia
	CreateObject(2942, 1921.5, -1765.8000, 13.2, 0.0, 0.0, 180.0);
	CreateObject(2942, 2744, -1639.5, 12.7, 0.0, 0.0, 270.0);
	CreateObject(2942, 1831.1999, -1891.6999, 13.1, 0.0, 0.0, 270.0);
	CreateObject(2942, 1457.9000, -1754.9000, 13.2, 0.0, 0.0, 270.0);
	CreateObject(2942, 1647.0999, -1171.9000, 23.7, 0.0, 0.0, 180.0);
	CreateObject(2942, 285.8999, -1749.4000, 4.2, 0.0, 0.0, 180.0);
	CreateObject(2942, -78.1, -1169.0999, 1.8, 0.0, 0.0, 250.0);
	CreateObject(2942, -2028.6999, -102, 34.8, 0.0, 0.0, 182.0);
	CreateObject(2942, -1980.5999, 131.8999, 27.3, 0.0, 0.0, 270.0);
	CreateObject(2942, -1677.1999, 431, 6.8, 0.0, 0.0, 44.5);
	CreateObject(2942, -262, 1414.9000, 6.7, 0.0, 0.0, 70.0);
	CreateObject(2942, -1691.4000, 948.4000, 24.5, 0.0, 0.0, 318.5);
	CreateObject(2942, 1142.8000, -1763.3000, 13.3, 0.0, 0.0, 90.0);
	return true;
}

Hook:Bank_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{	
	if(newkeys == 16)
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			if(IsABankomat(playerid))
			{
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
				ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
				new listitems[] = "- Снять наличные\n- Баланс";
				ShowPlayerDialog(playerid, DialogBankomat, DIALOG_STYLE_LIST, "Терминал приема платежей", listitems, "Далее", "Выход");
				return true;
			}
			if(PlayerToPoint(1.0,playerid,2308.8201,-13.2660,26.7422))
			{
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
				ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
				new listitems[] = "[1] Снять со счета\n[2] Положить на счет\n[3] Информация";
				ShowPlayerDialog(playerid, BankDialog, DIALOG_STYLE_LIST, "Банковские услуги", listitems, "Выбрать", "Отмена");
				return true;
			}
		}
	}
	return true;
}

Hook:Bank_OnPlayerPickUpPickup(playerid, pickupid)
{	
	if(pickupid == BankPic[0]) //Банк вход
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerPos(playerid,2307.6462,-15.7474,26.7496);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 281.2246);
	}
	else if(pickupid == BankPic[1]) //Банк выход
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerPos(playerid,1414.14,-1702.78,13.5395);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 209.7472);
	}
	return true;
}

Hook:Bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[256];
	if(response)
	{
		switch(dialogid)
		{
			case BankDialogCut:
			{			
				if(response)
				{
					new summa;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						format(string,sizeof(string), "Баланс Вашего счета: %d долларов\nВведите нужную Вам сумму.", GetPVarInt(playerid, "MoneyBank"));
						ShowPlayerDialog(playerid,BankDialogCut,DIALOG_STYLE_INPUT,"Снятие со счета",string,"Снять","Назад");
					}
					summa = strval(inputtext);
					if(GetPVarInt(playerid, "MoneyBank") < summa) return SendClientMessage(playerid, COLOR_GREY, "У Вас нет столько денег!");
					if(summa < 1 || summa > 1000000) { SendClientMessage(playerid, COLOR_GREY, "Нельзя снять более 1000000 долларов!"); return true; }
					SetPVarInt(playerid, "Money", GetPVarInt(playerid, "Money")+summa);
					SendClientMessage(playerid, COLOR_YELLOW2, "::: Возьмите, пожалуйста, Ваш чек :::");
					SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-summa);
					format(string, sizeof(string), "Снято со счета: %d долларов",summa);
					SendClientMessage(playerid, COLOR_GRAD4, string);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, sizeof(string), "Новый баланс: %d долларов", GetPVarInt(playerid, "MoneyBank"));
					SendClientMessage(playerid, 0xFEBC41AA, string);
					SendClientMessage(playerid, COLOR_YELLOW2, "::: Возьмите, пожалуйста, Ваш чек :::");
					return true;
				}
				else
				{
					new listitems[] = "[1] Снять со счета\n[2] Положить на счет\n[3] Информация";
					ShowPlayerDialog(playerid, BankDialog, DIALOG_STYLE_LIST, "Банковские услуги", listitems, "Выбрать", "Отмена");
				}
			}
			case BankDialogPut:
			{			
				if(response)
				{
					new summa;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						format(string,sizeof(string), "Баланс Вашего счета: %d долларов\nВведите нужную Вам сумму.", GetPVarInt(playerid, "MoneyBank"));
						ShowPlayerDialog(playerid,BankDialogPut,DIALOG_STYLE_INPUT,"Положить на счет",string,"Ок","Отмена");
					}
					summa = strval(inputtext);
					if(GetPVarInt(playerid, "Money") < summa) return SendClientMessage(playerid, COLOR_GREY, "У Вас нет столько денег!");
					if(summa < 1 || summa > 1000000) { SendClientMessage(playerid, COLOR_GREY, "Нельзя снять более 1000000 долларов!"); return true; }
					SetPVarInt(playerid, "Money", GetPVarInt(playerid, "Money")-summa);
					SendClientMessage(playerid, COLOR_YELLOW2, "::: Возьмите, пожалуйста, Ваш чек :::");
					SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")+summa);
					format(string, sizeof(string), "Положено на счет: %d долларов",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, sizeof(string), "Новый баланс: %d долларов", GetPVarInt(playerid, "MoneyBank"));
					SendClientMessage(playerid, COLOR_WHITE, string);
					SendClientMessage(playerid, COLOR_YELLOW2, "::: Возьмите, пожалуйста, Ваш чек :::");
					return true;
				}
				else
				{
					new listitems[] = "[1] Снять со счета\n[2] Положить на счет\n[3] Информация";
					ShowPlayerDialog(playerid, BankDialog, DIALOG_STYLE_LIST, "Банковские услуги", listitems, "Выбрать", "Отмена");
				}
			}
			case DialogBankomatInfo:
			{
				if(response)
				{
					new listitems[] = "- Снять наличные\n- Баланс";
					ShowPlayerDialog(playerid, DialogBankomat, DIALOG_STYLE_LIST, "Терминал приема платежей", listitems, "Далее", "Выход");
					return true;
				}
			}
			case BankDialog:
			{			
				new sendername[MAX_PLAYER_NAME];
				GetPlayerName(playerid, sendername, sizeof(sendername));
				if(response)
				{
					switch(listitem)
					{
					case 0:
						{
							format(string,sizeof(string), "Баланс Вашего счета: %d долларов\nВведите нужную Вам сумму.", GetPVarInt(playerid, "MoneyBank"));
							ShowPlayerDialog(playerid,BankDialogCut,DIALOG_STYLE_INPUT,"Снятие со счета",string,"Снять","Назад");
							return true;
						}
					case 1:
						{
							format(string,sizeof(string), "Баланс Вашего счета: %d долларов\nВведите нужную Вам сумму.", GetPVarInt(playerid, "MoneyBank"));
							ShowPlayerDialog(playerid,BankDialogPut,DIALOG_STYLE_INPUT,"Положить на счет",string,"Ок","Назад");
							return true;
						}
					case 2:
						{
							format(string, sizeof(string), "- Имя: %s\n- Счет в банке: %d долларов", sendername, GetPVarInt(playerid, "MoneyBank"));
							ShowPlayerDialog(playerid, BankDialogInfo, DIALOG_STYLE_LIST, "Информация", string, "Выбрать", "Назад");
							return true;
						}
					}
				}
				else
				{
					GameTextForPlayer(playerid, "~g~Good Luck", 1000, 1);
					return true;
				}
			}
			case DialogBankomat:
			{
				if(response)
				{
					switch(listitem)
					{
					case 0:
						{
							format(string,sizeof(string), "Баланс Вашего счета: %d долларов", GetPVarInt(playerid,"MoneyBank"));
							ShowPlayerDialog(playerid,DialogBankomatCut,DIALOG_STYLE_LIST,string," - 500$\n- 1000$\n- 5000$\n- 10000$\n- 20000$\n- 50000$\n- 100000$","Снять","Назад");
							return true;
						}
					case 1:
						{
							new sendername[MAX_PLAYER_NAME];
							GetPlayerName(playerid, sendername, sizeof(sendername));
							format(string,sizeof(string), "{FFFFFF}Клиент: %s\nБаланс: %d долларов",sendername, GetPVarInt(playerid,"MoneyBank"));
							ShowPlayerDialog(playerid,DialogBankomatInfo,DIALOG_STYLE_MSGBOX,"Банкомат",string,"Назад","");
							return true;
						}
					}
				}
			}
			case DialogBankomatCut:
			{
				if(response)
				{
					switch(listitem)
					{
					case 0: { money = 500; }
					case 1: { money = 1000; }
					case 2: { money = 5000; }
					case 3: { money = 10000; }
					case 4: { money = 20000; }
					case 5: { money = 50000; }
					case 6: { money = 100000; }
					}
					if (money > GetPVarInt(playerid,"MoneyBank"))
					{
						ShowPlayerDialog(playerid, 10010, DIALOG_STYLE_MSGBOX, "Банкомат.", "На Вашем счету недостаточно денег!", "Назад", "");
						return true;
					}
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")+money);
					SetPVarInt(playerid,"MoneyBank",GetPVarInt(playerid,"MoneyBank")-money);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, sizeof(string), "Вы сняли со счета: %d Долларов. Остаток: %d долларов", money,GetPVarInt(playerid,"MoneyBank"));
					SendClientMessage(playerid, 0x6495EDFF, string);
					format(string, sizeof(string), "~b~+%d", money);
					GameTextForPlayer(playerid, string, 3000, 1);
					return true;
				}
				else
				{
					new listitems[] = "- Снять наличные\n- Баланс";
					ShowPlayerDialog(playerid, DialogBankomat, DIALOG_STYLE_LIST, "Терминал приема платежей", listitems, "Далее", "Выход");
					return true;
				}
			}
			case BankDialogInfo:
			{			
				if(response)
				{
					if(listitem == 0)
					{
						new listitems[] = "[1] Снять со счета\n[2] Положить на счет\n[3] Информация";
						ShowPlayerDialog(playerid, BankDialog, DIALOG_STYLE_LIST, "Банковские услуги", listitems, "Выбрать", "Отмена");
						return true;
					}
				}
				else
				{
					new listitems[] = "[1] Снять со счета\n[2] Положить на счет\n[3] Информация";
					ShowPlayerDialog(playerid, BankDialog, DIALOG_STYLE_LIST, "Банковские услуги", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
		}
	}
	return true;
}