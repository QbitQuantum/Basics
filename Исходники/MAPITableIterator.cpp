MAPITableIterator::~MAPITableIterator()
{
    if (m_pRows != NULL)
        FreeProws(m_pRows);
}