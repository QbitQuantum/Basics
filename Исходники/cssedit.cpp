void CSSEdit::colorSelectClicked()
{
    QToolButton *colorButton;
    QString propertyName;
    if (sender() == m_colorButton)
    {
        colorButton = m_colorButton;
        propertyName = "color";
    }
    else if (sender() == m_backgroundButton)
    {
        colorButton = m_backgroundButton;
        propertyName = "background-color";
    }
    else
        return;

    if (! m_elements.contains(m_currentElement))
        return;
    Element *element = &m_elements[m_currentElement];
    Element parentElement = getParentElement(m_currentElement);
    QColor color = QColorDialog::getColor(QColor(colorButton->text()), this);
    if (color.isValid())
    {
        colorButton->setText(color.name());
        QPalette palette = colorButton->palette();
        palette.setColor(QPalette::Normal, QPalette::ButtonText, color);
        colorButton->setPalette(palette);
        if (parentElement[propertyName] == color.name())
            element->remove(propertyName);
        else
            element->insert(propertyName, color.name());
        updatePreview();
    }
}