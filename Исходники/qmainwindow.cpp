void QMainWindow::moveToolBar( QToolBar * t , QMouseEvent * e )
{
    if ( e->type() == Event_MouseButtonPress ) {
	//debug( "saw press" );
	d->moving = 0;
	d->offset = e->pos();
	d->pos = QCursor::pos();
	return;
    } else if ( e->type() == Event_MouseButtonRelease ) {
	//debug( "saw release" );
	if ( d->moving ) {
	    qApp->removeEventFilter( this );
	    d->moving = 0;
	}
	return;
    }

    //debug( "saw move" );

    // with that out of the way, let's concentrate on the moves...

    // first, the threshold

    QPoint p( QCursor::pos() );
    if ( !d->moving &&
	 QABS( p.x() - d->pos.x() ) < 3 &&
	 QABS( p.y() - d->pos.y() ) < 3 )
	return;

    // okay.  it's a real move.

    //    debug( "move event to %d, %d", p.x(), p.y() );

    if ( !d->moving ) {
	d->moving = t;
	qApp->installEventFilter( this );
    }

    QPoint lp( mapFromGlobal( p ) );
    QMainWindowPrivate::ToolBarDock * dock = 0;
    // five possible cases: in each of the docs, and outside.
    if ( centralWidget()->geometry().contains( lp ) ||
	 !rect().contains( lp ) ) {
	// not a dock
	if ( t->parentWidget() ) {
	    t->recreate( 0, 0,
			 QPoint( p.x() - d->offset.x(),
				 p.y() - d->offset.y() ),
			 TRUE );
	    QApplication::syncX();
	    dock = d->tornOff;
	} else {
	    t->move( p.x() - d->offset.x(),
		     p.y() - d->offset.y() );
	}
    } else if ( lp.y() < centralWidget()->y() ) {
	//top dock
	dock = d->top;
    } else if ( lp.y() >= centralWidget()->y() + centralWidget()->height() ) {
	// bottom dock
	dock = d->bottom;
    } else if ( lp.x() < centralWidget()->x() ) {
	// bottom dock
	dock = d->left;
    } else if ( lp.x() >= centralWidget()->x() + centralWidget()->width() ) {
	// right dock
	dock = d->right;
    } else {
	fatal( "never to happen" );
    }

    if ( !dock )
	return;

    debug( "1" );
    // at this point dock points to the new dock
    QMainWindowPrivate::ToolBar * ct;
    ct = takeToolBarFromDock( t, d->top );
    if ( !ct )
	ct = takeToolBarFromDock( t, d->left );
    if ( !ct )
	ct = takeToolBarFromDock( t, d->right );
    if ( !ct )
	ct = takeToolBarFromDock( t, d->bottom );
    if ( dock != d->tornOff && !ct )
	ct = takeToolBarFromDock( t, d->tornOff );
    if ( dock == d->tornOff || ct == 0 )
	return;

    debug( "2" );
    QMainWindowPrivate::ToolBar * c = dock->first();
    QRect inLine;
    QRect betweenLines;
    int linestart = 0;
    while( c && ct ) {
	debug( "3 %p %p", c, ct );
	if ( c->nl ) {
	    if ( dock == d->top ) {
		betweenLines.setRect( 0, 0, width(),
				      c->t->y() + c->t->height()/4 );
	    } else if ( dock == d->bottom ) {
		betweenLines.setRect( 0, c->t->y() + c->t->height()/4,
				      width(), c->t->height()/2 );
	    } else if ( dock == d->left ) {
		betweenLines.setRect( 0, 0, c->t->x() + c->t->width()/4,
				      height() );
	    } else {
		betweenLines.setRect( c->t->x() + 3*c->t->width()/4, 0,
				      c->t->width()/2, height() );
	    }
	    linestart = dock->at();
	}
	if ( dock == d->top || dock == d->bottom ) {
	    inLine.setRect( c->t->x()-c->t->height()/4, c->t->y(),
			    c->t->height()/2, c->t->height() );
	} else {
	    inLine.setRect( c->t->x(), c->t->y() - c->t->width()/4,
			    c->t->width(), c->t->width()/2 );
	}
	if ( inLine.contains( lp ) ) {
	    // ct goes in just before c, and takes over nl
	    dock->insert( dock->at(), ct );
	    if ( t->parentWidget() != this )
		t->recreate( this, 0, QPoint( 0, -t->height() ), TRUE );
	    t->setOrientation( (dock == d->top || dock == d->bottom )
			       ? QToolBar::Horizontal : QToolBar::Vertical );
	    ct->nl = c->nl;
	    c->nl = FALSE;
	    ct = 0;
	    triggerLayout();
	} else {
	    QMainWindowPrivate::ToolBar * c2 = dock->next();
	    if ( c2 == 0 || c2->nl ) {
		// about to do the next line, so check whether c
		// should go in above this line
		if ( betweenLines.contains( lp ) ) {
		    dock->insert( linestart, ct );
		    if ( t->parentWidget() != this )
			t->recreate( this, 0, QPoint( 0, -t->height() ),
				     TRUE );
		    t->setOrientation( (dock == d->top || dock == d->bottom )
				       ? QToolBar::Horizontal
				       : QToolBar::Vertical );
		    ct->nl = TRUE;
		    ct = 0;
			triggerLayout();
		} else {
		    // perhaps at the end of this line?  let's see
		    if ( dock == d->top || dock == d->bottom )
			inLine.setRect( c->t->x() + c->t->width(),
					c->t->y(),
					width() - c->t->x() - c->t->width(),
					c->t->height() );
		    else
			inLine.setRect( c->t->x(),
					c->t->y() + c->t->height(),
					c->t->width(),
					height() - c->t->y() - c->t->height());
		    if ( inLine.contains( lp ) ) {
			dock->insert( dock->at(), ct );
			if ( t->parentWidget() != this )
			    t->recreate( this, 0, QPoint( 0, -t->height() ),
					 TRUE );
			t->setOrientation( (dock == d->top ||
					    dock == d->bottom )
					   ? QToolBar::Horizontal
					   : QToolBar::Vertical );
			ct->nl = FALSE;
			ct = 0;
			triggerLayout();
		    }
		}
	    }
	    c = c2;
	}
    }
    debug( "4" );
    // okay, is it at the very end?
    if ( ct ) {
	debug( "4a" );
	dock->append( ct );
	if ( t->parentWidget() != this )
	    t->recreate( this, 0, QPoint( 0, -t->height() ), TRUE );
	t->setOrientation( (dock == d->top || dock == d->bottom )
			   ? QToolBar::Horizontal : QToolBar::Vertical );
	ct->nl = TRUE;
	triggerLayout();
    }
}