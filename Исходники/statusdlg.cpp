//----------------------------------------------------------------------------
// StatusShowDlg
// FIXME: Will no longer be needed once it is out of the groupchat contactview
//----------------------------------------------------------------------------
StatusShowDlg::StatusShowDlg(const UserListItem &u)
	: QDialog(0, 0, false)
{
	setAttribute(Qt::WA_DeleteOnClose);
	// build the dialog
	QVBoxLayout *vb = new QVBoxLayout(this, 8);
	PsiTextView *te = new PsiTextView(this);
	vb->addWidget(te);
	QHBoxLayout *hb = new QHBoxLayout(vb);
	QPushButton *pb = new QPushButton(tr("&Close"), this);
	connect(pb, SIGNAL(clicked()), SLOT(close()));
	hb->addStretch(1);
	hb->addWidget(pb);
	hb->addStretch(1);

	// set the rest up
	te->setReadOnly(true);
	te->setTextFormat(Qt::RichText);
	te->setText(u.makeDesc());

	setWindowTitle(tr("Status for %1").arg(JIDUtil::nickOrJid(u.name(), u.jid().full())));
	resize(400,240);

	pb->setFocus();
}