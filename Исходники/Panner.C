Panner::Panner ( int X, int Y, int W, int H, const char *L ) :
    Fl_Group( X, Y, W, H, L )
{
    _bg_image = 0;
    _bg_image_scaled = 0;
    _bg_image_projection = 0;
//    _projection = POLAR;
    _points.push_back( Point( 1, 0 ) );
    
    static float ranges[] = { 1,3,5,10,15 };
    { Fl_Choice *o = _range_choice = new Fl_Choice(X + 40,Y + H - 18,75,18,"Range:");
        o->box(FL_UP_FRAME);
        o->down_box(FL_DOWN_FRAME);
        o->textsize(9);
        o->labelsize(9);
        o->align(FL_ALIGN_LEFT);
        o->add("1 Meter",0,0,&ranges[0]);
        o->add("3 Meters",0,0,&ranges[1]);
        o->add("5 Meters",0,0,&ranges[2]);
        o->add("10 Meters",0,0,&ranges[3]);
        o->add("15 Meters",0,0,&ranges[4]);
        o->value(_range_mode);
        o->callback( cb_mode, this );
    }

    { Fl_Choice *o = _projection_choice = new Fl_Choice(X + W - 75,Y + H - 18,75,18,"Projection:");
        o->box(FL_UP_FRAME);
        o->down_box(FL_DOWN_FRAME);
        o->textsize(9);
        o->labelsize(9);
        o->align(FL_ALIGN_LEFT);
        o->add("Spherical");
        o->add("Planar");
        o->value(_projection_mode);
        o->callback( cb_mode, this );
    }
                  
    end();
}