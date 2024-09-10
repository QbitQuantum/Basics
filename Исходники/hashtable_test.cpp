TEST(hashtable_test, simple_condition)
{
    HashTable *hashtable = new HashTable(4);
    EXPECT_EQ(hashtable->find(1, 5), -1);
    hashtable->insert(1, 5, 7);
    EXPECT_EQ(hashtable->find(1, 5), 7);
    hashtable->insert(2, 4, 8);
    hashtable->remove(1, 5);
    EXPECT_EQ(hashtable->find(1, 5), -1);
    delete hashtable;
}