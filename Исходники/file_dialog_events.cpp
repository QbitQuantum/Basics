IFACEMETHODIMP rusty::controls::FileDialogEvents::QueryInterface(REFIID riid, void** ppv)
{
    #ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4838)
    #endif
    static const QITAB qit[] = {QITABENT(FileDialogEvents, IFileDialogEvents), QITABENT(FileDialogEvents, IFileDialogControlEvents), {0}};
    #ifdef _MSC_VER
    #pragma warning(pop)
    #endif
    return QISearch(this, qit, riid, ppv);
}