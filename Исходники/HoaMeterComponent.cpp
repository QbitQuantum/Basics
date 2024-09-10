void HoaMeterComponent::draw_leds(Graphics& g)
{
    int i;
    float j, dB;
    float angle_start, angle, angle_end, radius, center_x, center_y;
    float led_width = 0.49 * getWidth() / 18.;
    float h = led_width * 18.;
    float thickness  = led_width - 2;
    if(getWidth() < 125)
        thickness = led_width - 1;

    Path p;

    for(i = 0; i < m_meter->getNumberOfChannels(); i++)
    {
        angle   = -m_meter->getChannelAzimuthMapped(i);

        center_x    = Hoa::abscissa(m_radius - h, angle);
        center_y    = Hoa::ordinate(m_radius - h, angle);

        angle_start = angle - m_meter->getChannelWidth(i) * 0.5f;
        angle_end   = angle + m_meter->getChannelWidth(i) * 0.5f;


        for(j = 11, dB = -34.5; j > -1; j--, dB += 3.)
        {
            radius    = (j + 5.) * led_width;
            if(m_meter->getChannelEnergy(i) > dB)
            {
                if(j > 8)
                    g.setColour(Colours::green);
                else if(j > 5)
                    g.setColour(Colours::greenyellow);
                else if(j > 2)
                    g.setColour(Colours::yellow);
                else
                    g.setColour(Colours::orange);

                p.addCentredArc(center_x + m_center, center_y + m_center, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(thickness, PathStrokeType::beveled, PathStrokeType::butt));
                p.clear();
            }
            else if(j != -1)
            {
                g.setColour(Colours::grey);
                p.addCentredArc(center_x + m_center, center_y + m_center, radius, radius, HOA_2PI, angle_start, angle_end, 1);
                g.strokePath(p, PathStrokeType(thickness, PathStrokeType::beveled, PathStrokeType::butt));
                p.clear();
            }
        }
    }
};