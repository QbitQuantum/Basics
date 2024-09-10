/*
====================
GenerateMegaMipMaps
====================
*/
void	idMegaTexture::GenerateMegaMipMaps( megaTextureHeader_t *header, idFile *outFile ) {
	outFile->Flush();

	// out fileSystem doesn't allow read / write access...
	idFile	*inFile = fileSystem->OpenFileRead( outFile->GetName() );

	int	tileOffset = 1;
	int	width = header->tilesWide;
	int	height = header->tilesHigh;

	int		tileSize = header->tileSize * header->tileSize * 4;
	byte	*oldBlock = (byte *)_alloca( tileSize );
	byte	*newBlock = (byte *)_alloca( tileSize );

	while ( width > 1 || height > 1 ) {
		int	newHeight = (height+1) >> 1;
		if ( newHeight < 1 ) {
			newHeight = 1;
		}
		int	newWidth = (width+1) >> 1;
		if ( width < 1 ) {
			width = 1;
		}
		common->Printf( "generating %i x %i block mip level\n", newWidth, newHeight );

		int		tileNum;

		for ( int y = 0 ; y < newHeight ; y++ ) {
			common->Printf( "row %i\n", y );
			session->UpdateScreen();

			for ( int x = 0 ; x < newWidth ; x++ ) {
				// mip map four original blocks down into a single new block
				for ( int yy = 0 ; yy < 2 ; yy++ ) {
					for ( int xx = 0 ; xx< 2 ; xx++ ) {
						int	tx = x*2 + xx;
						int ty = y*2 + yy;

						if ( tx > width || ty > height ) {
							// off edge, zero fill
							memset( newBlock, 0, sizeof( newBlock ) );
						} else {
							tileNum = tileOffset + ty * width + tx;
							inFile->Seek( tileNum * tileSize, FS_SEEK_SET );
							inFile->Read( oldBlock, tileSize );
						}
						// mip map the new pixels
						for ( int yyy = 0 ; yyy < TILE_SIZE / 2 ; yyy++ ) {
							for ( int xxx = 0 ; xxx < TILE_SIZE / 2 ; xxx++ ) {
								byte *in = &oldBlock[ ( yyy * 2 * TILE_SIZE + xxx * 2 ) * 4 ];
								byte *out = &newBlock[ ( ( ( TILE_SIZE/2 * yy ) + yyy ) * TILE_SIZE + ( TILE_SIZE/2 * xx ) + xxx ) * 4 ];
								out[0] = ( in[0] + in[4] + in[0+TILE_SIZE*4] + in[4+TILE_SIZE*4] ) >> 2;
								out[1] = ( in[1] + in[5] + in[1+TILE_SIZE*4] + in[5+TILE_SIZE*4] ) >> 2;
								out[2] = ( in[2] + in[6] + in[2+TILE_SIZE*4] + in[6+TILE_SIZE*4] ) >> 2;
								out[3] = ( in[3] + in[7] + in[3+TILE_SIZE*4] + in[7+TILE_SIZE*4] ) >> 2;
							}
						}

						// write the block out
						tileNum = tileOffset + width * height + y * newWidth + x;
						outFile->Seek( tileNum * tileSize, FS_SEEK_SET );
						outFile->Write( newBlock, tileSize );

					}
				}
			}
		}
		tileOffset += width * height;
		width = newWidth;
		height = newHeight;
	}

	delete inFile;
}