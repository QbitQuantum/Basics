void
PartitionsPage::_BuildUI()
{
	BString text;
	text << B_TRANSLATE_COMMENT("Partitions", "Title") << "\n"
		<< B_TRANSLATE("The following partitions were detected. Please "
			"check the box next to the partitions to be included "
			"in the boot menu. You can also set the names of the "
			"partitions as you would like them to appear in the "
			"boot menu.");
	fDescription = CreateDescription("description", text);
	MakeHeading(fDescription);

	fPartitions = new BGridView("partitions", 0,
		be_control_look->DefaultItemSpacing() / 3);

	BLayoutBuilder::Grid<>(fPartitions)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING,
			B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
		.SetColumnWeight(0, 0)
		.SetColumnWeight(1, 1)
		.SetColumnWeight(2, 0.5)
		.SetColumnWeight(3, 0.5);
	_FillPartitionsView(fPartitions);

	BScrollView* scrollView = new BScrollView("scrollView", fPartitions, 0,
		false, true);

	SetLayout(new BGroupLayout(B_VERTICAL));

	BLayoutBuilder::Group<>((BGroupLayout*)GetLayout())
		.Add(fDescription)
		.Add(scrollView);
}