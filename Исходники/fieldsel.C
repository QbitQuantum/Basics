FieldSelect::FieldSelect(Procview *pv, Proc *proc)
            : QDialog(0, "select fields"),
	      nbuttons(proc->cats.size()),
	      disp_fields(nbuttons),
	      procview(pv)
{
    QVBoxLayout *tl = new QVBoxLayout(this, 10, 10);

    updating = FALSE;
    setCaption("qps: select fields");
    buts = new QCheckBox*[nbuttons];

    QGridLayout *l1 = new QGridLayout((nbuttons + 1) / 2, 5, 0);
    tl->addLayout(l1, 1);
    l1->addColSpacing(2, 15);

    int half = (nbuttons + 1) / 2;
    for(int i = 0; i < nbuttons; i++) {
      QCheckBox *but = new QCheckBox(proc->cats[i]->name, this);
	QLabel *desc = new QLabel(proc->cats[i]->help, this);
	but->setMinimumSize(but->sizeHint());
	desc->setMinimumSize(desc->sizeHint());

	if(i < half) {
	  l1->addWidget(but, i, 0);
	  l1->addWidget(desc, i, 1);
	} else {
	  l1->addWidget(but, i-half, 3);
	  l1->addWidget(desc, i-half, 4);
	}
	buts[i] = but;
	connect(but, SIGNAL(toggled(bool)), this, SLOT(field_toggled(bool)));
    }
    update_boxes();

    KButtonBox *bbox = new KButtonBox(this);
    bbox->addStretch(1);
    QPushButton *closebut = bbox->addButton(i18n("Close"));
    closebut->setDefault(TRUE);
    closebut->setFocus();
    closebut->setFixedSize(closebut->sizeHint());
    bbox->layout();
    tl->addWidget(bbox);

    connect(closebut, SIGNAL(clicked()), SLOT(closed()));

    QAccel *acc = new QAccel(this);
    acc->connectItem(acc->insertItem(CTRL + Key_W),
		     this, SLOT(closed()));
    tl->freeze();
}