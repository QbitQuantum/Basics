	void step_attach_widget()
	{
		MyGUI::Widget* widget1 = get_random(all_widgets);
		MyGUI::Widget* widget2 = get_random(all_widgets);
		if (!widget1 || !widget2) return;

		MyGUI::Widget* test = widget1;
		do
		{
			if (test == widget2) return;
			test = test->getParent();
		}
		while (test);

		widget2->attachToWidget(widget1, get_type(), get_layer());
		test_widgets();
	}