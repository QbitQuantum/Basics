	TEST<1>() {
		set_test_name("client connect fails because IP address is invalid format");
		const auto bad_ip = "127_0_0_1";
		try {
			Socket soc;
			soc.connect(bad_ip,9999);
			fail("exception not thrown");
		} catch (std::runtime_error &ex) {
			ensure_contains(ex,bad_ip);
		}
	}