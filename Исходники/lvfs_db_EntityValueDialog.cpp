EntityValueDialog::EntityValueDialog(const Interface::Adaptor<IStorage> &storage, const EntityValueReader &reader, QWidget *parent) :
    NestedPlainDialog(parent),
    m_handler(this),
    m_mainWidget(storage, reader, &m_handler, this)
{
    init(toQRect(storage->listGeometry(m_mainWidget.entity())));
    setWindowTitle(tr("Values of \"%1\"").arg(toUnicode(m_mainWidget.entity().name())));
}