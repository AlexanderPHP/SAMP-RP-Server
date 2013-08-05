new AS_pickup[3];
new AS_carid[MAX_PLAYERS];

enum AS_CarsInfo{
	AS_Carmodel,
	AS_Carname[14],
	AS_Price
};
new AS_Elite_Cars[20][AS_CarsInfo] = {
	{411, "INFERNUS", 3900000}, 
	{402, "BUFFALO", 3200000}, 
	{415, "CHEETAH", 3700000}, 
	{429, "BANSHEE", 3600000}, 
	{451, "TURIZMO", 3600000}, 
	{506, "SUPER GT", 3400000}, 
	{541, "BULLET", 4000000}, 
	{522, "NRG-500", 3100000}, 
	{477, "ZR-350", 1900000}, 
	{480, "COMET", 2000000}, 
	{535, "SLAMVAN", 1600000}, 
	{545, "HUSLTLER", 1500000}, 
	{559, "TOYOTA SUPRA", 1800000}, 
	{560, "SULTAN", 1800000}, 
	{562, "ELEGY", 1800000}, 
	{565, "FLASH", 1700000}, 
	{587, "EUROS", 1700000}, 
	{602, "ALPHA", 1600000}, 
	{463, "FREEWAY", 1600000}, 
	{468, "SANCHEZ", 1500000}
};

new AS_Used_Cars[36][AS_CarsInfo] = {
	{419,"ESPERANTO",80000},
	{421,"WASHINGTON",830000},
	{445,"ADMIRAL",830000},
	{489,"RANCHER",880000},
	{491,"VIRGO",800000},
	{534,"REMINGTON",760000},
	{554,"YOSEMITE",840000},
	{555,"WINDSOR",940000},
	{561,"STRATUM",910000},
	{579,"HUNTLEY",940000},
	{580,"STAFFORD",1000000},
	{589,"CLUB",70000},
	{604,"PHOENIX",750000},
	{418,"MOONBEAN",700000},
	{461,"PCJ-600",1000000},
	{581,"BF-400",1000000},
	{586,"WAYFARER",800000},
	{401,"BRAVURA",340000},
	{405,"SENTINEL",400000},
	{412,"VOODOO",390000},
	{422,"BOBCAT",310000},
	{426,"PREMIER",420000},
	{467,"OCEANIC",390000},
	{474,"HERMES",370000},
	{496,"BLISA COMPACT",480000},
	{507,"ELEGANT",450000},
	{529,"WILLARD",440000},
	{536,"BLADE",40000},
	{540,"VINCENT",330000},
	{550,"SUNRISE",480000},
	{551,"MERIT",480000},
	{566,"TAHOMA",340000},
	{575,"BROADWAY",460000},
	{576,"TORNADO",350000},
	{585,"EMPEROR",360000},
	{600,"PICARDO",420000}
};

new AS_Trash_Cars[21][AS_CarsInfo] = {
	{400,"LANDSTALKER",130000},
	{404,"PERRENIEL",320000},
	{436,"PREVION",100000},
	{439,"STALLION",150000},
	{458,"SOLAIR",120000},
	{466,"GLENDALE",110000},
	{475,"SABRE",190000},
	{478,"WALTON",100000},
	{479,"REGINA",110000},
	{492,"GREENWOOD",140000},
	{516,"NEBULA",140000},
	{517,"MAJESTIC",150000},
	{518,"BUCCANEER",170000},
	{526,"FORTUNE",110000},
	{527,"CARDONA",100000},
	{542,"CLOVER",120000},
	{542,"SADLER",100000},
	{516,"INTRUDER",140000},
	{547,"PRIMO",110000},
	{549,"TAMPA",120000},
	{567,"SAVANNA",200000}
};

Hook:AS_OnGameModeInit()
{
	AS_pickup[0] = CreatePickup(19133, 23, -1657.2484, 1211.0175, 7.2500);//СФсалон
	AS_pickup[1] = CreatePickup(19133, 23, -1956.84, 295.641, 35.4688);//СФСгараж
	AS_pickup[2] = CreatePickup(19133, 23, 553.848, -1293.12, 17.2482);//ЛС
}

