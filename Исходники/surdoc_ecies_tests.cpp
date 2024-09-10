void dec_data(const std::string &encdata, ECPrivKey &sk)
{
	OCTETSTR bytes;
	hexstr_to_octstr(encdata, bytes);
	try { 
		DER der2(bytes);
		ECIES decrypt = der2.toECIES();
		OCTETSTR plain2 = decrypt.decrypt(sk);	
		std::cout << "decrpyted data: " << std::endl;
		for (int i=0; i<plain2.size(); i++)
			std::cout << plain2[i];
		std::cout << std::endl;
	} catch (borzoiException e) { 
		e.debug_print ();
		return;
	}
}