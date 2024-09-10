void AdsEditor::renderUI() {
  AdsApplication *app = AdsApplication::adsApplication();
  cppdb::session &db = app->db_;
  
  clear();
  WPushButton *btn = new WPushButton("Criar Anuncio", this);
  btn->clicked().connect(this, &AdsEditor::novoAnuncio);
  WPushButton *update = new WPushButton("Atualiza", this);
  update->clicked().connect(this, &AdsEditor::renderUI);
  new WBreak(this);
  new WBreak(this);
  new WText("<h3>Lista de Anuncios</h3>",this);
  
  Wt::WContainerWidget *w = new Wt::WContainerWidget(this);
  w->resize(600, WLength::Auto);
  WVBoxLayout *layout = new Wt::WVBoxLayout();
  cppdb::result res = db <<
    "select id, titulo, url, imagem, texto, ativo "
    " from anuncio";
  while(res.next()) {
    WContainerWidget *cont = new WContainerWidget();
    AdsAnuncio *anuncio = new AdsAnuncio(cont);
    
    res >>  anuncio->id >> anuncio->titulo_ >> anuncio->link_ >>
      anuncio->imagem_ >> anuncio->texto_ >> anuncio->ativo_;    
    
    WPushButton *tituloBtn = new WPushButton("Titulo",cont);
    tituloBtn->clicked().connect(anuncio, &AdsAnuncio::editarTitulo);
    
    WPushButton *urlBtn = new WPushButton("URL",cont);
    urlBtn->clicked().connect(anuncio, &AdsAnuncio::editarURL);
    
    WPushButton *imagemBtn = new WPushButton("Imagem",cont);
    imagemBtn->clicked().connect(anuncio, &AdsAnuncio::editarImagem);
    
    WPushButton *textoBtn = new WPushButton("Texto",cont);
    textoBtn->clicked().connect(anuncio, &AdsAnuncio::editarTexto);
    
    WCheckBox *ativoCheck = new Wt::WCheckBox("Ativo",cont);
    if(anuncio->ativo_ == 1)
      ativoCheck->setChecked(true);
    else 
      ativoCheck->setChecked(false);
    ativoCheck->changed().connect(anuncio, &AdsAnuncio::changeAtiva);

    WPushButton *deletaBtn = new WPushButton("Deleta",cont);
    deletaBtn->clicked().connect(anuncio, &AdsAnuncio::deletaAnuncio);

    anuncio->renderUI();
    layout->addWidget(cont);
  }
  w->setLayout(layout);
}