void HashTable::rebuildTable(unsigned int newSize, HashFunction *hashFunct)
{
    List **oldTable = table;
    unsigned int oldSize = hTsize;
    hTsize = newSize;
    createTable();
    collisions = 0;
    maxCollLength = 0;
    LoadFactor = 0;
    elemQuantity = 0;
    delete hash;
    hash = hashFunct;
    for (unsigned int i = 0; i < oldSize; i++)
    {
        if (oldTable[i] != NULL && !oldTable[i]->isEmpty())
        {
            ListElement *temp = oldTable[i]->getHead();
            while (temp->getNext() != NULL)
            {
                add(temp->getStr(), temp->getElemCounter());
                temp = temp->getNext();
            }
            add(temp->getStr(), temp->getElemCounter());
        }
    }
    for (int i = 0; i < hTsize; i++)
		delete oldTable[i];
    delete[] oldTable;
}