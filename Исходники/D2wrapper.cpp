void freeD2Libraries()
{
	log_msg("***** Free Libraries *****\n");

	freeLibrary( offset_SmackW32 );
	freeLibrary( offset_D2Common );
	freeLibrary( offset_ijl11 );
	freeLibrary( offset_D2Gdi );
	freeLibrary( offset_D2Win );
	freeLibrary( offset_D2sound );
//	freeLibrary( offset_D2Multi );
//	freeLibrary( offset_D2MCPCLI );
	freeLibrary( offset_D2Launch );
	freeLibrary( offset_D2gfx );
	freeLibrary( offset_D2Game );
	freeLibrary( offset_D2Client );
	freeLibrary( offset_D2Net );
	freeLibrary( offset_D2Lang );
	freeLibrary( offset_D2CMP );
	freeLibrary( offset_Bnclient );
	freeLibrary( offset_Fog	);
	freeLibrary( offset_Storm );

	log_msg("\n\n");
}