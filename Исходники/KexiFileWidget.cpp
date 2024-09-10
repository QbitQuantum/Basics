void KexiFileWidget::updateFilters()
{
    if (d->filtersUpdated)
        return;
    d->filtersUpdated = true;

    d->lastFileName.clear();
// m_lastUrl = KUrl();

    clearFilter();

    QString filter;
    KMimeType::Ptr mime;
    QStringList allfilters;

    const bool normalOpeningMode = d->mode & Opening && !(d->mode & Custom);
    const bool normalSavingMode = d->mode & SavingFileBasedDB && !(d->mode & Custom);

    if (normalOpeningMode || normalSavingMode) {
        mime = KMimeType::mimeType(KexiDB::defaultFileBasedDriverMimeType());
        if (mime && !d->excludedMimeTypes.contains(mime->name().toLower())) {
            filter += KexiUtils::fileDialogFilterString(mime);
            allfilters += mime->patterns();
        }
    }
    if (normalOpeningMode || d->mode & SavingServerBasedDB) {
        mime = KMimeType::mimeType("application/x-kexiproject-shortcut");
        if (mime && !d->excludedMimeTypes.contains(mime->name().toLower())) {
            filter += KexiUtils::fileDialogFilterString(mime);
            allfilters += mime->patterns();
        }
    }
    if (normalOpeningMode || d->mode & SavingServerBasedDB) {
        mime = KMimeType::mimeType("application/x-kexi-connectiondata");
        if (mime && !d->excludedMimeTypes.contains(mime->name().toLower())) {
            filter += KexiUtils::fileDialogFilterString(mime);
            allfilters += mime->patterns();
        }
    }

//! @todo hardcoded for MSA:
    if (normalOpeningMode) {
        mime = KMimeType::mimeType("application/vnd.ms-access");
        if (mime && !d->excludedMimeTypes.contains(mime->name().toLower())) {
            filter += KexiUtils::fileDialogFilterString(mime);
            allfilters += mime->patterns();
        }
    }

    foreach(const QString& mimeName, d->additionalMimeTypes) {
        if (mimeName == "all/allfiles")
            continue;
        if (d->excludedMimeTypes.contains(mimeName.toLower()))
            continue;
        filter += KexiUtils::fileDialogFilterString(mimeName);
        mime = KMimeType::mimeType(mimeName);
        allfilters += mime->patterns();
    }

    if (!d->excludedMimeTypes.contains("all/allfiles"))
        filter += KexiUtils::fileDialogFilterString("all/allfiles");
// mime = KMimeType::mimeType("all/allfiles");
// if (mime) {
//  filter += QString(mime->patterns().isEmpty() ? "*" : mime->patterns().join(" "))
//   + "|" + mime->comment()+ " (*)\n";
// }
    //remove duplicates made because upper- and lower-case extenstions are used:
    QStringList allfiltersUnique = allfilters.toSet().toList();
    qSort(allfiltersUnique);

    if (allfiltersUnique.count() > 1) {//prepend "all supoported files" entry
        filter.prepend(allfilters.join(" ") + "|"
                       + i18n("All Supported Files (%1)", allfiltersUnique.join(", ")) + "\n");
    }

    if (filter.right(1) == "\n")
        filter.truncate(filter.length() - 1);
    setFilter(filter);

    if (d->mode & Opening) {
        KFileWidget::setMode(KFile::ExistingOnly | KFile::LocalOnly | KFile::File);
        setOperationMode(KFileWidget::Opening);
    } else {
        KFileWidget::setMode(KFile::LocalOnly | KFile::File);
        setOperationMode(KFileWidget::Saving);
    }
}