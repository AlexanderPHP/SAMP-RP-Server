// ======== [������ ����������] ======== //
new Text:Box;//���������� �������� ����� //
new	Text:Speed;//���������� ����� ����� �� ������ Speed
new	Text:SpeedShow[MAX_PLAYERS];//���������� ���������� �������� ����������(�������� ��� ������� ������)
new	Text:LightShow[MAX_PLAYERS];
new Text:Fuel;//���������� ���������� �� ������ fuel
new Text:FuelShow[MAX_PLAYERS];//���������� ���������� ������������ �����(�������� ��� ������� ������)
new Text:Status;//���������� ���������� �� ������ Status
new Text:StatusShow[MAX_PLAYERS];//���������� ���������� ������������ status ����(�������� ��� ������� ������)
new Text:KMShow[MAX_PLAYERS];//���������� ���������� ������������ status ����(�������� ��� ������� ������)
new spd1[10],spd2[64],spd3[10],spd5[10],spd4[64];
new Float:FuelVeh[MAX_VEHICLES];
//, Refueling[MAX_PLAYERS], OldFuel[MAX_PLAYERS];print("11");
new STimer[MAX_PLAYERS];
new bool:IsLocked[MAX_VEHICLES];
new starting[MAX_PLAYERS];
new light_car[MAX_PLAYERS];

Hook:SPD_OnGameModeInit()
{	
	new File = ini_openFile("[logs]/benzin.ini");
	new str[5], Float:fill;//,benz[];
	for(new Vehicles = 0; Vehicles < MAX_VEHICLES; Vehicles++)
	{
		 format(str, sizeof(str), "%s", Vehicles);
		 ini_getFloat(File, str, fill);
		 FuelVeh[Vehicles] = fill;
		 SetVehicleNumberPlate(Vehicles, "Free");
	}
	ini_closeFile(File);
	return true;
}

Hook:SPD_OnPlayerConnect(playerid)
{	
	SpeedShow[playerid] = TextDrawCreate(355.000000,400.000000,"0");
	TextDrawBackgroundColor(SpeedShow[playerid],COLOR_BLACK);//������� ������
	TextDrawLetterSize(SpeedShow[playerid],0.399999,1.010000);//������ ������
	TextDrawFont(SpeedShow[playerid],3);//�����
	TextDrawColor(SpeedShow[playerid],0xFFFFFFAA);//���� ������
	TextDrawSetOutline(SpeedShow[playerid],1);//������ �������
	TextDrawSetProportional(SpeedShow[playerid],1);
	TextDrawSetShadow(SpeedShow[playerid],1);//����

	LightShow[playerid] = TextDrawCreate(435.000000,400.000000, "_____");//��� Text Draw Status
	//	StatusShow[playerid] = TextDrawCreate(570.000000,420.000000, "0");//��� Text Draw Status
	TextDrawBackgroundColor(LightShow[playerid], COLOR_BLACK);//������� ������
	TextDrawLetterSize(LightShow[playerid],0.399999,1.010000);//������ ������
	TextDrawFont(LightShow[playerid], 3);//�����
	TextDrawColor(LightShow[playerid], COLOR_RED);//���� ������
	TextDrawSetOutline(LightShow[playerid], 1);//������ �������
	TextDrawSetProportional(LightShow[playerid],1);
	TextDrawSetShadow(LightShow[playerid],1);//����
	
	StatusShow[playerid] = TextDrawCreate(435.000000,410.000000, "0");//��� Text Draw Status
	//	StatusShow[playerid] = TextDrawCreate(570.000000,420.000000, "0");//��� Text Draw Status
	TextDrawBackgroundColor(StatusShow[playerid], COLOR_BLACK);//������� ������
	TextDrawLetterSize(StatusShow[playerid],0.399999,1.010000);//������ ������
	TextDrawFont(StatusShow[playerid], 3);//�����
	TextDrawColor(StatusShow[playerid], COLOR_GREEN);//���� ������
	TextDrawSetOutline(StatusShow[playerid], 1);//������ �������
	TextDrawSetProportional(StatusShow[playerid],1);
	TextDrawSetShadow(StatusShow[playerid],1);//����

	KMShow[playerid] = TextDrawCreate(385.000000,400.000000, "0");
	//KMShow[playerid] = TextDrawCreate(580.000000,410.000000, "_");//��� Text Draw Status
	TextDrawBackgroundColor(KMShow[playerid], COLOR_BLACK);//������� ������
	TextDrawLetterSize(KMShow[playerid],0.399999,1.010000);//������ ������
	TextDrawFont(KMShow[playerid], 3);//�����
	TextDrawColor(KMShow[playerid], 0x6495EDFF);//���� ������
	TextDrawSetOutline(KMShow[playerid], 1);//������ �������
	TextDrawSetProportional(KMShow[playerid],1);
	TextDrawSetShadow(KMShow[playerid],1);//����

	FuelShow[playerid] = TextDrawCreate(355.000000,410.000000, "0");
	// FuelShow[playerid] = TextDrawCreate(540.000000,390.000000, "_");//��� Text Draw fuel
	TextDrawBackgroundColor(FuelShow[playerid], COLOR_BLACK);//������� ������
	TextDrawLetterSize(FuelShow[playerid],0.399999,1.010000);//������ ������
	TextDrawFont(FuelShow[playerid], 3);//�����
	TextDrawColor(FuelShow[playerid], COLOR_RED);//���� ������
	TextDrawSetOutline(FuelShow[playerid], 1);//������ �������
	TextDrawSetProportional(FuelShow[playerid],1);
	TextDrawSetShadow(FuelShow[playerid],1);//����
	
	Box = TextDrawCreate(425.000000,380.000000,"______");
	TextDrawLetterSize(Speed,0.399999,1.010000); 
	TextDrawFont(Speed,3); 
	TextDrawBackgroundColor(Speed,COLOR_BLACK); 
	TextDrawColor(Speed,COLOR_BBLUE); 
	TextDrawSetOutline(Speed,1); 
	TextDrawSetProportional(Speed,1);
	TextDrawSetShadow(Speed,1); 
	TextDrawUseBox(Box, 1);
	TextDrawBoxColor(Box, COLOR_BOX);
	TextDrawTextSize(Box, 0.0, 160.0);
	TextDrawLetterSize(Box, 0.0, 6.7); 
	TextDrawAlignment(Box, 2);
	return true;
}

