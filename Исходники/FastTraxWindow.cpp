void FastTraxWindow :: MessageReceived( BMessage * msg )
{
	switch( msg->what )
	{
		case B_ABOUT_REQUESTED:
		{
			BMessenger msgr( be_app ) ;
			if( msgr.IsValid() )
				msgr.SendMessage( msg ) ;
			break ;
		}
		case ( Messages::SetTab | 'N' ) :
		{
			fCurrentView->Hide() ;
			fCurrentView = fNameView ;
			fCurrentView->Show() ;

			fDisabledButton->SetEnabled( true ) ;
			fDisabledButton = fNameButton ;
			fDisabledButton->SetEnabled( false ) ;
			break ;
		}
		case ( Messages::SetTab | 'F' ) :
		{
			fCurrentView->Hide() ;
			fCurrentView = fFileView ;
			fCurrentView->Show() ;

			fDisabledButton->SetEnabled( true ) ;
			fDisabledButton = fFileButton ;
			fDisabledButton->SetEnabled( false ) ;
			break ;
		}
		case ( Messages::SetTab | 'D' ) :
		{
			fCurrentView->Hide() ;
			fCurrentView = fDateView ;
			fCurrentView->Show() ;

			fDisabledButton->SetEnabled( true ) ;
			fDisabledButton = fDateButton ;
			fDisabledButton->SetEnabled( false ) ;
			break ;
		}
		case Messages::LibInUse:
		{
			fFindButton->SetEnabled( false ) ;
			break ;
		}
		case Messages::LibNotInUse:
		{
			fFindButton->SetEnabled( true ) ;
			delete[] fNameStr ;
			delete[] fContainsStr ;

			fNameStr = NULL ;
			fContainsStr = NULL ;
			break ;
		}
		case Messages::StartFind :
		{
			if( !FindLibThread::InitFind( "FastTraX" ) )
			{
				beep() ;
				break ;
			}
			
			findlib_start_predicates() ;
			const char * str ;

			time_t now = time( NULL ) ;
			
			str = fpCreAfter->Text() ;
			if( str[0] )
			{
				time_t t ;
				signed char ok = GetTime( str, now, &t ) ;
				if( ok < 0 )
					break ;
				if( ok > 0 )
					findlib_insert_crtime( COMP_GT, t ) ;
			}
			str = fpCreBefore->Text() ;
			if( str[0] )
			{
				time_t t ;
				signed char ok = GetTime( str, now, &t ) ;
				if( ok < 0 )
					break ;
				if( ok > 0 )
				{
					findlib_insert_crtime( COMP_LT, t ) ;
				}
			}

			str = fpModAfter->Text() ;
			if( str[0] )
			{
				time_t t ;
				signed char ok = GetTime( str, now, &t ) ;
				if( ok < 0 )
					break ;
				if( ok > 0 )
				{
					findlib_insert_mtime( COMP_GT, t ) ;
				}
			}

			str = fpModBefore->Text() ;
			if( str[0] )
			{
				time_t t ;
				signed char ok = GetTime( str, now, &t ) ;
				if( ok < 0 )
					break ;
				if( ok > 0 )
				{
					findlib_insert_mtime( COMP_LT, t ) ;
				}
			}


			fNameStr = strdup( fpName->Text() ) ;
			if( fNameStr[0] )
				findlib_insert_iname( fNameStr ) ;
			
			if( fpSubDirs->Value() == 0 )
				findlib_insert_maxdepth( 1Ul ) ;
	
			fContainsStr = strdup( fpContaining->Text() ) ;
			if( fContainsStr[0] )
			{
				findlib_insert_open_paren() ;
				findlib_insert_type( S_IFREG ) ;
				findlib_insert_and() ;
				findlib_insert_contains_istr( fContainsStr ) ;
				findlib_insert_close_paren() ;
			}

			str = fpSizeLT->Text() ;
			if( str[0] )
			{
				float f = atof(str) ;
				findlib_insert_fsize( COMP_LT, f, 1024 ) ;
			}

			str = fpSizeGT->Text() ;
			if( str[0] )
			{
				float f = atof(str) ;
				findlib_insert_fsize( COMP_GT, f, 1024 ) ;
			}
			
			int32 i = fpKind->GetIndex() ;
			if( i )
				findlib_insert_type( kKindType[i] ) ;

			findlib_end_predicates() ;
			FindLibThread * thread = new FindLibThread ;
			
			entry_ref ref ;
			fpFolder->GetRef( &ref ) ;
			BEntry ent( &ref ) ;
			thread->Path.SetTo( &ent ) ;
			thread->StartThread() ;

			break ;
		}
		case Messages::SettingsRequested:
		{
			fSettingsWindow->Lock() ;
			if( fSettingsWindow->IsHidden() )
				fSettingsWindow->Show();
			fSettingsWindow->Unlock() ;
			fSettingsWindow->Activate( true ) ;
			break ;
		}		
		default:
		{
			inherited::MessageReceived( msg ) ;
		}
	}
}