void sortScript()
{
	//this saves dynamic space
	UInt16 i, k, size;
	Err err;
	ScriptType temp[map.numCmds];
	
	//get rid of all map cmds
	for(i = 0; i < map.numCmds; i++)
	{
		if(!cmdIsAI(script[i].type))
		{
			//copy next cmd into this one if there is			
			for(k = i; k < map.numCmds;k++)
			{
				//if there is a cmd left
				if(k != (map.numCmds - 1))
				{
					//if it still isn't ai then continue
					if(!cmdIsAI(script[k + 1].type))
					{
						continue;
					}
					else
					{
						//copy it into new, discard old
						MemMove(&temp[i], &script[k + 1], sizeof(ScriptType));						
						size++;
						//get out of loop
						break;
					}	
				}
			}
		}	
		//leave it if it is an ai	
	}	
	
	//resize script to value of size
	err = MemHandleResize(scriptH, sizeof(ScriptType) * size);
	if(err == memErrChunkLocked)
	{
		//unlock
		MemHandleUnlock(scriptH);
		if(err = MemHandleResize(scriptH, sizeof(ScriptType) * size))
		{
			ErrFatalDisplay("In sortscript, couldn't resize script");
		}
		script = (ScriptType *)MemHandleLock(scriptH);		 
	}		
	else if(err != 0)
	{
		//some other error
		ErrFatalDisplay("In sortscript, couldn't resize script");	
	}	
	
	//move all script into new one
	MemMove(script, &temp, sizeof(ScriptType) * size);
}