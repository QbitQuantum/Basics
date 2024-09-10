	void M11TabBar::paintEvent(QPaintEvent*)
	{
		QStyleOptionTab tabOverlap;
		tabOverlap.shape = shape();
		int overlap = style()->pixelMetric(QStyle::PM_TabBarBaseOverlap, &tabOverlap, this);
		QWidget *theParent = parentWidget();
		QStyleOptionTabBarBase optTabBase;
		optTabBase.init(this);
		optTabBase.shape = shape();
		if (theParent && overlap > 0) {
			QRect rect;
			switch (tabOverlap.shape) {
			case M11TabBar::RoundedNorth:
			case M11TabBar::TriangularNorth:
				rect.setRect(0, height() - overlap, width(), overlap);
				break;
			case M11TabBar::RoundedSouth:
			case M11TabBar::TriangularSouth:
				rect.setRect(0, 0, width(), overlap);
				break;
			case M11TabBar::RoundedEast:
			case M11TabBar::TriangularEast:
				rect.setRect(0, 0, overlap, height());
				break;
			case M11TabBar::RoundedWest:
			case M11TabBar::TriangularWest:
				rect.setRect(width() - overlap, 0, overlap, height());
				break;
			}
			optTabBase.rect = rect;
		}

		QStylePainter p(this);
		p.fillRect(rect(), Utils::instance().gradientTopToBottom(rect()));
		QPen pen = p.pen();

		int selected = -1;
		int cut = -1;
		bool rtl = optTabBase.direction == Qt::RightToLeft;
		bool verticalTabs = (shape() == M11TabBar::RoundedWest || shape() == M11TabBar::RoundedEast
		                     || shape() == M11TabBar::TriangularWest
		                     || shape() == M11TabBar::TriangularEast);
		QStyleOptionTab cutTab;
		QStyleOptionTab selectedTab;
		for (int i = 0; i < count(); ++i) {
			QStyleOptionTabV2 tab = getStyleOption(i);
			if (!(tab.state & QStyle::State_Enabled)) {
				tab.palette.setCurrentColorGroup(QPalette::Disabled);
			}
			// If this tab is partially obscured, make a note of it so that we can pass the information
			// along when we draw the tear.
			if ((!verticalTabs && (!rtl && tab.rect.left() < 0) ||
			     (rtl && tab.rect.right() > width())) ||
			    (verticalTabs && tab.rect.top() < 0)) {
				cut = i;
				cutTab = tab;
			}
			// Don't bother drawing a tab if the entire tab is outside of the visible tab bar.
			if ((!verticalTabs && (tab.rect.right() < 0 || tab.rect.left() > width()))
			    || (verticalTabs && (tab.rect.bottom() < 0 || tab.rect.top() > height())))
				continue;

			optTabBase.tabBarRect |= tab.rect;
			if (i == currentIndex()) {
				selected = i;
				selectedTab = tab;
				optTabBase.selectedTabRect = tab.rect;
			}

			QIcon icon = tabIcon(i);
			QSize iconSize = icon.actualSize(QSize(tab.rect.height(), tab.rect.height()));
			int iconMargin = (tab.rect.height() - iconSize.height()) / 2;
			QRect iconRect(tab.rect.left() + iconMargin, tab.rect.top(), iconSize.width(), tab.rect.height());
			QString text = tabText(i);
			QRect textRect(
			    tab.rect.left() + iconMargin + iconSize.width(),
			    tab.rect.top(),
			    tab.rect.width() - iconSize.width(),
			    tab.rect.height()
			);

			p.fillRect(
			    tab.rect,
			    i == currentIndex() ?
			    Utils::instance().palette().base() :
			    tab.rect.contains(mapFromGlobal(QCursor::pos())) ?
			    Utils::instance().palette().light() : Utils::instance().gradientTopToBottom(tab.rect)
			);

			p.setPen(Utils::instance().palette().dark().color());

			switch (shape()) { // override the widget's border to make it consistent over inactive tabs
			case M11TabBar::RoundedNorth:
			case M11TabBar::TriangularNorth:
				if (i == currentIndex()) {
					p.drawRect(tab.rect.adjusted(0, 0, -1, 0));
				}
				else {
					p.drawLine(tab.rect.bottomLeft(), tab.rect.bottomRight());
				}
				break;
			case M11TabBar::RoundedSouth:
			case M11TabBar::TriangularSouth:
				if (i == currentIndex()) {
					p.drawRect(tab.rect.adjusted(0, -1, -1, -1));
				}
				else {
					p.drawLine(tab.rect.topLeft(), tab.rect.topRight());
				}
				break;
			case M11TabBar::RoundedEast:
			case M11TabBar::TriangularEast:
				if (i == currentIndex()) {
					p.drawRect(tab.rect.adjusted(-1, 0, -1, -1));
				}
				else {
					p.drawLine(tab.rect.topLeft(), tab.rect.bottomLeft());
				}
				break;
			case M11TabBar::RoundedWest:
			case M11TabBar::TriangularWest:
				if (i == currentIndex()) {
					p.drawRect(tab.rect.adjusted(0, 0, 0, -1));
				}
				else {
					p.drawLine(tab.rect.topRight(), tab.rect.bottomRight());
				}
				break;
			default:
				Q_ASSERT(false);
				break;
			}

			p.setPen(m_tabLabelColors.contains(i) ? m_tabLabelColors.value(i).color() : pen);

			QString textToDraw = fontMetrics().elidedText(
			                         text,
			                         elideMode(),
			                         1 + (
			                             verticalTabs ? tabRect(i).height() : tabRect(i).width()
			                         ) - style()->pixelMetric(QStyle::PM_TabBarTabHSpace, &tab, this),
			                         Qt::TextShowMnemonic
			                     );

			p.drawItemPixmap(iconRect, Qt::AlignCenter, icon.pixmap(iconSize));

			p.drawItemText(
			    textRect,
			    Qt::AlignLeft | Qt::AlignVCenter,
			    QPalette(),
			    tab.state & QStyle::State_Enabled,
			    textToDraw
			);

			p.setPen(pen);
		}

		if (!drawBase()) {
			p.setBackgroundMode(Qt::TransparentMode);
		}
		else {
			// p.drawPrimitive(QStyle::PE_FrameTabBarBase, optTabBase);
		}

		// Only draw the tear indicator if necessary. Most of the time we don't need too.
		if (cut >= 0) {
			cutTab.rect = rect();
			cutTab.rect = style()->subElementRect(QStyle::SE_TabBarTearIndicator, &cutTab, this);
			p.drawPrimitive(QStyle::PE_IndicatorTabTear, cutTab);
		}

		// p.setPen(Qt::black);
		// p.drawRect(rect());
	}