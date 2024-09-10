//***************************************************************************************
void CBCGPHeaderCtrl::RemoveSortColumn (int iColumn)
{
    ASSERT_VALID (this);
    m_mapColumnsStatus.RemoveKey (iColumn);
    RedrawWindow ();
}