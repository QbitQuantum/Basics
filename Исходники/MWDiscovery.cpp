CMWDiscovery::CMWDiscovery(IDispatch* pDispatch) :
    m_hwnd(0), m_pReportManager(NULL), m_pDocDispatch(pDispatch), m_bHasPassword(false)
{
    Excel::_WorkbookPtr spWorkBook;
    spWorkBook = m_pDocDispatch;
    if(spWorkBook)
    {
        m_officeType = OfficeApplicationType::Excel;
        m_name = PathFindFileNameW(spWorkBook->FullName);
        m_bHasPassword = spWorkBook->GetHasPassword() == VARIANT_TRUE;
        return;
    }

    PowerPoint::_PresentationPtr spPresentation = pDispatch;
    if(spPresentation)
    {
        m_officeType = OfficeApplicationType::PowerPoint;
        PowerPoint::_ApplicationPtr pPptApp = spPresentation->Application;
        // hopefully PowerPoint 14 will give a new way to get the App HWND?
#pragma warning (push)
#pragma warning (disable : 4312)
        m_hwnd = reinterpret_cast<HWND>(pPptApp->GetHWND());
#pragma warning (pop)
        return;
    }

    Word::_DocumentPtr spDocument;
    spDocument = m_pDocDispatch;
    if(spDocument)
    {
        m_officeType = OfficeApplicationType::Word;
    }
}