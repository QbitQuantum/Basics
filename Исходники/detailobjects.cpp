//-----------------------------------------------------------------------------
// Parses the key-value pairs in the detail.rad file
//-----------------------------------------------------------------------------
static void ParseDetailGroup( int detailId, KeyValues* pGroupKeyValues )
{
	// Sort the group by alpha
	float alpha = pGroupKeyValues->GetFloat( "alpha", 1.0f );
	
	int i = s_DetailObjectDict[detailId].m_Groups.Count();
	while ( --i >= 0 )
	{
		if (alpha > s_DetailObjectDict[detailId].m_Groups[i].m_Alpha)
			break;
	}

	// Insert after the first guy who's more transparent that we are!
	i = s_DetailObjectDict[detailId].m_Groups.InsertAfter(i);
	DetailObjectGroup_t& group = s_DetailObjectDict[detailId].m_Groups[i];

	group.m_Alpha = alpha;

	// Add in all the model groups
	KeyValues* pIter = pGroupKeyValues->GetFirstSubKey();
	float totalAmount = 0.0f;
	while( pIter )
	{
		if (pIter->GetFirstSubKey())
		{
			int i = group.m_Models.AddToTail();

			DetailModel_t &model = group.m_Models[i];

			model.m_ModelName = pIter->GetString( "model", 0 );
			if (model.m_ModelName != UTL_INVAL_SYMBOL)
			{
				model.m_Type = DETAIL_PROP_TYPE_MODEL;
			}
			else
			{
				const char *pSpriteData = pIter->GetString( "sprite", 0 );
				if (pSpriteData)
				{
					const char *pProcModelType = pIter->GetString( "sprite_shape", 0 );

					if ( pProcModelType )
					{
						if ( !Q_stricmp( pProcModelType, "cross" ) )
						{
							model.m_Type = DETAIL_PROP_TYPE_SHAPE_CROSS;
						}
						else if ( !Q_stricmp( pProcModelType, "tri" ) )
						{
							model.m_Type = DETAIL_PROP_TYPE_SHAPE_TRI;
						}
						else
							model.m_Type = DETAIL_PROP_TYPE_SPRITE;
					}					
					else
					{
						// card sprite
                        model.m_Type = DETAIL_PROP_TYPE_SPRITE;
					}

					model.m_Tex[0].Init();
					model.m_Tex[1].Init();

					float x = 0, y = 0, flWidth = 64, flHeight = 64, flTextureSize = 512;
					int nValid = sscanf( pSpriteData, "%f %f %f %f %f", &x, &y, &flWidth, &flHeight, &flTextureSize ); 
					if ( (nValid != 5) || (flTextureSize == 0) )
					{
						Error( "Invalid arguments to \"sprite\" in detail.vbsp!\n" );
					}

					model.m_Tex[0].x = ( x + 0.5f ) / flTextureSize;
					model.m_Tex[0].y = ( y + 0.5f ) / flTextureSize;
					model.m_Tex[1].x = ( x + flWidth - 0.5f ) / flTextureSize;
					model.m_Tex[1].y = ( y + flHeight - 0.5f ) / flTextureSize;

					model.m_Pos[0].Init( -10, 20 );
					model.m_Pos[1].Init( 10, 0 );

					pSpriteData = pIter->GetString( "spritesize", 0 );
					if (pSpriteData)
					{
						sscanf( pSpriteData, "%f %f %f %f", &x, &y, &flWidth, &flHeight );

						float ox = flWidth * x;
						float oy = flHeight * y;

						model.m_Pos[0].x = -ox;
						model.m_Pos[0].y = flHeight - oy;
						model.m_Pos[1].x = flWidth - ox;
						model.m_Pos[1].y = -oy;
					}

					model.m_flRandomScaleStdDev = pIter->GetFloat( "spriterandomscale", 0.0f );

					// sway is a percent of max sway, cl_detail_max_sway
					float flSway = clamp( pIter->GetFloat( "sway", 0.0f ), 0.0, 1.0 );
					model.m_SwayAmount = (unsigned char)( 255.0 * flSway );

					// shape angle
					// for the tri shape, this is the angle each side is fanned out
					model.m_ShapeAngle = pIter->GetInt( "shape_angle", 0 );

					// shape size
					// for the tri shape, this is the distance from the origin to the center of a side
					float flShapeSize = clamp( pIter->GetFloat( "shape_size", 0.0f ), 0.0, 1.0 );
					model.m_ShapeSize = (unsigned char)( 255.0 * flShapeSize );
				}
			}

			model.m_Amount = pIter->GetFloat( "amount", 1.0 ) + totalAmount;
			totalAmount = model.m_Amount;

			model.m_Flags = 0;
			if (pIter->GetInt( "upright", 0 ))
			{
				model.m_Flags |= MODELFLAG_UPRIGHT;
			}

			// These are used to prevent emission on steep surfaces
			float minAngle = pIter->GetFloat( "minAngle", 180 );
			float maxAngle = pIter->GetFloat( "maxAngle", 180 );
			model.m_MinCosAngle = cos(minAngle * M_PI / 180.f);
			model.m_MaxCosAngle = cos(maxAngle * M_PI / 180.f);
			model.m_Orientation = pIter->GetInt( "detailOrientation", 0 );

			// Make sure minAngle < maxAngle
			if ( model.m_MinCosAngle < model.m_MaxCosAngle)
			{
				model.m_MinCosAngle = model.m_MaxCosAngle;
			}
		}
		pIter = pIter->GetNextKey();
	}

	// renormalize the amount if the total > 1
	if (totalAmount > 1.0f)
	{
		for (i = 0; i < group.m_Models.Count(); ++i)
		{
			group.m_Models[i].m_Amount /= totalAmount;
		}
	}
}