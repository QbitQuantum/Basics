// ----------------------------------------------------------------------------
// DrawToDCClipped - play back the op list to the DC but clip any objects
//                   known to be not in rect.  This is a coarse level of 
//                   clipping to speed things up when lots of objects are off 
//                   screen and doesn't affect the dc level clipping
// ----------------------------------------------------------------------------
void wxPseudoDC::DrawToDCClipped(wxDC *dc, const wxRect& rect)
{
    pdcObjectList::Node *pt = m_objectlist.GetFirst();
    pdcObject *obj;
    while (pt) 
    {
        obj = pt->GetData();
        if (!obj->IsBounded() || rect.Intersects(obj->GetBounds()))
            obj->DrawToDC(dc);
        pt = pt->GetNext();
    }
}