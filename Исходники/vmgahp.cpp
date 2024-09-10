void
VMGahp::printAllReqsWithResult()
{
	char *one_result = NULL;
	MyString output;
	m_result_list.rewind();
	while( (one_result = m_result_list.next()) != NULL ) {
		output = one_result;
		output += "\n";
		write_to_daemoncore_pipe(vmgahp_stdout_pipe,
				output.Value(), output.Length());
		m_result_list.deleteCurrent();
	}
}