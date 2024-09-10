//*****************************************************************************************************************
void CGroupHeader::resizeColumnsAndContainer(sint32 margin)
{
	std::vector<CGroupHeaderEntry *> entries;
	getEntries(entries);
	sint32 totalWidth = 0;
	for (uint k = 0; k < entries.size(); ++k)
	{
		CInterfaceGroup *colEnclosing = entries[k]->getTargetColumn();
		if (colEnclosing && !colEnclosing->getGroups().empty())
		{
			CInterfaceGroup *col = colEnclosing->getGroups()[0];
			if (col)
			{
				// enlarge to the max to be able to measure the sub text (they may clamp themselves based
				// on their first non-"child resizing" parent (see CViewText::updateCoords)
				colEnclosing->setW(16384);
				colEnclosing->invalidateCoords();
				colEnclosing->updateCoords();

				// assume that first child is resizing from its children width (either 'child_resize_w=true' or a CGroupList)
				entries[k]->setW(std::max(entries[k]->getMinSize(), col->getW() + margin));
				entries[k]->invalidateCoords();
				totalWidth += entries[k]->getW();
			}
		}
	}

	// resize W
	if (totalWidth <= _HeaderMaxSize)
	{
		// search first parent that limit size, if it is larger then enlarge to fit size
		CInterfaceGroup *limitingParent = getParent();
		while (limitingParent && (limitingParent->getResizeFromChildW() || dynamic_cast<CGroupList *>(limitingParent)))
		{
			// NB nico : the dynamic_cast for CGroupList is bad!!
			// can't avoid it for now, because, CGroupList implicitly does a "resize from child" in its update coords
			// ...
			limitingParent = limitingParent->getParent();
		}

		getParentContainer()->setW(totalWidth + getParentContainer()->getWReal() - limitingParent->getWReal());
	}

	// resize H
	if(entries.size()>0)
	{
		CInterfaceGroup *colEnclosing = entries[0]->getTargetColumn();
		if (colEnclosing && !colEnclosing->getGroups().empty())
		{
			CInterfaceGroup *col = colEnclosing->getGroups()[0];
			if (col)
			{
				// search first parent that limit size, if it is larger then enlarge to fit size
				CInterfaceGroup *limitingParent = colEnclosing->getParent();
				while (limitingParent && (limitingParent->getResizeFromChildH() || dynamic_cast<CGroupList *>(limitingParent)))
					limitingParent = limitingParent->getParent();

				getParentContainer()->setH(col->getH() + getParentContainer()->getHReal() - limitingParent->getHReal());
			}
		}
	}


	invalidateCoords();
}