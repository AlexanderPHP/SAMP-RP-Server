/*

			 Threaded CMD include
			    BJIADOKC & Co.
	Remove this copyright, if you want to be a superman!
*/





#if defined _tcmd_included
	#endinput
#endif

#define _tcmd_included





#pragma tabsize 8





#define TCMD:%0(%1) \
	forward cmd_%0(%1); \
		public cmd_%0(%1)

#define TCOMMAND:%0(%1) \
	TCMD:%0(%1)

#define tcommand(%0, %1, %2, %3) \
	TCMD:%0(%1, %2, %3)

#define tcmd(%0, %1, %2, %3) \
	TCMD:%0(%1, %2, %3)





native exec_cmd(playerid, cmdtext[]);





public OnPlayerCommandText(playerid, cmdtext[])
{
	exec_cmd(playerid, cmdtext);
	return CallLocalFunction("tcmd_OnPlayerCommandText", "is", playerid, cmdtext);
}

#if defined _ALS_OnPlayerCommandText
    #undef OnPlayerCommandText
#else
    #define _ALS_OnPlayerCommandText
#endif

forward tcmd_OnPlayerCommandText(playerid, cmdtext[]);  
 
#define OnPlayerCommandText tcmd_OnPlayerCommandText
 
//forward OnNonLatinCMDExecuted(playerid, cmd[], params[], params_len); - coming soon!


#pragma tabsize 4