Hook:AS_OnPlayerPickUpPickup(playerid, pickupid)
{
	if(pickupid == AS_pickup[0])
	{
		return ShowPlayerDialog(playerid, D_DIALOGS+13, DIALOG_STYLE_MSGBOX, "Добро пожаловать в Автосалон!", "Хотите ли Вы войти?", "Да", "Нет");
	}
	else if(pickupid == AS_pickup[1])
	{
		return ShowPlayerDialog(playerid, D_DIALOGS+14, DIALOG_STYLE_MSGBOX, "Добро пожаловать в Автосалон!", "Хотите ли Вы войти?", "Да", "Нет");
	}
	else if(pickupid == AS_pickup[2])
	{
		return ShowPlayerDialog(playerid, D_DIALOGS+15, DIALOG_STYLE_MSGBOX, "Добро пожаловать в Автосалон!", "Хотите ли Вы войти?", "Да", "Нет");
	}

	return true;
}

Hook:AS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(dialogid)
		{
			case D_DIALOGS+13:
			{
				new text[40];

				SetPlayerVirtualWorld(playerid,playerid+1);
				SetPlayerPos(playerid,-1654.2831,1210.0433,7.2500);
				TogglePlayerControllable(playerid,0);		
				SetPlayerCameraPos(playerid,-1658.888793, 1208.621459, 22.340900);
				AS_carid[playerid] = CreateVehicle(411,-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				SetPlayerCameraLookAt(playerid,-1658.888793, 1208.621459, 22.340900,2);

				Create3DMenu(1,-1654.4026,1209.6061,21.1563,316.1330,4,playerid);
				
				SendMes(playerid,COLOR_GREEN,"Для переключения между меню используйте 'Y' и 'N', для выбора 'Space'");

				SetBoxText(1,0,"Следующая\n[BUFFALO]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(1,1,"Предыдущая\n[SANCHEZ]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(1,2,"Купить",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(1,3,"Выход",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

				Create3DMenu(2,-1654.0709,1207.7697,21.1563,30,4,playerid);

				f(text,"%s\nСтоимость: %d",AS_Elite_Cars[0][AS_Carname],AS_Elite_Cars[0][AS_Price]);

				SetBoxText(2,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

				Select3DMenu(playerid,1);
			}

			case D_DIALOGS+14:
			{
				new text[40];
				SetPlayerVirtualWorld(playerid,playerid+1);
				SetPlayerPos(playerid,-1654.2831,1210.0433,7.2500);
				TogglePlayerControllable(playerid,0);		
				SetPlayerCameraPos(playerid,-1658.888793, 1208.621459, 22.340900);
				AS_carid[playerid] = CreateVehicle(419,-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				SetPlayerCameraLookAt(playerid,-1658.888793, 1208.621459, 22.340900,2);
				
				Create3DMenu(3,-1654.4026,1209.6061,21.1563,316.1330,4,playerid);

				SendMes(playerid,COLOR_GREEN,"Для переключения между меню используйте 'Y' и 'N', для выбора 'Space'");
				
				SetBoxText(3,0,"Следующая\n[WASHINGTON]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(3,1,"Предыдущая\n[PICARDO]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(3,2,"Купить",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(3,3,"Выход",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				Create3DMenu(4,-1654.0709,1207.7697,21.1563,30,4,playerid);

				f(text,"%s\nСтоимость: %d",AS_Used_Cars[0][AS_Carname],AS_Used_Cars[0][AS_Price]);

				SetBoxText(4,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

				Select3DMenu(playerid,3);
			}
			
			case D_DIALOGS+15:
			{
				new text[40];
				SetPlayerVirtualWorld(playerid,playerid+1);
				SetPlayerPos(playerid,-1654.2831,1210.0433,7.2500);
				TogglePlayerControllable(playerid,0);		
				SetPlayerCameraPos(playerid,-1658.888793, 1208.621459, 22.340900);
				AS_carid[playerid] = CreateVehicle(400,-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				SetPlayerCameraLookAt(playerid,-1658.888793, 1208.621459, 22.340900,2);
				
				Create3DMenu(5,-1654.4026,1209.6061,21.1563,316.1330,4,playerid);
				
				SendMes(playerid,COLOR_GREEN,"Для переключения между меню используйте 'Y' и 'N', для выбора 'Space'");

				SetBoxText(5,0,"Следующая\n[PERRENIEL]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(5,1,"Предыдущая\n[PICARDO]",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(5,2,"Купить",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				SetBoxText(5,3,"Выход",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				Create3DMenu(6,-1654.0709,1207.7697,21.1563,30,4,playerid);

				f(text,"%s\nСтоимость: %d",AS_Trash_Cars[0][AS_Carname],AS_Trash_Cars[0][AS_Price]);

				SetBoxText(6,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

				Select3DMenu(playerid,5);
			}
		}
	}
	return true;
}

stock AS_OnPlayerSelect3DMenuBox(playerid,MenuID,boxid)
{
	//printf("%d %d %d %d",1,AS_3DMenuID[1],AS_3DMenuID[2],MenuID);
	switch(MenuID)
	{
		case 1:
		{
			new text[26];
			static ncarcnt = 1, pcarcnt = 19;
			switch(boxid)
			{
				case 0:
				{

					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Elite_Cars[ncarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);

					if(ncarcnt == 19) ncarcnt = -1;
					if(pcarcnt == 19) pcarcnt = -1;
					ncarcnt++;
					pcarcnt++;
			//		printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Elite_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Elite_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Elite_Cars[ncarcnt][AS_Carname]);
					
					SetBoxText(1,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
					f(text,"Предыдущая\n[%s]",AS_Elite_Cars[pcarcnt][AS_Carname]);
					
					SetBoxText(1,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);

					Destroy3DMenu(2);

					Create3DMenu(2,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Elite_Cars[ncarcnt-1][AS_Carname],AS_Elite_Cars[ncarcnt-1][AS_Price]);

					SetBoxText(2,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					//printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 1:
				{
				
					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Elite_Cars[pcarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				
					if(pcarcnt == 0) pcarcnt = 20;
					if(ncarcnt == 0) ncarcnt = 20;
					ncarcnt--;
					pcarcnt--;
		//			printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Elite_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Elite_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Elite_Cars[ncarcnt][AS_Carname]);
				
					SetBoxText(1,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					f(text,"Предыдущая\n[%s]",AS_Elite_Cars[pcarcnt][AS_Carname]);
				
					SetBoxText(1,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					Destroy3DMenu(2);

					Create3DMenu(2,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Elite_Cars[pcarcnt+1][AS_Carname],AS_Elite_Cars[pcarcnt+1][AS_Price]);

					SetBoxText(2,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				//	printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 2:
				{
					//покупка
				}
				case 3:
				{
					SetCameraBehindPlayer(playerid);
					SetPlayerVirtualWorld(playerid,0);
					TogglePlayerControllable(playerid,1);
					Destroy3DMenu(1);
					Destroy3DMenu(2);
				}
			}
		}
		case 3:
		{
			new text[26];
			static ncarcnt = 1, pcarcnt = 35;
			switch(boxid)
			{
				case 0:
				{

					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Used_Cars[ncarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);

					if(ncarcnt == 35) ncarcnt = -1;
					if(pcarcnt == 35) pcarcnt = -1;
					ncarcnt++;
					pcarcnt++;
				//	printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Used_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Used_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Used_Cars[ncarcnt][AS_Carname]);
					
					SetBoxText(3,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
					f(text,"Предыдущая\n[%s]",AS_Used_Cars[pcarcnt][AS_Carname]);
					
					SetBoxText(3,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);

					Destroy3DMenu(4);

					Create3DMenu(4,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Used_Cars[ncarcnt-1][AS_Carname],AS_Used_Cars[ncarcnt-1][AS_Price]);

					SetBoxText(4,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					//printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 1:
				{
				
					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Used_Cars[pcarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				
					if(pcarcnt == 0) pcarcnt = 36;
					if(ncarcnt == 0) ncarcnt = 36;
					ncarcnt--;
					pcarcnt--;
				//	printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Used_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Used_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Used_Cars[ncarcnt][AS_Carname]);
				
					SetBoxText(3,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					f(text,"Предыдущая\n[%s]",AS_Used_Cars[pcarcnt][AS_Carname]);
				
					SetBoxText(3,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					Destroy3DMenu(4);

					Create3DMenu(4,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Used_Cars[pcarcnt+1][AS_Carname],AS_Used_Cars[pcarcnt+1][AS_Price]);

					SetBoxText(4,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				//	printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 2:
				{
					//покупка
				}
				case 3:
				{	
					SetPlayerPos(playerid, -1967.2998,293.7426,35.2000);
					SetCameraBehindPlayer(playerid);
					SetPlayerVirtualWorld(playerid,0);
					TogglePlayerControllable(playerid,1);
					Destroy3DMenu(3);
					Destroy3DMenu(4);
				}
			}
		}
		case 5:
		{
			new text[26];
			static ncarcnt = 1, pcarcnt = 20;
			switch(boxid)
			{
				case 0:
				{

					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Trash_Cars[ncarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);

					if(ncarcnt == 20) ncarcnt = -1;
					if(pcarcnt == 20) pcarcnt = -1;
					ncarcnt++;
					pcarcnt++;
					//printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Trash_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Trash_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Trash_Cars[ncarcnt][AS_Carname]);
					
					SetBoxText(5,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
					
					f(text,"Предыдущая\n[%s]",AS_Trash_Cars[pcarcnt][AS_Carname]);
					
					SetBoxText(5,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);

					Destroy3DMenu(6);

					Create3DMenu(6,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Trash_Cars[ncarcnt-1][AS_Carname],AS_Trash_Cars[ncarcnt-1][AS_Price]);

					SetBoxText(6,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					//printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 1:
				{
				
					DestroyVehicle(AS_carid[playerid]);
				
					AS_carid[playerid] = CreateVehicle(AS_Trash_Cars[pcarcnt][AS_Carmodel],-1651.305664, 1206.520385, 20.875724, 65.775344, 0, 0, 0);
				
					SetVehicleVirtualWorld(AS_carid[playerid],playerid+1);
				
					if(pcarcnt == 0) pcarcnt = 21;
					if(ncarcnt == 0) ncarcnt = 21;
					ncarcnt--;
					pcarcnt--;
					//printf(" Next car:%d %s Prev Car:%d %s\n", ncarcnt,AS_Trash_Cars[ncarcnt][AS_Carname],pcarcnt,AS_Trash_Cars[pcarcnt][AS_Carname]);
					f(text,"Следующая\n[%s]",AS_Trash_Cars[ncarcnt][AS_Carname]);
				
					SetBoxText(5,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
					f(text,"Предыдущая\n[%s]",AS_Trash_Cars[pcarcnt][AS_Carname]);
				
					SetBoxText(5,1,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

					Destroy3DMenu(6);

					Create3DMenu(6,-1654.0709,1207.7697,21.1563,30,4,playerid);

					f(text,"%s\nСтоимость: %d",AS_Trash_Cars[pcarcnt+1][AS_Carname],AS_Trash_Cars[pcarcnt+1][AS_Price]);

					SetBoxText(6,0,text,OBJECT_MATERIAL_SIZE_256x64,"Tahoma",36,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
				
				//	printf("%d %d\n", ncarcnt,pcarcnt);
				}
				case 2:
				{
					//покупка
				}
				case 3:
				{	
					SetPlayerPos(playerid, -1967.2998,293.7426,35.2000);
					SetCameraBehindPlayer(playerid);
					SetPlayerVirtualWorld(playerid,0);
					TogglePlayerControllable(playerid,1);
					Destroy3DMenu(5);
					Destroy3DMenu(6);
				}

			}
		}
	}
  	//SetBoxText(MenuID,boxid,"Привет!\nWheee!",OBJECT_MATERIAL_SIZE_256x64,"Tahoma",24,true,0xFFFFFFFF,0xFF0000FF,0xFFFF0000,OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
  	return true;
}