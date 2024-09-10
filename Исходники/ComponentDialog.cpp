void ComponentDialog::init_uml_tab()
{
    bool visit = !hasOkButton();

    BrowserComponent * bn = (BrowserComponent *) data->get_browser_node();
    VVBox * vbox;
    GridBox * grid = new GridBox(2, this);

    umltab = grid;
    grid->setMargin(5);
    grid->setSpacing(5);

    grid->addWidget(new QLabel(tr("name : "), grid));
    grid->addWidget(edname = new LineEdit(bn->get_name(), grid));
    edname->setReadOnly(visit);

    grid->addWidget(new QLabel(tr("stereotype : "), grid));
    grid->addWidget(edstereotype = new QComboBox(grid));
    edstereotype->setEditable(true);
    edstereotype->addItem(toUnicode(data->get_stereotype()));

    if (! visit) {
        edstereotype->addItems(BrowserComponent::default_stereotypes());
        edstereotype->addItems(ProfiledStereotypes::defaults(UmlComponent));
        edstereotype->setAutoCompletion(completion());
    }

    edstereotype->setCurrentIndex(0);
    QSizePolicy sp = edstereotype->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    edstereotype->setSizePolicy(sp);

    grid->addWidget(vbox = new VVBox(grid));
    vbox->addWidget(new QLabel(tr("description :"), vbox));

    if (! visit)
    {
        SmallPushButton* sButton;
        connect(sButton = new SmallPushButton(tr("Editor"), vbox), SIGNAL(clicked()),
                this, SLOT(edit_description()));
        vbox->addWidget(sButton);
    }

    grid->addWidget(comment = new MultiLineEdit(grid));
    comment->setReadOnly(visit);
    comment->setText(bn->get_comment());
    QFont font = comment->font();

    if (! hasCodec())
        font.setFamily("Courier");

    font.setFixedPitch(TRUE);
    comment->setFont(font);

    addTab(grid, "Uml");
}