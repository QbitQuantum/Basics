TEST(HashTableTest, IntKey)  {
	
	HashTable<uint,uint,IntHash> ht;
	
	EXPECT_EQ(0UL,ht.count());
	EXPECT_FALSE(ht.containsKey(1));
	ht.add(1,1);
	EXPECT_EQ(1UL,ht.count());
	EXPECT_TRUE(ht.containsKey(1));
	EXPECT_TRUE(ht.contains(1,1));
	ht[1] = 0;
	EXPECT_TRUE(ht[1] == 0U);
	ht.remove(1);
	EXPECT_EQ(0UL,ht.count());
}