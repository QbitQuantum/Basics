/*!
    This function constructs a dialog which contains a label and a linedit for the given variable
    It return either the entered value or an empty string if the user hit cancel
 */
QString SnippetWidget::showSingleVarDialog(QString var, QMap<QString, QString> * mapSave, QRect & dlgSize)
{
  // --BEGIN-- building a dynamic dialog
  QDialog dlg(this);
  dlg.setCaption(i18n("Enter Values for Variables"));

  QGridLayout * layout = new QGridLayout( &dlg, 1, 1, 11, 6, "layout");
  QGridLayout * layoutTop = new QGridLayout( 0, 1, 1, 0, 6, "layoutTop");
  QGridLayout * layoutVar = new QGridLayout( 0, 1, 1, 0, 6, "layoutVar");
  QGridLayout * layoutBtn = new QGridLayout( 0, 2, 1, 0, 6, "layoutBtn");

  KTextEdit *te = NULL;
  QLabel * labTop = NULL;
  QCheckBox * cb = NULL;

  labTop = new QLabel( &dlg, "label" );
  layoutTop->addWidget(labTop, 0, 0);
  labTop->setText(i18n("Enter the replacement values for %1:").arg( var ));
  layout->addMultiCellLayout( layoutTop, 0, 0, 0, 1 );


  cb = new QCheckBox( &dlg, "cbVar" );
  cb->setChecked( FALSE );
  cb->setText(i18n( "Make value &default" ));

  te = new KTextEdit( &dlg, "teVar" );
  layoutVar->addWidget( te, 0, 1, Qt::AlignTop);
  layoutVar->addWidget( cb, 1, 1, Qt::AlignTop);
  if ((*mapSave)[var].length() > 0) {
    cb->setChecked( TRUE );
    te->setText((*mapSave)[var]);
  }

  QToolTip::add( cb, i18n("Enable this to save the value entered to the right as the default value for this variable") );
  QWhatsThis::add( cb, i18n("If you enable this option, the value entered to the right will be saved. "
                            "If you use the same variable later, even in another snippet, the value entered to the right "
                            "will be the default value for that variable.") );

  layout->addMultiCellLayout( layoutVar, 1, 1, 0, 1 );

  KPushButton * btn1 = new KPushButton( &dlg, "pushButton1" );
  btn1->setText(i18n("&Cancel"));
  layoutBtn->addWidget( btn1, 0, 0 );

  KPushButton * btn2 = new KPushButton( &dlg, "pushButton2" );
  btn2->setText(i18n("&Apply"));
  btn2->setDefault( TRUE );
  layoutBtn->addWidget( btn2, 0, 1 );

  layout->addMultiCellLayout( layoutBtn, 2, 2, 0, 1 );
  te->setFocus();
  // --END-- building a dynamic dialog

  //connect the buttons to the QDialog default slots
  connect(btn1, SIGNAL(clicked()), &dlg, SLOT(reject()) );
  connect(btn2, SIGNAL(clicked()), &dlg, SLOT(accept()) );

  //execute the dialog
  QString strReturn = "";
  if (dlgSize.isValid())
    dlg.setGeometry(dlgSize);
  if ( dlg.exec() == QDialog::Accepted ) {
    if (cb->isChecked())     //if the checkbox is on; save the values for later
      (*mapSave)[var] = te->text();
    else
      (*mapSave).erase(var);

    strReturn = te->text();    //copy the entered values back the the given map

    dlgSize = dlg.geometry();
  }

  //do some cleanup
  delete cb;
  delete te;
  delete labTop;
  delete btn1;
  delete btn2;
  delete layoutTop;
  delete layoutVar;
  delete layoutBtn;
  delete layout;

  return strReturn;
}