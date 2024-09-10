/**
 * Constructeur
 * @param parent Parent du widget
 */
DocumentWidget::DocumentWidget(QWidget *parent) :
  NoteWidget(parent)
{
  //Construction du layout du widget
  QVBoxLayout *layout = new QVBoxLayout;
  //Construction de l'edition du titre du document
  titleEdit = new QLineEdit;
  connect(titleEdit,SIGNAL(textChanged(QString)),this,SLOT(changeTitle(QString)));
  layout->addWidget(titleEdit,1,Qt::AlignTop);

//  QScrollArea *scroll = new QScrollArea();
//  QWidget *childrenWidget = new QWidget();

  childrenLayout = new QVBoxLayout;
  layout->addLayout(childrenLayout);

  //Construction du menu associé au bouton "ajouter"
  noteTypeMenu = new QMenu(tr("..."));

  QMap<QString, NoteFactory*> &factories = NotesManager::getInstance()->getFactories();
  QMap<QString, NoteFactory*>::iterator it = factories.begin();
  QMap<QString, NoteFactory*>::iterator end = factories.end();
  while (it != end) {
    if (*it) {
      QAction *newNote = noteTypeMenu->addAction((*it)->getName());
      newNote->setData(it.key());
      newNote->setIcon(QIcon((*it)->getIcon()));
      connect(newNote,SIGNAL(triggered()),this,SLOT(addChild()));
    }
    it++;
  }


  QPushButton *more = new QPushButton(tr("Add child"));
  more->setMenu(noteTypeMenu);

  layout->addWidget(more,0,Qt::AlignBottom);

  setLayout(layout);
}