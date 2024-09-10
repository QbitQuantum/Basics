            void ClientTxnMapTest::testKeySetValues() {
                std::string name = "testKeySetValues";
                IMap<std::string, std::string> map = client->getMap<std::string, std::string>(name);
                map.put("key1", "value1");
                map.put("key2", "value2");

                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalMap<std::string, std::string> txMap = context.getMap<std::string, std::string>(name);
                assertNull(txMap.put("key3", "value3").get());


                assertEqual(3, (int)txMap.size());
                assertEqual(3, (int)txMap.keySet().size());
                assertEqual(3, (int)txMap.values().size());
                context.commitTransaction();

                assertEqual(3, (int)map.size());
                assertEqual(3, (int)map.keySet().size());
                assertEqual(3, (int)map.values().size());

            }