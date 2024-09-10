/*!
    Sets the label's color to follow the theme.
 */
void SnsrLabel::setThemedTextColor()
{
    QColor textColor(HbColorScheme::color(SnsrColors::WidgetColorRole.latin1()));
    if (textColor.isValid()) {
        setTextColor(textColor);
    } else {
        // fallback mechanism when color definition is missing in default theme
        setTextColor(Qt::white);
    }
}