void Cmap_button::delete_attempt()
{
    QMessageBox msg;
    msg.setText( tr( "Are you really sure that you want to delete " )
                 + this->text + tr( " ?" ) );
    msg.addButton( tr( "Delete" ), QMessageBox::AcceptRole );
    msg.addButton( tr( "Cancel" ), QMessageBox::RejectRole );
    if ( msg.exec() == QDialog::Rejected )
    {
        //remove map files
        QFile f;
        f.remove( this->absolute_map_path );
        f.remove( this->absolute_map_path + ".preview" );
    }

    QTimer::singleShot( 500, this, SIGNAL(please_refresh_as_we_deleted_something()) );
}