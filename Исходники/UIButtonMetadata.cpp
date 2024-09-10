QColor UIButtonMetadata::GetFontColorForState(UIControl::eControlState state) const
{
    UIStaticText* referenceButtonText = GetActiveUIButton()->GetStateTextControl(state);
    if (referenceButtonText)
    {
		return DAVAColorToQTColor(referenceButtonText->GetTextColor());
    }
    
    return QColor();
}