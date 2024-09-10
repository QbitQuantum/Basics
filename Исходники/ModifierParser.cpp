IFXRESULT ModifierParser::ParseGlyphModifier()
{
	IFXRESULT result = IFX_OK;
	GlyphModifier* pGlyphModifier = 
		static_cast< GlyphModifier* >( m_pModifier );
	IFXString billboard;
	IFXString singleShader;
	IFXMatrix4x4 tm;
	I32 count = 0;

	result = m_pScanner->ScanStringToken( 
								IDTF_ATTRIBUTE_BILLBOARD, 
								&billboard );

	if( IFXSUCCESS( result ) )
		result = m_pScanner->ScanStringToken( 
								IDTF_ATTRIBUTE_SINGLESHADER, 
								&singleShader );

	if( IFXSUCCESS( result ) )
		result = m_pScanner->ScanIntegerToken( 
								IDTF_GLYPH_COMMAND_COUNT, 
								&count );

	if( IFXSUCCESS( result ) && count > 0 )
	{
		I32 i, number;
		IFXString type;

		result = BlockBegin( IDTF_GLYPH_COMMAND_LIST );

		for( i = 0; i < count && IFXSUCCESS( result ); ++i )
		{
			if( IFXSUCCESS( result ) )
				result = BlockBegin( IDTF_GLYPH_COMMAND, &number );

			if( IFXSUCCESS( result ) && number == i )
				result = m_pScanner->ScanStringToken( 
										IDTF_GLYPH_COMMAND_TYPE, &type );

			if( IFXSUCCESS( result ) )
			{
				if( type == IDTF_END_GLYPH )
				{
					EndGlyph glyph;
					F32 offset_x = 0, offset_y = 0;

					result = m_pScanner->ScanFloatToken( 
											IDTF_END_GLYPH_OFFSET_X, 
											&offset_x );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
											IDTF_END_GLYPH_OFFSET_Y, 
											&offset_y );

					if( IFXSUCCESS( result ) )
					{
						glyph.SetType( IDTF_END_GLYPH );
						glyph.m_offset_x = offset_x;
						glyph.m_offset_y = offset_y;

						result = pGlyphModifier->AddCommand( &glyph );
					}
				}
				else if( type == IDTF_MOVE_TO )
				{
					MoveTo glyph;
					F32 x = 0, y = 0;

					result = m_pScanner->ScanFloatToken( 
										IDTF_MOVE_TO_X, &x );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_MOVE_TO_Y, &y );

					if( IFXSUCCESS( result ) )
					{
						glyph.SetType( IDTF_MOVE_TO );
						glyph.m_moveto_x = x;
						glyph.m_moveto_y = y;

						result = pGlyphModifier->AddCommand( &glyph );
					}
				}
				else if( type == IDTF_LINE_TO )
				{
					LineTo glyph;
					F32 x = 0, y = 0;

					result = m_pScanner->ScanFloatToken( 
										IDTF_LINE_TO_X, &x );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_LINE_TO_Y, &y );

					if( IFXSUCCESS( result ) )
					{
						glyph.SetType( IDTF_LINE_TO );
						glyph.m_lineto_x = x;
						glyph.m_lineto_y = y;

						result = pGlyphModifier->AddCommand( &glyph );
					}
				}
				else if( type == IDTF_CURVE_TO )
				{
					CurveTo glyph;
					F32 x1 = 0, y1 = 0, x2 = 0, y2 = 0, end_x = 0, end_y = 0;

					result = m_pScanner->ScanFloatToken( 
										IDTF_CONTROL1_X, &x1 );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_CONTROL1_Y, &y1 );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_CONTROL2_X, &x2 );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_CONTROL2_Y, &y2 );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_ENDPOINT_X, &end_x );

					if( IFXSUCCESS( result ) )
						result = m_pScanner->ScanFloatToken( 
										IDTF_ENDPOINT_Y, &end_y );

					if( IFXSUCCESS( result ) )
					{
						glyph.SetType( IDTF_CURVE_TO );
						glyph.m_control1_x = x1;
						glyph.m_control1_y = y1;
						glyph.m_control2_x = x2;
						glyph.m_control2_y = y2;
						glyph.m_endpoint_x = end_x;
						glyph.m_endpoint_y = end_y;

						result = pGlyphModifier->AddCommand( &glyph );
					}
				}
				else
				{
					GlyphCommand glyph;

					glyph.SetType( type );

					result = pGlyphModifier->AddCommand( &glyph );
				}
			}

			if( IFXSUCCESS( result ) )
				result = BlockEnd();
		}

		if( IFXSUCCESS( result ) )
			result = BlockEnd();
	}

	if( IFXSUCCESS( result ) )
		result = BlockBegin( IDTF_GLYPH_TM );

	if( IFXSUCCESS( result ) )
		result = m_pScanner->ScanTM( &tm );

	if( IFXSUCCESS( result ) )
		result = BlockEnd();

	if( IFXSUCCESS( result ) )
	{
		pGlyphModifier->SetBillboard( billboard );
		pGlyphModifier->SetSingleShader( singleShader );
		pGlyphModifier->SetTM( tm );
	}

	IFXASSERT( IFXSUCCESS( result ) ); 
	return result;
}