int main(int argc, char** argv){
	
	unsigned int max = atoi( argv[1] );

	BigInteger n(n_digits,1);

	for(unsigned int i=2; i<=max; i++){
		BigInteger *add = Pow(i,i);
		n.Add(*add);
		delete add; add = NULL;
	}
	
	n.Print();

	
	return 0;
}