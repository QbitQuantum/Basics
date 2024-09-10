StripperWindow::StripperWindow(QTreeWidget *parent, HWND hwnd):
        QTreeWidgetItem(parent, QTreeWidgetItem::Type)
{
    //stubbed out.
    handle = hwnd;

    HICON icon_handle = (HICON)GetClassLongPtr(handle, GCLP_HICON);
    //pre-empt the "failed to GetIconInfo() error" so it speeds through quickly.
    ICONINFO dummy;
    if(!GetIconInfo(icon_handle, &dummy)) {
        icon = QPixmap();
    } else {
        icon = QPixmap::fromWinHICON(icon_handle);
    }

    LPWSTR lpwstr_buf = (WCHAR*)calloc(sizeof(WCHAR), 255);
    GetWindowText(hwnd, lpwstr_buf, 255);
    title = QString::fromWCharArray(lpwstr_buf, 255);
    free(lpwstr_buf);

    borderless_p = false;

    //this might seem like duplication...
    setData(0, Qt::DecorationRole, QVariant(icon));
    setData(1, Qt::DisplayRole, QVariant(title));
    setFont(1, QFont(QString("Verdana"), 0, QFont::Bold, false));
    setData(2, Qt::CheckStateRole, QVariant(StrippedP()));
}