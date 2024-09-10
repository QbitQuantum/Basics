void CloseCaptionTool::ComputeStreamWork( CChoreoWidgetDrawHelper &helper, int available_width, CCloseCaptionItem *item )
{
	// Start with a clean param block
	WorkUnitParams params;

	const wchar_t *curpos = item->GetStream();
	
	CUtlVector< COLORREF > colorStack;

	for ( ; curpos && *curpos != L'\0'; ++curpos )
	{
		wchar_t cmd[ 256 ];
		wchar_t args[ 256 ];

		if ( SplitCommand( &curpos, cmd, args ) )
		{
			if ( !wcscmp( cmd, L"cr" ) )
			{
				params.newline = true;
				AddWorkUnit( item, params);
			}
			else if ( !wcscmp( cmd, L"clr" ) )
			{
				AddWorkUnit( item, params );

				if ( args[0] == 0 && colorStack.Count()>= 2)
				{
					colorStack.Remove( colorStack.Count() - 1 );
					params.clr = colorStack[ colorStack.Count() - 1 ];
				}
				else
				{
					int r, g, b;
					COLORREF newcolor;
					if ( 3 == swscanf( args, L"%i,%i,%i", &r, &g, &b ) )
					{
						newcolor = RGB( r, g, b );
						colorStack.AddToTail( newcolor );
						params.clr = colorStack[ colorStack.Count() - 1 ];
					}
				}
			}
			else if ( !wcscmp( cmd, L"playerclr" ) )
			{
				AddWorkUnit( item, params );

				if ( args[0] == 0 && colorStack.Count()>= 2)
				{
					colorStack.Remove( colorStack.Count() - 1 );
					params.clr = colorStack[ colorStack.Count() - 1 ];
				}
				else
				{
					// player and npc color selector
					// e.g.,. 255,255,255:200,200,200
					int pr, pg, pb, nr, ng, nb;
					COLORREF newcolor;
					if ( 6 == swscanf( args, L"%i,%i,%i:%i,%i,%i", &pr, &pg, &pb, &nr, &ng, &nb ) )
					{
						// FIXME:  nothing in .vcds is ever from the player...
						newcolor = /*item->IsFromPlayer()*/ false ? RGB( pr, pg, pb ) : RGB( nr, ng, nb );
						colorStack.AddToTail( newcolor );
						params.clr = colorStack[ colorStack.Count() - 1 ];
					}
				}
			}
			else if ( !wcscmp( cmd, L"I" ) )
			{
				AddWorkUnit( item, params );
				params.italic = !params.italic;
			}
			else if ( !wcscmp( cmd, L"B" ) )
			{
				AddWorkUnit( item, params );
				params.bold = !params.bold;
			}

			continue;
		}

		HFONT useF = m_hFonts[ params.GetFontNumber() ];
		
		int w = helper.CalcTextWidthW( useF, L"%c", *curpos ); 

		if ( ( params.x + params.width ) + w > available_width )
		{
			params.newline = true;
			AddWorkUnit( item, params );
		}
		*params.out++ = *curpos;
		params.width += w;
	}

	// Add the final unit.
	params.newline = true;
	AddWorkUnit( item, params );

	item->SetSizeComputed( true );

	// DumpWork( item );
}