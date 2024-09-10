KDMShutdown::KDMShutdown( int mode, QWidget* _parent, const char* _name,
			  const char* _shutdown, 
			  const char* _restart)
     : FDialog( _parent, _name, true)
{
     shutdown = _shutdown;
     restart  = _restart;
     int h = 10, w = 0;
     QFrame* winFrame = new QFrame( this);
     winFrame->setFrameStyle( QFrame::WinPanel | QFrame::Raised);
     QBoxLayout* box = new QBoxLayout( winFrame, QBoxLayout::TopToBottom, 
				       10, 10);
     QString shutdownmsg =  klocale->translate( "Shutdown or restart?");
     if( mode == KDMConfig::RootOnly) {
	  shutdownmsg += '\n';
	  shutdownmsg += klocale->translate( "(Enter Root Password)");
     }
     label = new QLabel( shutdownmsg, winFrame);
     set_fixed( label);
     h += label->height() + 10;
     w = label->width();

     box->addWidget( label, 0, AlignCenter);

     QFrame* sepFrame = new QFrame( this);
     sepFrame->setFrameStyle( QFrame::HLine| QFrame::Sunken);
     h += sepFrame->height(); 
     box->addWidget( sepFrame);

     btGroup = new QButtonGroup( /* this */);
     
     QRadioButton *rb;
     rb = new QRadioButton( winFrame /*btGroup*/);
     rb->setText( klocale->translate("Shutdown"));
     set_min( rb);
     rb->setFocusPolicy( StrongFocus);
     // Default action
     rb->setChecked( true);
     rb->setFocus();
     cur_action = shutdown;
     
     h += rb->height() + 10;
     w = QMAX( rb->width(), w);

     box->addWidget( rb);
     btGroup->insert( rb);
     rb = new QRadioButton( winFrame /*btGroup*/);
     rb->setText( klocale->translate("Shutdown and restart"));
     set_min( rb);
     rb->setFocusPolicy( StrongFocus);
     h += rb->height() + 10;
     w = QMAX( rb->width(), w);

     box->addWidget( rb);
     btGroup->insert( rb);
     rb = new QRadioButton( winFrame /*btGroup*/);
     rb->setText( klocale->translate("Restart X Server"));//better description
     set_min( rb);
     rb->setFocusPolicy( StrongFocus);
     h += rb->height() + 10;
     w = QMAX( rb->width(), w);

     box->addWidget( rb);
     btGroup->insert( rb);

     // Passwd line edit
     if( mode == KDMConfig::RootOnly) {
	  pswdEdit = new QLineEdit( winFrame);
	  //set_min( pswdEdit);
	  pswdEdit->setMinimumHeight( pswdEdit->sizeHint().height());
	  pswdEdit->setEchoMode( QLineEdit::NoEcho);
	  /*QColorGroup   passwdColGroup(
	       QApplication::palette()->normal().foreground(),
	       QApplication::palette()->normal().background(),
	       QApplication::palette()->normal().light(),
	       QApplication::palette()->normal().dark(),
	       QApplication::palette()->normal().mid(),
	       QApplication::palette()->normal().base(),
	       QApplication::palette()->normal().base());
	  QPalette passwdPalette( passwdColGroup, passwdColGroup, 
				  passwdColGroup);
	  pswdEdit->setPalette( passwdPalette);
	  */
	  pswdEdit->setFocusPolicy( StrongFocus);
	  pswdEdit->setFocus();
	  h+= pswdEdit->height() + 10;
	  box->addWidget( pswdEdit);
     }

     QBoxLayout* box3 = new QBoxLayout( QBoxLayout::LeftToRight, 10);
     box->addLayout( box3);

     okButton = new QPushButton( klocale->translate("OK"), winFrame);
     set_min( okButton);
     okButton->setFocusPolicy( StrongFocus);
     cancelButton = new QPushButton( klocale->translate("Cancel"), winFrame);
     set_min( cancelButton);
     //cancelButton->setDefault( true);
     cancelButton->setFocusPolicy( StrongFocus);
     h += cancelButton->height() + 10;
     w = QMAX( (okButton->width() + 10 + cancelButton->width()), w);

     box3->addWidget( okButton);
     box3->addWidget( cancelButton);
     // Connections
     connect( okButton, SIGNAL(clicked()), SLOT(bye_bye()));
     connect( cancelButton, SIGNAL(clicked()), SLOT(reject()));
     connect( btGroup, SIGNAL(clicked(int)), SLOT(rb_clicked(int)));
     if( mode == KDMConfig::RootOnly) {
	  okButton->setEnabled( false);
	  connect( pswdEdit, SIGNAL( returnPressed()), this, SLOT( pw_entered()));
     } else
	  cancelButton->setFocus();
     resize( 20 + w, h);
     winFrame->setGeometry( 0, 0, width(), height());
}