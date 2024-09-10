void   CStaticTrans::UpdateCtrl() 
{ 
        CWnd*   pParent   =   GetParent(); 
        CRect   rect; 
        
        GetWindowRect(rect); 
        pParent->ScreenToClient(rect); 
        rect.DeflateRect(2,   2); 
        
        pParent->InvalidateRect(rect,   FALSE);         
} 