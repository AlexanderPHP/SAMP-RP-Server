#undef MAX_PLAYERS
//�������
#define PTG             									"Account"
#define PTGH             									"House"
#define BanList                                             "BanList"
#define SPA                                                 "SpawnAndFraction"
//�������
#define Register                               				991
#define Login				                                992
#define D_DIALOGS                                           9000
#define D_NONE                                              0
#define BankDialog                                          1000
#define BankDialogCut                                       1001
#define BankDialogPut                                       1002
#define BankDialogInfo                                      1003
#define DialogBankomatInfo                                  1004
#define DialogBankomatCut                                   1005
#define DialogBankomat                                      1006
#define DialogMM                                     		2000
#define DialogSlivMM                                     	2001
#define DialogSettingMM                                     2002
#define DialogSexMM                                     	2003
#define DialogMSGMM                                     	2004
#define DIALOG_AMMO                                    		3000
#define DIALOG_AMMO_AUTOMAT                                 3001
#define DIALOG_AMMO_PISTOL                                  3002
#define DIALOG_AMMO_SHOT                                    3003
#define DIALOG_AMMO_M4                                    	3004
#define DIALOG_AMMO_AK47                                    3005
#define DIALOG_AMMO_MP5                                     3006
#define DIALOG_AMMO_DEAGLE                                  3007
#define DIALOG_AMMO_SHOTGUN                                 3008
//������� ��� �������� 1% ������
#define Ammo_SDPISTOL 30 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������
#define Ammo_DEAGLE 24 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������
#define Ammo_SHOTGUN 15 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������
#define Ammo_MP5 75 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������
#define Ammo_AK47 100 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������
#define Ammo_M4A1 89 //��� - ��, ������� ���� ����������, ���� ��������� 1 �������  
//������
#define for_c(%0,%1,%2)   									for(new %2 = %0; %2 != %1; --%2)
#define SellHome(%0)    									f(%0,"{0000FF}��� ���������..{FFFFFF}\n\n-{FF0000}%d{FFFFFF}\n����: {7CFC00}$%d{FFFFFF}", idx, HouseInfo[idx][hPrice])
#define MAX_INTER                                      						 	36
#define MAX_HOUSE 										50 // ������������ ���-�� �����.
#define MAX_PLAYERS                     								(50) // !> ������������ ���-�� �������.
#assert MAX_PLAYERS                								>(0)
#define BYTES_PER_CELL 	 								(cellbits / 8)
#define public:%0(%1)     									forward %0(%1); public %0(%1)
#define GivePVarInt(%1,%2,%3) 								SetPVarInt(%1,%2,GetPVarInt(%1,%2) + %3)
#define GiveGVarInt(%0,%1,%2) 								SetGVarInt(%0,(GetGVarInt(%0, %2) + %1),%2)
#define f(%1, 		 									format(%1,sizeof(%1),
#define MSG_MyID(%0)                                        						SendMes(%0, 0xF97804FF, "�� ������� ���� ID")
#define MSG_NoneOnlinePlayer(%0)                           						SendMes(%0, COLOR_GREY, "������ ������ ��� ��� �� ��� �� ����� !")
#define oSetMoney(%1,%2) 									SetGVarInt("Money", %2, %1), ResetPlayerMoney(%1); GivePlayerMoney(%1, %2)
#define oGiveMoney(%1,%2)                                   						GiveGVarInt("Money", %2, %1); GivePlayerMoney(%1, %2)
#define oSetSkin(%1,%2)                                     						SetGVarInt("Skin", %2, %1), GetPlayerSkin(%1); SetPlayerSkin(%1, %2)
#define FreezePlayer(%0) 									TogglePlayerControllable(%0, false)
#define UnFreezePlayer(%0)									TogglePlayerControllable(%0, true)
#define VEHICLE_PARAMS_OFF  								0
#define VEHICLE_PARAMS_ON   								1
// MySQL
#define MySQL_DEBUG             						1
#define MySQL_HOST              							"localhost" // Host
#define MySQL_USER              							"root" // User
#define MySQL_DATABASE  							"test" // DB Name
#define MySQL_PASS              							"" // Password
#define mysql_player playerid, query[]
// ====== ����� ======
#define COLOR_GREEN 0x00FF00AA
#define COLOR_RED 0xFF0000AA
#define COLOR_AQUA	 0x7FC0E3FF
#define COLOR_BOX 0x00000050
#define COLOR_BBLUE 0x20A9FFFF
#define COLOR_ISPOLZUY 0x7FB151FF
#define COLOR_GRAD1 0xB4B5B7FF
#define COLOR_SINIY 0x00004FAA
#define COLOR_LG 0x7FFF00FF
#define COLOR_BLUE 0x33AAFFFF
#define COLOR_SALMON 0xFA8072AA
#define COLOR_SYSTEM 0xEFEFF7AA
#define COLOR_KHAKI 0xF0E68CAA
#define COLOR_TEAL 0x008080FF
#define COLOR_GRAD2 0xBFC0C2FF
#define COLOR_INDIGO 0x4B00B0AA
#define COLOR_IVORY 0xFFFF82AA
#define COLOR_TEAL 0x008080FF
#define COLOR_GRAD3 0xCBCCCEFF
#define COLOR_GRAD4 0xD8D8D8FF
#define COLOR_GRAD5 0xE3E3E3FF
#define COLOR_GRAD6 0xF0F0F0FF
#define COLOR_GRAD7 0xF0F0F0FF
#define COLOR_GRAD8 0xF0F0F0FF
#define COLOR_BLACK 0x000000AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_BLUEGREEN 0x46BBAA00
#define COLOR_ORANGE 0xFF9900AA
#define COLOR_LIGHTRED 0xFF6347AA
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_LIGHTGREEN 0x9ACD32AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_YELLOW2 0xF5DEB3AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_BROW 0xA85400AA
#define COLOR_FADE1 0xE6E6E6E6
#define COLOR_FADE2 0xC8C8C8C8
#define COLOR_FADE3 0xAAAAAAAA
#define COLOR_FADE4 0x8C8C8C8C
#define COLOR_FADE5 0x6E6E6E6E
#define COLOR_PURPLE 0xC2A2DAAA
#define COLOR_DBLUE 0x2641FEAA
#define COLOR_NEWS 0xFFA500AA
#define COLOR_LIFE 0xFEBC41AA
#define COLOR_OOC 0xE0FFFFAA
// ================================================================
new engine, lights, alarm, doors, bonnet, boot, objective;
new shifthour;
new checkpoint[MAX_PLAYERS];
new RulesMSG[23][] = {
	/*0*/    {"{FFCC00}<< 1. ������� ������� >>\n"},
	/*1*/    {"{FF0000}���������:\n"},
	/*2*/    {"{FFFFFF}������������� ����� �������� �������� ����� �.�.�. ������ ��������� ������������ � ����.\n"},
	/*3*/    {"{FFFFFF}������������� ����� (������, �������������� ����).\n"},
	/*4*/    {"{FFFFFF}������������ ESC � ����� ����� �� ������/������.\n"},
	/*5*/    {"{FFFFFF}������� ������� �� ������ (����� �����������, ���� �����������).\n"},
	/*6*/    {"{FFFFFF}������� ������� ��� ������ ���������� (������, �������� � ������������� �����).\n"},
	/*7*/    {"{FFFFFF}��������/��������� ����������� ����� ������� ��� ������� (�� - Death Match).\n"},
	/*8*/    {"{FFFFFF}��������������� �������� ������������� ��� �������� ��������� �������.\n\n"},
	//���
	/*9*/    {"{FFCC00}<< 2. ��� � ���� >>\n"},
	/*10*/ 	  {"{FFFFFF}��� ������ �������� �� �����_������� � ��������� ����.\n"},
	/*11*/    {"{FF0000}���������{FFFFFF} ������������ ����� (��� ���-�� ������� ����).\n"},
	/*12*/    {"{FF0000}���������{FFFFFF} ������������ ����, ���������� �������������� �/��� ����������� �����.\n\n"},
	//���
	/*13*/	{"{FFCC00}<< 3. ��� >>\n"},
	/*14*/	{"{FF0000}���������:\n"},
	/*15*/	{"{FFFFFF}������������, ����������� ��� ����������� ����.\n"},
	/*16*/	{"{FFFFFF}������ ������� (�� ����������� � �������� ��������).\n"},
	/*17*/	{"{FFFFFF}������ ��������� � ������� �������� (Caps Lock).\n"},
	/*18*/	{"{FFFFFF}������ � ��� ���������� ��������� �� ����������� � Role Play.\n"},
	/*19*/	{"{FFFFFF}������������� OOC ���������� � IC (M�tag�ming).\n"},
	/*20*/	{"{FFFFFF}������ ���� � ���� ��������� ������� �����.\n"},
	/*21*/	{"{FFFFFF}���������, ����������� �������� �������������.\n"},
	/*22*/	{"{FFFFFF}������� ��������� ��������.\n\n"}
};
new RulesMSGG[13][] = {
	//�������������
	/*23*/	{"{FFCC00}<< 1. ������������� ������� >>\n\n"},
	/*24*/	{"{FF0000}���������{FFFFFF} �������������� ������������� � ������.\n"},
	/*25*/	{"{FFFFFF}���������� �������� ������������� � ����� ���� ���������� �� ������ ������ (/mm > report).\n"},
	/*26*/	{"{FFFFFF}������������� �������������� �������� �������� ������� ��� ������� �� �������.\n"},
	/*27*/	{"{FFFFFF}������� ������������� �������� ������������� � �� �������� ����������.\n"},
	/*28*/	{"{FFFFFF}�������� ������� ����� ����������� ��� ��������������� ����� ���������, ��� � ����� ��������� �����.\n"},
	/*29*/	{"{FFFFFF}�������� ������ �� ����������� ��� �� ���������������!\n\n"},
	{"{FFCC00}<< 2. ������������� ��������. >>\n\n"},
	{"{FF0000}��������� {FFFFFF}����� �������� ���������.\n"},
	{"{FF0000}���������{FFFFFF} ������� / ������� ���� ����, �� �������� ������.\n"},
	{"{FF0000}��������{FFFFFF} ����� ��� ������� ��������� � ����� �����, �� �������.\n"},
	{"{FF0000}��������{FFFFFF} ����� ���� ���� ����� �������� ���������.\n"},
	{"{FF0000}���������{FFFFFF} ������� / �������� ���������."}
};

enum fInfoSpawn
{
    fID,
	Float:fSpawnX,
	Float:fSpawnY,
	Float:fSpawnZ,
	fColor[24],
	fInt,
	fVw,
	fPickup,
	fText,
	fSkin[11],
	fSkinGirl[7]
};

enum hInfo
{
    	hID,
	Float:hEnterX,
	Float:hEnterY,
	Float:hEnterZ,
	Float:hExitX,
	Float:hExitY,
	Float:hExitZ,
	Float:hSpawn[4],
	hOwner[MAX_PLAYER_NAME],
	hPrice,
	hInt,
	hLock,
	hOwned,
   	hPickup,
   	hIcon,
	hVirtualWorld,
};

enum hInter
{
    	vID,
    	vName[24],
	Float:vX,
	Float:vY,
	Float:vZ,
	vInt,
	vPrice_Frac,
};

new
	g_CH, /* ~MySQL */
	Menu:regskin,
	SpawnInfo[1][fInfoSpawn],
	HouseInfo[MAX_HOUSE][hInfo],
	Interior[MAX_INTER][hInter];