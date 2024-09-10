BOOL kiwi_krbcred_valid_header(OssBuf *input)
{
	return ((input->length > 4) && (_byteswap_ushort(*(PUSHORT) input->value) == 0x7682));
}