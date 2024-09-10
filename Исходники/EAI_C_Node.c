//writes all the parents of a given node into an allocated array and passes the address of it to the outParentArray argument. Caller should free the array.
//returns the number of parents, "0" if none found, "-1" if an error occurred
int X3D_getParentNodes(X3DNode* child, X3DNode** outParentArray)
{
	char *ptr;
	int adr;
	char arg[10];
	X3DNode* tmpBuf;
	X3DNode* tmpReallocBuf;
	char* parentToken;
	char* next_token;
	int parentAdr;
	int parentCount;

	parentToken=NULL;
	next_token=NULL;

	if((child->X3D_SFNode.type != FIELDTYPE_SFNode) && (child->X3D_MFNode.type != FIELDTYPE_MFNode)) {
		printf ("X3D_getParentNodes, expected a node, got a %s\n",FIELDTYPES[child->X3D_SFNode.type]);		
		return -1;
	}

	if (child->X3D_SFNode.type == FIELDTYPE_SFNode) {
		adr = child->X3D_SFNode.adr;
	} else {
		if (child->X3D_MFNode.n != 1) {
			printf ("warning - will only get event for first child = have %d nodes\n",child->X3D_MFNode.n);
		}
		/* get the first address in the list */
		adr = child->X3D_MFNode.p[5].adr; 
	}

	snprintf(arg, 10, "%d", adr);
	
	ptr = _X3D_make1StringCommand(GETNODEPARENTS,arg);

	REMOVE_EOT;

	//start tokenizer
	parentToken = STRTOK_S(ptr," ",&next_token);

	sscanf(parentToken,"%d",&parentAdr);

	//parent search did not found parents or encountered an error?
	if(parentAdr <= 0)
	{
		*outParentArray = NULL;
		return parentAdr;
	}		

	tmpBuf = (X3DNode*) calloc(10,sizeof(X3DNode));
	parentCount=0;

	while(parentToken)
	{
		//parentCount is a multiply of 10?
		if(parentCount && parentCount%10==0)
		{
			//reallocate the buffer with 10 more slots
			tmpReallocBuf =(X3DNode*) realloc(tmpBuf,(sizeof(X3DNode)*(parentCount+10)));

			//buffer was not reallocated, we exit
			if(!tmpReallocBuf)
			{
				*outParentArray = tmpBuf;
				return -1;
			}

			tmpBuf = tmpReallocBuf;
		}
				
		tmpBuf[parentCount].X3D_SFNode.type = FIELDTYPE_SFNode;

		sscanf(parentToken,"%d",&parentAdr);

		//parent search did not found parents or encountered an error?
		if(parentAdr <= 0)
		{
			*outParentArray = tmpBuf;
			return parentAdr;
		}

		tmpBuf[parentCount].X3D_SFNode.adr = parentAdr;

		parentCount++;		

		//find next parent address
		parentToken = STRTOK_S(NULL," ",&next_token);
	}

	*outParentArray = tmpBuf;

	return parentCount;
}