/*
 * Path is not saved in linux without installer - added workspace to properties dialog.
 */
NewProject::NewProject(QWidget *parent) : QDialog(parent)
{
    mypath = getCurrentPath();
    path = new QLineEdit(mypath,this);
    path->setToolTip(tr("Directory for new project."));

    QPushButton *btnBrowsePath = new QPushButton(this);
    btnBrowsePath->setText(tr("Browse"));

    name = new QLineEdit(this);
    name->setToolTip(tr("New project name and sub-directory."));
    connect(name,SIGNAL(textChanged(QString)),this,SLOT(nameChanged()));

    path->setText(mypath+name->text());
    QLabel *pathLabel = new QLabel(tr("Workspace"));
    QLabel *nameLabel = new QLabel(tr("Project Name"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBrowsePath, SIGNAL(clicked()), this, SLOT(browsePath()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    okButton = (QPushButton*) buttonBox->buttons().at(0);
    cancelButton = (QPushButton*) buttonBox->buttons().at(1);
    if(okButton->text().contains("cancel",Qt::CaseInsensitive)) {
        okButton = (QPushButton*) buttonBox->buttons().at(1);
        cancelButton = (QPushButton*) buttonBox->buttons().at(1);
    }

    QLabel *create = new QLabel(this);
    create->setText(tr("Creating a new project:"));
    create->setFont(QFont(this->font().family(),this->font().pointSize()*1.5,QFont::Bold));
    QLabel *inst = new QLabel(this);
    inst->setText(tr(" 1) Choose project workspace.\n 2) Set project name.\n\n" \
            "A project folder with project name will be created in the workspace.\n" \
            "The new folder will have a main .c file and a .side project file.\n"));

    QVBoxLayout *blay = new QVBoxLayout(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(path,0,1,1,1); // tab order for widgets is according to add order
    layout->addWidget(name,1,1,1,1);
    layout->addWidget(btnBrowsePath,0,2,1,1);
    layout->addWidget(nameLabel,1,0,1,1);
    layout->addWidget(pathLabel,0,0,1,1);

    blay->addWidget(create);
    blay->addWidget(inst);
    blay->addLayout(layout);
    blay->addWidget(new QLabel(this));
    blay->addWidget(buttonBox);
    setLayout(blay);
    buttonBox->setFocus();

    int fontSize = path->fontInfo().pixelSize();
    setMinimumWidth(mypath.length()*fontSize+100);
    setWindowFlags(Qt::Tool);
}