void PHPCodeGenerator::GenConstruction(PObjectBase obj, bool is_widget )
{
	wxString type = obj->GetObjectTypeName();
	PObjectInfo info = obj->GetObjectInfo();

	if ( ObjectDatabase::HasCppProperties( type ) )
	{
		m_source->WriteLn( GetCode( obj, wxT("construction") ) );

		GenSettings( obj->GetObjectInfo(), obj );

		bool isWidget = !info->IsSubclassOf( wxT("sizer") );

		for ( unsigned int i = 0; i < obj->GetChildCount(); i++ )
		{
			PObjectBase child = obj->GetChild( i );
			GenConstruction( child, isWidget );

			if ( type == wxT("toolbar") )
			{
				GenAddToolbar(child->GetObjectInfo(), child);
			}
		}

		if ( !isWidget ) // sizers
		{
			wxString afterAddChild = GetCode( obj, wxT( "after_addchild" ) );
			if ( !afterAddChild.empty() )
			{
				m_source->WriteLn( afterAddChild );
			}
			m_source->WriteLn();

			if (is_widget)
			{
				// the parent object is not a sizer. There is no template for
				// this so we'll make it manually.
				// It's not a good practice to embed templates into the source code,
				// because you will need to recompile...

				wxString _template =	wxT("#wxparent $name->SetSizer( @$$name ); #nl")
										wxT("#wxparent $name->Layout();")
										wxT("#ifnull #parent $size")
										wxT("@{ #nl @$$name->Fit( #wxparent $name ); @}");

				PHPTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
				m_source->WriteLn(parser.ParseTemplate());
			}
		}
		else if ( type == wxT("splitter") )
		{
			// Generating the split
			switch ( obj->GetChildCount() )
			{
				case 1:
				{
					PObjectBase sub1 = obj->GetChild(0)->GetChild(0);
					wxString _template = wxT("@$this->$name->Initialize( ");
					_template = _template + wxT("@$this->") + sub1->GetProperty( wxT("name") )->GetValue() + wxT(" );");

					PHPTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
					m_source->WriteLn(parser.ParseTemplate());
					break;
				}
				case 2:
				{
					PObjectBase sub1,sub2;
					sub1 = obj->GetChild(0)->GetChild(0);
					sub2 = obj->GetChild(1)->GetChild(0);

					wxString _template;
					if ( obj->GetProperty( wxT("splitmode") )->GetValue() == wxT("wxSPLIT_VERTICAL") )
					{
						_template = wxT("@$this->$name->SplitVertically( ");
					}
					else
					{
						_template = wxT("@$this->$name->SplitHorizontally( ");
					}

					_template = _template + wxT("@$this->") + sub1->GetProperty( wxT("name") )->GetValue() +
						wxT(", @$this->") + sub2->GetProperty( wxT("name") )->GetValue() + wxT(", $sashpos );");

					PHPTemplateParser parser( obj, _template, m_i18n, m_useRelativePath, m_basePath );
					m_source->WriteLn(parser.ParseTemplate());
					break;
				}
				default:
					wxLogError( wxT("Missing subwindows for wxSplitterWindow widget.") );
					break;
			}
		}
		else if (
				type == wxT("menubar")	||
				type == wxT("menu")		||
				type == wxT("submenu")	||
				type == wxT("toolbar")	||
				type == wxT("ribbonbar")	||
				type == wxT("listbook")	||
				type == wxT("simplebook") ||
				type == wxT("notebook")	||
				type == wxT("auinotebook")	||
				type == wxT("treelistctrl")	||
				type == wxT("flatnotebook") ||
				type == wxT("wizard")
			)
		{
			wxString afterAddChild = GetCode( obj, wxT("after_addchild") );
			if ( !afterAddChild.empty() )
			{
				m_source->WriteLn( afterAddChild );
			}
			m_source->WriteLn();
		}
	}
	else if ( info->IsSubclassOf( wxT("sizeritembase") ) )
	{
		// The child must be added to the sizer having in mind the
		// child object type (there are 3 different routines)
		GenConstruction( obj->GetChild(0), false );

		PObjectInfo childInfo = obj->GetChild(0)->GetObjectInfo();
		wxString temp_name;
		if ( childInfo->IsSubclassOf( wxT("wxWindow") ) || wxT("CustomControl") == childInfo->GetClassName() )
		{
			temp_name = wxT("window_add");
		}
		else if ( childInfo->IsSubclassOf( wxT("sizer") ) )
		{
			temp_name = wxT("sizer_add");
		}
		else if ( childInfo->GetClassName() == wxT("spacer") )
		{
			temp_name = wxT("spacer_add");
		}
		else
		{
			LogDebug( wxT("SizerItem child is not a Spacer and is not a subclass of wxWindow or of sizer.") );
			return;
		}

		m_source->WriteLn( GetCode( obj, temp_name ) );
	}
	else if (	type == wxT("notebookpage")		||
				type == wxT("flatnotebookpage")	||
				type == wxT("listbookpage")		||
				type == wxT("simplebookpage")	||
				type == wxT("choicebookpage")	||
				type == wxT("auinotebookpage")
			)
	{
		GenConstruction( obj->GetChild( 0 ), false );
		m_source->WriteLn( GetCode( obj, wxT("page_add") ) );
		GenSettings( obj->GetObjectInfo(), obj );
	}
	else if ( type == wxT("treelistctrlcolumn") )
	{
		m_source->WriteLn( GetCode( obj, wxT("column_add") ) );
		GenSettings( obj->GetObjectInfo(), obj );
	}
	else if ( type == wxT("tool") )
	{
		// If loading bitmap from ICON resource, and size is not set, set size to toolbars bitmapsize
		// So hacky, yet so useful ...
		wxSize toolbarsize = obj->GetParent()->GetPropertyAsSize( _("bitmapsize") );
		if ( wxDefaultSize != toolbarsize )
		{
			PProperty prop = obj->GetProperty( _("bitmap") );
			if ( prop )
			{
				wxString oldVal = prop->GetValueAsString();
				wxString path, source;
				wxSize toolsize;
				TypeConv::ParseBitmapWithResource( oldVal, &path, &source, &toolsize );
				if ( wxT("Load From Icon Resource") == source && wxDefaultSize == toolsize )
				{
					prop->SetValue( wxString::Format( wxT("%s; %s [%i; %i]"), path.c_str(), source.c_str(), toolbarsize.GetWidth(), toolbarsize.GetHeight() ) );
					m_source->WriteLn( GetCode( obj, wxT("construction") ) );
					prop->SetValue( oldVal );
					return;
				}
			}
		}
		m_source->WriteLn( GetCode( obj, wxT("construction") ) );
	}
	else
	{
		// Generate the children
		for ( unsigned int i = 0; i < obj->GetChildCount(); i++ )
		{
			GenConstruction( obj->GetChild( i ), false );
		}
	}
}