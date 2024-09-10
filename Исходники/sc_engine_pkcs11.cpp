static void _set_pkcs11_error(CK_RV rv, const String& msg)
{
	String emsg;
	emsg.sprintf("%s: %s (0x%0lX)")(msg)(_ckrvToString(rv))(rv);
	jq_emitError(emsg);
}