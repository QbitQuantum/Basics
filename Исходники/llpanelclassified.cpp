//virtual
BOOL LLFloaterPriceForListing::postBuild()
{
	LLLineEditor* edit = getChild<LLLineEditor>("price_edit");
	if (edit)
	{
		edit->setPrevalidate(LLLineEditor::prevalidateNonNegativeS32);
		std::string min_price = llformat("%d", MINIMUM_PRICE_FOR_LISTING);
		edit->setText(min_price);
		edit->selectAll();
		edit->setFocus(TRUE);
	}

	childSetAction("set_price_btn", onClickSetPrice, this);

	childSetAction("cancel_btn", onClickCancel, this);

	setDefaultBtn("set_price_btn");
	return TRUE;
}