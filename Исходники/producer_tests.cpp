void handle_error(boost::system::error_code const& error, int expected_error, std::string const& expected_message)
{
	BOOST_CHECK_EQUAL(expected_error, error.value());
	BOOST_CHECK_EQUAL(expected_message, error.message());
}