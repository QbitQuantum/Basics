//
// This callback gets called for the PostToolChanged and SelectionChanged events.
// It checks to see if the current context is the dragAttrContext, which is the context
// applied by default when a custom numeric attribute is selected in the channel box.
// In this case, the customAttrManip context is set.
// 
static void eventCB(void * data)
{
	// This check prevents recursion from happening when overriding the manip.
	if (isSetting)
		return;

	MSelectionList selList;
	MGlobal::getActiveSelectionList(selList);

	MString curCtx = "";
	MGlobal::executeCommand("currentCtx", curCtx);

	MDagPath path;
	MObject dependNode;
	for (unsigned int i=0; i<selList.length(); i++)
	{
        if ((selList.getDependNode(i, dependNode)) == MStatus::kSuccess)
		{
			MFnTransform node;
			if (node.hasObj(dependNode))
				node.setObject(dependNode);
			else
				continue;

			if (node.typeId() == rockingTransformNode::id)
			{
				// If the current context is the dragAttrContext, check to see
				// if the custom channel box attributes are selected.  If so,
				// attach the custom manipulator.
				if ((curCtx == "dragAttrContext") || (curCtx == ""))
				{
					// Make sure that the correct channel box attributes are selected
					// before setting the tool context.
					unsigned int c;
					MStringArray cboxAttrs;
					MGlobal::executeCommand(
							"channelBox -q -selectedMainAttributes $gChannelBoxName", cboxAttrs);
					for (c=0; c<cboxAttrs.length(); c++)
					{
						if (cboxAttrs[c] == customAttributeString)
						{
							isSetting = true;
							MGlobal::executeCommand("setToolTo myCustomAttrContext");
							isSetting = false;
							return;
						}
					}
				}
				if ((curCtx == "moveSuperContext") || (curCtx == "manipMoveContext") ||
					(curCtx == ""))
				{
					isSetting = true;
					MGlobal::executeCommand("setToolTo myCustomTriadContext");
					isSetting = false;
					return;
				}
			}
		}
	}
}