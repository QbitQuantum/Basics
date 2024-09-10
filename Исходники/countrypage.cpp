void CountryPage::createContent()
{
  if (m_pageMode == CountryModel::BY_ARTIST)
    m_countryModel = new CountryModel(m_dbStorage, m_artistID);
  else
    m_countryModel = new CountryModel(m_dbStorage);

  QGraphicsWidget *panel = centralWidget();
  MLayout *layout = new MLayout(panel);
  layout->setAnimation(NULL);
  panel->setLayout(layout);
  m_policy = new MLinearLayoutPolicy(layout, Qt::Vertical);

  // No country label
  m_noCountryLabel = new MLabel(tr("No events to show.<br/>"
                                   "Possible reasons:<br/>"
                                   "<ul>"
                                   "<li>None of your artist is on tour.</li>"
                                   "<li>You don't have added an artist yet.</li>"
                                   "</ul>"));
  m_noCountryLabel->setAlignment(Qt::AlignJustify);
  if (m_countryModel->rowCount() == 0) {
    m_policy->addItem(m_noCountryLabel);
    m_noCountryLabelVisible = true;
  } else
    m_noCountryLabelVisible = false;

  MList *countryList = new MList();
  countryList->setSelectionMode(MList::SingleSelection);

  CountryItemCreator *cellCreator = new CountryItemCreator();
  countryList->setCellCreator(cellCreator);
  countryList->setItemModel(m_countryModel);
  m_policy->addItem(countryList);

  connect (countryList, SIGNAL(itemClicked(QModelIndex)),
           this, SLOT(slotCountryClicked(QModelIndex)));
  connect (DBManager::instance(m_dbStorage), SIGNAL(locationCreated(int)),
           this, SLOT(slotLocationCreated(int)));
}