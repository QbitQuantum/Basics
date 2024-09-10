void GalaxyEffect::Render(Effect *effect, const SettingsMap &SettingsMap, RenderBuffer &buffer) {
    int center_x = SettingsMap.GetInt("SLIDER_Galaxy_CenterX");
    int center_y = SettingsMap.GetInt("SLIDER_Galaxy_CenterY");
    int start_radius = SettingsMap.GetInt("SLIDER_Galaxy_Start_Radius");
    int end_radius = SettingsMap.GetInt("SLIDER_Galaxy_End_Radius");
    int start_angle = SettingsMap.GetInt("SLIDER_Galaxy_Start_Angle");
    int revolutions = SettingsMap.GetInt("SLIDER_Galaxy_Revolutions");
    int start_width = SettingsMap.GetInt("SLIDER_Galaxy_Start_Width");
    int end_width = SettingsMap.GetInt("SLIDER_Galaxy_End_Width");
    int duration = SettingsMap.GetInt("SLIDER_Galaxy_Duration");
    int acceleration = SettingsMap.GetInt("SLIDER_Galaxy_Accel");
    bool reverse_dir = SettingsMap.GetBool("CHECKBOX_Galaxy_Reverse");
    bool blend_edges = SettingsMap.GetBool("CHECKBOX_Galaxy_Blend_Edges");
    bool inward = SettingsMap.GetBool("CHECKBOX_Galaxy_Inward");

    if( revolutions == 0 ) return;
    std::vector< std::vector<double> > temp_colors_pct(buffer.BufferWi, std::vector<double>(buffer.BufferHt));
    std::vector< std::vector<double> > pixel_age(buffer.BufferWi, std::vector<double>(buffer.BufferHt));

    double eff_pos = buffer.GetEffectTimeIntervalPosition();
    int num_colors = buffer.palette.Size();
    xlColor color, c_old, c_new;
    HSVValue hsv1;
    double eff_pos_adj = buffer.calcAccel(eff_pos, acceleration);
    double revs = (double)revolutions;

    double pos_x = buffer.BufferWi * center_x/100.0;
    double pos_y = buffer.BufferHt * center_y/100.0;

    double head_duration = duration/100.0;    // time the head is in the frame
    double tail_length = revs * (1.0 - head_duration);
    double color_length = tail_length / num_colors;
    if(color_length < 1.0) color_length = 1.0;


    double tail_end_of_tail = ((revs + tail_length) * eff_pos_adj) - tail_length;
    double head_end_of_tail = tail_end_of_tail + tail_length;

    double radius1 = start_radius;
    double radius2 = end_radius;
    double width1 = start_width;
    double width2 = end_width;

    double step = buffer.GetStepAngle(radius1, radius2);

    for( int x = 0; x < buffer.BufferWi; x++ )
    {
        for( int y = 0; y < buffer.BufferHt; y++ )
        {
            temp_colors_pct[x][y] = 0.0;
            pixel_age[x][y] = 0.0;
        }
    }
    buffer.ClearTempBuf();

    double last_check = (inward ? std::min(head_end_of_tail,revs) : std::max(0.0, tail_end_of_tail) ) + (double)start_angle;

    for( double i = (inward ? std::min(head_end_of_tail,revs) : std::max(0.0, tail_end_of_tail));
        (inward ? i >= std::max(0.0, tail_end_of_tail) : i <= std::min(head_end_of_tail,revs));
        (inward ? i -= step : i += step) )
    {
        double adj_angle = i + (double)start_angle;
        if( reverse_dir )
        {
            adj_angle *= -1.0;
        }
        double color_val = (head_end_of_tail-i) / color_length;
        int color_int = (int)color_val;
        double color_pct = color_val - (double)color_int;
        int color2 = std::min(color_int+1, num_colors-1);
        if( color_int < color2 )
        {
            buffer.Get2ColorBlend(color_int, color2, std::min( color_pct, 1.0), color);
        }
        else
        {
            buffer.palette.GetColor(color2, color);
        }
        HSVValue hsv(color);
        double full_brightness = hsv.value;
        double pct = i/revs;
        double current_radius = radius2 * pct + radius1 * (1.0 - pct);
        double current_width = width2 * pct + width1 * (1.0 - pct);
        double half_width = current_width / 2.0;
        double inside_radius = current_radius - half_width;
        for( double r = inside_radius; ; r += 0.5 )
        {
            if( r > current_radius ) r = current_radius;
            double x1 = buffer.sin(ToRadians(adj_angle)) * r + (double)pos_x;
            double y1 = buffer.cos(ToRadians(adj_angle)) * r + (double)pos_y;
            double outside_radius = current_radius + (current_radius - r);
            double x2 = buffer.sin(ToRadians(adj_angle)) * outside_radius + (double)pos_x;
            double y2 = buffer.cos(ToRadians(adj_angle)) * outside_radius + (double)pos_y;
            double color_pct2 = (r-inside_radius)/(current_radius-inside_radius);
            if( blend_edges )
            {
                if( hsv.value > 0.0 )
                {
                    if ((int)x1 >= 0 && (int)x1 < buffer.BufferWi && (int)y1 >= 0 && (int)y1 < buffer.BufferHt)
                    {
                        buffer.SetTempPixel((int)x1,(int)y1,color);
                        temp_colors_pct[(int)x1][(int)y1] = color_pct2;
                        pixel_age[(int)x1][(int)y1] = adj_angle;
                    }
                    if ((int)x2 >= 0 && (int)x2 < buffer.BufferWi && (int)y2 >= 0 && (int)y2 < buffer.BufferHt)
                    {
                        buffer.SetTempPixel((int)x2,(int)y2,color);
                        temp_colors_pct[(int)x2][(int)y2] = color_pct2;
                        pixel_age[(int)x2][(int)y2] = adj_angle;
                    }
                }
            }
            else
            {
                hsv.value = full_brightness * color_pct2;
                if( hsv.value > 0.0 )
                {
                    buffer.SetPixel(x1,y1,hsv);
                    buffer.SetPixel(x2,y2,hsv);
                }
            }
            if( r >= current_radius ) break;
        }
        // blend old data down into final buffer
        if( blend_edges && ( (inward ? (last_check-adj_angle) : (adj_angle-last_check)) >= 90.0) )
        {
            for( int x = 0; x < buffer.BufferWi; x++ )
            {
                for( int y = 0; y < buffer.BufferHt; y++ )
                {
                    if( temp_colors_pct[x][y] > 0.0 && ((inward ? (pixel_age[x][y]-adj_angle) : (adj_angle-pixel_age[x][y])) >= 180.0) )
                    {
                        buffer.GetTempPixel(x,y,c_new);
                        buffer.GetPixel(x,y,c_old);
                        buffer.Get2ColorAlphaBlend(c_old, c_new, temp_colors_pct[x][y], color);
                        buffer.SetPixel(x,y,color);
                        temp_colors_pct[x][y] = 0.0;
                        pixel_age[x][y] = 0.0;
                    }
                }
            }
            last_check = adj_angle;
        }
    }

    // blend remaining data down into final buffer
    if( blend_edges )
    {
        for( int x = 0; x < buffer.BufferWi; x++ )
        {
            for( int y = 0; y < buffer.BufferHt; y++ )
            {
                if( temp_colors_pct[x][y] > 0.0 )
                {
                    buffer.GetTempPixel(x,y,c_new);
                    buffer.GetPixel(x,y,c_old);
                    buffer.Get2ColorAlphaBlend(c_old, c_new, temp_colors_pct[x][y], color);
                    buffer.SetPixel(x,y,color);
                }
            }
        }
    }

}