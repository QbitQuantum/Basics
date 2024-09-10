// Choose the "most relevant" operation for this object, and show a button for
// that operation as the left-most button in the inspector.
void LLInspectObject::updateButtons(LLSelectNode* nodep)
{
	// We'll start with everyone hidden and show the ones we need
	hideButtons();
	
	LLViewerObject* object = nodep->getObject();
	LLViewerObject *parent = (LLViewerObject*)object->getParent();
	bool for_copy = anyone_copy_selection(nodep);
	bool for_sale = enable_buy_object();
	S32 price = nodep->mSaleInfo.getSalePrice();
	U8 click_action = final_click_action(object);

	if (for_copy
		|| (for_sale && price == 0))
	{
		// Free copies have priority over other operations
		getChild<LLUICtrl>("take_free_copy_btn")->setVisible(true);
	}
	else if (for_sale)
	{
		getChild<LLUICtrl>("buy_btn")->setVisible(true);
	}
	else if ( enable_pay_object() )
	{
		getChild<LLUICtrl>("pay_btn")->setVisible(true);
	}
	else if (click_action == CLICK_ACTION_SIT)
	{
		// Click-action sit must come before "open" because many objects on
		// which you can sit have scripts, and hence can be opened
		getChild<LLUICtrl>("sit_btn")->setVisible(true);
		updateSitLabel(nodep);
	}
	else if (object->flagHandleTouch()
		|| (parent && parent->flagHandleTouch()))
	{
		getChild<LLUICtrl>("touch_btn")->setVisible(true);
		updateTouchLabel(nodep);
	}
	else if ( enable_object_open() )
	{
		// Open is last because anything with a script in it can be opened
		getChild<LLUICtrl>("open_btn")->setVisible(true);
	}
	else
	{
		// By default, we can sit on anything
		getChild<LLUICtrl>("sit_btn")->setVisible(true);
		updateSitLabel(nodep);
	}

	// No flash
	focusFirstItem(FALSE, FALSE);
}