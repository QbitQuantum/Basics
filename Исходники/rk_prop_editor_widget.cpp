PropEditorWidget::PropEditorWidget(ObjTreeQtModel* aObjTreeMdl, QWidget * parent, Qt::WindowFlags flags) :
                                   QDockWidget(parent, flags),
                                   Ui::RKPropEditorWidget(),
                                   mdl(aObjTreeMdl->get_object_graph(),aObjTreeMdl->get_root_node()),
                                   delegate(&mdl)
{
  setupUi(this);
  this->tableView->setModel(&mdl);
  this->tableView->setRootIndex(QModelIndex());
  this->tableView->setItemDelegate(&delegate);
  this->tableTab->setAttribute(Qt::WA_AlwaysShowToolTips, true);
  this->sourceTab->setAttribute(Qt::WA_AlwaysShowToolTips, true);
  
  connect(aObjTreeMdl, SIGNAL(objectNodeSelected(serialization::object_node_desc)), &mdl, SLOT(selectObject(serialization::object_node_desc)));
  connect(&mdl, SIGNAL(objectTreeChanged()), aObjTreeMdl, SLOT(treeChanged()));

  connect(&mdl, SIGNAL(objectNameChanged(std::string)), this, SLOT(objNameChanged(std::string)));
  connect(&mdl, SIGNAL(sourceDataChanged()), this, SLOT(xmlSrcChanged()));
  connect(this, SIGNAL(editedXMLSrc(std::string)), &mdl, SLOT(sourceDataEdited(std::string)));
  
  connect(this->applyButton, SIGNAL(clicked()), this, SLOT(applyButtonClick()));
  connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClick()));
  
  connect(this->textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
};