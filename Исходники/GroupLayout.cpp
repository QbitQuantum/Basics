//==== Create & Init Gui ToggleButton  ====//
void GroupLayout::AddButton( CheckButtonBit& cbutton, const char* label, int value )
{
    assert( m_Group && m_Screen );

    //==== Add Check Button ====//
    int bw = FitWidth( 0, m_ButtonWidth );
    Fl_Light_Button* flbutton = new Fl_Light_Button( m_X, m_Y, bw, m_StdHeight, label );
    flbutton->labelfont( 1 );
    flbutton->labelsize( 12 );
    flbutton->align( Fl_Align( 132 | FL_ALIGN_INSIDE ) );
    flbutton->labelcolor( FL_DARK_BLUE );
    flbutton->copy_label( label );
    m_Group->add( flbutton );
    AddX( bw );

    AddY( m_StdHeight );
    NewLineX();

    cbutton.Init( m_Screen, flbutton, value );
}