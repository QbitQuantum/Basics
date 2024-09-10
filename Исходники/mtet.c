void done( void )
{
	v_show_c( handle, 0 );
	v_clsvwk( handle );
	if (score>hiscore)
	{
		puts("\033HSie haben einen neuen Highscore erreicht!");
		printf("Geben Sie Ihren Namen ein: ");
		scanf("%126s",hiname);
		highfile=(int)Fcreate("HISCORE.DAT",0);
		Fwrite(highfile, 4, &score );
		Fwrite(highfile, 128, hiname );
		Fclose(highfile);
	}
}