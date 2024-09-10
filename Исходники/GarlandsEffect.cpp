void GarlandsEffect::Render(Effect *effect, const SettingsMap &SettingsMap, RenderBuffer &buffer) {
    int GarlandType = SettingsMap.GetInt("SLIDER_Garlands_Type", 0);
    int Spacing = SettingsMap.GetInt("SLIDER_Garlands_Spacing", 0);
    float cycles = SettingsMap.GetDouble("TEXTCTRL_Garlands_Cycles", 1.0);

    if (Spacing < 1) {
        Spacing = 1;
    }
    int x,y,yadj,ylimit,ring;
    double ratio;
    xlColor color;
    int dir = GetDirection(SettingsMap.Get("CHOICE_Garlands_Direction", "Up"));
    double position = buffer.GetEffectTimeIntervalPosition(cycles);
    if (dir > 3) {
        dir -= 4;
        if (position > 0.5) {
            position = (1.0 - position) * 2.0;
        } else {
            position *= 2.0;
        }
    }
    int buffMax = buffer.BufferHt;
    int garlandWid = buffer.BufferWi;
    if (dir > 1) {
        buffMax = buffer.BufferWi;
        garlandWid = buffer.BufferHt;
    }
    double PixelSpacing=Spacing*buffMax/100.0;
    if (PixelSpacing < 2.0) PixelSpacing=2.0;


    double total = buffMax * PixelSpacing - buffMax + 1;
    double positionOffset = total * position;

    for (ring = 0; ring < buffMax; ring++)
    {
        ratio=double(buffMax-ring-1)/double(buffMax);
        buffer.GetMultiColorBlend(ratio, false, color);

        y = 1.0 + ring*PixelSpacing - positionOffset;


        ylimit=ring;
        for (x=0; x<garlandWid; x++)
        {
            yadj=y;
            switch (GarlandType)
            {
            case 1:
                switch (x%5)
                {
                case 2:
                    yadj-=2;
                    break;
                case 1:
                case 3:
                    yadj-=1;
                    break;
                }
                break;
            case 2:
                switch (x%5)
                {
                case 2:
                    yadj-=4;
                    break;
                case 1:
                case 3:
                    yadj-=2;
                    break;
                }
                break;
            case 3:
                switch (x%6)
                {
                case 3:
                    yadj-=6;
                    break;
                case 2:
                case 4:
                    yadj-=4;
                    break;
                case 1:
                case 5:
                    yadj-=2;
                    break;
                }
                break;
            case 4:
                switch (x%5)
                {
                case 1:
                case 3:
                    yadj-=2;
                    break;
                }
                break;
            }
            if (yadj < ylimit) yadj=ylimit;
            if (yadj < buffMax) {
                if (dir == 1 || dir == 2) {
                    yadj = buffMax - yadj - 1;
                }
                if (dir > 1) {
                    buffer.SetPixel(yadj,x,color);
                } else {
                    buffer.SetPixel(x,yadj,color);
                }
            }
        }
    }
}