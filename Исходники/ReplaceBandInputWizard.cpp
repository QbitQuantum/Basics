void ReplaceBandInputWizard::addDestBandPage()
{
   QWizardPage* pPage = new QWizardPage(this);
   pPage->setTitle("Select destination band");
   QLabel* pPageLabel = new QLabel("Select the destination band.", pPage);
   pPageLabel->setWordWrap(true);
   mpDestBand = new QComboBox(pPage);
   mpDestBand->setEditable(false);
   mpDestBand->addItems(getBandNames(static_cast<const RasterDataDescriptor*>(mpDest->getDataDescriptor())));

   QVBoxLayout* pLayout = new QVBoxLayout();
   pLayout->addWidget(pPageLabel);
   pLayout->addWidget(mpDestBand);
   pPage->setLayout(pLayout);

   addPage(pPage);
}