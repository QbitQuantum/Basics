	void FalagardSuperTooltip::setPageElementsName(const String& strName)
	{
		//Split string 
		std::vector< String > vElementNameVector = split_string(strName, (utf8*)";", getChildCount());

		//Hide all sub window
		int nChildSize = (int)getChildCount();
		for(int i=0; i<nChildSize; i++)
		{
			d_children[i]->hide();
		}

		//Clear old elements
		d_VectorElements.clear();
		int nSize = (int)vElementNameVector.size();
		for(int i=0; i<nSize; i++)
		{
			//Only accept child window
			if(!isChild(vElementNameVector[i])) continue;

			//Get Child window
			Window* pChild = getChild(vElementNameVector[i]);
			pChild->show();

			Elements newElement;
			newElement.pWindow = pChild;
			//Dynamic size window (Resize Text)
			if(pChild->testClassName("FalagardSuperTooltip/ResizeText"))
			{
				newElement.bDynamicSize = true;
			}
			//Static size window
			else
			{
				newElement.bDynamicSize = false;
			}

			d_VectorElements.push_back(newElement);
		}
	}