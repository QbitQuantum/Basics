//////////
//
// Debugger interface to request function addresses for interface
//
// See devhelp.txt.  Duplicate changes here in VDebug.h, vvm.cpp, vvm_v1.cpp, vvm_defs.h, and vo_class.h.
//
//////
	// See what function they're requesting
	u64 CALLTYPE vvm_debuggerInterfaceCallback(s8* tcFunctionName)
	{
		u64			lnFuncAddress;
		u32			lnI, lnHaystackLength, lnNeedleLength;
		s8*			lcFuncName;
		void**		lcFuncAddress;


//////////
//
// O S S   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmOssFunction's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gVvmOssFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gVvmOssFunctions[(lnI * 2) + 0];						// Grab the indirect address to store
			lcFuncName		= (s8*)   gVvmOssFunctions[(lnI * 2) + 1];						// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return((u64)*lcFuncAddress);
		}
		// If we get here, not found in VVMOSS functions


//////////
//
// M C   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmmcFunctions's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gMcFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lcFuncAddress	= (void**)gMcFunctions[(lnI * 2) + 0];							// Grab the indirect address to store
			lcFuncName		= (s8*)   gMcFunctions[(lnI * 2) + 1];							// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return((u64)*lcFuncAddress);
		}
		// If we get here, not found



//////////
//
// V V M   FUNCTIONS
//
//////
		// Search for the needle (tnFunctionName) in the haystack (gVvmmcFunctions's lcFuncName)
		lnNeedleLength = strlen(tcFunctionName);
		for (lnI = 0; lnI < gVvmFunctionCount; lnI++)
		{
			// Grab the details of this entry
			lnFuncAddress	= (u64)gVvmFunctions[(lnI * 2) + 0];							// Grab the indirect address to store
			lcFuncName		= (s8*)gVvmFunctions[(lnI * 2) + 1];							// Grab the function name to request

			lnHaystackLength = strlen(lcFuncName);
			if (lnNeedleLength == lnHaystackLength && _memicmp(tcFunctionName, lcFuncName, lnHaystackLength) == 0)
				return(lnFuncAddress);
		}
		// If we get here, not found

		// If we get here, indicate our failure
		return(NULL);
	}