int
main ( int argc, char **argv )
{
    {
    Fl_Single_Window *w = new Fl_Single_Window( 800, 600 );
    
    { Fl_Choice *o = new Fl_Choice( 0, 0, 200, 24, "Boxtype" );
        o->align( FL_ALIGN_RIGHT );

        o->callback( boxtype_cb, NULL );

        o->add( "UP_BOX" );
        o->add( "FLAT_BOX" );
        o->add( "ROUNDED_BOX" );
        o->add( "OVAL_BOX" );
    }

    {
        Fl_Pack *o = new Fl_Pack( 0, 24, 800, 600 - 24 );
        o->type( 0 );
        
        {
            PerfTest *o = new PerfTest( 0,0, 800, 400, "Xlib" );
        }

        {
            PerfTest *o = new PerfTest( 0,0, 800, 400, "Cairo" );
            o->use_cairo = true;
        }

        o->end();
    }
    
    w->end();
    w->show();
    }

    /* { */
    /* Fl_Single_Window *w = new Fl_Single_Window( 800, 600 ); */

    /* PerfTest *o = new PerfTest( 0,0, 800, 600 ); */
    
    /* w->end(); */
    /* w->show(); */
    /* } */

    Fl::run();
}