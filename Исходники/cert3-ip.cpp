void ip_run32test(GOST gg, byte to[CT32][BS], byte key[KL])
{
	byte tt1[BS], tt2[BS];
	byte ip[4];
	u32bit i, j;

	cout << "Test key:" << endl;
	for (i = 0; i < 8; i++)
	{
		cout << "X" << i << "  " 
			<< hex << setfill('0') << setw(2)
			<< (int)key[4*i+3] << "  "
			<< hex << setfill('0') << setw(2)
			<< (int)key[4*i+2] << "  "
			<< hex << setfill('0') << setw(2)
			<< (int)key[4*i+1] << "  "
			<< hex << setfill('0') << setw(2)
			<< (int)key[4*i]
			<< endl;
	}	
	cout << endl;
		
	gg.set_key(key, KL);		

	// Output open data
	cout << "Open data:" << endl;
	for ( j = 0; j < CT32; j++)
	{
		cout << "To" << dec << setfill('0') << setw(2) << j+1 << "  ";
		for (i = 8; i > 0; i--)
			cout << hex << setfill('0') << setw(2) 
				 << (int)to[j][i-1] << " ";
		cout << endl;
	}
	cout << endl;

	// Make Imito-Pristavka
	gg.encrypt(to[0], tt1);
	for (j = 1; j < CT32; j++)
	{
		xor_buf(tt2, tt1, to[j], BS);
		gg.encrypt(tt2, tt1);
	}

	for (i = 0; i < 4; i++)
		ip[i] = tt1[i];

	cout << "I32   ";
	for (i = 4; i > 0; i--)
		cout << hex << setfill('0') << setw(2) 
			 << (int)ip[i-1] << " ";
	cout << endl;
}