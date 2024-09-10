QucsSettingsDialog::QucsSettingsDialog(QucsApp *parent, const char *name)
			: QDialog(parent, name)
{
  App = parent;
  setWindowTitle(tr("Edit Qucs Properties"));

  Expr.setPattern("[\\w_]+");
  Validator  = new QRegExpValidator(Expr, this);

  all = new QVBoxLayout(this); // to provide the neccessary size
  QTabWidget *t = new QTabWidget();
  all->addWidget(t);

  // ...........................................................
  QWidget *Tab1 = new QWidget(t);
  QGridLayout *gp = new QGridLayout(Tab1);

  gp->addWidget(new QLabel(tr("Font (set after reload):"), Tab1), 0,0);
  FontButton = new QPushButton(Tab1);
  connect(FontButton, SIGNAL(clicked()), SLOT(slotFontDialog()));
  gp->addWidget(FontButton,0,1);

  gp->addWidget(new QLabel(tr("Document Background Color:"), Tab1) ,1,0);
  BGColorButton = new QPushButton("      ", Tab1);
  connect(BGColorButton, SIGNAL(clicked()), SLOT(slotBGColorDialog()));
  gp->addWidget(BGColorButton,1,1);

  gp->addWidget(new QLabel(tr("Language (set after reload):"), Tab1) ,2,0);
  LanguageCombo = new QComboBox(Tab1);
  LanguageCombo->insertItem(tr("system language"));
  LanguageCombo->insertItem(tr("English")+" (en)");
  LanguageCombo->insertItem(tr("German")+" (de)");
  LanguageCombo->insertItem(tr("French")+" (fr)");
  LanguageCombo->insertItem(tr("Spanish")+" (es)");
  LanguageCombo->insertItem(tr("Italian")+" (it)");
  LanguageCombo->insertItem(tr("Polish")+" (pl)");
  LanguageCombo->insertItem(tr("Romanian")+" (ro)");
  LanguageCombo->insertItem(tr("Japanese")+" (jp)");
  LanguageCombo->insertItem(tr("Swedish")+" (sv)");
  LanguageCombo->insertItem(tr("Hungarian")+" (hu)");
  LanguageCombo->insertItem(tr("Hebrew")+" (he)");
  LanguageCombo->insertItem(tr("Portuguese")+" (pt)");
  LanguageCombo->insertItem(tr("Turkish")+" (tr)");
  LanguageCombo->insertItem(tr("Ukrainian")+" (uk)");
  LanguageCombo->insertItem(tr("Russian")+" (ru)");
  LanguageCombo->insertItem(tr("Czech")+" (cs)");
  LanguageCombo->insertItem(tr("Catalan")+" (ca)");
  LanguageCombo->insertItem(tr("Arabic")+" (ar)");
  LanguageCombo->insertItem(tr("Kazakh")+" (kk)");
  gp->addWidget(LanguageCombo,2,1);

  val200 = new QIntValidator(0, 200, this);
  gp->addWidget(new QLabel(tr("maximum undo operations:"), Tab1) ,3,0);
  undoNumEdit = new QLineEdit(Tab1);
  undoNumEdit->setValidator(val200);
  gp->addWidget(undoNumEdit,3,1);

  gp->addWidget(new QLabel(tr("text editor:"), Tab1) ,4,0);
  editorEdit = new QLineEdit(Tab1);
  gp->addWidget(editorEdit,4,1);

  gp->addWidget(new QLabel(tr("start wiring when clicking open node:"), Tab1) ,5,0);
  checkWiring = new QCheckBox(Tab1);
  gp->addWidget(checkWiring,5,1);


  t->addTab(Tab1, tr("Settings"));

  // ...........................................................
  QWidget *Tab3 = new QWidget(t);
  QGridLayout *gp3 = new QGridLayout(Tab3);

  gp3->addMultiCellWidget(new QLabel(tr("Colors for Syntax Highlighting:"), Tab3), 0,0,0,1);

  ColorComment = new QPushButton(tr("Comment"), Tab3);
  ColorComment->setPaletteForegroundColor(QucsSettings.Comment);
  ColorComment->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorComment, SIGNAL(clicked()), SLOT(slotColorComment()));
  gp3->addWidget(ColorComment,1,0);

  ColorString = new QPushButton(tr("String"), Tab3);
  ColorString->setPaletteForegroundColor(QucsSettings.String);
  ColorString->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorString, SIGNAL(clicked()), SLOT(slotColorString()));
  gp3->addWidget(ColorString,1,1);

  ColorInteger = new QPushButton(tr("Integer Number"), Tab3);
  ColorInteger->setPaletteForegroundColor(QucsSettings.Integer);
  ColorInteger->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorInteger, SIGNAL(clicked()), SLOT(slotColorInteger()));
  gp3->addWidget(ColorInteger,1,2);

  ColorReal = new QPushButton(tr("Real Number"), Tab3);
  ColorReal->setPaletteForegroundColor(QucsSettings.Real);
  ColorReal->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorReal, SIGNAL(clicked()), SLOT(slotColorReal()));
  gp3->addWidget(ColorReal,2,0);

  ColorCharacter = new QPushButton(tr("Character"), Tab3);
  ColorCharacter->setPaletteForegroundColor(QucsSettings.Character);
  ColorCharacter->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorCharacter, SIGNAL(clicked()), SLOT(slotColorCharacter()));
  gp3->addWidget(ColorCharacter,2,1);

  ColorDataType = new QPushButton(tr("Data Type"), Tab3);
  ColorDataType->setPaletteForegroundColor(QucsSettings.Type);
  ColorDataType->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorDataType, SIGNAL(clicked()), SLOT(slotColorDataType()));
  gp3->addWidget(ColorDataType,2,2);

  ColorAttribute = new QPushButton(tr("Attribute"), Tab3);
  ColorAttribute->setPaletteForegroundColor(QucsSettings.Attribute);
  ColorAttribute->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorAttribute, SIGNAL(clicked()), SLOT(slotColorAttribute()));
  gp3->addWidget(ColorAttribute,3,0);

  ColorDirective = new QPushButton(tr("Directive"), Tab3);
  ColorDirective->setPaletteForegroundColor(QucsSettings.Directive);
  ColorDirective->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorDirective, SIGNAL(clicked()), SLOT(slotColorDirective()));
  gp3->addWidget(ColorDirective,3,1);

  ColorTask = new QPushButton(tr("Task"), Tab3);
  ColorTask->setPaletteForegroundColor(QucsSettings.Task);
  ColorTask->setPaletteBackgroundColor(QucsSettings.BGColor);
  connect(ColorTask, SIGNAL(clicked()), SLOT(slotColorTask()));
  gp3->addWidget(ColorTask,3,2);


  t->addTab(Tab3, tr("Source Code Editor"));

  // ...........................................................
  QWidget *Tab2 = new QWidget(t);
  QGridLayout *gp2 = new QGridLayout(Tab2);

  QLabel *note = new QLabel(
     tr("Register filename extensions here in order to\nopen files with an appropriate program."));
  gp2->addWidget(note,0,0,1,2);

  tableWidget = new QTableWidget(Tab2);
  tableWidget->setColumnCount(2);

  QTableWidgetItem *item1 = new QTableWidgetItem();
  QTableWidgetItem *item2 = new QTableWidgetItem();

  tableWidget->setHorizontalHeaderItem(0, item1);
  tableWidget->setHorizontalHeaderItem(1, item2);

  item1->setText(tr("Suffix"));
  item2->setText(tr("Program"));

  tableWidget->horizontalHeader()->setStretchLastSection(true);
  tableWidget->verticalHeader()->hide();
  connect(tableWidget, SIGNAL(cellClicked(int,int)), SLOT(slotTableCliked(int,int)));
  gp2->addWidget(tableWidget,1,0,3,1);

  // fill listview with already registered file extensions
  QStringList::Iterator it = QucsSettings.FileTypes.begin();
  while(it != QucsSettings.FileTypes.end()) {
    int row = tableWidget->rowCount();
    tableWidget->setRowCount(row+1);
    QTableWidgetItem *suffix = new QTableWidgetItem(QString((*it).section('/',0,0)));
    QTableWidgetItem *program = new QTableWidgetItem(QString((*it).section('/',1,1)));
    suffix->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    program->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidget->setItem(row, 0, suffix);
    tableWidget->setItem(row, 1, program);
    it++;
  }

  QLabel *l5 = new QLabel(tr("Suffix:"), Tab2);
  gp2->addWidget(l5,1,1);
  Input_Suffix = new QLineEdit(Tab2);
  Input_Suffix->setValidator(Validator);
  gp2->addWidget(Input_Suffix,1,2);
