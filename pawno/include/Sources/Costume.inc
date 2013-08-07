new ChangeSkin[MAX_PLAYERS];
new bool:zips[MAX_PLAYERS];
new zip[2];
new setCenaSkin[20];
new Text:CenaSkin[MAX_PLAYERS];
new victim[2];
new skinshop[4];
new Menu:skinshopmagaz;
new PedsMen[70][2] = {
	{66,1000},
	{15,1000},
	{36,1000},
	{50,1000},
	{95,1000},
	{96,1000},
	{136,1000},
	{143,1000},
	{155,1000},
	{2,50000},
	{14,50000},
	{24,50000},
	{58,100000},
	{7,300000},
	{23,300000},
	{33,300000},
	{60,500000},
	{67,500000},
	{73,500000},
	{184,500000},
	{21,700000},
	{22,700000},
	{30,700000},
	{183,700000},
	{255,700000},
	{4,700000},
	{6,700000},
	{8,700000},
	{42,700000},
	{273,700000},
	{17,1000000},
	{45,1000000},
	{82,1000000},
	{83,1000000},
	{185,1000000},
	{290,1000000},
	{291,1000000},
	{28,1200000},
	{29,1200000},
	{247,1200000},
	{248,1200000},
	{254,1200000},
	{249,1200000},
	{18,1500000},
	{19,1500000},
	{47,1500000},
	{48,1500000},
	{101,1500000},
	{299,1500000},
	{289,1500000},
	{61,2000000},
	{121,2000000},
	{227,2000000},
	{228,2000000},
	{292,2000000},
	{293,2000000},
	{297,2000000},
	{122,2500000},
	{111,3000000},
	{117,3500000},
	{118,3500000},
	{126,4000000},
	{127,4000000},
	{296,4000000},
	{3,4000000},
	{119,4000000},
	{208,4000000},
	{295,4500000},
	{46,5000000},
	{294,5000000}//70
};

new PedsMale[13][2] = {
	{65,1000},
	{192,1000000},
	{216,1000000},
	{219,1000000},
	{93,2000000},
	{211,2000000},
	{233,2000000},
	{148,3000000},
	{169,4000000},
	{141,5000000},
	{76,5000000},
	{150,5000000},
	{214,5000000}
};

Hook:CST_OnGameModeInit()
{
	skinshopmagaz = CreateMenu("Zip", 1, 50.0, 160.0, 90.0);//I
	AddMenuItem(skinshopmagaz,0,"Next >>");
	AddMenuItem(skinshopmagaz,0,"<< Previous");
	AddMenuItem(skinshopmagaz,0,"Buy");
	AddMenuItem(skinshopmagaz,0,"Exit");
	
	victim[0] = CreatePickup(1318,23,461.7025,-1500.7941,31.0454);// iaaacei iaa?au no?aeea
	victim[1] = CreatePickup(1318,23,227.5632,-8.0904,1002.2109);
	zip[0] = CreatePickup(1318,23,-1882.5100,866.3918,35.1719);
	zip[1] = CreatePickup(1318,23,161.3232,-97.1035,1001.8047);
	skinshop[0] = CreatePickup(1275,23,206.0302,-3.5463,1001.2109);//neeioii
	skinshop[1] = CreatePickup(1275,23,205.9253,-12.9991,1001.2178);//neeioi
	skinshop[2] = CreatePickup(1275,23,181.3787,-86.4860,1002.0234);//neeioi
	skinshop[3] = CreatePickup(1275,23,181.5291,-89.3950,1002.0307);//neeioi
	return true;
}

