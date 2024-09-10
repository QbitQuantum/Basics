void WalletApi::TestSendMoney(int64_t transferAmount, uint64_t fee, uint64_t mixIn, const std::string& extra) {
  prepareBobWallet();

  alice->initAndGenerate("pass");

  ASSERT_NO_FATAL_FAILURE(WaitWalletSync(aliceWalletObserver.get()));
  ASSERT_NO_FATAL_FAILURE(GetOneBlockReward(*alice));

  //unblock Alice's money
  generator.generateEmptyBlocks(10);
  uint64_t expectedBalance = TEST_BLOCK_REWARD;

  aliceNode->updateObservers();

  ASSERT_NO_FATAL_FAILURE(WaitWalletSync(aliceWalletObserver.get()));

  EXPECT_EQ(0, alice->pendingBalance());
  EXPECT_EQ(expectedBalance, alice->actualBalance());

  EXPECT_EQ(expectedBalance, aliceWalletObserver->actualBalance);
  EXPECT_EQ(0, aliceWalletObserver->pendingBalance);

  bob->initAndGenerate("pass2");

  ASSERT_NO_FATAL_FAILURE(WaitWalletSync(bobWalletObserver.get()));

  ASSERT_NO_FATAL_FAILURE(TransferMoney(*alice, *bob, transferAmount, fee, 0, ""));

  generator.generateEmptyBlocks(10);

  aliceNode->updateObservers();
  ASSERT_NO_FATAL_FAILURE(WaitWalletSync(aliceWalletObserver.get()));

  bobNode->updateObservers();
  ASSERT_NO_FATAL_FAILURE(WaitWalletSync(bobWalletObserver.get()));

  EXPECT_EQ(0, bob->pendingBalance());
  EXPECT_EQ(transferAmount, bob->actualBalance());

  EXPECT_EQ(0, alice->pendingBalance());
  EXPECT_EQ(expectedBalance - transferAmount - fee, alice->actualBalance());

  alice->shutdown();
  bob->shutdown();
}