void WEXPORT WInputDialog::browseButton( WWindow* ) {
/***************************************************/

    WFileName   fn;

    WWindow *old = WWindow::hasFocus();
    if( _multiSelect ) {
        WFileNameList   fn_list;
        _browseDialog->getOpenFileName( fn_list, "", "Pick filename", WFOpenNew );
        fn = fn_list.cString( 0, -1 );
    } else {
        fn = _browseDialog->getOpenFileName( "", "Pick filename", WFOpenNew );
    }
    if( fn.size() > 0 ) {
        _input->setText( fn );
    }
    old->setFocus();
}