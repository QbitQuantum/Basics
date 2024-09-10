/**
Removes comm addresses from the 3 lists that are already in the database and have been updated.
It takes the 3 lists in as parameters and modifies them accordingly. It also populates the list
of comm address ids that are free to be recycled during updating.
*/
void CPplCommAddrTable::RemoveNonUpdatedAddrsL(RArray<TMatch>& aNewPhones, RArray<TPtrC>& aNewEmails, RArray<TPtrC>& aNewSips,
					  RArray<TInt>& aFreeCommAddrIds, const TInt aItemId,CPplCommAddrTable::TCommAddrExtraInfoType 
                      aExtraInfoType )
	{
	// build the RSqlStatement
	RSqlStatement stmnt;
	CleanupClosePushL(stmnt);
	stmnt.PrepareL(iDatabase, iWholeSelectStmnt->SqlStringL() );
	const TInt KContactIdParamIndex(KFirstIndex); // first and only parameter in the query
	User::LeaveIfError(stmnt.BindInt(KContactIdParamIndex, aItemId) ) ;

	// fetch the results from the query and compare them with the new comm_addrs we have
	TInt err(KErrNone);
	while ((err = stmnt.Next() ) == KSqlAtRow)
		{
		const TInt KType(stmnt.ColumnInt(iWholeSelectStmnt->ParameterIndex(KCommAddrType() ) ) );
		if (KType == EPhoneNumber)
			{
			TMatch phoneNumber;
			TPtrC valString    = stmnt.ColumnTextL(iWholeSelectStmnt->ParameterIndex(KCommAddrValue() ) );
			TPtrC extValString = stmnt.ColumnTextL(iWholeSelectStmnt->ParameterIndex(KCommAddrExtraValue() ) );
			TInt extTypeInfoString = stmnt.ColumnInt(iWholeSelectStmnt->ParameterIndex(KCommAddrExtraTypeInfo() ) );
			User::LeaveIfError(TLex(valString).Val(phoneNumber.iLowerSevenDigits) );
			User::LeaveIfError(TLex(extValString).Val(phoneNumber.iUpperDigits) );

			TInt matchIndex(aNewPhones.Find(phoneNumber, TIdentityRelation<TMatch>(&TMatch::Equals) ) );
			// remove any phone numbers from the new list if we already
			// have them in the db and they haven't changed...
			if (matchIndex != KErrNotFound  && (extTypeInfoString == aExtraInfoType))
				{
				aNewPhones.Remove(matchIndex);
				}
			// ...and add any spare ids to the recycle list
			else
				{
				aFreeCommAddrIds.AppendL(
					stmnt.ColumnInt(iWholeSelectStmnt->ParameterIndex(KCommAddrId() ) ) );
				}
			}
		else // is Email or SIP
			{
			TPtrC valString = stmnt.ColumnTextL(iWholeSelectStmnt->ParameterIndex(KCommAddrValue() ) );
			TInt matchIndex(0);

			// remove any email and sip addresses from the new list if
			// we already have them in the db and they haven't changed...
			if (KType == EEmailAddress)
				{
				matchIndex = aNewEmails.Find(valString);
				if (matchIndex != KErrNotFound)
					{
					aNewEmails.Remove(matchIndex);
					}
				}
			else // SIP
				{
				matchIndex = aNewSips.Find(valString);
				if (matchIndex != KErrNotFound)
					{
					aNewSips.Remove(matchIndex);
					}
				}

			// ...and add any spare ids to the recycle list
			if (matchIndex == KErrNotFound)
				{
				aFreeCommAddrIds.AppendL(
					stmnt.ColumnInt(iWholeSelectStmnt->ParameterIndex(KCommAddrId() ) ) );
				}
			}
		}
	// leave if we didn't complete going through the results properly
	if(err != KSqlAtEnd)
		{
		User::Leave(err);
		}
	CleanupStack::PopAndDestroy(&stmnt);
	}