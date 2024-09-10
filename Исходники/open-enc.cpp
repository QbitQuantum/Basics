CStr EVP_decrypt(CStr passw, CStr strin, const char *cipher)
{
	int len = strin.Length();
	if (len > 0 && passw.Length() > 0) {
		strin.Grow(len + EVP_MAX_IV_LENGTH);
		return strin.Grow(
			EVP_decrypt(passw.SafeP(), passw.Length(), strin.GetBuffer(), len, cipher)
		);
	} else
		return strin;
}