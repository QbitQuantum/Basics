OIS::MouseEvent OgreFramework::_adjustMousePosition(const OIS::MouseEvent &evt)
{
    CRect rcParent;
    CRect rcView;

    CWnd* pWnd = AfxGetMainWnd();
    pWnd->GetWindowRect(&rcParent);

    GetWindowRect(_hWnd, &rcView);

    static OIS::MouseState	ms;
    ms = evt.state;
    ms.X.abs	-= rcView.left;
    ms.Y.abs	-= rcView.top;
    ms.X.abs	+= rcParent.left;
    ms.Y.abs	+= rcParent.top;

    return OIS::MouseEvent(const_cast<OIS::Object*>(evt.device), ms);
}