	string MsDrbg::hash_df_hex(const unsigned char* seed_material,
	                                   const size_t seed_material_size,
									   const size_t seedlen)
	{
		size_t len = seedlen/20 + (seedlen%20 ? 1 : 0);
		string result = "";
		unsigned char hash[20];
		char hexstring[41];
		for(size_t counter=1; counter <= len; ++counter)
		{
			unsigned char* counter_bytes = get_raw_bytes(counter);
			size_t counter_size = sizeof(counter);
			unsigned char* seedlen_bytes = get_raw_bytes(seedlen);
			size_t seedlen_size = sizeof(seedlen_size);
			unsigned char* counter_seedlen_bytes = concatenate(counter_bytes,
			                                                   counter_size, seedlen_bytes,
															   seedlen_size);
			size_t counter_seedlen_size = counter_size + seedlen_size;
			delete[] counter_bytes;
			delete[] seedlen_bytes;

			unsigned char* hash_material = concatenate(counter_seedlen_bytes,
			                                           counter_seedlen_size, seed_material,
													   seed_material_size);
			size_t hash_material_size = counter_seedlen_size + seed_material_size;
			delete[] counter_seedlen_bytes;

			Sha1::calc(hash_material, static_cast<int>(hash_material_size), hash);
			Sha1::to_hex_string(hash, hexstring);
			result += string(hexstring);

			delete[] hash_material;
		}

		return result.substr(0,2*seedlen);
	}