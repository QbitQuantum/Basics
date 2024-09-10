PageItem_NoteFrame::PageItem_NoteFrame(PageItem_TextFrame* inFrame, NotesStyle *nStyle) : PageItem_TextFrame(inFrame->doc(),inFrame->xPos(), inFrame->yPos(),inFrame->width(), inFrame->height(),inFrame->lineWidth(), inFrame->fillColor(), inFrame->lineColor())
{
	m_nstyle = nStyle;
	m_masterFrame = inFrame;

	AnName = generateUniqueCopyName(nStyle->isEndNotes() ? tr("Endnote frame ") + m_nstyle->name() : tr("Footnote frame ") + m_nstyle->name(), false);
	AutoName = false;
	setUName(AnName);

	//set default style for note frame
	ParagraphStyle newStyle;
	if (nStyle->notesParStyle().isEmpty() || (nStyle->notesParStyle() == tr("No Style")))
	{
		if (nStyle->isEndNotes())
			//set default doc style
			newStyle.setParent(m_Doc->paragraphStyles()[0].name());
		else
		{
			newStyle.setParent(m_masterFrame->itemText.defaultStyle().parent());
			newStyle.applyStyle(m_masterFrame->currentStyle());
		}
	}
	else
		newStyle.setParent(nStyle->notesParStyle());
	itemText.blockSignals(true);
	itemText.setDefaultStyle(newStyle);
	itemText.blockSignals(false);
	
	double frameHeight = calculateLineSpacing(newStyle, this);
	if (frameHeight == 0.0 && !m_nstyle->isAutoNotesHeight())
		frameHeight = newStyle.charStyle().fontSize()/10;
	m_height = oldHeight = frameHeight;
	oldWidth = m_width;
	oldRot = m_rotation;
	oldXpos = m_xPos;
	m_yPos = oldYpos =m_masterFrame->yPos() + m_masterFrame->height();

	textFlowModeVal = TextFlowUsesFrameShape;
	setColumns(1);

	if (m_nstyle->isAutoWeldNotesFrames() && (m_masterFrame != NULL))
	{
		addWelded(m_masterFrame);
		m_masterFrame->addWelded(this);
		m_masterFrame->setWeldPoint(0, m_masterFrame->height(), this);
		setWeldPoint(0,0, m_masterFrame);
	}
	if (m_nstyle->isAutoNotesHeight())
		m_SizeVLocked = true;
	else
		m_SizeVLocked = false;
	if (m_nstyle->isAutoNotesWidth())
		m_SizeHLocked = true;
	else
		m_SizeHLocked = false;
	if (m_nstyle->isAutoNotesHeight() && m_nstyle->isAutoNotesWidth())
		m_SizeLocked = true;
	else
		m_SizeLocked = false;
	deleteIt = false;
}