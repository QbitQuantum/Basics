void VEditDlg::browseButton( WWindow* ) {
    WWindow *old;
    WFileName fn;

    old = WWindow::hasFocus();
    fn = _browseDialog->getOpenFileName( NULL, "Enter target filename", WFOpenExisting );
    if( fn.size() > 0 ) {
        fn.setExt( "" );
        _editorName->setText( fn );
    }
    old->setFocus();
}