CMD:en(playerid, params[])
{
	new carid = GetPlayerVehicleID(playerid);
	if(starting[playerid] == 0)
	{
		if(GetVehicleModel(carid) != 462)
		{
			if (FuelVeh[carid] <= 0) return SendClientMessage(playerid, COLOR_RED, "Вызовите механика или заправьтесь с конистры!");
		}
		if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
				SetVehicleParamsEx(GetPlayerVehicleID(playerid) ,VEHICLE_PARAMS_ON,lights,alarm,doors,bonnet,boot,objective);
				starting[playerid] = 1;
			}
		}
	}
	else if(starting[playerid] == 1)
	{
		if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
				SetVehicleParamsEx(GetPlayerVehicleID(playerid),VEHICLE_PARAMS_OFF,lights,alarm,doors,bonnet,boot,objective);
				starting[playerid] = 0;
			}
		}
	}
	return true;
}
CMD:light(playerid, params[])
{
	if(light_car[playerid] == 0)
	{
		if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
				SetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,VEHICLE_PARAMS_ON,alarm,doors,bonnet,boot,objective);
				light_car[playerid] = 1;
				print(light_car[playerid]);
			}
		}
	}
	else if(light_car[playerid] == 1)
	{
		if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				GetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,lights,alarm,doors,bonnet,boot,objective);
				SetVehicleParamsEx(GetPlayerVehicleID(playerid),engine,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective);
				light_car[playerid] = 0;
				print(light_car[playerid]);
			}
		}
	}
	return true;
}

CMD:afill(playerid,params[],help)
{
	if(GetPVarInt(playerid, "Admin") < 3) return true;
	new carid = GetPlayerVehicleID(playerid);
	FuelVeh[carid] = 300;
	return true;
}