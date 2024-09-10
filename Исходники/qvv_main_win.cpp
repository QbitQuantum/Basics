void QvvMainWindow::loadDir( QString path )
{
    QString last_path = cdir.absolutePath();

    cdir.cd( path );

    QString new_path = cdir.absolutePath();

    setWindowTitle( QString() + " QVV " + QVV_VERSION + ": " + new_path );

    QString save_item_name;
    if( tree->topLevelItemCount() > 0 ) save_item_name = tree->currentItem()->text( 1 );

    QStringList filters;
    filters.append( QString( "*" ) );

    QFileInfoList info_list = cdir.entryInfoList( filters );

    QTreeWidgetItem *current = NULL;

    tree->clear();
    for( int i = 0; i < info_list.count(); i++ )
    {
        QFileInfo fi = info_list.at( i );

        if( opt_dirs_only && ! fi.isDir() ) continue;

        if( fi.fileName() == "."  ) continue;
        if( fi.fileName() == ".." ) continue;

        QString ext = "." + fi.suffix() + ".";
        if( ! fi.isDir() && extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;

        QString file_name = fi.fileName();

        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText( 0, fi.isDir() ? ITEM_TYPE_DIR : "" );
        item->setText( 1, file_name );
        item->setText( 2, QVariant( fi.size() ).toString() );
        item->setText( 3, fi.lastModified().toString( "yyyy-MM-dd hh:mm:ss" ) );
        item->setTextAlignment( 2, Qt::AlignRight );

        if( last_path == new_path + "/" + file_name ) current = item;

        tree->addTopLevelItem( item );
    }

    if( current )
        tree->setCurrentItem( current );
    else
    {
        tree->setCurrentItem( tree->topLevelItem( 0 ) );
        if( save_item_name != "" )
            tree->findNext( save_item_name );
    }

    statusBar()->showMessage( QString( tr( "Loaded items" ) ) + ": " + QVariant( tree->topLevelItemCount() ).toString() );

    if( opt_thumbs )
        loadThumbs();

    tree->resizeColumnToContents( 2 );
    tree->resizeColumnToContents( 3 );
};