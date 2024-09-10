void DIALOG_LABEL_EDITOR::InitDialog()
{
    wxString msg;
    bool multiLine = false;

    if( m_CurrentText->m_MultilineAllowed )
    {
        m_textLabel = m_textLabelMultiLine;
        m_textLabelSingleLine->Show(false);
        multiLine = true;
    }
    else
    {
        m_textLabel = m_textLabelSingleLine;
        m_textLabelMultiLine->Show(false);
    }

    m_textLabel->SetValue( m_CurrentText->m_Text );
    m_textLabel->SetFocus();

    switch( m_CurrentText->Type() )
    {
    case SCH_GLOBAL_LABEL_T:
        SetTitle( _( "Global Label Properties" ) );
        break;

    case SCH_HIERARCHICAL_LABEL_T:
        SetTitle( _( "Hierarchical Label Properties" ) );
        break;

    case SCH_LABEL_T:
        SetTitle( _( "Label Properties" ) );
        break;

    case SCH_SHEET_PIN_T:
        SetTitle( _( "Hierarchical Sheet Pin Properties." ) );
        break;

    default:
        SetTitle( _( "Text Properties" ) );
        m_textLabel->Disconnect( wxEVT_COMMAND_TEXT_ENTER,
                                 wxCommandEventHandler ( DIALOG_LABEL_EDITOR::OnEnterKey ),
                                 NULL, this );
        break;
    }

    int MINTEXTWIDTH = 40;    // M's are big characters, a few establish a lot of width

    int max_len = 0;

    if ( !multiLine )
    {
        max_len =m_CurrentText->m_Text.Length();
    }
    else
    {
        // calculate the length of the biggest line
        // we cannot use the length of the entire text that has no meaning
        int curr_len = MINTEXTWIDTH;
        int imax = m_CurrentText->m_Text.Len();

        for( int count = 0; count < imax; count++ )
        {
            if( m_CurrentText->m_Text[count] == '\n' ||
                m_CurrentText->m_Text[count] == '\r' ) // new line
            {
                curr_len = 0;
            }
            else
            {
                curr_len++;

                if ( max_len < curr_len )
                    max_len = curr_len;
            }
        }
    }

    if( max_len < MINTEXTWIDTH )
        max_len = MINTEXTWIDTH;

    wxString textWidth;
    textWidth.Append( 'M', MINTEXTWIDTH );
    EnsureTextCtrlWidth( m_textLabel, &textWidth );

    // Set validators
    m_TextOrient->SetSelection( m_CurrentText->GetOrientation() );
    m_TextShape->SetSelection( m_CurrentText->GetShape() );

    int style = 0;

    if( m_CurrentText->m_Italic )
        style = 1;

    if( m_CurrentText->m_Bold )
        style += 2;

    m_TextStyle->SetSelection( style );

    wxString units = ReturnUnitSymbol( g_UserUnit, wxT( "(%s)" ) );
    msg = _( "H" ) + units + _( " x W" ) + units;
    m_staticSizeUnits->SetLabel( msg );

    msg = ReturnStringFromValue( g_UserUnit, m_CurrentText->m_Size.x );
    m_TextSize->SetValue( msg );

    if( m_CurrentText->Type() != SCH_GLOBAL_LABEL_T
     && m_CurrentText->Type() != SCH_HIERARCHICAL_LABEL_T )
    {
        m_TextShape->Show( false );
    }

    m_sdbSizer1OK->SetDefault();
}