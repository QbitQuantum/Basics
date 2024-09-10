void CPDF_Annot::GetRect(CPDF_Rect& rect) const
{
    if (m_pAnnotDict == NULL) {
        return;
    }
    rect = m_pAnnotDict->GetRect("Rect");
    rect.Normalize();
}