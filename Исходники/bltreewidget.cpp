/**
\return
**/
void BlTreeWidget::contextMenuEvent ( QContextMenuEvent * )
{
    BL_FUNC_DEBUG

    int column = currentColumn();
    
    if ( column < 0 ) return;

    QMenu *menu = new QMenu ( this );

    /// Lanzamos el evento para que pueda ser capturado por terceros.
    emit pintaMenu ( menu );

    /// Lanzamos la propagaci&oacute;n del men&uacute; a trav&eacute;s de las clases derivadas.
    createMenu ( menu );

    QAction *adjustColumnSize = menu->addAction ( _ ( "Ajustar columa" ) );
    QAction *adjustAllColumnsSize = menu->addAction ( _ ( "Ajustar columnas" ) );
    QAction *menuOption = menu->exec ( QCursor::pos() );

    /// Si no hay ninguna opci&oacute;n pulsada se sale sin hacer nada.
    if ( !menuOption ) return;

    if ( menuOption == adjustAllColumnsSize ) {

	for (int i = 0; i < columnCount(); i++) {
	    resizeColumnToContents (i);
	} // end for
	
    } else if ( menuOption == adjustColumnSize )  {
        resizeColumnToContents ( column );
    } // end if

    emit trataMenu ( menuOption );

    /// Activamos las herederas.
    execMenuAction ( menuOption );

    delete menu;
}