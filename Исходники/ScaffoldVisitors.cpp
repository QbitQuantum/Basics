ScaffoldWriterVisitor::ScaffoldWriterVisitor(const std::string& filename)
{
    m_pWriter = createWriter(filename);
}