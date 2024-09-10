void LayoutCellPane::AdjustSize( int & nSizeLeft, int & nTotalWeight ) {

	RECT rc;
	this->getClientRect( rc );

	int nNewTotalWeight = 0;
	int nNewSizeLeft = nSizeLeft;

	VectorOfNodePtrs::iterator itStart = this->m_vpCells.begin( );
	VectorOfNodePtrs::iterator itEnd = this->m_vpCells.end( );

	while ( itStart != itEnd ) {

		LayoutCell * pChild = (*itStart).first;
		int nWeight = (*itStart).second;

		// don't put extra width/height on items of zero weight
		if ( nWeight == 0 || pChild->isVisible( ) == FALSE ) {

			itStart++;
			continue;
		}

		int nAddSize = nSizeLeft * nWeight / nTotalWeight;

		RECT rectNew, rectOld;

		pChild->getRect( rectOld );
		rectNew = rectOld;

		if ( m_nType == HORZ ) {

			rectNew.right += nAddSize;
			pChild->setRect( rectNew );
			pChild->getRect( rectNew );

			if ( rectOld.right != rectNew.right ) {

				nNewSizeLeft -= rectNew.right - rectOld.right;

				CellMinMaxInfo cmmiChild;

				cmmiChild.m_MinSize.x = 0;
				cmmiChild.m_MinSize.y = 0;
				cmmiChild.m_MaxSize.x = rc.right - rc.left;
				cmmiChild.m_MaxSize.y = rc.bottom - rc.top;

				pChild->getMinMaxInfo( &cmmiChild );

				if ( rectNew.right - rectNew.left != cmmiChild.m_MaxSize.x )
					nNewTotalWeight += nWeight;
			}
		}
		else {

			rectNew.bottom += nAddSize;
			pChild->setRect( rectNew );
			pChild->getRect( rectNew );

			if ( rectOld.bottom != rectNew.bottom ) {

				nNewSizeLeft -= rectNew.bottom - rectOld.bottom;

				CellMinMaxInfo cmmiChild;

				cmmiChild.m_MinSize.x = 0;
				cmmiChild.m_MinSize.y = 0;
				cmmiChild.m_MaxSize.x = rc.right - rc.left;
				cmmiChild.m_MaxSize.y = rc.bottom - rc.top;

				pChild->getMinMaxInfo( &cmmiChild );

				if ( rectNew.bottom - rectNew.top != cmmiChild.m_MaxSize.y )
					nNewTotalWeight += nWeight;
			}
		}

		itStart++;
	}

	nTotalWeight = nNewTotalWeight;
	nSizeLeft = nNewSizeLeft;
}