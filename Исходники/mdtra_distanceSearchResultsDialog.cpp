MDTRA_DistanceSearchResultsDialog :: MDTRA_DistanceSearchResultsDialog( QWidget *parent )
								   : QDialog( parent )
{
	m_pMainWindow = qobject_cast<MDTRA_MainWindow*>(parent);
	assert(m_pMainWindow != NULL);

	setupUi( this );
	setFixedSize( width(), height() );
	setWindowIcon( QIcon(":/png/16x16/ds.png") );

	QStringList hrzHeader;
	hrzHeader << tr("First Atom");
	hrzHeader << tr("Second Atom");
	hrzHeader << tr("Stream1 Value");
	hrzHeader << tr("Stream2 Value");
	hrzHeader << tr("Difference");
	hrzHeader << tr("Options");
	resultTable->setHorizontalHeaderLabels(hrzHeader);
	resultTable->setRowCount( MDTRA_MAX( 15, s_SignificantPairs.count() ) );

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QApplication::processEvents();

	for (int i = 0; i < s_SignificantPairs.count(); i++) {
		const MDTRA_DistanceSearchPair *pPair = &s_SignificantPairs.at(i);
		const MDTRA_PDB_Atom *pCurrentAtom1 = s_ldsd[0].pStream->pdb->fetchAtomByIndex( pPair->atom1[0] );
		const MDTRA_PDB_Atom *pCurrentAtom2 = s_ldsd[0].pStream->pdb->fetchAtomByIndex( pPair->atom2[0] );
		QTableWidgetItem_SortByUserRole_i *pItemi;
		QTableWidgetItem_SortByUserRole_f *pItemf;
		QPushButtonWithTag *pButton;

		pItemi = new QTableWidgetItem_SortByUserRole_i(QString("%1-%2 %3").arg(pCurrentAtom1->trimmed_residue).arg(pCurrentAtom1->residuenumber).arg(pCurrentAtom1->trimmed_title));
		pItemi->setData(Qt::UserRole, pCurrentAtom1->serialnumber);
		pItemi->setTextAlignment( Qt::AlignCenter );
		resultTable->setItem(i, 0, pItemi);

		pItemi = new QTableWidgetItem_SortByUserRole_i(QString("%1-%2 %3").arg(pCurrentAtom2->trimmed_residue).arg(pCurrentAtom2->residuenumber).arg(pCurrentAtom2->trimmed_title));
		pItemi->setData(Qt::UserRole, pCurrentAtom2->serialnumber);
		pItemi->setTextAlignment( Qt::AlignCenter );
		resultTable->setItem(i, 1, pItemi);

		pItemf = new QTableWidgetItem_SortByUserRole_f();
		pItemf->setData(Qt::UserRole, pPair->value1);
		pItemf->setData(Qt::DisplayRole, pPair->value1);
		pItemf->setTextAlignment( Qt::AlignCenter );
		pItemf->setToolTip( s_ldsd[0].pStream->name );
		resultTable->setItem(i, 2, pItemf);

		pItemf = new QTableWidgetItem_SortByUserRole_f();
		pItemf->setData(Qt::UserRole, pPair->value2);
		pItemf->setData(Qt::DisplayRole, pPair->value2);
		pItemf->setTextAlignment( Qt::AlignCenter );
		pItemf->setToolTip( s_ldsd[1].pStream->name );
		resultTable->setItem(i, 3, pItemf);

		pItemf = new QTableWidgetItem_SortByUserRole_f();
		pItemf->setData(Qt::UserRole, pPair->diff);
		pItemf->setData(Qt::DisplayRole, pPair->diff);
		pItemf->setTextAlignment( Qt::AlignCenter );
		resultTable->setItem(i, 4, pItemf);

		pButton = new QPushButtonWithTag( i, tr("Add..."), resultTable );
		resultTable->setCellWidget(i, 5, pButton);
		connect(pButton, SIGNAL(clicked()), this, SLOT(exec_on_result_add()));
	}

	QApplication::restoreOverrideCursor();

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(exec_save()));
	connect(resultTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(exec_on_header_clicked(int)));
	createPopupMenu();
}