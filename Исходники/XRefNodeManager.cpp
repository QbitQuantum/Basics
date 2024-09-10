StringBuffer &CXRefNode::serializeDirectories(StringBuffer &buf)
{
    if(!m_directories.get())
    {
        IPropertyTree* directoriesBranch = m_XRefTree->queryPropTree("Directories");
        if(directoriesBranch == 0)
        {
            directoriesBranch = m_XRefTree->addPropTree("Directories",createPTree());
            commit();
        }
        StringBuffer tmpbuf;
        m_directories.set(directoriesBranch);
    }
    buf.clear();
    MemoryBuffer data;
    m_directories->getPropBin("data",data);
    if (data.length())
    {
        buf.append(data.length(),data.toByteArray());
    }
    return buf;
}