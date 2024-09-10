int QmitkNumberPropertyEditor::valueFromText(const QString& text) const
{
    return ROUND( text.toDouble() / m_FactorSpinboxToDisplay );
}