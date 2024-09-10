            TEST_F(ClientTxnTest, testTxnRollback) {
                util::CountDownLatch memberRemovedLatch(1);
                std::string queueName = "testTxnRollback";
                MyLifecycleListener myLifecycleListener(memberRemovedLatch);
                client->getCluster().addMembershipListener(&myLifecycleListener);

                TransactionContext context = client->newTransactionContext();
                context.beginTransaction();
                TransactionalQueue<std::string> queue = context.getQueue<std::string>(queueName);
                queue.offer("item");
                server->shutdown();

                ASSERT_THROW(context.commitTransaction(), exception::IException);

                context.rollbackTransaction();

                ASSERT_TRUE(memberRemovedLatch.await(10));

                IQueue<std::string> q = client->getQueue<std::string>(queueName);
                try {
                    ASSERT_EQ(0, q.size());
                    ASSERT_EQ(q.poll().get(), (std::string *)NULL);
                } catch (exception::IException& e) {
                    std::cout << e.what() << std::endl;
                }
            }