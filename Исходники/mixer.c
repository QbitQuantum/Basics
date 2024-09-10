Mixer::Mixer ( int X, int Y, int W, int H, const char *L ) :
    Fl_Group( X, Y, W, H, L )
{
    Loggable::dirty_callback( &Mixer::handle_dirty, this );

    _rows = 1;
    box( FL_FLAT_BOX );
    labelsize( 96 );
    { Fl_Group *o = new Fl_Group( X, Y, W, 24 );

        { Fl_Menu_Bar *o = menubar = new Fl_Menu_Bar( X, Y, W, 24 );
            o->add( "&Project/&New" );
            o->add( "&Project/&Open" );
            o->add( "&Project/&Save", FL_CTRL + 's', 0, 0 );
            o->add( "&Project/&Quit", FL_CTRL + 'q', 0, 0 );
            o->add( "&Mixer/&Add Strip", 'a', 0, 0 );
            o->add( "&Mixer/Add &N Strips" );
            o->add( "&Mixer/&Import Strip" );
            o->add( "&Mixer/&Rows/One", '1', 0, 0 );
            o->add( "&Mixer/&Rows/Two", '2', 0, 0 );
            o->add( "&Mixer/&Rows/Three", '3', 0, 0 );
            o->add( "&View/&Theme", 0, 0, 0 );
            o->add( "_&Options/&Display/&Knobs/&Arc", 0, 0, 0, FL_MENU_RADIO   );
            o->add( "_&Options/&Display/&Knobs/&Burnished", 0, 0, 0, FL_MENU_RADIO );
            o->add( "_&Options/&Display/&Knobs/&Plastic", 0, 0, 0, FL_MENU_RADIO | FL_MENU_VALUE );
            o->add( "_&Options/&Display/&Sliders/&Nice", 0, 0, 0, FL_MENU_RADIO | FL_MENU_VALUE );
            o->add( "_&Options/&Display/&Sliders/&Fill", 0, 0, 0, FL_MENU_RADIO );
            o->add( "_&Options/&Display/&Sliders/&Simple", 0, 0, 0, FL_MENU_RADIO );
            o->add( "_&Options/&Display/&Colors/&System", 0, 0, 0, FL_MENU_RADIO );
            o->add( "&Help/&Manual" );
            o->add( "&Help/&About" );
            o->callback( cb_menu, this );
        }
        { Fl_Box *o = project_name = new Fl_Box( X + 150, Y, W, 24 );
            o->labelfont( FL_HELVETICA_ITALIC );
            o->label( 0 );
            o->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER );
            o->labeltype( FL_SHADOW_LABEL );
            Fl_Group::current()->resizable( o );
        }
        { sm_blinker = new Fl_Button( ( X + W) - 37, Y + 4, 35, 15, "SM");
            sm_blinker->box(FL_ROUNDED_BOX);
            sm_blinker->down_box(FL_ROUNDED_BOX);
            sm_blinker->color(FL_DARK2);
            sm_blinker->selection_color((Fl_Color)93);
            sm_blinker->labeltype(FL_NORMAL_LABEL);
            sm_blinker->labelfont(3);
            sm_blinker->labelsize(14);
            sm_blinker->labelcolor(FL_DARK3);
            sm_blinker->align(Fl_Align(FL_ALIGN_CENTER));
            sm_blinker->when(FL_WHEN_RELEASE);
            sm_blinker->deactivate();

        } // Fl_Blink_Button* sm_blinker
        o->end();
    }
    { Fl_Scroll *o = scroll = new Fl_Scroll( X, Y + 24, W, H - 24 );
        o->box( FL_FLAT_BOX );
//        o->type( Fl_Scroll::HORIZONTAL_ALWAYS );
//        o->box( Fl_Scroll::BOTH );
        {
            Fl_Flowpack *o = mixer_strips = new Fl_Flowpack( X, Y + 24, W, H - 18 - 24 );
//            label( "Non-Mixer" );
            align( (Fl_Align)(FL_ALIGN_CENTER | FL_ALIGN_INSIDE) );
            o->box( FL_FLAT_BOX );
            o->type( Fl_Pack::HORIZONTAL );
            o->hspacing( 2 );
            o->vspacing( 2 );
            o->end();
            Fl_Group::current()->resizable( o );
        }
        o->end();
        Fl_Group::current()->resizable( o );
    }

    end();

//    Fl::add_timeout( STATUS_UPDATE_FREQ, update_cb, this );

    update_menu();

    load_options();
}