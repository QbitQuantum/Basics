void KnightsView::gameOver ( Color winner ) {
	qCDebug(LOG_KNIGHTS) << sender() << colorName ( winner );

	QPointer<QDialog> dlg = new QDialog ( this );
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QWidget *mainWidget = new QWidget(this);
	dlg->setLayout(mainLayout);
	dlg->setWindowTitle ( i18n("Game over") );
	mainLayout->addWidget(mainWidget);

	QDialogButtonBox *bBox = new QDialogButtonBox( QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Apply );
	KActionCollection* c = qobject_cast<KXmlGuiWindow*>( parentWidget() )->actionCollection();
	Q_ASSERT(c);

	QMap<QDialogButtonBox::StandardButton, QByteArray> buttonsMap;
	buttonsMap[QDialogButtonBox::Ok] = KStandardGameAction::name ( KStandardGameAction::New );
	buttonsMap[QDialogButtonBox::Apply] = KStandardGameAction::name ( KStandardGameAction::Save );

	for ( QMap<QDialogButtonBox::StandardButton, QByteArray>::ConstIterator it = buttonsMap.constBegin(); it != buttonsMap.constEnd(); ++it ) {
		QAction* a = c->action ( QLatin1String ( it.value() ) );
		Q_ASSERT(a);

		bBox->button ( it.key() )->setText ( a->text() );
		bBox->button ( it.key() )->setIcon ( QIcon ( a->icon() ) );
		bBox->button ( it.key() )->setToolTip ( a->toolTip() );
	}

	connect( bBox, &QDialogButtonBox::accepted, dlg, &QDialog::accept );
	connect( bBox, &QDialogButtonBox::rejected, dlg, &QDialog::reject );
	connect( bBox->button (QDialogButtonBox::Apply), &QPushButton::clicked,
	         static_cast<MainWindow *> (window()), &MainWindow::fileSave );

	QLabel* label = new QLabel(this);
	if ( winner == NoColor )
		label->setText ( i18n ( "The game ended in a draw" ) );
	else {
		QString winnerName = Protocol::byColor ( winner )->playerName();
		if ( winnerName == colorName(winner) ) {
			if ( winner == White ) {
				label->setText ( i18nc("White as in the player with white pieces",
				                       "The game ended with a victory for <em>White</em>") );
			} else {
				label->setText ( i18nc("Black as in the player with black pieces",
				                       "The game ended with a victory for <em>Black</em>") );
			}
		} else {
			if ( winner == White ) {
				label->setText ( i18nc("Player name, then <White as in the player with white pieces",
				                       "The game ended with a victory for <em>%1</em>, playing White", winnerName) );
			} else {
				label->setText ( i18nc("Player name, then Black as in the player with black pieces",
				                       "The game ended with a victory for <em>%1</em>, playing Black", winnerName) );
			}
		}
	}
	mainLayout->addWidget(label);
	mainLayout->addWidget(bBox);

	if ( dlg->exec() == QDialog::Accepted )
		emit gameNew();

	qCDebug(LOG_KNIGHTS) << Protocol::white();
	qCDebug(LOG_KNIGHTS) << Protocol::black();
	delete dlg;
}