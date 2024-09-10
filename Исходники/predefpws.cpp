QDomElement ReglerPredefPw::getWindowXml( VtlWidget * parent  )
{
  Pie * pie = dynamic_cast<Pie*>(parent);
  if (!pie ) {
    qWarning () << "BAD WIDGET TYPE!!!!";
    return QDomElement();
  }
  ConfigRC conf_rc;

  FakeApplicationWindow app;
  FakeSimpleMdiWindow * mdi = new FakeSimpleMdiWindow(&app, "PopupVtlWindow");
  if (buttonType() == LeftButton )
    mdi->addParam ("popup", "lb");
  else if (buttonType() == RightButton )
    mdi->addParam ("popup", "rb");
  mdi->setPaletteBackgroundColor (QColor(194, 199, 200));
  
  int x = 0, y = 0;
  calculatePwPos (pie, 135, 240, x, y);

  mdi->setWindowTitle (pie->toolTip());
  mdi->setGeometry (QRect(x, y, 135, 240));
  
  FakeTButton * big_up = new FakeTButton( mdi, "big_up" );
  big_up->setProperty ( "geometry", QRect (-20, 0, 80, 50) );
  big_up->setProperty ( "ETCPICT", "2uparrow.svg");
  big_up->setProperty ( "B_TP", 4 );
  big_up->setProperty ( "CMD", 3.0f );
  big_up->setProperty ( "TLTP", "Довгий імпульс на відкриття");

  FakeTButton * small_up = new FakeTButton( mdi, "small_up" );
  small_up->setProperty ( "geometry", QRect (-20, 50, 80, 50) );
  small_up->setProperty ( "ETCPICT", "1uparrow.svg");
  small_up->setProperty ( "B_TP", 4 );
  small_up->setProperty ( "CMD", 1.0f );
  small_up->setProperty ( "TLTP", "Короткий імпульс на відкриття");

  FakeTButton * small_down = new FakeTButton( mdi, "small_down" );
  small_down->setProperty ( "geometry", QRect (-20, 100, 80, 50) );
  small_down->setProperty ( "ETCPICT", "1downarrow.svg");
  small_down->setProperty ( "B_TP", 4 );
  small_down->setProperty ( "CMD", 2.0f );
  small_down->setProperty ( "TLTP", "Короткий імпульс на закриття");

  FakeTButton * big_down = new FakeTButton( mdi, "big_down" );
  big_down->setProperty ( "geometry", QRect (-20, 150, 80, 50) );
  big_down->setProperty ( "ETCPICT", "2downarrow.svg");
  big_down->setProperty ( "B_TP", 4 );
  big_down->setProperty ( "CMD", 4.0f );
  big_down->setProperty ( "TLTP", "Довгий імпульс на закриття" );
  

  FakeTButton * to_auto = new FakeTButton( mdi, "to_auto" );
  to_auto->setProperty ( "geometry", QRect (65, 100, 80, 50) );
  to_auto->setProperty ( "CPT", "АВТ" );
  to_auto->setProperty ( "font", QFont ("Tahoma", 20 ) );
  to_auto->setProperty ( "B_TP", 4 );
  to_auto->setProperty ( "CMD", 5.0f );
  to_auto->setProperty ( "TLTP", "Переключення в автоматичний режим" );

  FakeTButton * to_man = new FakeTButton( mdi, "to_man" );
  to_man->setProperty ( "geometry", QRect (65, 150, 80, 50) );
  to_man->setProperty ( "CPT", "РУЧ" );
  to_man->setProperty ( "font", QFont ("Tahoma", 20 ) );
  to_man->setProperty ( "B_TP", 4 );
  to_man->setProperty ( "CMD", 6.0f );
  to_man->setProperty ( "TLTP", "Переключення в ручний режим" );
  
  
  FakeTButton * reg_btn = new FakeTButton( mdi, "reg_btn" );
  reg_btn->setProperty ( "geometry", QRect (-20, 200, 165, 40) );
  reg_btn->setProperty ( "B_TP", 1 );
  reg_btn->setProperty ( "font", QFont ("Tahoma", 14 ) );
  reg_btn->setProperty ( "CPT", "Регулятор" );
  reg_btn->setProperty ( "TLTP", "Перехід до настройки регулятора") ;
  
  FakePie * fake_pie = new FakePie (mdi, "pie");
  fake_pie->setProperty ("geometry", QRect (75, 5, 50, 50) );
  fake_pie->setProperty ("SRC", pie->sourcerName() );
  
  FakeFigures * fig = new FakeFigures (mdi, "figures");
  fig->setProperty ("geometry", QRect(60, 55, 55, 30));
  fig->setProperty ("SRC", pie->sourcerName() );
//  fig->setProperty ("font", QFont("Tahoma", 18) );
  fig->setProperty ("NDG", 1 );
  fig->setProperty ("SFF", " %" );
  fig->setProperty ("BCKG_C", QColor(194, 199, 200));


  FakeMessageList * list = new FakeMessageList (mdi, "ma");
  list->setProperty ("geometry", QRect(115, 55, 20, 30));
  list->setProperty ("font", QFont("Tahoma", 18) );
  list->setProperty ("BCKG_C", QColor(194, 199, 200) );
  list->setProperty ("NRM_C", QColor(0, 0, 0) );
  NamedList l("TextStruct");
  {
    NamedMap m("TextStruct");
    m["min"] = -0.1f;
    m["max"] = 0.1f;
    m["txt"] = "A";
    
    l.append (QVariant::fromValue(m));
  }
  
  {
    NamedMap m("TextStruct");
    m["min"] = 3.9f;
    m["max"] = 4.1f;
    m["txt"] = "P";
    
    l.append (QVariant::fromValue(m));
  }
  list->setProperty("TXT_L", QVariant::fromValue (l) );
  
  XmlObjectSaverBase<VtlWrapper> saver;
  saver.save (mdi->selfWrapper());

  return saver.document().firstChild().toElement();
}