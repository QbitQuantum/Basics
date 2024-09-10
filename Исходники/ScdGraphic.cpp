CDocument* GetGrfDoc(int index, LPCTSTR name)
{
    bool Done=false;
    CDocument* pDoc=NULL;
    int GrfDocCnt=-1;
    CDocTemplate &Templ = ScdApp()->GraphTemplate();
    POSITION PosD = Templ.GetFirstDocPosition();
    while (!Done && PosD)
    {
        pDoc = Templ.GetNextDoc(PosD);
        POSITION pos = pDoc->GetFirstViewPosition();
        if (pos)
        {
            CView* pFirstView = pDoc->GetNextView(pos);
            CWnd* w = pFirstView->GetParent();
//      if (pDoc->IsKindOf(RUNTIME_CLASS(CGrfDoc)))
            if (dynamic_cast<CGrfDoc*>(pDoc))
            {
                //ASSERT(dynamic_cast<CGrfFrameWnd*>(w));
                GrfDocCnt++;
                if (index<0 && pDoc->GetTitle().CompareNoCase(name)==0)
                    Done = true;
                else if (GrfDocCnt==index)
                    Done = true;
            }
        }
    }
    if (!Done)
        return NULL;
    return pDoc;
}