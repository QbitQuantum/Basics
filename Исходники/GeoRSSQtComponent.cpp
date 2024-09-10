void GeoRSSQtComponent::_displayGeoRSSItemGUI ( GeoRSSItem& item, Usul::Interfaces::IUnknown* caller )
{
  QDialog dialog ( 0x0 );
  
  // Make page to edit geoRSS values.
  GeoRSSItemWidget *page ( new GeoRSSItemWidget ( &dialog ) );
  page->title ( item.name() );
  page->description ( item.description() );
  
  const QDialogButtonBox::StandardButtons buttons ( QDialogButtonBox::NoButton|QDialogButtonBox::Ok );
  QDialogButtonBox *buttonBox ( new QDialogButtonBox ( buttons, Qt::Horizontal, &dialog ) );
  
  QObject::connect ( buttonBox, SIGNAL ( accepted() ), &dialog, SLOT ( accept() ) );
  
  QVBoxLayout *topLayout ( new QVBoxLayout );
  dialog.setLayout ( topLayout );
  
  topLayout->addWidget ( page );
  topLayout->addWidget ( buttonBox );
  
  // Set the title.
  dialog.setWindowTitle ( QString ( item.name().c_str() ) );
  
	dialog.exec();
}