void CSQLiteAddressbookPlugin::addAddressbook(const wxString& name,
                                              const wxString& path)
{
  UUID id;
  wxASSERT(!addressBookNameExists(name) && !addressBookPathExists(path));
  UuidCreate(&id);
  CSQLiteAddressbook *pBook = new CSQLiteAddressbook(id, name, path);
  m_Addressbooks.push_back(pBook);
  m_pApplication->registerModule(pBook);
  saveAddressbookInfo();
}