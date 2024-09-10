                void putGetRemoveTestThread(util::ThreadArgs& args) {
                    MultiMap<std::string, std::string> *mm = (MultiMap<std::string, std::string > *)args.arg0;
                    HazelcastClient *client = (HazelcastClient *)args.arg1;
                    util::CountDownLatch *latch = (util::CountDownLatch *)args.arg2;
                    std::string key = util::IOUtil::to_string(util::Thread::getThreadID());
                    client->getMultiMap<std::string, std::string>("testPutGetRemove").put(key, "value");
                    TransactionContext context = client->newTransactionContext();
                    context.beginTransaction();
                    TransactionalMultiMap<std::string, std::string> originalMultiMap = context.getMultiMap<std::string, std::string >("testPutGetRemove");
                    client::adaptor::RawPointerTransactionalMultiMap<std::string, std::string> multiMap(originalMultiMap);
                    ASSERT_FALSE(multiMap.put(key, "value"));
                    ASSERT_TRUE(multiMap.put(key, "value1"));
                    ASSERT_TRUE(multiMap.put(key, "value2"));
                    ASSERT_EQ(3, (int)multiMap.get(key)->size());
                    context.commitTransaction();

                    ASSERT_EQ(3, (int)mm->get(key).size());

                    latch->countDown();
                }