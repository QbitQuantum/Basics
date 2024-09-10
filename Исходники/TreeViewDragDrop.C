  /*! \brief Populate the files model.
   *
   * Data (and headers) is read from the CSV file data/files.csv. We
   * add icons to the first column, resolve the folder id to the
   * actual folder name, and configure item flags, and parse date
   * values.
   */
  void populateFiles() {
    fileModel_->invisibleRootItem()->setRowCount(0);

    std::ifstream f((appRoot() + "data/files.csv").c_str());

    if (!f)
      throw std::runtime_error("Could not read: data/files.csv");

    readFromCsv(f, fileModel_);

    for (int i = 0; i < fileModel_->rowCount(); ++i) {
      WStandardItem *item = fileModel_->item(i, 0);
      item->setFlags(item->flags() | ItemIsDragEnabled);
      item->setIcon("icons/file.gif");

      std::string folderId = item->text().toUTF8();

      item->setData(boost::any(folderId), UserRole);
      item->setText(folderNameMap_[folderId]);

      convertToDate(fileModel_->item(i, 4));
      convertToDate(fileModel_->item(i, 5));
    }
  }