UserMenuRefData::UserMenuRefData
(
	QWidget* parent,
	const char* name
)
	:
	Inherited( parent, name, 241664 )
{
	MenuName = new("QLineEdit") QLineEdit( this, "LineEdit_1" );
	MenuName->setGeometry( 280, 40, 100, 30 );
	MenuName->setMinimumSize( 10, 10 );
	MenuName->setMaximumSize( 32767, 32767 );
	MenuName->setText( "" );
	MenuName->setMaxLength( 32767 );
	MenuName->setEchoMode( QLineEdit::Normal );
	MenuName->setFrame( TRUE );

	MenuCommand = new("QLineEdit") QLineEdit( this, "LineEdit_2" );
	MenuCommand->setGeometry( 280, 120, 100, 30 );
	MenuCommand->setMinimumSize( 100, 30 );
	MenuCommand->setMaximumSize( 100, 30 );
	MenuCommand->setText( "" );
	MenuCommand->setMaxLength( 32767 );
	MenuCommand->setEchoMode( QLineEdit::Normal );
	MenuCommand->setFrame( TRUE );

	MenuType = new("QComboBox") QComboBox( FALSE, this, "ComboBox_1" );
	MenuType->setGeometry( 280, 80, 100, 30 );
	MenuType->setMinimumSize( 10, 10 );
	MenuType->setMaximumSize( 32767, 32767 );
	connect( MenuType, SIGNAL(highlighted(int)), SLOT(typeSetActive(int)) );
	MenuType->setSizeLimit( 2 );
	MenuType->setAutoResize( FALSE );
	MenuType->insertItem( "Seperator" );
	MenuType->insertItem( "Action" );

	QLabel* dlgedit_Label_1;
	dlgedit_Label_1 = new("QLabel") QLabel( this, "Label_1" );
	dlgedit_Label_1->setGeometry( 170, 40, 100, 30 );
	dlgedit_Label_1->setMinimumSize( 10, 10 );
	dlgedit_Label_1->setMaximumSize( 32767, 32767 );
	dlgedit_Label_1->setText( i18n("Menu Name") );
	dlgedit_Label_1->setAlignment( 290 );
	dlgedit_Label_1->setMargin( -1 );

	QLabel* dlgedit_Label_2;
	dlgedit_Label_2 = new("QLabel") QLabel( this, "Label_2" );
	dlgedit_Label_2->setGeometry( 170, 80, 100, 30 );
	dlgedit_Label_2->setMinimumSize( 10, 10 );
	dlgedit_Label_2->setMaximumSize( 32767, 32767 );
	dlgedit_Label_2->setText( i18n("Type") );
	dlgedit_Label_2->setAlignment( 290 );
	dlgedit_Label_2->setMargin( -1 );

	QLabel* dlgedit_Label_3;
	dlgedit_Label_3 = new("QLabel") QLabel( this, "Label_3" );
	dlgedit_Label_3->setGeometry( 180, 120, 90, 30 );
	dlgedit_Label_3->setMinimumSize( 10, 10 );
	dlgedit_Label_3->setMaximumSize( 32767, 32767 );
	dlgedit_Label_3->setText( i18n("Command") );
	dlgedit_Label_3->setAlignment( 290 );
	dlgedit_Label_3->setMargin( -1 );

	MenuOpOnly = new("QCheckBox") QCheckBox( this, "CheckBox_1" );
	MenuOpOnly->setGeometry( 280, 160, 100, 30 );
	MenuOpOnly->setMinimumSize( 10, 10 );
	MenuOpOnly->setMaximumSize( 32767, 32767 );
	MenuOpOnly->setText( i18n("OP Only") );
	MenuOpOnly->setAutoRepeat( FALSE );
	MenuOpOnly->setAutoResize( FALSE );

	ApplyButton = new("QPushButton") QPushButton( this, "PushButton_1" );
	ApplyButton->setGeometry( 280, 240, 100, 30 );
	ApplyButton->setMinimumSize( 10, 10 );
	ApplyButton->setMaximumSize( 32767, 32767 );
	connect( ApplyButton, SIGNAL(clicked()), SLOT(terminate()) );
	ApplyButton->setText( i18n("Close") );
	ApplyButton->setAutoRepeat( FALSE );
	ApplyButton->setAutoResize( FALSE );

	insertButton = new("QPushButton") QPushButton( this, "PushButton_2" );
	insertButton->setGeometry( 170, 240, 100, 30 );
	insertButton->setMinimumSize( 10, 10 );
	insertButton->setMaximumSize( 32767, 32767 );
	connect( insertButton, SIGNAL(clicked()), SLOT(insertMenu()) );
	insertButton->setText( i18n("Insert") );
	insertButton->setAutoRepeat( FALSE );
	insertButton->setAutoResize( FALSE );

	MainListBox = new("QListBox") QListBox( this, "ListBox_1" );
	MainListBox->setGeometry( 30, 40, 120, 230 );
	MainListBox->setMinimumSize( 10, 10 );
	MainListBox->setMaximumSize( 32767, 32767 );
	connect( MainListBox, SIGNAL(highlighted(int)), SLOT(newHighlight(int)) );
	connect( MainListBox, SIGNAL(selected(int)), SLOT(newHighlight(int)) );
	MainListBox->setFrameStyle( 51 );
	MainListBox->setLineWidth( 2 );
	MainListBox->setMultiSelection( FALSE );

	QPushButton* dlgedit_PushButton_3;
	dlgedit_PushButton_3 = new("QPushButton") QPushButton( this, "PushButton_3" );
	dlgedit_PushButton_3->setGeometry( 170, 200, 100, 30 );
	dlgedit_PushButton_3->setMinimumSize( 10, 10 );
	dlgedit_PushButton_3->setMaximumSize( 32767, 32767 );
	connect( dlgedit_PushButton_3, SIGNAL(clicked()), SLOT(deleteMenu()) );
	dlgedit_PushButton_3->setText( i18n("Delete") );
	dlgedit_PushButton_3->setAutoRepeat( FALSE );
	dlgedit_PushButton_3->setAutoResize( FALSE );

	QPushButton* dlgedit_PushButton_4;
	dlgedit_PushButton_4 = new("QPushButton") QPushButton( this, "PushButton_4" );
	dlgedit_PushButton_4->setGeometry( 280, 200, 100, 30 );
	dlgedit_PushButton_4->setMinimumSize( 10, 10 );
	dlgedit_PushButton_4->setMaximumSize( 32767, 32767 );
	connect( dlgedit_PushButton_4, SIGNAL(clicked()), SLOT(modifyMenu()) );
	dlgedit_PushButton_4->setText( i18n("Modify") );
	dlgedit_PushButton_4->setAutoRepeat( FALSE );
	dlgedit_PushButton_4->setAutoResize( FALSE );

	resize( 400,300 );
	setMinimumSize( 400, 300 );
	setMaximumSize( 400, 300 );
}