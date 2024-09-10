void LatexDocVisitor::visitPre(DocImage *img)
{
    if (img->type()==DocImage::Latex)
    {
        if (m_hide) return;
        QCString gfxName = img->name();
        if (gfxName.right(4)==".eps" || gfxName.right(4)==".pdf")
        {
            gfxName=gfxName.left(gfxName.length()-4);
        }

        visitPreStart(m_t,img->hasCaption(), gfxName, img->width(),  img->height());
    }
    else // other format -> skip
    {
        pushEnabled();
        m_hide=TRUE;
    }
}