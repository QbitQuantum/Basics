void CCommandInfoFile::AddSubCommandL(TLex& aNameLex, TLex& aDataLex, RFs& aFs, const TDesC& aFileName)
	{
	TPtrC subCommandName(NextWord(aNameLex));
	TBool found(EFalse);
	for (TInt i = (iChildren.Count() - 1); i >= 0; --i)
		{
		if (iChildren[i]->Name() == subCommandName)
			{
			iChildren[i]->AddSubCommandL(aNameLex, aDataLex, aFs, aFileName);
			found = ETrue;
			break;
			}
		}
	__ASSERT_ALWAYS(found || (aNameLex.Remainder().Length() == 0), IoUtils::Panic(ECifSubCommandParentNotFound));
	if (!found)
		{
		CCommandInfoFile* subCommand = new(ELeave) CCommandInfoFile(*this);
		CleanupStack::PushL(subCommand);
		subCommand->iName.Set(subCommandName);
		subCommand->ReadDetailsL(aDataLex, aFs, aFileName);
		iChildren.AppendL(subCommand);
		CleanupStack::Pop(subCommand);
		}
	}