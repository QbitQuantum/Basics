//! Sets the node to the given filepath.
//! \note This function uses `SHCreateItemFromParsingName()`, which is limited to `MAX_PATH` (260) chars.
bool ShellNodeInfo::setNode(QString filepath)
{
    wchar_t converted[MAX_PATH] = {'\0'};
    // maybe some day
    /*
    auto converted = QVarLengthArray<wchar_t, MAX_PATH>();
    if (filepath.length() > MAX_PATH) {
        if (!filepath.startsWith(detail::longPathPrefix))
            filepath.prepend(detail::longPathPrefix);
        converted.reserve(filepath.length());
    }*/
    if (filepath.length() > MAX_PATH - 1) {
        qDebug() << "Can't add paths longer than 260 literals to the shell.";
        d.reset();
        return false;
    }

    //Actually copy the string
    Q_ASSERT(filepath.toWCharArray(converted) > 0);

    auto item = ShellItem2Pointer();
    SHCreateItemFromParsingName(converted, nullptr, IID_PPV_ARGS(item.addressOf()));
    if (!item) {
        qDebug() << "Failed to create NodeInfo from path: " << filepath;
        return false;
    }
    d = ShellNodeData::create(item);
    refresh();
    return true;
}