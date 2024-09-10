int main ()
{
    HashTable *hashTable = createTable(hashConst, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);
    hashTable = createTable(hashCountCodes, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);
    hashTable = createTable(hashGood, SIZE);
    textAnalyzer(hashTable);
    stat(hashTable);
    freeTable(hashTable);

}