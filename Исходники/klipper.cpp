void Klipper::slotEditData()
{
    const HistoryStringItem* item = dynamic_cast<const HistoryStringItem*>(m_history->first());

    KDialog dlg;
    dlg.setModal( true );
    dlg.setCaption( i18n("Edit Contents") );
    dlg.setButtons( KDialog::Ok | KDialog::Cancel );

    KTextEdit *edit = new KTextEdit( &dlg );
    if (item) {
        edit->setText( item->text() );
    }
    edit->setFocus();
    edit->setMinimumSize( 300, 40 );
    dlg.setMainWidget( edit );
    dlg.adjustSize();

    if ( dlg.exec() == KDialog::Accepted ) {
        QString text = edit->toPlainText();
        if (item) {
            m_history->remove( item );
        }
        m_history->insert( new HistoryStringItem(text) );
        if (m_myURLGrabber) {
            m_myURLGrabber->checkNewData( m_history->first() );
        }
    }

}