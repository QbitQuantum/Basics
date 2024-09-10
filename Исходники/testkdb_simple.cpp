TEST_F (Simple, GetAppendNamespaces)
{
	using namespace kdb;
	for (size_t i = 0; i < namespaces.size (); ++i)
	{
		KDB kdb;
		KeySet ks;
		ks.append (Key (namespaces[i].name + testRoot + "key", KEY_END));
		kdb.get (ks, testRoot);
		ASSERT_EQ (ks.size (), 1) << "did not got key appended first with namespace " << namespaces[i].name;
		ks.rewind ();
		ks.next ();
		EXPECT_EQ (ks.current ().getName (), namespaces[i].name + "/tests/kdb/key") << "name of element in keyset wrong";
		EXPECT_EQ (ks.current ().getString (), "") << "string of element in keyset wrong";
	}
}