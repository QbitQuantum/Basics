/*!

*/
bool QFoldPanel::paint(QPainter *p, QEditor *e)
{
	QDocument *doc = editor()->document();
	QLanguageDefinition *def = e->languageDefinition();

	if ( !def || !doc )
	{
		return true;
	}

	m_rects.clear();
	m_lines.clear();

	bool bVisible = false; //,
	//	inCursorBlock = false;

	int pos,
		max = doc->lines(),
		ls = doc->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();
	
	pos = - contentsY;

	//qDebug("beg pos : %i", pos);

	QFoldedLineIterator fli = def->foldedLineIterator(doc);

	bool oldFolding=false;

	for (; fli.lineNr<max; ++fli)
	{
		if ( pos > pageBottom )
			break;

		const QDocumentLine &line=fli.line;

		if ( fli.lineFlagsInvalid() ){
			//correct folding when the folding of the current line is invalid
			//problems: slow (but O(n) like the paint method is anyways), doesn't work if panel is hidden
			//pro: simple, doesn't correct invalid, but invisible folding (e.g. like folding that is only temporary invalid, until the user writes a closing bracket; otherwise writing $$ would expand every folded $-block)
			doc->correctFolding(fli.lineNr, doc->lines()); //this will again call paint
			return true;
		}

		if ( line.isHidden() )
		{
			continue;
		}

		int len = ls * line.lineSpan();

//		bool oldFolding = !fli.openParentheses.empty() && fli.openParentheses.first().line!=fli.lineNr;

		bVisible = ((pos + len) >= 0);

		if ( fli.open )
		{
			if ( line.hasFlag(QDocumentLine::CollapsedBlockStart) )
			{
				// outermost block folded : none of the opening is actually opened
				int bound = (ls - 8) / 2;
				int mid = pos + len - ls / 6;

				if ( bVisible )
				{
					// draw icon

					if ( bound > 0 && oldFolding )
					{
						p->drawLine(7, pos, 7, pos + bound);
					}

					if ( fli.close )
					{
						p->drawLine(7, pos + 8 + bound, 7, mid);
						p->drawLine(7, mid, 12, mid);
					}

					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 3, pos + bound, true);
				}

				int firstParenthesisPos = fli.openParentheses.size() - fli.open;
				const FoldedParenthesis firstParenthesis = fli.openParentheses[firstParenthesisPos];

				while (fli.lineNr<doc->lines() &&
				       firstParenthesisPos<fli.openParentheses.size() &&
				       fli.openParentheses[firstParenthesisPos] == firstParenthesis){
					if (fli.lineNr < doc->lines()-1 && !doc->line(fli.lineNr+1).isHidden()) {
						if ( bVisible )
							p->drawLine(7, pos + 8 + bound, 7, pos + len);
						break;
					}
					++fli;
				}

				if ( bVisible && !fli.openParentheses.empty() )
				{
					if ( fli.close )
						p->drawLine(7, mid, 7, pos + len);
					else
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
				}
			} else {
				if ( bVisible )
				{
					int bound = (ls - 8) / 2;

					if ( oldFolding && bound > 0 )
						p->drawLine(7, pos, 7, pos + bound);

					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 3, pos + bound, false);

					int mid = pos + len - ls / 6;

					if ( fli.close )
						p->drawLine(7, mid, 12, mid);

					if ( bound > 0 )
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
				}
			}
		} else if ( (oldFolding) && bVisible ) {
			if ( fli.close )
			{
				int mid = pos + len - ls / 6;

				p->drawLine(7, pos, 7, mid);
				p->drawLine(7, mid, 12, mid);

				if ( !fli.openParentheses.empty() )
					p->drawLine(7, pos, 7, pos + len);
			} else  {
				p->drawLine(7, pos, 7, pos + len);
			}
		}

		pos += len;
		oldFolding=!fli.openParentheses.empty();
	}
	
	return true;
}