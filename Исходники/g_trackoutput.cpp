bool TrackOutput::on_expose_event(GdkEventExpose* event)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  
  if(window)    // Only run if Window does exist
  {
    // clip to the area indicated by the expose event so that we only redraw
    // the portion of the window that needs to be redrawn
    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
    cr->rectangle(event->area.x, event->area.y,
            event->area.width, event->area.height);
    cr->clip();
    
    cr->rectangle(event->area.x, event->area.y,
        event->area.width, event->area.height);
    cr->set_source_rgb(0.1 , 0.1 , 0.1 );
    cr->fill();
    
    
    TrackOutputState* state = &stateStore->trackoutputState.at(ID);
    
    if ( state->selected )
      setColour(cr, COLOUR_GREY_3 );
    else
      setColour(cr, COLOUR_GREY_4 );
    
    cr->rectangle(0, 0, 74, 102);
    cr->fill();
    
    Dial(cr,true, 7,4,state->pan,DIAL_MODE_PAN); // pan
    Mute(cr, 9  , 41 , state->ID, state->mute ); // mute button
    Solo(cr, 9  , 68 , state->ID, state->solo ); // solo button
    Rec (cr, 9  , 85 , state->ID, state->recEnable); // rec button
    Fader(cr,46 , 4  , state->volume, state->rms, state->falloff ); // fader
    
    if ( state->selected )
    {
      cr->rectangle(0, -10, 74, 200);
      setColour( cr, COLOUR_PURPLE_1 );
      cr->set_line_width(1);
      cr->stroke();
    }
    
  }
  return true;
}