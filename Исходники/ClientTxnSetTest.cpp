            void ClientTxnSetTest::testAddRemove() {
                ISet<std::string> s = client->getSet<std::string>("testAddRemove");
                s.add("item1");

                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalSet<std::string> set = context.getSet<std::string>("testAddRemove");
                assertTrue(set.add("item2"));
                assertEqual(2, set.size());
                assertEqual(1, s.size());
                assertFalse(set.remove("item3"));
                assertTrue(set.remove("item1"));

                context.commitTransaction();

                assertEqual(1, s.size());
            }