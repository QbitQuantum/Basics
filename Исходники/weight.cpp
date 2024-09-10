/*!
\brief recurses through the container given to calculate the total weight
\author Ison (02/20/99), rewritten by Tauriel (03/20/99), rewritten by Duke (04/11/00)
\return the weight
\param bp the item
*/
float weights::RecursePacks(P_ITEM bp)
{
	double totalweight=0.0;

	if (!ISVALIDPI(bp)) return 0.0;
	
	NxwItemWrapper si;
	si.fillItemsInContainer( bp, false );
	for( si.rewind(); !si.isEmpty(); si++ )
	{
		P_ITEM pi=si.getItem();
		if( !ISVALIDPI(pi)) continue;

		R32 itemsweight=pi->getWeightActual();
		if (pi->isContainer()) //item is another container
		{
			totalweight+=(itemsweight/100.0);		// the weight of container itself
			totalweight+=RecursePacks(pi); //find the item's weight within this container
		}
		
		totalweight+=((itemsweight)/100.0);
	}
	return static_cast<float>(totalweight);
}