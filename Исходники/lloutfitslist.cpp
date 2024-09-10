void LLOutfitsList::onAccordionTabRightClick(LLUICtrl* ctrl, S32 x, S32 y, const LLUUID& cat_id)
{
	LLAccordionCtrlTab* tab = dynamic_cast<LLAccordionCtrlTab*>(ctrl);
	if(mOutfitMenu && is_tab_header_clicked(tab, y) && cat_id.notNull())
	{
		// Focus tab header to trigger tab selection change.
		LLUICtrl* header = tab->findChild<LLUICtrl>("dd_header");
		if (header)
		{
			header->setFocus(TRUE);
		}

		uuid_vec_t selected_uuids;
		selected_uuids.push_back(cat_id);
		mOutfitMenu->show(ctrl, selected_uuids, x, y);
	}
}