Hook:CST_OnPlayerSelectedMenuRow(playerid, row)
{	
	new Menu:Current = GetPlayerMenu(playerid);
	if(Current == skinshopmagaz) // Iaaacei iaa?au
	{
		if(PlayerToPoint(3.0,playerid,259.2724,-41.4995,1002.0234))
		{
			switch(row)
			{
			case 0://Next >>
				{
					if(GetPVarInt(playerid, "Sex") == 0)//Anee ea?iea io?ee oi..
					{
						ChangeSkin[playerid]++;//Oaae?eaaai ia?aiaiio?..
						if(ChangeSkin[playerid] >= 70)//Anee ia?aiaiiay ?aaia ee aieaa 6 oi..
						{
							ChangeSkin[playerid] = 0;//Iaioeyai a?.. o.a. ia?aoiaei e neeio 0(Ia CJ A eaoi?ue a Ianeaa PedsMen naiue ia?aue)
						}
						SetPlayerSkin(playerid,PedsMen[ChangeSkin[playerid]][0]);//Iaiyai ea?ieo neei ia oio eaoi?ue ii aua?ae
						format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMen[ChangeSkin[playerid]][1]);
						TextDrawSetString(CenaSkin[playerid],setCenaSkin);
						TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
						//format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~%d$",PedsMen[ChangeSkin[playerid]][1]);//Iieacuaaai aio noieiinou neeia
						//GameTextForPlayer(playerid,string,2000,3);
						
					}
					else// Eee anee ea?ie ?aiueia
					{
						ChangeSkin[playerid]++;//aae?eaaai ia?aiaiio?
						if(ChangeSkin[playerid] >= 13)//Anee ia?aiaiiay ?aaia eee aieaa 5 oi
						{
							ChangeSkin[playerid] = 0;//Iaioeyai a? o.a. ia?aoiaei e neeio 0(Ia CJ A eaoi?ue a Ianeaa PedsMale naiue ia?aue)
						}
						SetPlayerSkin(playerid,PedsMale[ChangeSkin[playerid]][0]);//Iaiyai a? neei
						format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMale[ChangeSkin[playerid]][1]);
						TextDrawSetString(CenaSkin[playerid],setCenaSkin);
						TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
						//format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~%d$",PedsMale[ChangeSkin[playerid]][1]);//Iieacuaaai noieiinou neeia
						//GameTextForPlayer(playerid,string,2000,3);
					}
					ShowMenuForPlayer(skinshopmagaz, playerid);//Iieacuaaai iai?, o.e. iinea ia?aoey ia e?ao? eiiieo iii en?acaao
				}
			case 1://<< Previous
				{
					if(GetPVarInt(playerid, "Sex") == 0)//Anee ii io?ee
					{
						ChangeSkin[playerid]--;//Oiaiuoaai ia?aiaiio?
						if(ChangeSkin[playerid] <= 0)//Anee ia?aniaiiay iaiuoa eee ?aaia 0 oi
						{
							ChangeSkin[playerid] = 69;//Aa?i ae cia?aiea 6 ia?aoiaei e naiiio iineaaiaio neeio a ianeaa PedsMale
						}
						SetPlayerSkin(playerid,PedsMen[ChangeSkin[playerid]][0]);//Iaiyai neei
						format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMen[ChangeSkin[playerid]][1]);
						TextDrawSetString(CenaSkin[playerid],setCenaSkin);
						TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
						//format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~%d$",PedsMen[ChangeSkin[playerid]][1]);//Iieacuaaai aio noieiinou neeia
						//GameTextForPlayer(playerid,string,2000,3);
					}
					else//Anee iia ?aiueia
					{
						ChangeSkin[playerid]--;//Oiaiuoaai ia?aiaiio?
						if(ChangeSkin[playerid] <= 0)//Anee ia?aiaiiay ?aaia eee iaiuoa 0 oi
						{
							ChangeSkin[playerid] = 12;// Noaaei cia?aiea 5 e ia?aoiaei e iineaaieio neeio a ianeaa PedsMale
						}
						SetPlayerSkin(playerid,PedsMale[ChangeSkin[playerid]][0]);//Iaiyai neei
						format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMale[ChangeSkin[playerid]][1]);
						TextDrawSetString(CenaSkin[playerid],setCenaSkin);
						TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
						//format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~%d$",PedsMen[ChangeSkin[playerid]][1]);//Iieacuaaai aio noieiinou neeia
						//GameTextForPlayer(playerid,string,2000,3);
					}
					ShowMenuForPlayer(skinshopmagaz, playerid);//Iieacuaaai iai?, ca?ai y o?a aiaa?ee auoa
				}
			case 2://Buy
				{
					new cost;//Nicaaaei ia?aiaiio?..
					cost = PedsMen[ChangeSkin[playerid]][1];//I?e?aaieaaai ia?aiaiio? e oaia neeia a ianeaa Ouo?a 1 - aoi?ie noieaee ianeaa
					if(GetPVarInt(playerid, "Sex") == 0)//Anee ii io?ee oi
					{
						if(GetPVarInt(playerid, "MoneyBank") >= cost)//Anee o iaai aaiaa aieuoa e ?aaii oaia neeia oi
						{
							if(zips[playerid] == true)//cei
							{
								//PlayerInfo[playerid][pChar] = GetPlayerSkin(playerid);//Ocia?i aai neei e caienuaaai a aeaoio
								SetPlayerSkin(playerid,PedsMen[ChangeSkin[playerid]][0]);//Iaiyai aio neei ia oio eaoi?ue ii eoiee
								SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
								SetPlayerInterior(playerid,18);
								//CharPrice[playerid] = 0;
								SetCameraBehindPlayer(playerid);
								SetPlayerPos(playerid ,181.1844,-88.0599,1002);
								SetPlayerVirtualWorld(playerid,0);
								//SelectCharPlace[playerid] = 0;
								//SelectCharID[playerid] = 0;
								//SelectChar[playerid] = 0;
								SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-cost);
								//FracBank[0][fKazna] += cost/2;
								TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
								return true;
							}
							SetPVarInt(playerid, "Skin", GetPlayerSkin(playerid));//Ocia?i aai neei e caienuaaai a aeaoio
							SetPlayerSkin(playerid,GetPVarInt(playerid,"Skin"));//Iaiyai aio neei ia oio eaoi?ue ii eoiee
							SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
							//CharPrice[playerid] = 0;
							SetCameraBehindPlayer(playerid);
							SetPlayerInterior(playerid,5);
							SetPlayerPos(playerid ,209.4333,-7.9053,1001.2109);
							SetPlayerVirtualWorld(playerid,0);
							//SelectCharPlace[playerid] = 0;
							//SelectCharID[playerid] = 0;
							//SelectChar[playerid] = 0;
							SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-cost);
							TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
							TextDrawHideForPlayer(playerid,CenaSkin[playerid]);
						}
						else//Anee iaoo aaiaa oi
						{
							SendClientMessage(playerid,COLOR_GREY,"O aan ia ainoaoa?i aaiaa");//Ieoai niiauaiea
							ShowMenuForPlayer(skinshopmagaz, playerid);//Iieacuaaai iai?..
						}
					}
					else//Anee iia ?aiueia oi
					{
						new cena;//Nicaa?i au? iaio ia?aiaiio?..
						cena = PedsMale[ChangeSkin[playerid]][1];//;//I?e?aaieaaai ia?aiaiio? e oaia neeia a ianeaa Ouo?a 1 - aoi?ie noieaee ianeaa
						if(GetPVarInt(playerid, "MoneyBank") >= cena)//Anee o ia? aaiaa aieuoa eee ?aaii oaia neeio a ianeaa oi
						{
							if(zips[playerid] == true)//cei
							{
								//PlayerInfo[playerid][pChar] = GetPlayerSkin(playerid);//Ocia?i aai neei e caienuaaai a aeaoio
								SetPlayerSkin(playerid,PedsMale[ChangeSkin[playerid]][0]);//Iaiyai aio neei ia oio eaoi?ue ii eoiee
								SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
								SetPlayerInterior(playerid,18);
								//CharPrice[playerid] = 0;
								SetCameraBehindPlayer(playerid);
								SetPlayerPos(playerid ,181.1844,-88.0599,1002);
								SetPlayerVirtualWorld(playerid,0);
								//SelectCharPlace[playerid] = 0;
								//SelectCharID[playerid] = 0;
								//SelectChar[playerid] = 0;
								SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-cena);
								//FracBank[0][fKazna] += cena/2;
								TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
								return true;
							}
							SetPVarInt(playerid, "Skin", GetPlayerSkin(playerid));//Ocia?i aai neei e caienuaaai a aeaoio
							SetPlayerSkin(playerid,GetPVarInt(playerid,"Skin"));//Iaiyai aio neei ia oio eaoi?ue ii eoiee
							SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
							//CharPrice[playerid] = 0;
							SetCameraBehindPlayer(playerid);
							SetPlayerInterior(playerid,5);
							SetPlayerPos(playerid ,209.4333,-7.9053,1001.2109);
							SetPlayerVirtualWorld(playerid,0);
							//SelectCharPlace[playerid] = 0;
							//SelectCharID[playerid] = 0;
							//SelectChar[playerid] = 0;
							SetPVarInt(playerid, "MoneyBank", GetPVarInt(playerid, "MoneyBank")-cena);
							//FracBank[0][fKazna] += cena/2;
							TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
							TextDrawHideForPlayer(playerid,CenaSkin[playerid]);
						}
						else//Anee o ia? iaiuoa aaiaa oi
						{
							SendClientMessage(playerid,COLOR_GREY,"O aan ia ainoaoa?i aaiaa");//Iaoai niiauaiea
							ShowMenuForPlayer(skinshopmagaz, playerid);//Iaeacuaaai iai?
						}
					}
				}
			case 3://Exit
				{
					if(zips[playerid] == true)//cei
					{
						TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
						//PlayerInfo[playerid][pChar] = OldSkin[playerid];
						SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
						SetPlayerInterior(playerid,18);
						//CharPrice[playerid] = 0;
						SetCameraBehindPlayer(playerid);
						//PlayerInfo[playerid][pChar] = PlayerInfo[playerid][pChar];
						SetPlayerPos(playerid ,181.1844,-88.0599,1002);
						SetPlayerVirtualWorld(playerid,0);
						SetPlayerSkin(playerid, GetPVarInt(playerid,"Skin"));
						//SelectCharPlace[playerid] = 0;
						//SelectCharID[playerid] = 0;
						//SelectChar[playerid] = 0;
						return true;
					}
					TogglePlayerControllable(playerid, 1);//?acii?a?eaaai
					//PlayerInfo[playerid][pChar] = OldSkin[playerid];
					SetPlayerFacingAngle(playerid,273.5792);//Iaiyai iiai?io aieiau
					//CharPrice[playerid] = 0;
					SetCameraBehindPlayer(playerid);
					//PlayerInfo[playerid][pChar] = PlayerInfo[playerid][pChar];
					SetPlayerInterior(playerid,5);
					SetPlayerPos(playerid ,209.4333,-7.9053,1001.2109);
					SetPlayerVirtualWorld(playerid,0);
					SetPlayerSkin(playerid, GetPVarInt(playerid,"Skin"));
					TextDrawHideForPlayer(playerid,CenaSkin[playerid]);
					//SelectCharPlace[playerid] = 0;
					//SelectCharID[playerid] = 0;
					//SelectChar[playerid] = 0;
				}
			}
		}
		return true;
	}
	return true;
}

