stock ShowStats(playerid,targetid) 
{ 
    if(IsPlayerConnected(playerid)&&IsPlayerConnected(targetid)) 
    { 
        new cash = GetPVarInt(targetid, "Money"); 
        new atext[20]; 
        if(GetPVarInt(playerid, "Sex") == 0) { atext = "Мужской"; } 
        else if(GetPVarInt(playerid, "Sex") == 1) { atext = "Женский"; } 
//============================================================================== 
        new ftext[25]; 
		ftext = "Нет";
//============================================================================== 
        new rtext[64]; 
        rtext = "";
        new jtext[20]; 
        jtext = "Безработный";
        new drank[20]; 
        drank = "Обычный"; 
        new status[20]; 
        if(GetPVarInt(targetid, "Level") >= 1 &&
        GetPVarInt(targetid, "Level") <= 4) { status = "Новичек"; } 
        else if(GetPVarInt(targetid, "Level") >= 5 && 
        GetPVarInt(targetid, "Level") <= 9) { status = "Освоившийся"; } 
        else if(GetPVarInt(targetid, "Level") >= 10 &&
        GetPVarInt(targetid, "Level") <= 19) { status = "Постоянный игрок"; } 
        else if(GetPVarInt(targetid, "Level") > 20) { status = "Дед"; } 
        new married[20]; 
        format(married,sizeof(married),"%s",0); 
        new crimes = 0; 
        new arrests = 0; 
        new warrests = 0; 
        new drugs = 0; 
        new mats = 0; 
        new wanted = 0; 
        new level = GetPVarInt(targetid, "Level"); 
        new exp = GetPVarInt(targetid, "Exp"); 
        new pnumber = GetPVarInt(targetid, "Phone"); 
        new zakonop = 0; 
        new warns = 0; 
        new nxtlevel = GetPVarInt(targetid, "Level")+1; 
        new expamount = nxtlevel*4; 
        new Float:px,Float:py,Float:pz; 
        GetPlayerPos(targetid, px, py, pz); 
		new str[128],sctring[2000]; 
		new name[MAX_PLAYERS]; 
		GetPlayerName(targetid, name, sizeof(name)); 
        format(str,sizeof(str),"Имя:                     \t\t%s\n\n",name); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Уровень:                 \t\t%d\n",level); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Exp:                     \t\t%d/%d\n",exp,expamount); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Деньги:                 \t\t%d\n",cash);//atext 
        strcat(sctring,str); 
        format(str,sizeof(str),"Телефон:                 \t\t%d\n",pnumber); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Варнов:                 \t\t%d\n",warns); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Законопослушность:       \t%d\n",zakonop);//drank 
        strcat(sctring,str); 
        format(str,sizeof(str),"Преступлений:             \t%d\n",crimes);//married 
        strcat(sctring,str); 
        format(str,sizeof(str),"Арестов:                 \t\t%d\n",arrests);//jtext 
        strcat(sctring,str); 
        format(str,sizeof(str),"Смертей в розыске:        \t%d\n",warrests); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Уровень розыска:          \t%d\n",wanted); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Зависимость:              \t\t%d\n"); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Наркотики:                \t\t%d\n",drugs); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Материалы:                \t\t%d\n",mats); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Рыб поймано:              \t0\n"); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Организация:             \t\t%s\n",ftext); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Ранг:                    \t\t%s\n",rtext); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Работа:                 \t\t%s\n",jtext); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Статус:                 \t\t%s\n",status); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Жена/Муж:                \t\t%s\n",married); 
        strcat(sctring,str); 
        format(str,sizeof(str),"Пол:                    \t\t%s\n",atext); 
        strcat(sctring,str); 
        ShowPlayerDialog(playerid,1932,DIALOG_STYLE_MSGBOX,"Статистика",sctring,"Готово",""); 
    } 
}  