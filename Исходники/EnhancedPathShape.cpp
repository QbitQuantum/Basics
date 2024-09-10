void EnhancedPathShape::modifyReference(const QString &reference, qreal value)
{
    if (reference.isEmpty())
        return;

    QChar c = reference[0];

    if (c.toAscii() == '$') {
        bool success = false;
        int modifierIndex = reference.mid(1).toInt(&success);
        if (modifierIndex >= 0 && modifierIndex < m_modifiers.count())
            m_modifiers[modifierIndex] = value;
    }
}