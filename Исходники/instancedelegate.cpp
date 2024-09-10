void ListViewDelegate::paint ( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
	QStyleOptionViewItemV4 opt = option;
	initStyleOption ( &opt, index );
	painter->save();
	painter->setClipRect ( opt.rect );

	opt.features |= QStyleOptionViewItem::WrapText;
	opt.text = index.data().toString();
	opt.textElideMode = Qt::ElideRight;
	opt.displayAlignment = Qt::AlignTop | Qt::AlignHCenter;

	QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();

	//const int iconSize =  style->pixelMetric(QStyle::PM_IconViewIconSize);
	const int iconSize = 48;
	QRect iconbox = opt.rect;
	const int textMargin = style->pixelMetric ( QStyle::PM_FocusFrameHMargin, 0, opt.widget ) + 1;
	QRect textRect = opt.rect;
	QRect textHighlightRect = textRect;
	// clip the decoration on top, remove width padding
	textRect.adjust ( textMargin,iconSize + textMargin + 5,-textMargin,0 );
	
	textHighlightRect.adjust ( 0,iconSize + 5,0,0 );

	// draw background
	{
		QSize textSize = viewItemTextSize ( &opt );
		QPalette::ColorGroup cg;
		QStyleOptionViewItemV4 opt2(opt);
		
		if((opt.widget && opt.widget->isEnabled()) || (opt.state & QStyle::State_Enabled))
		{
			if(! ( opt.state & QStyle::State_Active ))
				cg = QPalette::Inactive;
			else
				cg = QPalette::Normal;
		}
		else
		{
			cg = QPalette::Disabled;
		}
		opt2.palette.setCurrentColorGroup(cg);
		
		// fill in background, if any
		if ( opt.backgroundBrush.style() != Qt::NoBrush )
		{
			QPointF oldBO = painter->brushOrigin();
			painter->setBrushOrigin ( opt.rect.topLeft() );
			painter->fillRect ( opt.rect, opt.backgroundBrush );
			painter->setBrushOrigin ( oldBO );
		}
		
		if ( opt.showDecorationSelected )
		{
			drawSelectionRect(painter,opt2, opt.rect);
			drawFocusRect(painter,opt2, opt.rect);
			//painter->fillRect ( opt.rect, opt.palette.brush ( cg, QPalette::Highlight ) );
		}
		else
		{
			
			//if ( opt.state & QStyle::State_Selected )
			{
				//QRect textRect = subElementRect ( QStyle::SE_ItemViewItemText,  opt, opt.widget );
				//painter->fillRect ( textHighlightRect, opt.palette.brush ( cg, QPalette::Highlight ) );
				drawSelectionRect(painter,opt2, textHighlightRect);
				drawFocusRect(painter,opt2, textHighlightRect);
			}
		}
	}

	// draw the icon
	{
		QIcon::Mode mode = QIcon::Normal;
		if ( ! ( opt.state & QStyle::State_Enabled ) )
			mode = QIcon::Disabled;
		else if ( opt.state & QStyle::State_Selected )
			mode = QIcon::Selected;
		QIcon::State state = opt.state & QStyle::State_Open ? QIcon::On : QIcon::Off;

		iconbox.setHeight ( iconSize );
		opt.icon.paint ( painter, iconbox, Qt::AlignCenter, mode, state );
	}
	// set the text colors
	QPalette::ColorGroup cg = opt.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
	if ( cg == QPalette::Normal && ! ( opt.state & QStyle::State_Active ) )
		cg = QPalette::Inactive;
	if ( opt.state & QStyle::State_Selected )
	{
		painter->setPen ( opt.palette.color ( cg, QPalette::HighlightedText ) );
	}
	else
	{
		painter->setPen ( opt.palette.color ( cg, QPalette::Text ) );
	}

	// draw the text
	QTextOption textOption;
	textOption.setWrapMode ( QTextOption::WrapAtWordBoundaryOrAnywhere );
	textOption.setTextDirection ( opt.direction );
	textOption.setAlignment ( QStyle::visualAlignment ( opt.direction, opt.displayAlignment ) );
	QTextLayout textLayout;
	textLayout.setTextOption ( textOption );
	textLayout.setFont ( opt.font );
	textLayout.setText ( opt.text );

	qreal width, height;
	viewItemTextLayout ( textLayout, iconbox.width(), height, width );

	const int lineCount = textLayout.lineCount();

	const QRect layoutRect = QStyle::alignedRect ( opt.direction, opt.displayAlignment, QSize ( iconbox.width(), int ( height ) ), textRect );
	const QPointF position = layoutRect.topLeft();
	for ( int i = 0; i < lineCount; ++i )
	{
		const QTextLine line = textLayout.lineAt ( i );
		line.draw ( painter, position );
	}

	painter->restore();
}