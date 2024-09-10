void SipTransactionList::toString(UtlString& string)
{
    lock();

    string.remove(0);

    UtlHashBagIterator iterator(mTransactions);
    SipTransaction* transactionFound = NULL;
    UtlString oneTransactionString;

    while((transactionFound = (SipTransaction*) iterator()))
    {
        transactionFound->toString(oneTransactionString, FALSE);
        string.append(oneTransactionString);
        oneTransactionString.remove(0);
    }

    unlock();
}