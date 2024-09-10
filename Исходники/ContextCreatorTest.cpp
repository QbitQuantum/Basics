TEST_F(ContextCreatorTest, ValidateSimpleEviction) {
  // Create a context and verify it gets evicted from the context creator:
  AutoRequired<Creator> creator;
  std::weak_ptr<CoreContext> ctxtWeak;

  {
    std::shared_ptr<CoreContext> ctxt;

    // Make a context:
    ctxt = creator->CreateContext(1).first;

    // Obtain a weak pointer, in order to ensure proper teardown:
    ctxtWeak = ctxt;
  }

  // Context must be destroyed as a precondition of the subsequent assertion
  ASSERT_TRUE(ctxtWeak.expired()) << "Expected the context to be destroyed";

  // Verify that our creator is now empty:
  ASSERT_EQ(0UL, creator->GetSize()) << "Context creator is non-empty after all created contexts were destroyed";
}