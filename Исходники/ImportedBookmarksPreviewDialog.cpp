void ImportedBookmarksPreviewDialog::AddItems()
{
    const int rootFolderIntId = (elist->importSource == ImportedEntityList::Source_Firefox ? 1 : 0);
    ui->chkRemoveImportedFile->setVisible(elist->importSource == ImportedEntityList::Source_Files);
    ui->chkRemoveImportedFile->setChecked(elist->removeImportedFiles);

    int index = 0;
    foreach (const ImportedBookmarkFolder& ibf, elist->ibflist)
    {
        QTreeWidgetItem* twi = new QTreeWidgetItem();
        twi->setText(0, ibf.title);
        twi->setIcon(0, icon_folder);
        twi->setData(0, TWID_IsFolder, true);
        twi->setData(0, TWID_Index, index);
        folderItems[ibf.intId] = twi;
        index++;

        //On Firefox, files and Urls, don't add or show the root folder.
        if (ibf.intId == rootFolderIntId && (elist->importSource == ImportedEntityList::Source_Firefox ||
                                             elist->importSource == ImportedEntityList::Source_Files ||
                                             elist->importSource == ImportedEntityList::Source_Urls))
            continue;

        if (ibf.parentId <= rootFolderIntId)
            ui->twBookmarks->addTopLevelItem(twi);
        else
            folderItems[ibf.parentId]->addChild(twi);
    }

    index = 0;
    foreach (const ImportedBookmark& ib, elist->iblist)
    {
        QTreeWidgetItem* twi = new QTreeWidgetItem();
        twi->setText(0, ib.title);
        SetBookmarkItemIcon(twi, ib);
        twi->setToolTip(0, ib.uri);
        twi->setData(0, TWID_IsFolder, false);
        twi->setData(0, TWID_Index, index);
        bookmarkItems[ib.intId] = twi;
        index++;

        if (ib.title.trimmed().isEmpty())
        {
            //For [title-less bookmarks] show their url in a different formatting.
            twi->setText(0, Util::FullyPercentDecodedUrl(ib.uri));
            twi->setTextColor(0, QColor(192, 128, 0));
            QFont italicFont = twi->font(0);
            italicFont.setItalic(true);
            twi->setFont(0, italicFont);
        }

        if (ib.parentId <= 0)
            ui->twBookmarks->addTopLevelItem(twi);
        else
            folderItems[ib.parentId]->addChild(twi);
    }

    ui->twBookmarks->expandAll();
    ui->twBookmarks->setCurrentItem(ui->twBookmarks->topLevelItem(0));
}