WWidget *StyleLayout::wBoxLayout()
{
  WContainerWidget *result = new WContainerWidget();
  topic("WHBoxLayout", "WVBoxLayout", result);

  addText(tr("layout-WBoxLayout"), result);

  WContainerWidget *container;
  WText *item;
  WHBoxLayout *hbox;
  WVBoxLayout *vbox;

  /*
   * first hbox
   */
  container = new WContainerWidget(result);
  container->setStyleClass("yellow-box");
  hbox = new WHBoxLayout();
  container->setLayout(hbox);

  item = addText(tr("layout-item1"));
  item->setStyleClass("green-box");
  hbox->addWidget(item);
  
  item = addText(tr("layout-item2"));
  item->setStyleClass("blue-box");
  hbox->addWidget(item);

  addText(tr("layout-WBoxLayout-stretch"), result);

  /*
   * second hbox
   */
  container = new WContainerWidget(result);
  container->setStyleClass("yellow-box");
  hbox = new WHBoxLayout();
  container->setLayout(hbox);

  item = addText(tr("layout-item1"));
  item->setStyleClass("green-box");
  hbox->addWidget(item, 1);
  
  item = addText(tr("layout-item2"));
  item->setStyleClass("blue-box");
  hbox->addWidget(item);

  addText(tr("layout-WBoxLayout-vbox"), result);

  /*
   * first vbox
   */
  container = new WContainerWidget(result);
  container->resize(150, 150);
  container->setStyleClass("yellow-box centered");
  vbox = new WVBoxLayout();
  container->setLayout(vbox);

  item = addText(tr("layout-item1"));
  item->setStyleClass("green-box");
  vbox->addWidget(item);
  
  item = addText(tr("layout-item2"));
  item->setStyleClass("blue-box");
  vbox->addWidget(item);

  /*
   * second vbox
   */
  container = new WContainerWidget(result);
  container->resize(150, 150);
  container->setStyleClass("yellow-box centered");
  vbox = new WVBoxLayout();
  container->setLayout(vbox);

  item = addText(tr("layout-item1"));
  item->setStyleClass("green-box");
  vbox->addWidget(item, 1);
  
  item = addText(tr("layout-item2"));
  item->setStyleClass("blue-box");
  vbox->addWidget(item);

  addText(tr("layout-WBoxLayout-nested"), result);

  /*
   * nested boxes
   */
  container = new WContainerWidget(result);
  container->resize(200, 200);
  container->setStyleClass("yellow-box centered");

  vbox = new WVBoxLayout();
  container->setLayout(vbox);

  item = addText(tr("layout-item1"));
  item->setStyleClass("green-box");
  vbox->addWidget(item, 1);

  hbox = new WHBoxLayout();
  vbox->addLayout(hbox);

  item = addText(tr("layout-item2"));
  item->setStyleClass("green-box");
  hbox->addWidget(item);

  item = addText(tr("layout-item3"));
  item->setStyleClass("blue-box");
  hbox->addWidget(item);

  return result;
}