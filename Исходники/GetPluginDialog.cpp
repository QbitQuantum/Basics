GetPluginDialog::GetPluginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GetPluginDialog()){
  ui->setupUi(this);
  selected = false; //nothing selected by default
  //Now center the window on the parent
  if(parent!=0){
    QWidget *top = parent;
    while(!top->isWindow()){ top = top->parentWidget(); }
    QPoint center = top->geometry().center();
    this->move(center.x()-(this->width()/2), center.y()-(this->height()/2) );
  }
  //Load the icons
  ui->push_cancel->setIcon( LXDG::findIcon("dialog-cancel","") );
  ui->push_accept->setIcon( LXDG::findIcon("dialog-ok","") );
  this->setWindowIcon( LXDG::findIcon("preferences-plugin") );
  //Connect the signals/slots
  connect(ui->combo_list, SIGNAL(currentIndexChanged(int)), this, SLOT(pluginchanged()) );
  connect(ui->push_cancel, SIGNAL(clicked()), this, SLOT(close()) );
  connect(ui->push_accept, SIGNAL(clicked()), this, SLOT(accept()) );
}