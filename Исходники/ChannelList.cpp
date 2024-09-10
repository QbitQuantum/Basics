void ChannelListItem::paintCell( QPainter *p, const QColorGroup &cg, int column, int width, int align )
{
	QPixmap back( width, height() );
	QPainter paint( &back );
	//KListViewItem::paintCell( &paint, cg, column, width, align );
	// PASTED FROM KLISTVIEWITEM:
	// set the alternate cell background colour if necessary
	QColorGroup _cg = cg;
	if (isAlternate())
		if (listView()->viewport()->backgroundMode()==Qt::FixedColor)
			_cg.setColor(QColorGroup::Background, static_cast< KListView* >(listView())->alternateBackground());
		else
			_cg.setColor(QColorGroup::Base, static_cast< KListView* >(listView())->alternateBackground());
	// PASTED FROM QLISTVIEWITEM
	{
		QPainter *p = &paint;

		QListView *lv = listView();
		if ( !lv )
			return;
		QFontMetrics fm( p->fontMetrics() );

		// any text we render is done by the Components, not by this class, so make sure we've nothing to write
		QString t;

		// removed text truncating code from Qt - we do that differently, further on

		int marg = lv->itemMargin();
		int r = marg;
	//	const QPixmap * icon = pixmap( column );

		const BackgroundMode bgmode = lv->viewport()->backgroundMode();
		const QColorGroup::ColorRole crole = QPalette::backgroundRoleFromMode( bgmode );

		if ( _cg.brush( crole ) != lv->colorGroup().brush( crole ) )
			p->fillRect( 0, 0, width, height(), _cg.brush( crole ) );
		else
		{
			// all copied from QListView::paintEmptyArea

			//lv->paintEmptyArea( p, QRect( 0, 0, width, height() ) );
			QStyleOption opt( lv->sortColumn(), 0 ); // ### hack; in 3.1, add a property in QListView and QHeader
			QStyle::SFlags how = QStyle::Style_Default;
			if ( lv->isEnabled() )
				how |= QStyle::Style_Enabled;

			lv->style().drawComplexControl( QStyle::CC_ListView,
						p, lv, QRect( 0, 0, width, height() ), lv->colorGroup(),
						how, QStyle::SC_ListView, QStyle::SC_None,
						opt );
		}



		if ( isSelected() &&
		(column == 0 || lv->allColumnsShowFocus()) ) {
			p->fillRect( r - marg, 0, width - r + marg, height(),
					_cg.brush( QColorGroup::Highlight ) );
	// removed text pen setting code from Qt
		}

		// removed icon drawing code from Qt

		// draw the tree gubbins
		if ( multiLinesEnabled() && column == 0 && isOpen() && childCount() ) {
			int textheight = fm.size( align, t ).height() + 2 * lv->itemMargin();
			textheight = QMAX( textheight, QApplication::globalStrut().height() );
			if ( textheight % 2 > 0 )
				textheight++;
			if ( textheight < height() ) {
				int w = lv->treeStepSize() / 2;
				lv->style().drawComplexControl( QStyle::CC_ListView, p, lv,
								QRect( 0, textheight, w + 1, height() - textheight + 1 ), _cg,
								lv->isEnabled() ? QStyle::Style_Enabled : QStyle::Style_Default,
								QStyle::SC_ListViewExpand,
								(uint)QStyle::SC_All, QStyleOption( this ) );
			}
		}
	}
	// END OF PASTE


	//do you see a better way to tell the TextComponent we are selected ?  - Olivier 2004-09-02
	if ( isSelected() )
		_cg.setColor(QColorGroup::Text , _cg.highlightedText() );

	QSimpleRichText myrichtext( text(column), paint.font() );
	myrichtext.draw(  &paint, 0, 0, paint.window(), _cg );

	paint.end();
	p->drawPixmap( 0, 0, back );
}