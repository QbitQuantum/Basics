void TEWidget::inputMethodEvent( QInputMethodEvent * e)  // is a virtual function
{
  static int c=0;
  qDebug("in TEWidget::inputMethodEvent : %d", c++);
  static QString preedit_string;
  preedit_string=e->preeditString();
  if (!e->commitString().isEmpty())
  {
    qDebug("!e->commitString() : %d", e->commitString().length() );
    static QString commit_string;
    commit_string=e->commitString();
    const char *ch=commit_string.toStdString().c_str();
    for (int i=0 ; i < commit_string.toStdString().length() ; ++i)
      qDebug("ch[i] : %x", ch[i]);
    //input_text_->setText(preedit_string+"*"+commit_string);
    input_text_->clear();
    //input_text_->setText("test"+commit_string);
    //input_text_->set_text("commit"+e->commitString() );
    //input_text_->show();
    //onRcvBlock();


    // QKeyEvent ( Type type, int key, Qt::KeyboardModifiers modifiers, const QString & text = QString(), bool autorep = false, ushort count = 1 )
#if 0
    int encode=get_encoding();
    QTextDecoder* decoder;
    QTextCodec *codec;
    QByteArray qba;
    const QChar * qchar;



    if ( get_input_encoding() == DS::BIG5)
    {
      codec = QTextCodec::codecForName("BIG5");
      //qDebug("(encoding==DS::BIG5)");
      //qDebug("(encoding==DS::UTF8)");
      qDebug("in encode==DS::BIG5");

    }
    if ( get_input_encoding() == DS::UTF8)
    {
      codec = QTextCodec::codecForName("UTF-8");
      //qchar= e->commitString().unicode();
      //codec = QTextCodec::codecForName("UTF-8");
      //qDebug("in encode==DS::UTF8");
      //qba=e->commitString().toUtf8();
    }



    QByteArray ba = codec->fromUnicode(ev->text());
    char *ba_data=ba.data();
    emit sndBlock(ba_data ,strlen(ba_data));    


    //for (int i=0 ; i < e->commitString().length() ; ++i)
      //qDebug("qchar[i] : %x", qchar[i].unicode () );
      //qDebug("qchar[i] : %x", i);
    decoder = codec->makeDecoder();
    const char *c_str= e->commitString().toStdString().c_str();
      qDebug("c_str len: %d", strlen(c_str));

    for (int i=0 ; i < strlen(c_str) ; ++i)
      qDebug("c_str[i]: %x", c_str[i]);

    commit_string=decoder->toUnicode(c_str, strlen(c_str));
#endif
    //QString str(qba);

    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, commit_string);

    //actSel=0; // Key stroke implies a screen update, so TEWidget won't
              // know where the current selection is.

    emit keyPressedSignal(ke); // expose
    //preedit_string="";
    //commit_string="";
    //sleep(3);
  }
  else
  {
    qDebug("e->commitString()");
    #if 0
    if (!preedit_string.isEmpty())
    {
    input_text_->set_text("preedit"+preedit_string);
    input_text_->show();
    }
    #endif
  }
#if 0
  if (!preedit_string.isEmpty())
  {
    input_text_->set_text(preedit_string);
    input_text_->show();
  }
#endif
}