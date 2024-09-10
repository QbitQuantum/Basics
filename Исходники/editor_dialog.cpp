// Inserts 2 string of text at the current insertion point. It is split into 2 strings
// so that can (a) Highlight a swatch of text and the start and ending text gets put
// on either side of the selected text, or (b) if no text selected, then backspace the
// caret to right before the ending text, so that when add a <h1></h1>, the caret gets
// placed in a logical place: <h1>|</h1> 
void editor_dialog::stc_or_textctrl_insert_text
    ( 
    wxString starting_text_to_insert,   // Text to insert at start of selection
    wxString ending_text_to_insert,     // Text to insert at end of a selection
    bool     tag_can_insert_newline     // Whether prudent to ever insert a '\n'
    )                                                 
{
    wxString selected_text;      // Currently selected text in the control
   
    // Add a trailing linefeed to the ending text, if so requested by the user in the
    // editor preferences, and it is prudent to do so (ie a newline after a <i> </i> doesn't
    // make sense.
    bool insert_a_linefeed = the_configuration->Read( wxT( "/PLUCKER_DESKTOP/editor_tools_insert_linefeeds"), 1L); 
    if ( insert_a_linefeed && tag_can_insert_newline ) 
    {
        ending_text_to_insert += wxT( "\n" );  
    }

    long selection_starting_caret_position;
    long selection_ending_caret_position;
    
    m_editor_textctrl->GetSelection( &selection_starting_caret_position,
                                     &selection_ending_caret_position );
                        
    // If selection starting caret position equals the end, that means was no selection
    if ( selection_starting_caret_position == selection_ending_caret_position ) 
    {       
        long original_caret_position = m_editor_textctrl->GetInsertionPoint();
        // No text selected, just add the two strings at the insertion point 
        m_editor_textctrl->WriteText( starting_text_to_insert );
        m_editor_textctrl->WriteText( ending_text_to_insert );
        // Now set the cursor to between the starting and ending text. The previous
        // insertion text ends up at the the original caret position, so just fast-forward
        // the length of the starting text
        long length_of_starting_text_to_insert = (long) starting_text_to_insert.Length();
        long new_caret_position = original_caret_position + length_of_starting_text_to_insert;
        m_editor_textctrl->SetInsertionPoint( new_caret_position );
    } 
    else
    {
        // Some text is selected, so put the ending_text at the end of the selected text,
        // and the starting text before the selected text.
        // Set the insertion point to selection end, then insert ending text
        m_editor_textctrl->SetInsertionPoint( selection_ending_caret_position );
        m_editor_textctrl->WriteText( ending_text_to_insert );
        // Set the insertion point to selection end, then insert ending text
        m_editor_textctrl->SetInsertionPoint( selection_starting_caret_position );
        m_editor_textctrl->WriteText( starting_text_to_insert );
    }
        
    // Set the focus from the toolbar, back to the TextCtrl. 
    m_editor_textctrl->SetFocus();
}