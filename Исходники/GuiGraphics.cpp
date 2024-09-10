void GuiGraphics::paramsToDialog(InsetGraphicsParams const & igp)
{
	static char const * const bb_units[] = { "bp", "cm", "mm", "in" };
	static char const * const bb_units_gui[] = { N_("bp"), N_("cm"), N_("mm"), N_("in[[unit of measure]]") };
	size_t const bb_size = sizeof(bb_units) / sizeof(bb_units[0]);

	lbXunit->clear();
	lbYunit->clear();
	rtXunit->clear();
	rtYunit->clear();
	
	for (size_t i = 0; i < bb_size; i++) {
		lbXunit->addItem(qt_(bb_units_gui[i]),
			toqstr(bb_units[i]));
		lbYunit->addItem(qt_(bb_units_gui[i]),
			toqstr(bb_units[i]));
		rtXunit->addItem(qt_(bb_units_gui[i]),
			toqstr(bb_units[i]));
		rtYunit->addItem(qt_(bb_units_gui[i]),
			toqstr(bb_units[i]));
	}

    preview->setImage(igp.imageData);
    imageData = igp.imageData;
	
	// set the right default unit
	Length::UNIT const defaultUnit = Length::defaultUnit();

	//lyxerr << bufferFilePath();
//	string const name =
//		igp.filename.outputFileName(fromqstr(bufferFilePath()));
//	filename->setText(toqstr(name));

	// set the bounding box values
	if (igp.bb.empty()) {
        string const bb = readBoundingBox(igp.imageData);
		// the values from the file always have the bigpoint-unit bp
		doubleToWidget(lbX, token(bb, ' ', 0));
		doubleToWidget(lbY, token(bb, ' ', 1));
		doubleToWidget(rtX, token(bb, ' ', 2));
		doubleToWidget(rtY, token(bb, ' ', 3));
		lbXunit->setCurrentIndex(0);
		lbYunit->setCurrentIndex(0);
		rtXunit->setCurrentIndex(0);
		rtYunit->setCurrentIndex(0);
		bbChanged = false;
	} else {
		// get the values from the inset
		Length anyLength;
		string const xl = token(igp.bb, ' ', 0);
		string const yl = token(igp.bb, ' ', 1);
		string const xr = token(igp.bb, ' ', 2);
		string const yr = token(igp.bb, ' ', 3);
		if (isValidLength(xl, &anyLength)) {
			doubleToWidget(lbX, anyLength.value());
			string const unit = unit_name[anyLength.unit()];
			lbXunit->setCurrentIndex(lbXunit->findData(toqstr(unit)));
		} else {
			lbX->setText(toqstr(xl));
		}
		if (isValidLength(yl, &anyLength)) {
			doubleToWidget(lbY, anyLength.value());
			string const unit = unit_name[anyLength.unit()];
			lbYunit->setCurrentIndex(lbYunit->findData(toqstr(unit)));
		} else {
			lbY->setText(toqstr(xl));
		}
		if (isValidLength(xr, &anyLength)) {
			doubleToWidget(rtX, anyLength.value());
			string const unit = unit_name[anyLength.unit()];
			rtXunit->setCurrentIndex(rtXunit->findData(toqstr(unit)));
		} else {
			rtX->setText(toqstr(xl));
		}
		if (isValidLength(yr, &anyLength)) {
			doubleToWidget(rtY, anyLength.value());
			string const unit = unit_name[anyLength.unit()];
			rtYunit->setCurrentIndex(rtYunit->findData(toqstr(unit)));
		} else {
			rtY->setText(toqstr(xl));
		}
		bbChanged = true;
	}

	// Update the draft and clip mode
	draftCB->setChecked(igp.draft);
	clip->setChecked(igp.clip);
	unzipCB->setChecked(igp.noUnzip);
	displayGB->setChecked(igp.display);
	displayscale->setText(toqstr(convert<string>(igp.lyxscale)));

	// the output section (width/height)

	doubleToWidget(Scale, igp.scale);
	//igp.scale defaults to 100, so we treat it as empty
	bool const scaleChecked = !igp.scale.empty() && igp.scale != "100";
	scaleCB->blockSignals(true);
	scaleCB->setChecked(scaleChecked);
	scaleCB->blockSignals(false);
	Scale->setEnabled(scaleChecked);
	displayGB->setEnabled(lyxrc.display_graphics);

	set<string> grp;
	graphics::getGraphicsGroups(buffer(), grp);
	set<string>::const_iterator it = grp.begin();
	set<string>::const_iterator end = grp.end();
	groupCO->blockSignals(true);
	groupCO->clear();
	for (; it != end; ++it)
		groupCO->addItem(toqstr(*it), toqstr(*it));
	groupCO->insertItem(0, qt_("None"), QString());
	if (igp.groupId.empty())
		groupCO->setCurrentIndex(0);
	else
		groupCO->setCurrentIndex(
			groupCO->findData(toqstr(igp.groupId), Qt::MatchExactly));
	groupCO->blockSignals(false);

	if (igp.width.value() == 0)
		lengthToWidgets(Width, widthUnit, _(autostr), defaultUnit);
	else
		lengthToWidgets(Width, widthUnit, igp.width, defaultUnit);

	bool const widthChecked = !Width->text().isEmpty() &&
		Width->text() != qt_(autostr);
	WidthCB->blockSignals(true);
	WidthCB->setChecked(widthChecked);
	WidthCB->blockSignals(false);
	Width->setEnabled(widthChecked);
	widthUnit->setEnabled(widthChecked);

	if (igp.height.value() == 0)
		lengthToWidgets(Height, heightUnit, _(autostr), defaultUnit);
	else
		lengthToWidgets(Height, heightUnit, igp.height, defaultUnit);

	bool const heightChecked = !Height->text().isEmpty()
		&& Height->text() != qt_(autostr);
	HeightCB->blockSignals(true);
	HeightCB->setChecked(heightChecked);
	HeightCB->blockSignals(false);
	Height->setEnabled(heightChecked);
	heightUnit->setEnabled(heightChecked);

	scaleCB->setEnabled(!widthChecked && !heightChecked);
	WidthCB->setEnabled(!scaleChecked);
	HeightCB->setEnabled(!scaleChecked);
	aspectratio->setEnabled(widthChecked && heightChecked);

	setAutoText();

	doubleToWidget(angle, igp.rotateAngle);
	rotateOrderCB->setChecked(igp.scaleBeforeRotation);

	rotateOrderCB->setEnabled( (widthChecked || heightChecked || scaleChecked)
		&& igp.rotateAngle != "0");

	origin->clear();

	for (size_t i = 0; i < rorigin_size; i++) {
		origin->addItem(qt_(rorigin_gui_strs[i]),
			toqstr(rorigin_lyx_strs[i]));
	}

	if (!igp.rotateOrigin.empty())
		origin->setCurrentIndex(origin->findData(toqstr(igp.rotateOrigin)));
	else
		origin->setCurrentIndex(0);

	// latex section
	latexoptions->setText(toqstr(igp.special));
}