//  connect(Input_Suffix, SIGNAL(returnPressed()), SLOT(slotGotoProgEdit())); //not implemented

  QLabel *l6 = new QLabel(tr("Program:"), Tab2);
  gp2->addWidget(l6,2,1);
  Input_Program = new QLineEdit(Tab2);
  gp2->addWidget(Input_Program,2,2);

  QPushButton *AddButt = new QPushButton(tr("Set"));
  gp2->addWidget(AddButt,3,1);
  connect(AddButt, SIGNAL(clicked()), SLOT(slotAdd()));
  QPushButton *RemoveButt = new QPushButton(tr("Remove"));
  gp2->addWidget(RemoveButt,3,2);
  connect(RemoveButt, SIGNAL(clicked()), SLOT(slotRemove()));

  gp2->setRowStretch(3,4);
  t->addTab(Tab2, tr("File Types"));

  // ...........................................................
  // buttons on the bottom of the dialog (independent of the TabWidget)
  QHBoxLayout *Butts = new QHBoxLayout();
  Butts->setSpacing(3);
  Butts->setMargin(3);
  all->addLayout(Butts);

  QPushButton *OkButt = new QPushButton(tr("OK"));
  Butts->addWidget(OkButt);
  connect(OkButt, SIGNAL(clicked()), SLOT(slotOK()));
  QPushButton *ApplyButt = new QPushButton(tr("Apply"));
  Butts->addWidget(ApplyButt);
  connect(ApplyButt, SIGNAL(clicked()), SLOT(slotApply()));
  QPushButton *CancelButt = new QPushButton(tr("Cancel"));
  Butts->addWidget(CancelButt);
  connect(CancelButt, SIGNAL(clicked()), SLOT(reject()));
  QPushButton *DefaultButt = new QPushButton(tr("Default Values"));
  Butts->addWidget(DefaultButt);
  connect(DefaultButt, SIGNAL(clicked()), SLOT(slotDefaultValues()));

  OkButt->setDefault(true);

  // ...........................................................
  // fill the fields with the Qucs-Properties
  Font  = QucsSettings.font;
  FontButton->setText(Font.toString());
  BGColorButton->setPaletteBackgroundColor(QucsSettings.BGColor);
  undoNumEdit->setText(QString::number(QucsSettings.maxUndo));
  editorEdit->setText(QucsSettings.Editor);
  checkWiring->setChecked(QucsSettings.NodeWiring);

  for(int z=LanguageCombo->count()-1; z>=0; z--)
    if(LanguageCombo->text(z).section('(',1,1).remove(')') == QucsSettings.Language)
      LanguageCombo->setCurrentItem(z);

  resize(300, 200);
}