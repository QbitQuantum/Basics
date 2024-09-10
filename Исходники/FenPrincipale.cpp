FenPrincipale::FenPrincipale()
{

    // Groupe : Définition de la classe
    nom = new QLineEdit;
    classeMere = new QLineEdit;

    QFormLayout *definitionLayout = new QFormLayout;
    definitionLayout->addRow("&Nom :", nom);
    definitionLayout->addRow("Classe &mère :", classeMere);

    QGroupBox *groupDefinition = new QGroupBox("Définition de la classe");
    groupDefinition->setLayout(definitionLayout);


    // Groupe : Options

    protections = new QCheckBox("Protéger le &header contre les inclusions multiples");
    protections->setChecked(true);
    genererConstructeur = new QCheckBox("Générer un &constructeur par défaut");
    genererDestructeur = new QCheckBox("Générer un &destructeur");

    QVBoxLayout *optionsLayout = new QVBoxLayout;
    optionsLayout->addWidget(protections);
    optionsLayout->addWidget(genererConstructeur);
    optionsLayout->addWidget(genererDestructeur);

    QGroupBox *groupOptions = new QGroupBox("Options");
    groupOptions->setLayout(optionsLayout);



    // Groupe : Commentaires

    auteur = new QLineEdit;
    date = new QDateEdit;
    date->setDate(QDate::currentDate());
    role = new QTextEdit;

    QFormLayout *commentairesLayout = new QFormLayout;
    commentairesLayout->addRow("&Auteur :", auteur);
    commentairesLayout->addRow("Da&te de création :", date);
    commentairesLayout->addRow("&Rôle de la classe :", role);

    groupCommentaires = new QGroupBox("Ajouter des commentaires");
    groupCommentaires->setCheckable(true);
    groupCommentaires->setChecked(false);
    groupCommentaires->setLayout(commentairesLayout);


    // Layout : boutons du bas (générer, quitter...)
    generer = new QPushButton("&Générer !");
    quitter = new QPushButton("&Quitter");

    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    boutonsLayout->setAlignment(Qt::AlignRight);

    boutonsLayout->addWidget(generer);
    boutonsLayout->addWidget(quitter);


    // Définition du layout principal, du titre de la fenêtre, etc.

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(groupDefinition);
    layoutPrincipal->addWidget(groupOptions);
    layoutPrincipal->addWidget(groupCommentaires);
    layoutPrincipal->addLayout(boutonsLayout);

    setLayout(layoutPrincipal);
    setWindowTitle("Zero Class Generator");
    setWindowIcon(QIcon("icone.png"));
    resize(400, 450);


    // Connexions des signaux et des slots
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generer, SIGNAL(clicked()), this, SLOT(genererCode()));

}