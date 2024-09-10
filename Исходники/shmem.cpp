void Shmem::SendVector(
    const Vector::const_iterator& first,
    const Vector::const_iterator& last,
    const int dest_pe)
{
    #ifdef DEBUG
    cout << INDENT(4) << "Shmem::SendVector()..." << endl;
    #endif
    for (auto it = first; it != last; it++)
    {
        const Index index = distance(first, it);
        IndexElemPair p(index, *it);
        #ifdef DEBUG
        cout << INDENT(5) << "Index = " << p.first
            << ", Value = " << p.second << endl;
        #endif
        shmem_send(&p, HandlerNumber(), sizeof(p), dest_pe);
        Stats::SendOpCounterInc();
        Stats::SendDataCounterAdd(sizeof(p));
    }
    #ifdef DEBUG
        cout << INDENT(4) << "Shmem::SendVector() return" << endl;
    #endif
}