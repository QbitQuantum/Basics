CItem *CDirstatDoc::GetSelectionParent()
{
    ASSERT(m_selectedItems.GetCount() > 0);
    CItem *item = m_selectedItems[0];
    return item->GetParent();
}