Hook:CST_OnPlayerPickUpPickup(playerid, pickupid)
{	
	if(pickupid == victim[0]) //aeeoei
	{
		SetPlayerInterior(playerid,5);
		SetPlayerPos(playerid,225.2378,-8.0487,1002.2109);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 89.5070);
	}
	else if(pickupid == victim[1]) //
	{
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,458.0936,-1501.5496,31.0372);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 101.4322);
	}
	else if(pickupid == zip[0]) //aeeoei
	{
		zips[playerid] = true;
		SetPlayerInterior(playerid,18);
		SetPlayerPos(playerid,161.6730,-95.5809,1001.8047);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 1.0183);
	}
	else if(pickupid == zip[1]) //
	{
		zips[playerid] = false;
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,-1885.0364,862.9141,35.1719);
		SetCameraBehindPlayer(playerid);
		SetPlayerFacingAngle(playerid, 151.0559);
	}
	else if(pickupid == skinshop[0] || pickupid == skinshop[2])
	{
		if(	GetPVarInt(playerid, "Sex") != 0)
		{
			SendClientMessage(playerid, COLOR_WHITE,"Вы ошиблись кабинкой.");
			return true;
		}
		SetPlayerInterior(playerid,5);
		ShowMenuForPlayer(skinshopmagaz,playerid);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Используйте клавишу 'Пробел', что бы выбрать.");
		SetPlayerPos(playerid, 259.2724,-41.4995,1002.0234), SetPlayerVirtualWorld(playerid, playerid);
		SetPlayerInterior(playerid, 14), SetPlayerFacingAngle(playerid, 92.6158);
		SetPlayerCameraPos(playerid,257.4099,-41.5846,1002.0234), SetPlayerCameraLookAt(playerid,257.4099,-41.5846,1002.0234);
		TogglePlayerControllable(playerid, 0);
		ShowMenuForPlayer(skinshopmagaz, playerid), FreezePlayer(playerid);
		SetPlayerSkin(playerid,PedsMen[0][0]);
		format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMen[0][1]);
		TextDrawSetString(CenaSkin[playerid],setCenaSkin);
		TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
		PlayerPlaySound(playerid, 1185, 0.0, 0.0, 0.0);
		//TogglePlayerControllable(playerid, 0);
		//SelectChar[playerid] = 255;
		//ChosenSkin[playerid] = 230;
		//CharPrice[playerid] = 1000;
		//SelectCharPlace[playerid] = 1;
		return true;
	}
	if(pickupid == skinshop[1] || pickupid == skinshop[3])
	{
		if(	GetPVarInt(playerid, "Sex") != 1)
		{
			SendClientMessage(playerid, COLOR_WHITE,"Вы ошиблись кабинкой.");
			return true;
		}
		SetPlayerInterior(playerid,5);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Используйте клавишу 'Пробел', что бы выбрать.");
		SetPlayerPos(playerid, 259.2724,-41.4995,1002.0234), SetPlayerVirtualWorld(playerid, playerid);
		SetPlayerInterior(playerid, 14), SetPlayerFacingAngle(playerid, 92.6158);
		SetPlayerCameraPos(playerid,257.4099,-41.5846,1002.0234), SetPlayerCameraLookAt(playerid,257.4099,-41.5846,1002.0234);
		TogglePlayerControllable(playerid, 0);
		ShowMenuForPlayer(skinshopmagaz, playerid), FreezePlayer(playerid);
		SetPlayerSkin(playerid,PedsMale[0][0]);
		format(setCenaSkin, sizeof(setCenaSkin),"~g~%d$",PedsMale[0][1]);
		TextDrawSetString(CenaSkin[playerid],setCenaSkin);
		TextDrawShowForPlayer(playerid,CenaSkin[playerid]);
		//SelectChar[playerid] = 255;
		//ChosenSkin[playerid] = 90;
		//SelectCharPlace[playerid] = 1;
		//PlayerInfo[playerid][pChar] = ChosenSkin[playerid];
		//new skin =2 + random(100);
		//SetPlayerVirtualWorld(playerid,skin);
		PlayerPlaySound(playerid, 1185, 0.0, 0.0, 0.0);
		//ChangeSkin[playerid] =0;
		return true;
	}
	return true;
}

Hook:CST_OnPlayerConnect(playerid)
{	
	CenaSkin[playerid] = TextDrawCreate(240.000000,390.000000,"0");
	TextDrawBackgroundColor(SpeedShow[playerid],COLOR_BLACK);//обводка текста
	TextDrawLetterSize(CenaSkin[playerid],1.599999,3.210000);//размер текста
	TextDrawFont(CenaSkin[playerid],3);//стиль
	TextDrawColor(CenaSkin[playerid],COLOR_GREEN);//цвет текста
	TextDrawSetOutline(CenaSkin[playerid],1);//размер обводки
	TextDrawSetProportional(CenaSkin[playerid],1);
	TextDrawSetShadow(CenaSkin[playerid],1);//тень
	return true;
}	