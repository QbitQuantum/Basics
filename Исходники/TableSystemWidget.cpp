void TableSystemWidget::Fit()
{
    int w = GetWidth(), h=GetHeight();
    int sb_width = _sb_width;
    int sb_height = _sb_height;

    if (_p_verti_scrollbar && _p_verti_scrollbar->Atom().IsVisible() )
    {
        _ResizePositive( _p_verti_scrollbar->AtomPtr(), sb_width, h-(_cs_height+sb_height) );
        _p_verti_scrollbar->Atom().SetPosition ( Pos( w-sb_width, _cs_height) );
    }
    if (_p_horiz_scrollbar && _p_horiz_scrollbar->Atom().IsVisible() )
    {
        _ResizePositive( _p_horiz_scrollbar->AtomPtr(), w-sb_width, sb_height );
        _p_horiz_scrollbar->Atom().SetPosition ( Pos( 0, h-sb_height ) );
    }

    if (_p_table_frame)
    {
        int frame_w = w-sb_width;
        int frame_h = h-sb_height;

        _p_table_frame->Fill( Rect( 0, 0, frame_w, frame_h ));
        Rect c = _p_table_frame->GetClientRect( _p_caption_scroller );
        _p_caption_scroller->Resize( c.GetW(), _cs_height );
        _p_caption_scroller->SetPosition( c.GetPos() );
        _ResizePositive( _p_table_scroller, c.GetW(), c.GetH()-_cs_height );
        _p_table_scroller->SetPosition( c.GetPos() + Pos( 0, _cs_height) );
    }
    else
    {
        if (_p_caption_scroller)
        {
            _p_caption_scroller->Resize( w-sb_width, _cs_height );
            _p_caption_scroller->SetPosition( Pos(0,0) );
        }
        if (_p_table_scroller)
        {
            _ResizePositive( _p_table_scroller, w-sb_width, h-(_cs_height+sb_height) );
            _p_table_scroller->SetPosition  ( Pos(0,_cs_height) );
        }
    }

    if ( _p_top_gadget )
    {
        _p_top_gadget->SetPosition( Pos( w-_p_top_gadget->GetWidth(), 0) );
        HubWidget::BringOnTop( _p_top_gadget );
    }
    if ( _p_bottom_gadget )
    {
        if ( sb_width && sb_height )
        { 
            _p_bottom_gadget->SetPosition( Pos( w-sb_width, h-sb_height) );

            if ( !_p_bottom_gadget->Atom().IsVisible() ) { _p_bottom_gadget->Atom().Show(); }
        }
        else if ( _p_bottom_gadget->Atom().IsVisible() ) { _p_bottom_gadget->Atom().Hide(); }
    }

    if ( _auto_cover )
    {
        int pri_tbl_width = _pri_tbl_width;
        int pri_tbl_height= _pri_tbl_height;
        int table_w = pri_tbl_width;
        int table_h = pri_tbl_height;
        int client_w = _p_table_scroller->GetWidth();
        int client_h = _p_table_scroller->GetHeight();

        // try to cover all client area by table (if table is smaller than area)
        if ( client_w > table_w )
        {
            _p_main_table->Atom().Resize( client_w, table_h );
        }
        else if ( client_w < pri_tbl_width )
        {
            _p_main_table->Atom().Resize( pri_tbl_width, table_h );
        }
    
        table_w = _p_main_table->Atom().GetWidth();

        if ( client_h > table_h )
        {
            _p_main_table->Atom().Resize( table_w, client_h );
        }
        else if ( client_h < pri_tbl_height )
        {
            _p_main_table->Atom().Resize( table_w, pri_tbl_height );
        }

        table_h = _p_main_table->Atom().GetHeight();

        // right scrollbar dissappears only if top-gadget does not exist
        if ( !_p_top_gadget )
        {
            // Check if full table would be visible if we hide both scrollbars
            bool would_fit_width = client_w + sb_width >= table_w;
            bool would_fit_height= client_h + sb_height >= table_h;
    
            if ( would_fit_width && would_fit_height )
            {
                _p_main_table->Atom().Resize( client_w + sb_width, client_h + sb_height);
                _sb_width = _sb_height = 0;
            }
        }
        _pri_tbl_width = pri_tbl_width;
        _pri_tbl_height= pri_tbl_height;
    }

    // Make sure that scrollbar sizes have not been changed, and if so try again
    if ( _sb_width!=sb_width || _sb_height!=sb_height ) { Fit(); }
}