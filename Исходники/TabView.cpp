void
BTab::Deselect()
{
	if (View()) {
		// NOTE: Views are not added/removed, if there is layout,
		// they are made visible/invisible in that case.
		bool removeView = false;
		BView* container = View()->Parent();
		if (container)
			removeView =
				dynamic_cast<BCardLayout*>(container->GetLayout()) == NULL;
		if (removeView)
			View()->RemoveSelf();
	}

	fSelected = false;
}