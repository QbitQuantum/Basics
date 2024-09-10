void CreateElementCommand::redo()
{
    static const ElementFactory factory;

    if (!model() || m_type == Element::ElementType) {
        qCDebug(KDSME_VIEW) << Q_FUNC_INFO << "Can't redo, invalid model or type";
        return;
    }

    Element* parentElement = m_parentElement ? m_parentElement : model()->state();
    StateModel::AppendOperation append(model(), parentElement);
    Element* element = factory.create(m_type);
    if (!element) {
        qCDebug(KDSME_VIEW) << Q_FUNC_INFO << "Element could not be instantiated, type:" << m_type;
        return;
    }

    element->setLabel(tr("Unnamed"));
    element->setParent(parentElement);
    m_createdElement = element;
    updateText();
}