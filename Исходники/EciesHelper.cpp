bool EciesHelper::Decrypt(const ByteArray &chiper, ByteArray &plain)
{
	assert (valid_);
	try { 
		DER der(chiper);
		ECIES decrypt = der.toECIES();
		OCTETSTR temp = decrypt.decrypt(*sk_);	
		plain = toByteArray(temp);
		return true;
	} catch (borzoiException e) { 
		//e.debug_print ();
		return false;
	}
}