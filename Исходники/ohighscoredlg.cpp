QString OHighscore::getName()
{
	QString name;
	QDialog *d = new QDialog ( this, 0, true );
	d->setCaption( tr( "Enter your name!" ));
	QLineEdit *ed = new QLineEdit ( d );
	( new QVBoxLayout ( d, 3, 3 ))->addWidget ( ed );
	ed->setFocus ( );

    if ( d->exec() == QDialog::Accepted ) {
        name = ed->text();
    }
    //delete d;
	return name;
}