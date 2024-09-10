void Gui::mouseMove( int x, int y, MouseButtons mb )
{
//  cout << "Ui::Gui::mouseMove(  )"  << endl;

	if ( pChannelPopup != NULL ) {
		pChannelPopup->mouseMove( x, y, mb );
		if ( pChannelPopup != NULL ) {
			if ( !pChannelPopup->passEvents() )
				return;
		}
	}

  if ( pMouseChannelWidget != NULL ) {

		Widget* o =  pMouseChannelWidget->mouseMove( x - pMouseChannelWidget->absoluteXPos(), y - pMouseChannelWidget->absoluteYPos(), mb );

    if ( pLastMouseOver != o ) {

      if ( (pLastMouseOver == pMouseChannelWidget) || (o == pMouseChannelWidget) ) {
        if ( o == pMouseChannelWidget ) {
          pMouseChannelWidget->mouseIn( mb );
        } else {
          pMouseChannelWidget->mouseOut( mb );
          pMouseChannelWidget->onDestroy.disconnect( this );
        }
      } else {
        pLastMouseOver->onDestroy.disconnect( this );
      }
      pLastMouseOver = o;
      pLastMouseOver->onDestroy.connect( this, &Gui::objectDestroyed );

    }

  } else {

    for( int i = 0; i < pPopups.count(); i++ ) {
      Popup* p = pPopups.get( i );
      Rect r = p->getRect();
      if ( r.pointInside( x, y ) ) {
        p->mouseMove( x, y, mb );
				if ( !p->passEvents() )
					return;
      }
    }

    Widget* o = fgFrame().mouseMove( x, y, mb );

    if ( o != NULL ) {
      if ( o != pLastMouseOver ) {

        if ( pLastMouseOver != NULL ) {
          pLastMouseOver->onDestroy.disconnect( this );
          pLastMouseOver->mouseOut( mb );
          pLastMouseOver = NULL;
        }

//        if ( o != &frame )
        o->mouseIn( mb );

        pLastMouseOver = o;
        pLastMouseOver->onDestroy.connect( this, &Gui::objectDestroyed );

      }
      //o->mouseMove( x, y, mb );

    } else {
      pLastMouseOver->onDestroy.disconnect( this );
      pLastMouseOver = NULL;
    }

  }
	if ( pMouseDragWidget != NULL ) {
		if ( ( Utils::max(x, pPressedX) - Utils::min(x, pPressedX) > 5 ) || ( Utils::max(y, pPressedY) - Utils::min(y, pPressedY) > 5 ) ) {
			DragObject* d = NULL;
			pMouseDragWidget->onDrag( pMouseDragWidget, x - pMouseDragWidget->absoluteXPos(), y - pMouseDragWidget->absoluteYPos(), &d );
			if ( d != NULL ) {
				pMouseDragWidget->mouseReleased( x - pMouseDragWidget->absoluteXPos(), y - pMouseDragWidget->absoluteYPos(), mb );
				d->popup( x - (d->width() / 2), y - (d->height() / 2), *this );
				if ( mouseChannelWidget() != NULL )
					unsetMouseChannelWidget( *mouseChannelWidget() );

				d->mousePressed( x, y, mb );
			}
			pMouseDragWidget->onDestroy.disconnect( this );
			pMouseDragWidget = NULL;
		}
	}
}