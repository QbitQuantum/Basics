void VCompDialog::browseButton( WWindow* )
{
    WWindow *old = WWindow::hasFocus();
//    NYI - let the user enter lists of targets to add
//    WFileNameList     fn_list;
//    if( _browseDialog->getOpenFileName( fn_list, "", "Enter target filename", WFOpenNew ) ) {
//      WFileName fn( fn_list.cString( 0, -1 ) );
    WFileName fn;
    fn = _browseDialog->getOpenFileName( NULL, "Enter target filename",
                                         WFOpenNew );
        if( fn.size() > 0 ) {
            WFileName cwd; cwd.getCWD( TRUE );
            int len = cwd.size();
            if( len > 0 ) {
                if( strnicmp( cwd, fn, len ) == 0 ) {
                    fn.chop( len );
                }
            }
            _eName->setText( fn );
        }
    old->setFocus();
}