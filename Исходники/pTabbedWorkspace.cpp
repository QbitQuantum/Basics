void pTabbedWorkspace::setTabShape( QTabBar::Shape s )
{
	if ( tabShape() != s )
	{
		// get sizepolicy
		QSizePolicy sp = mTabBar->sizePolicy();
		
		// update view layout
		switch ( s )
		{
		case QTabBar::RoundedNorth:
		case QTabBar::TriangularNorth:
			mTabLayout->setDirection( QBoxLayout::LeftToRight );
			mLayout->setDirection( QBoxLayout::TopToBottom );
			if ( tabShape() != QTabBar::RoundedSouth && tabShape() != QTabBar::TriangularSouth )
				sp.transpose();
			break;
		case QTabBar::RoundedSouth:
		case QTabBar::TriangularSouth:
			mTabLayout->setDirection( QBoxLayout::LeftToRight );
			mLayout->setDirection( QBoxLayout::BottomToTop );
			if ( tabShape() != QTabBar::RoundedNorth && tabShape() != QTabBar::TriangularNorth )
				sp.transpose();
			break;
		case QTabBar::RoundedWest:
		case QTabBar::TriangularWest:
			mTabLayout->setDirection( QBoxLayout::BottomToTop );
			mLayout->setDirection( QBoxLayout::LeftToRight );
			if ( tabShape() != QTabBar::RoundedEast && tabShape() != QTabBar::TriangularEast )
				sp.transpose();
			break;
		case QTabBar::RoundedEast:
		case QTabBar::TriangularEast:
			mTabLayout->setDirection( QBoxLayout::TopToBottom );
			mLayout->setDirection( QBoxLayout::RightToLeft );
			if ( tabShape() != QTabBar::RoundedWest && tabShape() != QTabBar::TriangularWest )
				sp.transpose();
			break;
		}
		
		// set size policy
		mTabBar->setSizePolicy( sp );
		
		// apply tab shape
		mTabBar->setShape( s );
		
		// update corners
		updateCorners();
		
		// emit shape changed
		emit tabShapeChanged( s );
	}
}