//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void BoundingBox::add(const BoundingBox& bb)
{
    if (bb.isValid())
    {
        add(bb.min());
        add(bb.max());
    }
}