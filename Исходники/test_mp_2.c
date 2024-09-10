/*
 * Implementing second part of secure MP protocol. This function reads the input file containing the two encrypted products seperated by a newline, decrypts them, multiplies them and again encrypts their 
 * product and writes to the output file. If the other party has n documents in its collection, this should be called n times by the native Jav API i.e. this acts per remotely-based collection document.
 * */
int read_decrypt_mul_encrypt_write_encrypted_rand_prod( const char * input_interm_prods_file_name, const char * output_encrypt_rand_prod_file_name, const char * key_file_name)
{
	mpz_t tfidf_prod1;	//holds input randomized, encrypted tfidf vector products
	mpz_t coord_prod2;	//holds input randomized, encrypted binary vector products
	mpz_t out_enc_ran_prod;	//holds the encrypted product of tfidf_prod1, coord_prod2

	FILE *input_interm_prods_file=NULL, *output_encrypt_rand_prod_file=NULL;


	input_interm_prods_file = fopen(input_interm_prods_file_name, "r");
	output_encrypt_rand_prod_file = fopen(output_encrypt_rand_prod_file_name, "w");

	strncpy(g_key_file_name, key_file_name, sizeof(g_key_file_name));

	//Initialize
	mpz_init(tfidf_prod1);
	mpz_init(coord_prod2);

	mpz_init(out_enc_ran_prod);

	init();

	//variables are set to 0

	//init();



	//check if files are opened properly
	if (input_interm_prods_file == NULL) {
		printf("\n%s", "Error: open %s!", input_interm_prods_file_name);
		return -2;
	}

	if (output_encrypt_rand_prod_file == NULL) {
		printf("\n%s", "Error: open %s!", output_encrypt_rand_prod_file_name);
		return -2;
	}

	//Read the product values
	//File structure can be found in the Java function in which it is written i.e. 
	//<Class_name>:<function_name> :: DocSimSecApp:acceptIntermValues()
	gmp_fscanf(input_interm_prods_file, "%Zd", tfidf_prod1);
	gmp_fscanf(input_interm_prods_file, "%Zd\n", coord_prod2);

	gmp_fprintf(stderr, "TFIDF Product read = %Zd\n\n", tfidf_prod1);
	gmp_fprintf(stderr, "Co-ord Product read = %Zd\n\n", coord_prod2);

	//Decrypt both
	decrypt(tfidf_prod1);
	decrypt(coord_prod2);

	gmp_fprintf(stderr, "After decrypting, TFIDF Product read = %Zd\n\n", tfidf_prod1);
	gmp_fprintf(stderr, "After decrypting, Co-ord Product read = %Zd\n\n", coord_prod2);


	//Multiply both
	mpz_mul(out_enc_ran_prod, tfidf_prod1, coord_prod2);
	mpz_mod(out_enc_ran_prod, out_enc_ran_prod, n);
	
	gmp_fprintf(stderr, "Unencrypted Product = %Zd\n\n", out_enc_ran_prod);

	//note obtained product is not encrypted, hence, encrypting it
	encrypt_big_num(out_enc_ran_prod, out_enc_ran_prod);
	gmp_fprintf(stderr, "Encrypted Product = %Zd\n\n", out_enc_ran_prod);
	gmp_fprintf(output_encrypt_rand_prod_file, "%Zd", out_enc_ran_prod);

	fflush(output_encrypt_rand_prod_file);
	fclose(input_interm_prods_file);
	fclose(output_encrypt_rand_prod_file);


	mpz_clear(tfidf_prod1);
	mpz_clear(coord_prod2);
	mpz_clear(out_enc_ran_prod);
	clear();

	return 0;
}