Hook:SPD_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)//���� ������ � ���� �� ���������� ��� ���������
	{
		light_car[playerid] = 0;
		if(starting[playerid] == 0)
		{
			SendClientMessage(playerid,COLOR_GREEN,"{26931c}����� ������� ��������� ������� ������� {ffffff}'2'");
		}
		TextDrawShowForPlayer(playerid,Box);
		TextDrawShowForPlayer(playerid,Speed);
		STimer[playerid] = SetTimerEx("UpdateSpeedometr", 100, true, "d", playerid);
		TextDrawShowForPlayer(playerid,SpeedShow[playerid]);
		TextDrawShowForPlayer(playerid,LightShow[playerid]);
		TextDrawShowForPlayer(playerid,Fuel);
		TextDrawShowForPlayer(playerid,FuelShow[playerid]);
		TextDrawShowForPlayer(playerid,Status);
		TextDrawShowForPlayer(playerid,StatusShow[playerid]);
		TextDrawShowForPlayer(playerid,KMShow[playerid]);
	}
	else if(newstate == PLAYER_STATE_ONFOOT)//������� ��������
	{
		TextDrawHideForPlayer(playerid,Box);
		TextDrawHideForPlayer(playerid,Speed);
		KillTimer(STimer[playerid]);
		//KillTimer(antiremover[playerid]);
		TextDrawHideForPlayer(playerid,SpeedShow[playerid]);
		TextDrawHideForPlayer(playerid,LightShow[playerid]);
		TextDrawHideForPlayer(playerid,Fuel);
		TextDrawHideForPlayer(playerid,FuelShow[playerid]);
		TextDrawHideForPlayer(playerid,Status);
		TextDrawHideForPlayer(playerid,StatusShow[playerid]);
		TextDrawHideForPlayer(playerid,KMShow[playerid]);
	}
	return true;
}

stock SpeedVehicle(playerid)//Ooieoey n iiiiuu? eioi?ie iu iieo?aai nei?inou aaoiiiaeey
{
	new Float:ST[4];
	if(IsPlayerInAnyVehicle(playerid))
	GetVehicleVelocity(GetPlayerVehicleID(playerid),ST[0],ST[1],ST[2]);
	else GetPlayerVelocity(playerid,ST[0],ST[1],ST[2]);
	ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 100.3;
	return floatround(ST[3]);
}

public: UpdateSpeedometr(playerid)//��������� ������ ������� ��� ���������
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid))
	{
		new locked[10];
		//locked = "~r~Lock";
		if(IsLocked[vehicleid] == true){locked = "~r~Lock";}
		else{locked = "~g~Open";}
		format(spd1, sizeof(spd1),"~w~%d",SpeedVehicle(playerid));
		if(FuelVeh[vehicleid]<20)
		{
			format(spd2, sizeof(spd2),"~r~Fuel: ~r~%.0f",FuelVeh[vehicleid]);
		}
		if(FuelVeh[vehicleid]>20)
		{
			format(spd2, sizeof(spd2),"~r~Fuel: ~w~%.0f",FuelVeh[vehicleid]);
		}
		if(light_car[playerid] == 0) {
			format(spd4, sizeof(spd4),"~y~Light: ~r~Off");
		}
		if(light_car[playerid] == 1) 
		{
			format(spd4, sizeof(spd4),"~y~Light: ~g~On");
		}
		format(spd5, sizeof(spd5), "%s",locked);
		format(spd3, sizeof(spd3), "~w~KM/H");
		new carid = GetPlayerVehicleID(playerid);
		if(FuelVeh[carid] < 1)
		{
			FuelVeh[carid] = 0;
			GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
			SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,lights,alarm,doors,bonnet,boot,objective);
			starting[playerid] = false;
		}
		new File = ini_openFile("[logs]/benzin.ini");
		new str[5];
		if(starting[playerid] == 1 && SpeedVehicle(playerid) != 0)
		{
			FuelVeh[vehicleid] -= 0.005;
			format(str, sizeof(str), "%s", vehicleid);
            ini_setFloat(File, str, FuelVeh[vehicleid]);
		}
		if(starting[playerid] == 1 && SpeedVehicle(playerid) == 0)
		{
			FuelVeh[vehicleid] -= 0.003;
			format(str, sizeof(str), "%s", vehicleid);
            ini_setFloat(File, str, FuelVeh[vehicleid]);
		}
        ini_closeFile(File);
		//GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
		TextDrawSetString(SpeedShow[playerid],spd1);
		TextDrawSetString(FuelShow[playerid],spd2);
		TextDrawSetString(LightShow[playerid],spd4);
		TextDrawSetString(StatusShow[playerid],spd5);
		TextDrawSetString(KMShow[playerid],spd3);
	}
	return true;
}