bool TreeNode::ValidateExpandButton() {
	bool repaint = false;

	if (child_nodes_ != 0 && expand_button_ == 0) {
		GUIImageManager* i_man = GetImageManager();

		/*expand_button_ = new CheckButton(expand_icon_id_, collapse_icon_id_,
						 expand_icon_id_, collapse_icon_id_,
						 collapse_icon_id_, expand_icon_id_,
						 "ExpandButton");*/

		expand_button_->SetPreferredSize(i_man->GetImageSize(expand_icon_id_));
		expand_button_->SetMinSize(expand_button_->GetPreferredSize());

		expand_button_->SetOnClick(TreeNode, OnExpandButtonUnclicked);

		// Create a rect with a CenterLayout in order to keep the button centered.
		RectComponent* rect = new RectComponent(new CenterLayout());
		rect->AddChild(expand_button_);

		rect->SetPreferredSize(expand_button_->GetPreferredSize());
		rect->SetMinSize(expand_button_->GetMinSize());

		if (((GridLayout*)GetLayout())->GetNumCols() > 1) {
			Component* comp = ((GridLayout*)GetLayout())->GetComponentAt(0, 0);
			((GridLayout*)GetLayout())->DeleteColumn(0);
			delete comp;
		}
		((GridLayout*)GetLayout())->InsertColumn(0);
		AddChild(rect, 0, 0);

		repaint = true;
	} else if (child_nodes_ == 0 && expand_button_ == 0) {
		GUIImageManager* i_man = GetImageManager();

		RectComponent* rect = new RectComponent(new CenterLayout());

		rect->SetPreferredSize(i_man->GetImageSize(expand_icon_id_));
		rect->SetMinSize(rect->GetPreferredSize());

		((GridLayout*)GetLayout())->InsertColumn(0);
		AddChild(rect, 0, 0);
	}

	return repaint;
}