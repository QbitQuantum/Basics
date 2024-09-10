/** attempt to transform this controller into a spatialization
    controller and connect to the given module's spatialization
    control inputs. Returns true on success, false if given module
    does not accept spatialization inputs. */
bool
Controller_Module::connect_spatializer_to ( Module *m )
{
    /* these are for detecting related parameter groups which can be
       better represented by a single control */
    Port *azimuth_port = NULL;
    float azimuth_value = 0.0f;
    Port *elevation_port = NULL;
    float elevation_value = 0.0f;

    for ( unsigned int i = 0; i < m->control_input.size(); ++i )
    {
        Port *p = &m->control_input[i];

        if ( !strcasecmp( "Azimuth", p->name() ) &&
             180.0f == p->hints.maximum &&
             -180.0f == p->hints.minimum )
        {
            azimuth_port = p;
            azimuth_value = p->control_value();
            continue;
        }
        else if ( !strcasecmp( "Elevation", p->name() ) &&
                  90.0f == p->hints.maximum &&
                  -90.0f == p->hints.minimum )
        {
            elevation_port = p;
            elevation_value = p->control_value();
            continue;
        }
    }

    if ( ! ( azimuth_port && elevation_port ) )
        return false;

    control_output.clear();
    add_port( Port( this, Port::OUTPUT, Port::CONTROL ) );
    add_port( Port( this, Port::OUTPUT, Port::CONTROL ) );

    control_output[0].connect_to( azimuth_port );
    control_output[1].connect_to( elevation_port );

    {
        clear();

        Panner *o = new Panner( 0,0, 100, 100 );

        o->box(FL_THIN_UP_BOX);
        o->color(FL_GRAY0);
        o->selection_color(FL_BACKGROUND_COLOR);
        o->labeltype(FL_NORMAL_LABEL);
        o->labelfont(0);
        o->labelcolor(FL_FOREGROUND_COLOR);
        o->align(FL_ALIGN_TOP);
        o->when(FL_WHEN_CHANGED);
        label( "Spatialization" );

        o->align(FL_ALIGN_TOP);
        o->labelsize( 10 );
//        o->callback( cb_panner_value_handle, new callback_data( this, azimuth_port_number, elevation_port_number ) );

        o->point( 0 )->azimuth( azimuth_value );
        o->point( 0 )->elevation( elevation_value );

        o->callback( cb_spatializer_handle, this );

        control = (Fl_Valuator*)o;

        if ( _pad )
        {
            Fl_Labelpad_Group *flg = new Fl_Labelpad_Group( o );
            flg->position( x(), y() );
            flg->set_visible_focus();
            size( flg->w(), flg->h() );
            add( flg );
        }
        else
        {
            o->resize( x(), y(), w(), h() );
            add( o );
            resizable( o );
            init_sizes();
        }

        _type = SPATIALIZATION;
        return true;
    }
}