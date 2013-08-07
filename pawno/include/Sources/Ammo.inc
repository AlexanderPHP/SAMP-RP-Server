new ammonac[3];

Hook:Ammo_OnGameModeInit()
{	
	ammonac[0] = CreatePickup(1318,23,1368.9360,-1279.7216,13.5469);//
	ammonac[1] = CreatePickup(1318,23,296.8585,-111.6806,1001.5156,-1);//
	ammonac[2] = CreatePickup(1318,23,-2625.8296,208.2379,4.8125);//
}

Hook:Ammo_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[256];
	if(response)
	{
		switch(dialogid)
		{
			case DIALOG_AMMO:
			{			
				if(response)
				{
					switch(listitem)
					{
					case 0:
						{
							print("ammocko");
							new listitems[] = "M4\nAK-47\nMP5";
							ShowPlayerDialog(playerid, DIALOG_AMMO_AUTOMAT, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Назад");
							return true;
						}
					case 1:
						{
							new listitems[] = "Deagle";
							ShowPlayerDialog(playerid, DIALOG_AMMO_PISTOL, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Назад");
							return true;
						}
					case 2:
						{
							new listitems[] = "Shotgun";
							ShowPlayerDialog(playerid, DIALOG_AMMO_SHOT, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Назад");
							return true;
						}
					}
				}
				else
				{
					return true;
				}
			}
			case DIALOG_AMMO_AUTOMAT:
			{
				if(response)
				{
					switch(listitem)
					{
					case 0:
						{
							print("ammocko");
							ShowPlayerDialog(playerid,DIALOG_AMMO_M4,DIALOG_STYLE_INPUT,"Покупка M4","Количество патронов.","ОК","Назад");
							return true;
						}
					case 1:
						{
							ShowPlayerDialog(playerid,DIALOG_AMMO_AK47,DIALOG_STYLE_INPUT,"Покупка AK47","Количество патронов.","ОК","Назад");
							return true;
						}
					case 2:
						{
							ShowPlayerDialog(playerid,DIALOG_AMMO_MP5,DIALOG_STYLE_INPUT,"Покупка MP5","Количество патронов.","ОК","Назад");
							return true;
						}
					}
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_PISTOL:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0:
						{
							ShowPlayerDialog(playerid,DIALOG_AMMO_DEAGLE,DIALOG_STYLE_INPUT,"Покупка DesertEagle","Количество патронов.","ОК","Назад");
							return true;
						}
					}	
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_SHOT:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0:
						{
							ShowPlayerDialog(playerid,DIALOG_AMMO_SHOTGUN,DIALOG_STYLE_INPUT,"Покупка ShotGun","Количество патронов.","ОК","Назад");
							return true;
						}
					}	
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_M4:
			{
				if(response)
				{
					new ammo;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						ShowPlayerDialog(playerid,DIALOG_AMMO_M4,DIALOG_STYLE_INPUT,"Покупка M4","Количество патронов.","ОК","Назад");
						return true;
					}
					ammo = strval(inputtext);
					new summa = ammo*150;
					if(GetPVarInt(playerid,"Money")<summa)
					{
						SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег!");
						return true;
					}
					GivePlayerWeapon(playerid, 31, ammo);
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")-summa);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, 256, "Вы купили оружие M4 за %d долларов!",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_AK47:
			{
				if(response)
				{
					new ammo;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						ShowPlayerDialog(playerid,DIALOG_AMMO_AK47,DIALOG_STYLE_INPUT,"Покупка AK47","Количество патронов.","ОК","Назад");
						return true;
					}
					ammo = strval(inputtext);
					new summa = ammo*150;
					if(GetPVarInt(playerid,"Money")<summa)
					{
						SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег!");
						return true;
					}
					GivePlayerWeapon(playerid, 30, ammo);
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")-summa);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, 256, "Вы купили оружие AK47 за %d долларов!",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_MP5:
			{
				if(response)
				{
					new ammo;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						ShowPlayerDialog(playerid,DIALOG_AMMO_MP5,DIALOG_STYLE_INPUT,"Покупка MP5","Количество патронов.","ОК","Назад");
						return true;
					}
					ammo = strval(inputtext);
					new summa = ammo*120;
					if(GetPVarInt(playerid,"Money")<summa)
					{
						SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег!");
						return true;
					}
					GivePlayerWeapon(playerid, 29, ammo);
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")-summa);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, 256, "Вы купили оружие MP5 за %d долларов!",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_DEAGLE:
			{
				if(response)
				{
					new ammo;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						ShowPlayerDialog(playerid,DIALOG_AMMO_DEAGLE,DIALOG_STYLE_INPUT,"Покупка Desert Eagle","Количество патронов.","ОК","Назад");
						return true;
					}
					ammo = strval(inputtext);
					new summa = ammo*80;
					if(GetPVarInt(playerid,"Money")<summa)
					{
						SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег!");
						return true;
					}
					GivePlayerWeapon(playerid, 24, ammo);
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")-summa);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, 256, "Вы купили оружие Desert Eagle за %d долларов!",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
			case DIALOG_AMMO_SHOTGUN:
			{
				if(response)
				{
					new ammo;
					if(!strlen(inputtext))// anee inoaaeyao ionoo? no?ieo, auaiaei aio iiyou ieii
					{
						ShowPlayerDialog(playerid,DIALOG_AMMO_DEAGLE,DIALOG_STYLE_INPUT,"Покупка Shotgun","Количество патронов.","ОК","Назад");
						return true;
					}
					ammo = strval(inputtext);
					new summa = ammo*90;
					if(GetPVarInt(playerid,"Money")<summa)
					{
						SendClientMessage(playerid, COLOR_GREY, "У Вас недостаточно денег!");
						return true;
					}
					GivePlayerWeapon(playerid, 24, ammo);
					SetPVarInt(playerid,"Money",GetPVarInt(playerid,"Money")-summa);
					oSetMoney(playerid, GetPVarInt(playerid, "Money"));
					format(string, 256, "Вы купили оружие Shotgun за %d долларов!",summa);
					SendClientMessage(playerid, COLOR_WHITE, string);
				}
				else
				{
					new listitems[] = "- Автоматы\n- Пистолеты\n- Винтовки и дробовики";
					ShowPlayerDialog(playerid, DIALOG_AMMO, DIALOG_STYLE_LIST, "Магазин оружия", listitems, "Выбрать", "Отмена");
					return true;
				}
			}
		}
	}
	return true;
}

Hook:Ammo_OnPlayerPickUpPickup(playerid, pickupid)
{	
	if(pickupid == ammonac[2]) //Aiii NO
	{
		SetPlayerInterior(playerid,6);
		SetPlayerPos(playerid,296.9891,-110.0699,1001.5156);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 90.0564);
		SetPlayerVirtualWorld(playerid, 1);
		SetPlayerCheckpoint(playerid,288.1286,-106.6562,1001.5156,1.0);
		checkpoint[playerid] = 1;
	}
	else if(pickupid == ammonac[0]) //Aiii en
	{
		SetPlayerInterior(playerid,6);
		SetPlayerPos(playerid,296.9891,-110.0699,1001.5156);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 90.0564);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerCheckpoint(playerid,288.1286,-106.6562,1001.5156,1.0);
		checkpoint[playerid] = 1;
	}
	else if(pickupid == ammonac[1]) //
	{
		SetPlayerInterior(playerid,0);
		if(GetPlayerVirtualWorld(playerid) == 0)
		{
			SetPlayerPos(playerid,1366.5776,-1279.5397,13.5469);
			SetPlayerFacingAngle(playerid, 89.7301);
		}	
		if(GetPlayerVirtualWorld(playerid) == 1)
		{
			SetPlayerPos(playerid,-2626.6384,210.3960,4.5971);
			SetPlayerFacingAngle(playerid, 13.1113);
		}
		SetCameraBehindPlayer(playerid);
		SetPlayerVirtualWorld(playerid,0);
		DisablePlayerCheckpoint(playerid);
	}
}

Hook:Ammo_OnPlayerUpdate(playerid)
{
	SetPVarInt(playerid, "NewPlayerAmmo", GetPlayerAmmo(playerid));
	if(GetPVarInt(playerid, "NewPlayerAmmo") != GetPVarInt(playerid, "PlayerAmmo"))
	{
			OnPlayerAmmoChange(playerid, GetPVarInt(playerid, "NewPlayerAmmo"), GetPVarInt(playerid, "PlayerAmmo"));
			SetPVarInt(playerid, "PlayerAmmo", GetPVarInt(playerid, "NewPlayerAmmo"));
	}
}	

stock OnPlayerAmmoChange(playerid, newammo, oldammo)
{
    if(newammo < oldammo)
    {
        switch(GetPlayerWeapon(playerid))
        {
            case 24:
            {
                SetPVarInt(playerid, "SkillD",GetPVarInt(playerid,"SkillD") +1);
                if(GetPVarInt(playerid,"SkillD") >= Ammo_DEAGLE && GetPVarInt(playerid,"deserteagle") < 100)
                {
                    SetPVarInt(playerid, "deserteagle", GetPVarInt(playerid,"deserteagle")+1);
                    SetPVarInt(playerid, "SkillD",0);
                }
            }
            case 23:
            {
                SetPVarInt(playerid, "SkillSD",GetPVarInt(playerid,"SkillSD") +1);
                if(GetPVarInt(playerid,"SkillSD")>= Ammo_SDPISTOL && GetPVarInt(playerid,"sdpistol") < 100)
                {
                     SetPVarInt(playerid, "sdpistol", GetPVarInt(playerid,"sdpistol")+1);
                     SetPVarInt(playerid, "SkillSD",0);
                }
            }
            case 25:
            {
                SetPVarInt(playerid, "SkillShot",GetPVarInt(playerid,"SkillShot") +1);
                if(GetPVarInt(playerid,"SkillShot") >= Ammo_SHOTGUN && GetPVarInt(playerid,"shotgun") < 100)
                {
                    SetPVarInt(playerid, "shotgun", GetPVarInt(playerid,"shotgun")+1);
                    SetPVarInt(playerid, "SkillShot",0);
                }
            }
            case 29:
            {
                SetPVarInt(playerid, "SkillMP5",GetPVarInt(playerid,"SkillMP5") +1);
                if(GetPVarInt(playerid,"SkillMP5") >= Ammo_MP5 && GetPVarInt(playerid,"mp5") < 100)
                {
                    SetPVarInt(playerid, "mp5", GetPVarInt(playerid,"mp5")+1);
                    SetPVarInt(playerid, "SkillMP5",0);
                }
            }
            case 30:
            {
                SetPVarInt(playerid, "SkillAk47",GetPVarInt(playerid,"SkillAk47") +1);
                if(GetPVarInt(playerid,"SkillAk47") >= Ammo_AK47 && GetPVarInt(playerid,"ak47") < 100)
                {
                    SetPVarInt(playerid, "ak47", GetPVarInt(playerid,"ak47")+1);
                    SetPVarInt(playerid, "SkillAk47",0);
                }
            }
            case 31:
            {
                SetPVarInt(playerid, "SkillM4",GetPVarInt(playerid,"SkillM4") +1);
                if(GetPVarInt(playerid,"SkillM4") >= Ammo_M4A1 && GetPVarInt(playerid,"m4") < 100)
                {
                    SetPVarInt(playerid, "m4", GetPVarInt(playerid,"m4")+1);
                    SetPVarInt(playerid, "SkillM4",0);
                }
            }
        }
    }
    return 1;
}  

stock SetPlayerSkills(playerid)
{
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, GetPVarInt(playerid,"sdpistol")*10);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, GetPVarInt(playerid,"deserteagle")*10);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, GetPVarInt(playerid,"shotgun")*10);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, GetPVarInt(playerid,"mp5")*10);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, GetPVarInt(playerid,"ak47")*10);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, GetPVarInt(playerid,"m4")*10);
    return 1;
} 

stock ToDevelopSkills(Slashes,Points)
{
    new SlashesAndPoints[400];
    new Slash[2] = "|";
    new Point[2] = "'";
    for(new i = 0; i < Slashes; i++) strcat(SlashesAndPoints, Slash);
    for(new i = 0; i < Points; i++) strcat(SlashesAndPoints, Point);
    return SlashesAndPoints;
}