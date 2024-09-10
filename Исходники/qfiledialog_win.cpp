static QStringList qt_win_CID_get_open_file_names(const QFileDialogArgs &args,
                                       QString *initialDirectory,
                                       const QStringList &filterList,
                                       QString *selectedFilter,
                                       int selectedFilterIndex)
{
    QStringList result;
    QDialog modal_widget;
    modal_widget.setAttribute(Qt::WA_NoChildEventsForParent, true);
    modal_widget.setParent(args.parent, Qt::Window);
    QApplicationPrivate::enterModal(&modal_widget);
    // Multiple selection is allowed only in IFileOpenDialog.
    IFileOpenDialog *pfd = 0;
    HRESULT hr = CoCreateInstance(QT_CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, QT_IID_IFileOpenDialog, 
        reinterpret_cast<void**>(&pfd));

    if (SUCCEEDED(hr)) {
        qt_win_set_IFileDialogOptions(pfd, args.selection,
                                      args.directory, args.caption,
                                      filterList, QFileDialog::ExistingFiles,
                                      args.options);
        // Set the currently selected filter (one-based index).
        hr = pfd->SetFileTypeIndex(selectedFilterIndex+1);
        QWidget *parentWindow = args.parent;
        if (parentWindow)
            parentWindow = parentWindow->window();
        else
            parentWindow = QApplication::activeWindow();
        // Show the file dialog.
        hr = pfd->Show(parentWindow ? parentWindow->winId() : 0);
        if (SUCCEEDED(hr)) {
            // Retrieve the results.
            IShellItemArray *psiaResults;
            hr = pfd->GetResults(&psiaResults);
            if (SUCCEEDED(hr)) {
                DWORD numItems = 0;
                psiaResults->GetCount(&numItems);
                for (DWORD i = 0; i<numItems; i++) {
                    IShellItem *psi = 0;
                    hr = psiaResults->GetItemAt(i, &psi);
                    if (SUCCEEDED(hr)) {
                        // Retrieve the file name from shell item.
                        wchar_t *pszPath;
                        hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
                        if (SUCCEEDED(hr)) {
                            QString fileName = QString::fromWCharArray(pszPath);
                            result.append(fileName);
                            CoTaskMemFree(pszPath);
                        }
                        psi->Release(); // Free the current item.
                    }
                }
                psiaResults->Release(); // Free the array of items.
            }
        }
    }
    QApplicationPrivate::leaveModal(&modal_widget);

    qt_win_eatMouseMove();

    if (!result.isEmpty()) {
        // Retrieve the current folder name.
        IShellItem *psi = 0;
        hr = pfd->GetFolder(&psi);
        if (SUCCEEDED(hr)) {
            wchar_t *pszPath;
            hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
            if (SUCCEEDED(hr)) {
                *initialDirectory = QString::fromWCharArray(pszPath);
                CoTaskMemFree(pszPath);
            }
            psi->Release();
        }
        // Retrieve the currently selected filter.
        if (selectedFilter) {
            quint32 filetype = 0;
            hr = pfd->GetFileTypeIndex(&filetype);
            if (SUCCEEDED(hr) && filetype && filetype <= (quint32)filterList.length()) {
                // This is a one-based index, not zero-based.
                *selectedFilter = filterList[filetype-1];
            }
        }
    }
    if (pfd)
        pfd->Release();
    return result;
}