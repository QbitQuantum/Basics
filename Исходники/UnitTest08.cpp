void test_determinant_float_100x100_1()
{
	Array<float> data = read_file_matrix<float>( std::string("unit_tests_files//test_determinant_float_100x100_1//data.txt") );
	
	float control = 2.094843919208893e+03;

	TEST_CALL( abs(data.determinant()), abs(control), BOOST_CURRENT_FUNCTION );
}