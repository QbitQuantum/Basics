DesertStrikeScenario::UInfo::UInfo( Resource &res, Tempest::Widget *owner, Game &game )
  :ModalWindow(res,owner), game(game), res(res) {
  using namespace Tempest;

  pause = game.isPaused();

  setLayout( Horizontal );

  ScroolWidget * w = new ScroolWidget(res);
  w->scroolBeforeBegin(1);

  w->setOrientation( Horizontal );
  w->setSizePolicy( Preferred, FixedMin );

  w->setMinimumSize( 0, 80 );
  w->setMaximumSize( w->maxSize().w, 80 );
  w->setScroolBarVisible(0);

  uname = new LineEdit(res);
  uname->setEditable(0);
  uname->setText(L"unit name");

  auto pr = DesertStrikeScenario::units;
  for( int i=0; i<3; ++i )
    for( int r=0; r<4; ++r )
      if( pr[i][r] ){
        const ProtoObject & obj = game.prototype( pr[i][r] );

        UBtn * u = new UBtn(res);
        u->icon = res.pixmap("gui/icon/"+obj.name);
        u->unit = obj.name;

        u->setMinimumSize( 80, 80 );
        u->setMaximumSize( u->minSize() );
        u->onClick.bind( *this, &UInfo::showUnit );

        w->centralWidget().layout().add( u );
        }

  uview = new UnitView(res);
  uview->alpha = true;
  uview->setFingerControl(1);

  Widget *detail = new Widget();
  Widget *l = new Widget();
  l->setLayout( Vertical );
  l->layout().add( uview );

  Widget *r = new Widget();
  r->setLayout( Vertical );
  desc = new RichText(res);
  r->layout().add( desc );

  hp = new LineEdit(res);
  r->layout().add( hp );
  damage = new LineEdit(res);
  r->layout().add( damage );
  armor = new LineEdit(res);
  r->layout().add( armor );

  LineEdit *efec = new LineEdit(res);
  efec->setText( Lang::tr("$(game_menu/efective) :"));
  r->layout().add( efec );

  hp->setEditable(0);
  damage->setEditable(0);
  armor->setEditable(0);

  efectiveUnits = new Panel(res);
  efectiveUnits->setMinimumSize(0, 75);
  efectiveUnits->setMargin(10);
  efectiveUnits->setSizePolicy( Tempest::Preferred, Tempest::FixedMin );
  r->layout().add( efectiveUnits );

  detail->setLayout( Horizontal );
  detail->layout().add( l );
  detail->layout().add( r );

  wnd = new Panel(res);
  wnd->setLayout( Vertical );
  wnd->layout().add( w );
  wnd->layout().add( uname );
  wnd->layout().add( detail );

  //Widget* wx;

  wnd->setMargin(10);
  wnd->setMaximumSize(480, 440);
  wnd->setMinimumSize(480, 440);
  wnd->setSizePolicy( FixedMin, FixedMin );

  layout().add( wnd );

  showUnit("pikeman");
  onResize.bind( this, &UInfo::resizeEvent );
  resizeEvent(0,0);
  }