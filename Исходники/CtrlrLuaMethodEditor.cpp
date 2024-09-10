void CtrlrLuaMethodEditor::itemDropped (ValueTree &targetItem, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
{
	if ( (targetItem.hasType(Ids::luaMethodGroup) || targetItem.hasType(Ids::luaManagerMethods)) && insertIndex == 0 )
	{
		StringArray ar;
		ar.addTokens (dragSourceDetails.description.toString(), ";", "\"'");

		for (int i=0; i<ar.size(); i++)
		{
			CtrlrValueTreeEditorItem *sourceItem = dynamic_cast<CtrlrValueTreeEditorItem*>(methodTree->findItemFromIdentifierString (ar[i]));
			if (sourceItem != nullptr)
			{
				ValueTree child		= sourceItem->getTree();
				ValueTree parent	= child.getParent();
				parent.removeChild (child, nullptr);
				targetItem.addChild (child, -1, nullptr);
			}
		}

		triggerAsyncUpdate();
	}
}