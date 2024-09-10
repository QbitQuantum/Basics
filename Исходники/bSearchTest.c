void test_4_bsearch_should_not_find_doulbe_value_from_elements(){
	double key=2.5;
	double elements[5]={1.0,2.0,3.0,6.0,8.0};
	ASSERT(NULL==(bSearch(&key,elements,5,sizeof(double),compareDouble)));
}