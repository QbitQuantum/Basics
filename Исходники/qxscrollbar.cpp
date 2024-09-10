void TQXheadercomp_scrollbar::OnMouseMove(UINT nFlags, int px, int py)
{
    int prt=G_partatpos(px,py);
    if ((prt!=curpart)&&((!pressing)||(curpart==1)||(curpart==2)))
    {
        curpart=prt;
        parent->Invalidate(0);
        parent->UpdateWindow();
        if (curpart>=0)
        {
            if (parent->GetCapture()!=parent) parent->SetCapture();
        }
        else
        {
            if (parent->GetCapture()==parent) ReleaseCapture();
        }
    }
    if ((curpart==0)&&(pressing))
    {
        if (dir==DIR_VERT) setscrollpos(pos2scroll(py+ps0dff));
        if (dir==DIR_HOR) setscrollpos(pos2scroll(px+ps0dff));
    }
}