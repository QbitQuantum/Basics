void SDLMouseCursor::load( ImageObject& img, const int& hotspotX, const int& hotspotY, const Color& transparentColor, const Color& invertColor )
{
	if ( imageIsSystemCursor( &img ) ) {

		Uint8* data = new Uint8[ (int)ceil( (double)(img.width() * img.height()) / 8 ) ];
		Uint8* mask = new Uint8[ (int)ceil( (double)(img.width() * img.height()) / 8 ) ];

		int bit = 1;
		int i = -1;

		Color black( 0, 0, 0 );
		Color white( 255, 255, 255 );
		//cout << "Cursor:" << endl;
		for( int y = 0; y < img.height(); y++ ) {
			for( int x = 0; x < img.width(); x++ ) {
				Color c = img.getPixel( x, y );

				if ( bit == 128 ) {
					bit = 64;
				}
				else if ( bit == 64 )
					bit = 32;
				else if ( bit == 32 )
					bit = 16;
				else if ( bit == 16 )
					bit = 8;
				else if ( bit == 8 )
					bit = 4;
				else if ( bit == 4 )
					bit = 2;
				else if ( bit == 2 )
					bit = 1;
				else if ( bit == 1 ) {
					bit = 128;
					i++;
					data[i] = 0;
					mask[i] = 0;
				}

				if ( c == white ) {
					//cout << ".";
					mask[i] |= bit;
				} else if ( c == black ) {
					//cout << "X";
					data[i] |= bit;
					mask[i] |= bit;
				} else if ( c == invertColor ) {
					//cout << "0";
					data[i] |= bit;
				} else {
					//cout << " ";
				}
			}
			//cout << endl;
		}
		pCursor = SDL_CreateCursor( data, mask, img.width(), img.height(), hotspotX, hotspotY );

		delete[] mask;
		delete[] data;

	} else {
	}
}