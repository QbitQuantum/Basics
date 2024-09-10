void Fenetre::modifSommetForme(Sommet *sommet)
{
    //Création d'une boîte de dialogue
    QDialog fenDiag;

    //Boutons OK et Annuler
    QHBoxLayout *layoutButton=new QHBoxLayout;
    QPushButton *okFenDiag=new QPushButton("&OK");
    QPushButton *cancFenDiag=new QPushButton("&Annuler");
    layoutButton->addWidget(okFenDiag);
    layoutButton->addWidget(cancFenDiag);

    connect(okFenDiag, SIGNAL(clicked()), &fenDiag, SLOT(accept()));
    connect(cancFenDiag, SIGNAL(clicked()), &fenDiag, SLOT(reject()));

    //Champ pour choisir la forme
    QComboBox *boxFormes=new QComboBox;
    boxFormes->addItems(graphe.getListeForme());

    //Ajout de tout ça à la fenêtre de dialogue
    QVBoxLayout *layoutFenetre=new QVBoxLayout;
    layoutFenetre->addWidget(boxFormes);
    layoutFenetre->addLayout(layoutButton);
    fenDiag.setLayout(layoutFenetre);

    //On affiche la fenêtre
    fenDiag.setVisible(true);
    fenDiag.setModal(true);

    //On traîte la demande
    if(fenDiag.exec()){ //Si on a cliqué sur ok !
        QString currentText=boxFormes->currentText();
        sommet->setForme(currentText);
    }
}