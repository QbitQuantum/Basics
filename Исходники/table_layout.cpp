void AutoTableLayout::layout()
{
    // table layout based on the values collected in the layout structure.
    int tableWidth = table->width() - table->bordersAndSpacing();
    int available = tableWidth;
    int nEffCols = table->numEffCols();

    if ( nEffCols != (int)layoutStruct.size() ) {
	qWarning("WARNING: nEffCols is not equal to layoutstruct!" );
	fullRecalc();
	nEffCols = table->numEffCols();
    }
#ifdef DEBUG_LAYOUT
    qDebug("AutoTableLayout::layout()");
#endif

    if ( effWidthDirty )
	calcEffectiveWidth();

#ifdef DEBUG_LAYOUT
    qDebug("    tableWidth=%d,  nEffCols=%d", tableWidth,  nEffCols );
    for ( int i = 0; i < nEffCols; i++ ) {
	qDebug("    effcol %d is of type %d value %d, minWidth=%d, maxWidth=%d",
	       i, layoutStruct[i].width.type, layoutStruct[i].width.value,
	       layoutStruct[i].minWidth, layoutStruct[i].maxWidth );
	qDebug("        effective: type %d value %d, minWidth=%d, maxWidth=%d",
	       layoutStruct[i].effWidth.type, layoutStruct[i].effWidth.value,
	       layoutStruct[i].effMinWidth, layoutStruct[i].effMaxWidth );
    }
#endif

    bool havePercent = false;
    bool haveRelative = false;
    int totalRelative = 0;
    int numVariable = 0;
    int numFixed = 0;
    int totalVariable = 0;
    int totalFixed = 0;
    int totalPercent = 0;
    int allocVariable = 0;

    // fill up every cell with it's minWidth
    for ( int i = 0; i < nEffCols; i++ ) {
	int w = layoutStruct[i].effMinWidth;
	layoutStruct[i].calcWidth = w;
	available -= w;
	Length& width = layoutStruct[i].effWidth;
        switch( width.type()) {
        case Percent:
	    havePercent = true;
	    totalPercent += width.value();
            break;
        case Relative:
	    haveRelative = true;
	    totalRelative += width.value();
            break;
        case Fixed:
            numFixed++;
            totalFixed += layoutStruct[i].effMaxWidth;
            // fall through
            break;
        case Variable:
        case Static:
            numVariable++;
            totalVariable += layoutStruct[i].effMaxWidth;
            allocVariable += w;
        }
    }

    // then allocate width to fixed cols
    if ( available > 0 ) {
	for ( int i = 0; i < nEffCols; ++i ) {
	    Length w = layoutStruct[i].effWidth;
	    if ( w.isFixed() && w.value() > layoutStruct[i].calcWidth ) {
		available += layoutStruct[i].calcWidth - w.value();
		layoutStruct[i].calcWidth = w.value();
            }
	}
    }
#ifdef DEBUG_LAYOUT
    qDebug("fixed satisfied: available is %d", available);
#endif

    // then allocate width to percent cols
    if ( available > 0 && havePercent ) {
	for ( int i = 0; i < nEffCols; i++ ) {
	    Length width = layoutStruct[i].effWidth;
	    if ( width.isPercent() ) {
                int w = kMax ( int( layoutStruct[i].effMinWidth ), width.minWidth( tableWidth ) );
		available += layoutStruct[i].calcWidth - w;
		layoutStruct[i].calcWidth = w;
	    }
	}
	if ( totalPercent > 100 ) {
	    // remove overallocated space from the last columns
	    int excess = tableWidth*(totalPercent-100)/100;
	    for ( int i = nEffCols-1; i >= 0; i-- ) {
		if ( layoutStruct[i].effWidth.isPercent() ) {
		    int w = layoutStruct[i].calcWidth;
		    int reduction = kMin( w,  excess );
		    // the lines below might look inconsistent, but that's the way it's handled in mozilla
		    excess -= reduction;
		    int newWidth = kMax( int (layoutStruct[i].effMinWidth), w - reduction );
		    available += w - newWidth;
		    layoutStruct[i].calcWidth = newWidth;
		    //qDebug("col %d: reducing to %d px (reduction=%d)", i, newWidth, reduction );
		}
	    }
	}
    }
#ifdef DEBUG_LAYOUT
    qDebug("percent satisfied: available is %d", available);
#endif

    // now satisfy relative
    if ( available > 0 ) {
	for ( int i = 0; i < nEffCols; i++ ) {
	    Length &width = layoutStruct[i].effWidth;
	    if ( width.isRelative() && width.value() ) {
		// width=0* gets effMinWidth.
		int w = width.value()*tableWidth/totalRelative;
		available += layoutStruct[i].calcWidth - w;
		layoutStruct[i].calcWidth = w;
	    }
	}
    }

    // now satisfy variable
    if ( available > 0 && numVariable ) {
	available += allocVariable; // this gets redistributed
 	//qDebug("redistributing %dpx to %d variable columns. totalVariable=%d",  available,  numVariable,  totalVariable );
	for ( int i = 0; i < nEffCols; i++ ) {
	    Length &width = layoutStruct[i].effWidth;
	    if ( width.isVariable() && totalVariable != 0 ) {
		int w = kMax( int ( layoutStruct[i].calcWidth ),
                              available * layoutStruct[i].effMaxWidth / totalVariable );
		available -= w;
		totalVariable -= layoutStruct[i].effMaxWidth;
		layoutStruct[i].calcWidth = w;
	    }
	}
    }
#ifdef DEBUG_LAYOUT
    qDebug("variable satisfied: available is %d",  available );
#endif

    // spread over fixed colums
    if ( available > 0 && numFixed) {
        // still have some width to spread, distribute to fixed columns
        for ( int i = 0; i < nEffCols; i++ ) {
            Length &width = layoutStruct[i].effWidth;
            if ( width.isFixed() ) {
                int w = available * layoutStruct[i].effMaxWidth / totalFixed;
                available -= w;
                totalFixed -= layoutStruct[i].effMaxWidth;
                layoutStruct[i].calcWidth += w;
            }
        }
    }

#ifdef DEBUG_LAYOUT
    qDebug("after fixed distribution: available=%d",  available );
#endif

    // spread over percent colums
    if ( available > 0 && hasPercent && totalPercent < 100) {
        // still have some width to spread, distribute weighted to percent columns
        for ( int i = 0; i < nEffCols; i++ ) {
            Length &width = layoutStruct[i].effWidth;
            if ( width.isPercent() ) {
                int w = available * width.value() / totalPercent;
                available -= w;
                totalPercent -= width.value();
                layoutStruct[i].calcWidth += w;
                if (!available || !totalPercent) break;
            }
        }
    }

#ifdef DEBUG_LAYOUT
    qDebug("after percent distribution: available=%d",  available );
#endif

    // spread over the rest
    if ( available > 0 ) {
        int total = nEffCols;
        // still have some width to spread
        int i = nEffCols;
        while (  i-- ) {
            int w = available / total;
            available -= w;
            total--;
            layoutStruct[i].calcWidth += w;
        }
    }

#ifdef DEBUG_LAYOUT
    qDebug("after equal distribution: available=%d",  available );
#endif
    // if we have overallocated, reduce every cell according to the difference between desired width and minwidth
    // this seems to produce to the pixel exaxt results with IE. Wonder is some of this also holds for width distributing.
    if ( available < 0 ) {
	int mw = 0;
	for ( int i = nEffCols-1; i >= 0; i-- )
	    mw += layoutStruct[i].calcWidth - layoutStruct[i].effMinWidth;
	for ( int i = nEffCols-1; i >= 0 && mw > 0; i-- ) {
	    int minMaxDiff = layoutStruct[i].calcWidth-layoutStruct[i].effMinWidth;
	    int reduce = available * minMaxDiff / mw;
	    layoutStruct[i].calcWidth += reduce;
	    available -= reduce;
	    mw -= minMaxDiff;
	    if ( available >= 0 )
		break;
	}
    }

    //qDebug( "    final available=%d", available );

    int pos = 0;
    for ( int i = 0; i < nEffCols; i++ ) {
#ifdef DEBUG_LAYOUT
	qDebug("col %d: %d (width %d)", i, pos, layoutStruct[i].calcWidth );
#endif
	table->columnPos[i] = pos;
	pos += layoutStruct[i].calcWidth + table->cellSpacing();
    }
    table->columnPos[table->columnPos.size()-1] = pos;

}