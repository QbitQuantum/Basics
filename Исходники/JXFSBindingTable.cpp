void
JXFSBindingTable::TableDrawCell
	(
	JPainter&		p,
	const JPoint&	cell,
	const JRect&	rect
	)
{
	JPoint editCell;
	if (GetEditedCell(&editCell) && cell == editCell)
		{
		return;
		}

	HilightIfSelected(p, cell, rect);

	const JFSBinding* b = itsBindingList->GetBinding(cell.y);
	JFSBinding::CommandType type;
	JBoolean singleFile;
	const JString& cmd = b->GetCommand(&type, &singleFile);

	if (cell.x == kPatternColumn)
		{
		p.SetFont(JGetMonospaceFontName(), kJDefaultMonoFontSize, JFontStyle());

		JRect r = rect;
		r.left += kHMarginWidth;
		p.String(r, b->GetPattern(), JPainter::kHAlignLeft, JPainter::kVAlignCenter);

		p.SetFont(JGetDefaultFontName(), kJDefaultFontSize, JFontStyle());
		}
	else if (cell.x == kCommandColumn)
		{
		p.SetFont(JGetMonospaceFontName(), kJDefaultMonoFontSize, JFontStyle());

		JRect r = rect;
		r.left += kHMarginWidth;
		p.String(r, cmd, JPainter::kHAlignLeft, JPainter::kVAlignCenter);

		p.SetFont(JGetDefaultFontName(), kJDefaultFontSize, JFontStyle());
		}
	else if (cell.x == kTypeColumn)
		{
		const JString& str = itsTypeMenu->GetItemText(kCmdTypeToMenuIndex[type]);
		p.String(rect, str, JPainter::kHAlignCenter, JPainter::kVAlignCenter);
		}
	else if (cell.x == kSingleFileColumn && singleFile)
		{
		JRect r;
		r.top    = rect.ycenter();
		r.left   = rect.xcenter();
		r.bottom = r.top+1;
		r.right  = r.left+1;
		r.Expand(3, 3);

		p.SetFilling(kJTrue);
		p.Ellipse(r);
		p.SetFilling(kJFalse);
		}
}