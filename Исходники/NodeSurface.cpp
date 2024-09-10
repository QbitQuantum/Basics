    void NodeSurface::DrawRoundedRectangle( 
        Cairo::RefPtr<Cairo::Context> refCairo, 
        double x, 
        double y, 
        double width, 
        double height, 
        double radius,
        double red,
        double green,
        double blue,
        bool selected )
    {
        refCairo->save();

        if ( (radius > height/2.0) || (radius > width/2.0) )
        {
            radius = std::min<double>(height / 2, width / 2);
        }

        refCairo->move_to( x, y + radius );
        refCairo->arc( x + radius, y + radius, radius, sk_pi, -sk_pi / 2.0 );
        refCairo->line_to( x + width - radius, y );
        refCairo->arc( x + width - radius, y + radius, radius, -sk_pi / 2.0, 0 );
        refCairo->line_to( x + width, y + height - radius );
        refCairo->arc( x + width - radius, y + height - radius, radius, 0, sk_pi / 2.0 );
        refCairo->line_to( x + radius, y + height );
        refCairo->arc( x + radius, y + height - radius, radius, sk_pi / 2.0, sk_pi );
        refCairo->close_path();

        refCairo->set_source_rgb( red, green, blue );
        refCairo->fill_preserve();

        if ( selected == true )
        {
            refCairo->set_source_rgb( 1.0, 0.0, 0.0 );
            refCairo->set_line_width( 2 );
            refCairo->stroke();   
        }
        else
        {
            refCairo->set_source_rgb( 0.0, 0.0, 0.0 );
            refCairo->set_line_width( 1 );
            refCairo->stroke();   
        }            

        refCairo->restore();
    }