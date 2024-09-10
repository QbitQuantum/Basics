SQLRETURN unixodbc_backend_debug::do_more_results(SQLHSTMT statement_handle) const
{
	std::cout << " *DEBUG* more_results";
	auto const return_code = SQLMoreResults(statement_handle);
	std::cout << " (return code " << return_code << ")" << std::endl;
	return return_code;
}