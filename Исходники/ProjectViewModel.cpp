void ProjectViewModel::GetValue( wxVariant& variant, const wxDataViewItem& item, unsigned int column ) const
{
	if ( !item.IsOk() || ( column >= m_ColumnLookupTable.size() ) )
	{
		return;
	}

	Asset *node = static_cast< Asset* >( item.GetID() );
	if ( !node )
	{
		return;
	}

	switch( m_ColumnLookupTable.at( column ) )
	{
	default:
		break;

	case ProjectModelColumns::Name:
		{            
			uint32_t docStatus = DocumentStatus::Default; //  node->GetDocumentStatus();

			String assetString( *node->GetName() );
			

			wxString name = *assetString;
			if ( HasFlags<uint32_t>( docStatus, DocumentStatus::Changed ) )
			{
				name = wxString( TXT( '*' ) ) + name; 
			}

			wxBitmap bitmap = wxArtProvider::GetBitmap( GetArtIDFromPath( node->GetPath() ), wxART_OTHER, wxSize(16, 16) );
			if ( docStatus > 0 )
			{
				wxImage image = bitmap.ConvertToImage();
				HELIUM_ASSERT( image.Ok() );

				int overlayWidth = image.GetWidth() / 2;
				int overlayHeight = image.GetHeight() / 2;

				wxImage overlayImage;

				if ( HasFlags<uint32_t>( docStatus, DocumentStatus::Saving ) )
				{
					overlayImage = wxArtProvider::GetBitmap( ArtIDs::Status::Busy, wxART_OTHER, wxSize( overlayWidth, overlayHeight ) ).ConvertToImage();
					HELIUM_ASSERT( overlayImage.Ok() );
				}
				else if ( HasFlags<uint32_t>( docStatus, DocumentStatus::Loading ) )
				{
					overlayImage = wxArtProvider::GetBitmap( ArtIDs::Status::Busy, wxART_OTHER, wxSize( overlayWidth, overlayHeight ) ).ConvertToImage();
					HELIUM_ASSERT( overlayImage.Ok() );
				}
				else if ( HasFlags<uint32_t>( docStatus, DocumentStatus::Changed ) )
				{
					overlayImage = wxArtProvider::GetBitmap( ArtIDs::Actions::Edit, wxART_OTHER, wxSize( overlayWidth, overlayHeight ) ).ConvertToImage();
					HELIUM_ASSERT( overlayImage.Ok() );
				}

				if ( overlayImage.Ok() )
				{
					if ( overlayImage.GetWidth() != overlayWidth || overlayImage.GetHeight() != overlayHeight )
					{
						overlayImage.Rescale( overlayWidth, overlayHeight );
					}

					int x = 0;
					int y = 0;
					IconArtFile::CalculatePlacement( image, overlayImage, OverlayQuadrants::BottomRight, x, y );
					image.Paste( overlayImage, x, y );
				}

				bitmap = wxBitmap( image );
			}

			wxIcon icon;
			icon.CopyFromBitmap( bitmap );

			variant << wxDataViewIconText( name, icon );

		}
		break;

	//case ProjectModelColumns::Icon:
	//    {
	//        int32_t imageID = GlobalFileIconsTable().GetIconIDFromPath( node->GetPath() );
	//        wxVariant bitmapVariant;
	//        bitmapVariant.
	//        variant = GlobalFileIconsTable().GetSmallImageList()->GetBitmap( imageID );
	//    }
	//    break;

	case ProjectModelColumns::Details:
		{
			variant = std::string( TXT( "" ) );
		}
		break;

	case ProjectModelColumns::FileSize:
		{
			variant = std::string( TXT( "" ) );
		}
		break;
	case ProjectModelColumns::Type:
		{
			const AssetType *pType = node->GetAssetType();
			HELIUM_ASSERT( pType );
			variant = std::string( *pType->GetName() );
		}
		break;
	}
}