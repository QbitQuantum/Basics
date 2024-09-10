void
Track::init ( void )
{
    _row = 0;
    _sequence = NULL;
    _name = NULL;
    _selected = false;
    _size = 1;

    record_ds = NULL;
    playback_ds = NULL;

    labeltype( FL_NO_LABEL );

//    clear_visible_focus();

    Fl_Group::size( timeline->w(), height() );

    Track *o = this;
    o->box( FL_FLAT_BOX );

    {
        Track_Header *o = new Track_Header( x(), y(), w(), h() );

        name_field = o->name_input;
        record_button = o->rec_button;
        mute_button = o->mute_button;
        solo_button = o->solo_button;
        menu_button = o->menu_button;
        show_all_takes_button = o->show_all_takes_button;
        overlay_controls_button = o->overlay_controls_button;
        
        name_field->callback( cb_button, this );
        record_button->callback( cb_button, this );
        mute_button->callback( cb_button, this );
        solo_button->callback( cb_button, this );

        show_all_takes_button->callback( cb_button, this );
        overlay_controls_button->callback( cb_button, this );
        menu_button->callback( cb_button, this );

        resizable( o );
//        o->color( (Fl_Color)53 );
    }
    
    {
        /* this pack holds the active sequence, annotation sequence, control sequences and takes */
        Fl_Pack *o = pack = new Fl_Pack( x(), y(), w(), h() );
        o->type( Fl_Pack::VERTICAL );
        o->labeltype( FL_NO_LABEL );
        /* o->resize( x() + width(), y(), w() - width(), h() ); */

        /* resizable( o ); */

        {
            Fl_Pack *o = annotation = new Fl_Pack( 0, 0, pack->w(), 1 );
            o->type( Fl_Pack::VERTICAL );
            o->end();
        }

        {
            {
                Fl_Group *o = controls_heading = new Fl_Group( 0, 0, pack->w(), 10 );
                o->box( FL_FLAT_BOX );
                o->color( fl_color_add_alpha( fl_rgb_color( 1,1,1 ), 127 ) );
                
                {
                    Fl_Box *o = new Fl_Box( 0,0, Track::width(), 10 );
                    o->label( "Controls" );
                    o->align( FL_ALIGN_RIGHT | FL_ALIGN_INSIDE );
                    o->labelsize( 10 );
                }

                o->hide();
                o->end();
                o->resizable( 0 );
            }

            {
                Fl_Sometimes_Pack *o = control = new Fl_Sometimes_Pack( 0, 0, pack->w(), 1 );
                o->spacing( 1 );
                o->box( FL_NO_BOX );
                o->color( FL_BACKGROUND_COLOR );
                o->type( Fl_Pack::VERTICAL );
                o->pack( true );
                o->hide();
                o->align( FL_ALIGN_TOP | FL_ALIGN_LEFT );
                o->end();
            }
        }

        {
            {
                Fl_Group *o = takes_heading = new Fl_Group( 0, 0, pack->w(), 10 );
                o->box( FL_FLAT_BOX );
                o->color( fl_color_add_alpha( fl_rgb_color( 1,1,1 ), 127 ) );
                
                {
                    Fl_Box *o = new Fl_Box( 0,0, Track::width(), 10 );
                    o->label( "Takes" );
                    o->align( FL_ALIGN_RIGHT | FL_ALIGN_INSIDE );
                    o->labelsize( 10 );
                }
                o->hide();
                o->end();
                o->resizable( 0 );
            }

        {
            Fl_Pack *o = takes = new Fl_Pack( 0, 0, pack->w(), 1 );
            o->type( Fl_Pack::VERTICAL );
            o->end();
            o->hide();
            o->align( FL_ALIGN_TOP | FL_ALIGN_LEFT );
        }
        }

        o->end();
    }
    end();
}