//--------------------------------------------------------------------
void FK2DEngine::ApplyColorKey( CBitmap& p_Bitmap, CColor p_Key )
{
	std::vector< CColor >	vecSurroundingColors;
	vecSurroundingColors.reserve( 4 );

	for( unsigned int unY = 0; unY < p_Bitmap.Height(); ++unY )
	{
		for( unsigned int unX = 0; unX < p_Bitmap.Width(); ++unX )
		{
			if( p_Bitmap.GetPixel( unX, unY ) == p_Key )
			{
				vecSurroundingColors.clear();

				if( unX > 0 && p_Bitmap.GetPixel( unX - 1, unY ) != p_Key )
				{
					vecSurroundingColors.push_back( p_Bitmap.GetPixel( unX - 1, unY ) );
				}
				if( unX < p_Bitmap.Width() - 1 && p_Bitmap.GetPixel( unX + 1, unY ) != p_Key )
				{
					vecSurroundingColors.push_back( p_Bitmap.GetPixel( unX + 1, unY ) );
				}
				if( unY > 0 && p_Bitmap.GetPixel( unX, unY - 1 ) != p_Key )
				{
					vecSurroundingColors.push_back( p_Bitmap.GetPixel( unX, unY - 1 ) );
				}
				if( unY < p_Bitmap.Height() - 1 && p_Bitmap.GetPixel( unX, unY + 1 ) != p_Key )
				{
					vecSurroundingColors.push_back( p_Bitmap.GetPixel( unX, unY + 1 ) );
				}


				if( vecSurroundingColors.empty() )
				{
					p_Bitmap.SetPixel( unX, unY, CColor::NONE );
					continue;
				}

				unsigned int unRed = 0;
				unsigned int unGreen = 0;
				unsigned int unBlue = 0;

				for( unsigned int i = 0; i < vecSurroundingColors.size(); ++i )
				{
					unRed		+= vecSurroundingColors[i].Red();
					unGreen		+= vecSurroundingColors[i].Green();
					unBlue		+= vecSurroundingColors[i].Blue();
				}

				p_Bitmap.SetPixel( unX, unY, CColor( 0, unRed / vecSurroundingColors.size(),
					unGreen / vecSurroundingColors.size(), unBlue / vecSurroundingColors.size() ) );
			}
		}
	}
}