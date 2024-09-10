void CContainer::ContentNotifyDelete()
{
	ADDTOCALLSTACK("CContainer::ContentNotifyDelete");
	if ( IsTrigUsed(TRIGGER_DESTROY) ) // no point entering this loop if the trigger is disabled
		return;

	// trigger @Destroy on contained items
	CItem *pItemNext = NULL;
	for (CItem *pItem = GetContentHead(); pItem != NULL; pItem = pItemNext)
	{
		pItemNext = pItem->GetNext();

		if ( pItem->NotifyDelete() == false )
		{
			// item shouldn't be destroyed and so cannot remain in this container,
			// drop it to the ground if it hasn't been moved already
			if (pItem->GetParent() == this)
				pItem->MoveToCheck( pItem->GetTopLevelObj()->GetTopPoint() );
		}
	}
}