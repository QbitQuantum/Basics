void ShockwaveEffect::Render(Effect *effect, const SettingsMap &SettingsMap, RenderBuffer &buffer) {
    int center_x = SettingsMap.GetInt("SLIDER_Shockwave_CenterX", 0);
    int center_y = SettingsMap.GetInt("SLIDER_Shockwave_CenterY", 0);
    int start_radius = SettingsMap.GetInt("SLIDER_Shockwave_Start_Radius", 0);
    int end_radius = SettingsMap.GetInt("SLIDER_Shockwave_End_Radius", 0);
    int start_width = SettingsMap.GetInt("SLIDER_Shockwave_Start_Width", 0);
    int end_width = SettingsMap.GetInt("SLIDER_Shockwave_End_Width", 0);
    int acceleration = SettingsMap.GetInt("SLIDER_Shockwave_Accel", 0);
    bool blend_edges = SettingsMap.GetBool("CHECKBOX_Shockwave_Blend_Edges");

    std::vector< std::vector<double> > temp_colors_pct(buffer.BufferWi, std::vector<double>(buffer.BufferHt));
    double eff_pos = buffer.GetEffectTimeIntervalPosition();
    int num_colors = buffer.palette.Size();
    if( num_colors == 0 )
        num_colors = 1;
    xlColor color, c_old, c_new;
    double eff_pos_adj = buffer.calcAccel(eff_pos, acceleration);

    double blend_pct = 1.0 / (num_colors-1);
    double color_pct1 = eff_pos_adj / blend_pct;
    int color_index = (int)color_pct1;
    blend_pct = color_pct1 - (double)color_index;
    buffer.Get2ColorBlend(color_index, std::min(color_index+1,num_colors-1), std::min( blend_pct, 1.0), color);

    double pos_x = buffer.BufferWi * center_x/100.0;
    double pos_y = buffer.BufferHt * center_y/100.0;

    double radius1 = start_radius;
    double radius2 = end_radius;
    double radius_center = radius1 + (radius2 - radius1) * eff_pos_adj;
    double half_width = (start_width + (end_width - start_width) * eff_pos_adj) / 2.0;
    radius1 = radius_center - half_width;
    radius2 = radius_center + half_width;

    double step = buffer.GetStepAngle(radius1, radius2);

    for( int x = 0; x < buffer.BufferWi; x++ )
    {
        for( int y = 0; y < buffer.BufferHt; y++ )
        {
            temp_colors_pct[x][y] = 0.0;
        }
    }
    buffer.ClearTempBuf();

    for( double current_angle = 0.0; current_angle <= 360.0; current_angle += step )
    {
        for( double r = std::max(0.0, radius1); r <= radius2; r += 0.5 )
        {
            double x1 = buffer.sin(ToRadians(current_angle)) * r + (double)pos_x;
            double y1 = buffer.cos(ToRadians(current_angle)) * r + (double)pos_y;

            if( blend_edges )
            {
                double color_pct = 1.0 - std::abs(r-radius_center)/half_width;
                if( color_pct > 0.0 )
                {
                    if (x1 >= 0 && x1 < buffer.BufferWi && y1 >= 0 && y1 < buffer.BufferHt)
                    {
                        if (buffer.allowAlpha) {
                            color.alpha = 255.0 * color_pct;
                            buffer.SetPixel((int)x1,(int)y1,color);
                        } else {
                            temp_colors_pct[(int)x1][(int)y1] = color_pct;
                            buffer.SetTempPixel((int)x1,(int)y1,color);
                        }
                    }
                }
            }
            else
            {
                buffer.SetPixel((int)x1,(int)y1,color);
            }
        }
    }

    // blend element data into final buffer
    if( blend_edges && !buffer.allowAlpha )
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
                    temp_colors_pct[x][y] = 0.0;
                }
            }
        }
    }
}