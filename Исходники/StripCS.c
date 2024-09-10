/************************************************************************************
 * Function: UnpackSystem_old
 * Description: This is a utility function that will take a packed System ,
 * optionally decrypt it based on the passed in password, and set up 
 * an unpacked system. 
 * **********************************************************************************/ 
static void 
UnpackSystem_old (System_old * sys, MemPtr p, MemPtr scratch, char *pass,
			   UInt16 recLen, Boolean decrypt, int v) 
{
	PSystem_old * psys;
	char *s;

	
		// if necessary, decrypt, otherwise just copy the memory to the scratch buffer
		if (decrypt)
		switch (v)
			
		{
			case 0:
				stripCrypt_tw (SysPass, p, scratch, recLen, 0);
				break;
			case 1:
				stripCrypt_idea (SysPass, p, scratch, recLen, 0);
				break;
			case 2:
				stripCrypt_des (SysPass, p, scratch, recLen, 0);
				break;
		}
	
	else
		MemMove (p, scratch, recLen);
	
		// set up the system, pointing the name to the first char in the name string.
		psys = (PSystem_old *) scratch;
	s = psys->name;
	sys->SystemID = psys->SystemID;
	sys->name = s;
	s += StrLen (s) + 1;
}