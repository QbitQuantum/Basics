void ComponentItem::SetText(IComponent *comp)
{
    if (ptr.lock().get() != comp)
        LogWarning("ComponentItem::SetText: the component given is different than the component this item represents.");

    QString compType = IComponent::EnsureTypeNameWithoutPrefix(comp->TypeName());
    QString name = QString("%1 %2").arg(compType).arg(comp->Name());

    setTextColor(0, QColor(Qt::black));

    QString localText = QApplication::translate("ComponentItem", "Local");
    QString temporaryText = QApplication::translate("ComponentItem", "Temporary");
    QString localOnlyText = QApplication::translate("ComponentItem", "UpdateMode:LocalOnly");
    QString disconnectedText = QApplication::translate("ComponentItem", "UpdateMode:Disconnected");

    const bool sync = comp->IsReplicated();
    const bool temporary = comp->IsTemporary();

    QString info;
    if (!sync)
    {
        setTextColor(0, QColor(Qt::blue));
        info.append(localText);
    }

    if (temporary)
    {
        setTextColor(0, QColor(Qt::red));
        if (!info.isEmpty())
            info.append(" ");
        info.append(temporaryText);
    }

    if (comp->UpdateMode() == AttributeChange::LocalOnly)
    {
        if (!info.isEmpty())
            info.append(" ");
        info.append(localOnlyText);
    }

    if (comp->UpdateMode() == AttributeChange::Disconnected)
    {
        if (!info.isEmpty())
            info.append(" ");
        info.append(disconnectedText);
    }

    if (!info.isEmpty())
    {
        info.prepend(" (");
        info.append(")");
        setText(0, name + info);
    }
    else
        setText(0, name);
}