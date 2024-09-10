///
//  Add an entry to the browser
//
bool FileBrowser::addEntry(bool rootDir, int entryDepth,
                           const std::string &baseDir,
                           const std::string &baseName,
                           int index)
{
    //
    //  The code below adds an entry into the tree such as follows:
    //
    //  + tract_meta.bash
    //  + dicom_seriesCollect.bash
    //  + tract_meta-stage-2-dcm2trk.bash
    //    |
    //    + stage-1-mri_convert
    //      |
    //      + diff_unpack
    //
    //   ...
    //
    //  The relatively convoluted logic below is responsible for
    //  adding a new item to this tree structure.

    // If it's not a root directory, add the unique folder names as
    // root folder entries
    if (!rootDir)
    {
        bool addEntry = true;

        int modelRow;

        // Iterate over all the rows in the root
        for (modelRow = 0; modelRow < mModel->rowCount(); modelRow++)
        {
            WStandardItem *item = mModel->item(modelRow);
            bool match = true;

            // For the depth of the folder, attempt to match as many folders
            // as possible.
            for (int depth = 0; depth <= entryDepth && item != NULL; depth++)
            {
                path dirPath = path(baseDir);
                for (int d = 0; d < (entryDepth - depth); d++)
                {
                    dirPath = dirPath.branch_path();
                }
                std::string folderLeafName = path(dirPath).leaf().string();

                boost::any displayData = item->data(DisplayRole);
                if (!displayData.empty())
                {
                    WString folderName = boost::any_cast<WString>(displayData);

                    // Folder did not match, this means we need to add it
                    // to the tree
                    if (folderName.toUTF8() != folderLeafName)
                    {
                        match = false;
                        break;
                    }
                }
            }

            // All folders matched, we do not need a new folder
            if (match)
            {
                addEntry = false;
            }
        }

        // Add all of the necessary folder entries to the tree
        if (addEntry)
        {
            WStandardItem *lastItem = mModel->invisibleRootItem();

            for (int depth = 0; depth <= entryDepth; depth++)
            {
                path dirPath = path(baseDir);
                for (int d = 0; d < (entryDepth - depth); d++)
                {
                    dirPath = dirPath.branch_path();
                }
                std::string folderLeafName = path(dirPath).leaf().string();

                bool addFolder = true;
                for (int row = 0; row < lastItem->rowCount(); row++)
                {
                    WStandardItem *item = lastItem->child(row);
                    std::string folderLeafName = path(dirPath).leaf().string();

                    boost::any displayData = item->data(DisplayRole);
                    if (!displayData.empty())
                    {
                        WString folderName = boost::any_cast<WString>(displayData);

                        if (folderName.toUTF8() == folderLeafName)
                        {
                           addFolder = false;
                           lastItem = item;
                           break;
                        }
                    }
                }

                if (addFolder)
                {
                    WStandardItem *newItem = new WStandardItem(folderLeafName);
                    newItem->setFlags(newItem->flags().clear(ItemIsSelectable));
                    newItem->setIcon("icons/folder.gif");
                    lastItem->appendRow(newItem);
                    lastItem = newItem;
                }
            }
        }
    }
    // For root entries, add the file logs
    else
    {
        mModel->appendRow(createEntry(baseName, index));
    }

    // Now add the items under the folders
    if (!rootDir)
    {
        WStandardItem *lastItem = mModel->invisibleRootItem();

        for (int depth = 0; depth <= entryDepth; depth++)
        {
            path dirPath = path(baseDir);
            for (int d = 0; d < (entryDepth - depth); d++)
            {
                dirPath = dirPath.branch_path();
            }
            std::string folderLeafName = path(dirPath).leaf().string();

            for (int row = 0; row < lastItem->rowCount(); row++)
            {
                WStandardItem *item = lastItem->child(row);
                std::string folderLeafName = path(dirPath).leaf().string();

                boost::any displayData = item->data(DisplayRole);
                if (!displayData.empty())
                {
                    WString folderName = boost::any_cast<WString>(displayData);

                    if (folderName.toUTF8() == folderLeafName)
                    {
                        lastItem = item;
                        break;
                    }
                }
            }
        }

        if (lastItem != NULL)
        {
            lastItem->appendRow(createEntry(baseName, index));
        }
    }

    // Add the directory to the watch list
    addWatchPath(baseDir);

    return true;
}