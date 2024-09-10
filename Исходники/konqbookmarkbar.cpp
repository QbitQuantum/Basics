// TODO    *** drop improvements ***
// open submenus on drop interactions
bool KBookmarkBar::eventFilter( QObject *, QEvent *e )
{
    if (d->m_filteredToolbar)
        return false; // todo: make this limit the actions

    if ( e->type() == QEvent::DragLeave )
    {
        removeTempSep();
    }
    else if ( e->type() == QEvent::Drop )
    {
        removeTempSep();

        QDropEvent *dev = static_cast<QDropEvent*>( e );
        QDomDocument doc;
        QList<KBookmark> list = KBookmark::List::fromMimeData( dev->mimeData(), doc );
        if ( list.isEmpty() )
            return false;
        if (list.count() > 1)
            kWarning(7043) << "Sorry, currently you can only drop one address "
                "onto the bookmark bar!";
        KBookmark toInsert = list.first();

        KBookmarkGroup parentBookmark = getToolbar();

        if(d->m_sepIndex == 0)
        {
            KBookmark newBookmark = parentBookmark.addBookmark(toInsert.fullText(), toInsert.url() );

            parentBookmark.moveBookmark( newBookmark, KBookmark() );
            m_pManager->emitChanged( parentBookmark );
            return true;
        }
        else
        {
            KBookmark after = parentBookmark.first();

            for(int i=0; i < d->m_sepIndex - 1 ; ++i)
                after = parentBookmark.next(after);
            KBookmark newBookmark = parentBookmark.addBookmark(toInsert.fullText(), toInsert.url() );

            parentBookmark.moveBookmark( newBookmark, after );
            m_pManager->emitChanged( parentBookmark );
            return true;
        }
    }
    else if ( e->type() == QEvent::DragMove || e->type() == QEvent::DragEnter )
    {
        QDragMoveEvent *dme = static_cast<QDragMoveEvent*>( e );
        if (!KBookmark::List::canDecode( dme->mimeData() ))
            return false;

        //cache text, save positions (inserting the temporary widget changes the positions)
        if(e->type() == QEvent::DragEnter)
        {
            QDomDocument doc;
            const QList<KBookmark> list = KBookmark::List::fromMimeData( dme->mimeData(), doc );
            if ( list.isEmpty() )
                return false;
            d->tempLabel  = list.first().url().pathOrUrl();

            d->widgetPositions.clear();

            for (int i = 0; i < m_toolBar->actions().count(); ++i)
                if (QWidget* button = m_toolBar->widgetForAction(m_toolBar->actions()[i])) {
                    if(m_toolBar->orientation() == Qt::Horizontal) {
                        if(QApplication::isLeftToRight()) {
                            d->widgetPositions.push_back(button->geometry().right());
                        } else {
                            d->widgetPositions.push_back(button->geometry().left());
                        }
                    } else {
                        d->widgetPositions.push_back(button->geometry().bottom());
                    }
                }
        }

        bool accept = handleToolbarDragMoveEvent(dme->pos(), d->m_actions, d->tempLabel);
        if (accept)
        {
            dme->accept();
            return true; //Really?
        }
    }
    return false;
}