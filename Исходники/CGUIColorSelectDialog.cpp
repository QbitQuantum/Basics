//! renders a antialiased, colored ring
void CGUIColorSelectDialog::buildColorRing( const core::dimension2d<u32> & dim, s32 supersample, const video::SColor& borderColor )
{
	const core::dimension2d<u32> d(dim.Width * supersample, dim.Height * supersample);
	video::CImage *RawTexture = new video::CImage(video::ECF_A8R8G8B8, d);

	RawTexture->fill ( 0x00808080 );

	const s32 radiusOut = ( d.Width / 2 ) - 4;
	const s32 fullR2 = radiusOut * radiusOut;

	video::SColor rgb(0xFF000000);
	video::SColorHSL hsl;
	hsl.Luminance = 0.5f;
	hsl.Saturation = 1.f;

	core::position2d<s32> p;
	for ( p.Y = -radiusOut;  p.Y <= radiusOut;  p.Y += 1  )
	{
		s32 y2 = p.Y * p.Y;

		for (p.X = -radiusOut; p.X <= radiusOut; p.X += 1)
		{
			s32 r2 = y2 + ( p.X * p.X );

			// test point in circle
			s32 testa = r2 - fullR2;

			if ( testa < 0 )
			{
				// dotproduct u ( x,y ) * v ( 1, 0 ) = cosinus(a)

				const f32 r = sqrtf((f32) r2);

				// normalize, dotproduct = xnorm
				const f32 xn = r == 0.f ? 0.f : -p.X * core::reciprocal(r);

				hsl.Hue = acosf(xn);
				if ( p.Y > 0 )
					hsl.Hue = (2.f * core::PI ) - hsl.Hue;

				hsl.Hue -= core::PI / 2.f;

				const f32 rTest = r / radiusOut;
/*
				if ( rTest < 0.25f )
				{
					hsl.Luminance = rTest / 0.25f;
					hsl.Saturation = 0.f;
					hsl.toRGB  ( rgb );
					*dst = rgb.color;
				}
				else
				if ( rTest < 0.4f )
				{
					hsl.Saturation = ( rTest - 0.25f ) / 0.15f;
					hsl.Luminance = 1.f - ( hsl.Saturation / 2.4f );
					hsl.Luminance = 0.5f;
					hsl.toRGB  ( rgb );
					// *dst = rgb.color;
				}
				else
				if ( rTest < 0.75f )
				{
					hsl.Luminance = 0.5f;
					hsl.Saturation = 1.f;
					hsl.toRGB  ( rgb );
					*dst = rgb.color;
				}
				else
				if ( rTest < 0.98f )
				{
					hsl.Luminance = 0.5f - ( ( rTest - 0.75f ) / 0.75f );
					hsl.Saturation = 1.f;
					hsl.toRGB  ( rgb );
					*dst = rgb.color;
				}
*/

				if ( rTest >= 0.5f )
				{
					hsl.Luminance = 0.5f;
					hsl.Saturation = 1.f;
					hsl.toRGB(rgb);

					if ( rTest <= 0.55f )
					{
						const u32 alpha = (u32) ( (rTest - 0.5f ) * ( 255.f / 0.05f ) );
						rgb.setAlpha(alpha);
					} 
					else if ( rTest >= 0.95f )
					{
						const u32 alpha = (u32) ( (rTest - 0.95f ) * ( 255.f / 0.05f ) );
						rgb.setAlpha(255-alpha);
					}
					else
						rgb.setAlpha(255);
					RawTexture->setPixel(4+p.X+radiusOut, 4+p.Y+radiusOut, rgb);
				}
			}
		}
	}

	RawTexture->unlock ();

	if ( supersample > 1 )
	{
		video::CImage * filter = new video::CImage(video::ECF_A8R8G8B8, dim );
		RawTexture->copyToScalingBoxFilter(filter);
		RawTexture->drop();
		RawTexture = filter;
	}

	video::IVideoDriver* driver = Environment->getVideoDriver();

	bool generateMipLevels = driver->getTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS);
	driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false);

	ColorRing.Texture = driver->addTexture ( "#colorring", RawTexture);
	RawTexture->drop();

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, generateMipLevels);
}