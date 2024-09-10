void
wField::on_selected( qulonglong uid )
{
	setValue( QString::number( uid ) );
	setFocus();
}