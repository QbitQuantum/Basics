static void usage( const char * exe_name )
{
	if( NULL == exe_name )
		return;
	
	_fprintf_p( stderr,
			"Usage:\n"
			"  %1$s gen-key < 128 | 192 | 256 > <key_file>\n"
			"\n"
			"  %1$s <base64_command> [options]\n"
			"\n"
			"    base64_command:\n"
			"      base64-enc: encode\n"
			"      base64-dec:  decode\n"
			"\n"
			"    options:\n"
			"      --in <path_in>\n"
			"      --out <path_out>\n"
			"\n"
			"  %1$s <aes_command> --key <base64_encoded_key_data> [options]\n"
			"  %1$s <aes_command> --key-file <key_file> [options]\n"
			"\n"
			"    aes_command:\n"
			"      aes-enc: encrypt\n"
			"      aes-dec:  decrypt\n"
			"\n"
			"    options:\n"
			"      --ecb: use ecb mode instead of cbc\n"
			"      --in <path_in>\n"
			"      --out <path_out>\n"
			"\n",
			exe_name
	);
}