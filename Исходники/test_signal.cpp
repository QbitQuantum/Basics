TEST(SignalTest, ConnectionOwn) {
	unsigned counter = 0;
	auto f = [&counter]() { ++counter; };

	Signal<> sig;

	ConnectionRef c0;
	{
		ConnectionRef tmp = sig.connect(f);
		tmp.own();
		c0 = tmp;
		ASSERT_TRUE(tmp.isOwning());
		ASSERT_FALSE(c0.isOwning());

		sig();
		ASSERT_EQ(1, counter);
	}
	ASSERT_TRUE(c0.isValid());
	ASSERT_FALSE(c0.isConnected());

	sig();
	ASSERT_EQ(1, counter);
}