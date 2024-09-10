/*
Print out current tree content
*/
void CLeafDirTree::DumpTreeContentL() const
	{
	RPointerArray<CLeafDirTreeNode>* nodeStack = new(ELeave) RPointerArray<CLeafDirTreeNode>(4);
	RFs fs;
	
    TInt nRes = fs.Connect();
    User::LeaveIfError(nRes);

	const TUint32 debugRegister = DebugRegister();
	fs.SetDebugRegister(debugRegister|KFSYS);
	if (iRoot != NULL)
		{
		nodeStack->Insert(iRoot, 0);
		while(nodeStack->Count() > 0)
			{
			CLeafDirTreeNode* current = (*nodeStack)[0];
			if (current->Parent() != NULL)
				{
				__PRINT3(_L("(\"%S\") -> \"%S\" : (%d)\n"), &current->Parent()->Path(), &current->Path(), current->StartClusterNum());
				}
			else
				{
				__PRINT2(_L("\"%S\" : (%d)\n"), &current->Path(), current->StartClusterNum());				
				}

			nodeStack->Remove(0);
			
			TInt currentCount = current->Children().Count();
			if (currentCount > 0)
				{
				RPointerArray<CLeafDirTreeNode> children = current->Children();
				for (TInt i = 0; i < currentCount; i++)
					{
					nodeStack->Insert(children[i], 0);
					}
				}
			}
		}

	fs.SetDebugRegister(debugRegister);
	fs.Close();
	nodeStack->Close();
	delete nodeStack;
	}