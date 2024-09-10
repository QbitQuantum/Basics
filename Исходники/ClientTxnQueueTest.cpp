            TEST_F(ClientTxnQueueTest, testTransactionalOfferPoll2) {
                util::CountDownLatch latch(1);
                util::Thread t(testTransactionalOfferPoll2Thread, &latch, client.get());
                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalQueue<std::string> q0 = context.getQueue<std::string>("defQueue0");
                TransactionalQueue<std::string> q1 = context.getQueue<std::string>("defQueue1");
                boost::shared_ptr<std::string> s;
                latch.countDown();
                s = q0.poll(10 * 1000);
                ASSERT_EQ("item0", *s);
                ASSERT_TRUE(q1.offer(*s));

                ASSERT_NO_THROW(context.commitTransaction());

                ASSERT_EQ(0, client->getQueue<std::string>("defQueue0").size());
                ASSERT_EQ("item0", *(client->getQueue<std::string>("defQueue1").poll()));
            }