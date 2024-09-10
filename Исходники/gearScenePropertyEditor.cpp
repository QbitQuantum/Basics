bool gearScenePropertyEditor::onMouseMove(float x, float y, int flag)
{
#if DEPRECATED
	//if(!isPointInsideWindow(x, y-getTopMarginOffsetHeight()))
	//	return;

	geTreeNode* selectedNode=m_cPropertiesTreeView.getSelectedNode();
	if((flag&MK_LBUTTON) && selectedNode)
	{
		if(m_cPropertiesTreeView.getScrollBar()->isScrollBarGrabbed())
			return true;

		if(selectedNode->getParent()==m_pAnimationParentNode)
		{
			std::vector<geGUIBase*>* newlist = new std::vector<geGUIBase*>();
			newlist->push_back(selectedNode);

			MDataObject* dataObject = new MDataObject(newlist, this);
			MDropSource* dropSource = new MDropSource();

			DWORD lpd=0;
			HRESULT ok=DoDragDrop(dataObject, dropSource, DROPEFFECT_MOVE, &lpd);

			dataObject->Release();
			dropSource->Release();
		}
		return true;
	}
#endif
	return true;
}