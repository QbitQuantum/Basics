bool FileItem::refresh(const Interface::Adaptor<IStorage> &storage)
{
    if (!m_file.isValid())
    {
        m_file = storage->file()->as<IDirectory>()->entry(value().value().asString());

        if (m_file.isValid())
        {
            m_name = toUnicode(m_file->as<IEntry>()->title());
            m_icon.addFile(toUnicode(m_file->as<IEntry>()->type()->icon()->as<IEntry>()->location()), QSize(16, 16));
            m_toolTip = toUnicode(m_file->as<IEntry>()->type()->name());

            return true;
        }
    }

    return false;
}