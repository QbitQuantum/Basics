void ColorWashEffect::Render(Effect *effect, const SettingsMap &SettingsMap, RenderBuffer &buffer) {
    bool HorizFade = SettingsMap.GetBool(CHECKBOX_ColorWash_HFade);
    bool VertFade = SettingsMap.GetBool(CHECKBOX_ColorWash_VFade);
    float cycles = SettingsMap.GetDouble(TEXTCTRL_ColorWash_Cycles, 1.0);
    bool EntireModel = SettingsMap.GetInt(CHECKBOX_ColorWash_EntireModel, 1);
    int x1 = SettingsMap.GetInt(SLIDER_ColorWash_X1, -50);
    int y1 = SettingsMap.GetInt(SLIDER_ColorWash_Y1, -50);
    int x2 = SettingsMap.GetInt(SLIDER_ColorWash_X2, 50);
    int y2 = SettingsMap.GetInt(SLIDER_ColorWash_Y2, 50);
    bool shimmer = SettingsMap.GetInt(CHECKBOX_ColorWash_Shimmer, 0);
    bool circularPalette = SettingsMap.GetInt(CHECKBOX_ColorWash_CircularPalette, 0);
    
    
    int x,y;
    xlColor color, orig;
    
    double position = buffer.GetEffectTimeIntervalPosition(cycles);
    buffer.GetMultiColorBlend(position, circularPalette, color);
    
    int startX = 0;
    int startY = 0;
    int endX = buffer.BufferWi - 1;
    int endY = buffer.BufferHt - 1;
    
    if (!EntireModel) {
        startX = std::min(x1, x2);
        endX = std::max(x1, x2);
        startY = std::min(y1, y2);
        endY = std::max(y1, y2);
        startX = std::round(double(buffer.BufferWi - 0.5) * (double)startX / 100.0);
        endX = std::round(double(buffer.BufferWi - 0.5) * (double)endX / 100.0);
        startY = std::round(double(buffer.BufferHt - 0.5) * (double)startY / 100.0);
        endY = std::round(double(buffer.BufferHt - 0.5) * (double)endY / 100.0);
        startX = std::max(startX, 0);
        endX = std::min(endX, buffer.BufferWi - 1);
        startY = std::max(startY, 0);
        endY = std::min(endY, buffer.BufferHt - 1);
    }
    int tot = buffer.curPeriod - buffer.curEffStartPer;
    if (!shimmer || (tot % 2) == 0) {
        double HalfHt=double(endY - startY)/2.0;
        double HalfWi=double(endX - startX)/2.0;
        
        orig = color;
        HSVValue hsvOrig = color.asHSV();
        xlColor color2 = color;
        for (x=startX; x <= endX; x++)
        {
            HSVValue hsv = hsvOrig;
            if (HorizFade) {
                if (buffer.allowAlpha) {
                    color.alpha = (double)orig.alpha*(1.0-std::abs(HalfWi-x-startX)/HalfWi);
                } else {
                    hsv.value*=1.0-std::abs(HalfWi-x-startX)/HalfWi;
                    color = hsv;
                }
            }
            color2.alpha = color.alpha;
            for (y=startY; y<=endY; y++) {
                if (VertFade) {
                    if (buffer.allowAlpha) {
                        color.alpha = (double)color2.alpha*(1.0-std::abs(HalfHt-(y-startY))/HalfHt);
                    } else {
                        HSVValue hsv2 = hsv;
                        hsv2.value*=1.0-std::abs(HalfHt-(y-startY))/HalfHt;
                        color = hsv2;
                    }
                }
                buffer.SetPixel(x, y, color);
            }
        }
    } else {
        orig = xlBLACK;
    }
    wxMutexLocker lock(effect->GetBackgroundDisplayList().lock);
    if (VertFade || HorizFade) {
        effect->GetBackgroundDisplayList().resize((buffer.curEffEndPer - buffer.curEffStartPer + 1) * 4 * 2);
        int total = buffer.curEffEndPer - buffer.curEffStartPer + 1;
        double x1 = double(buffer.curPeriod - buffer.curEffStartPer) / double(total);
        double x2 = (buffer.curPeriod - buffer.curEffStartPer + 1.0) / double(total);
        int idx = (buffer.curPeriod - buffer.curEffStartPer) * 8;
        buffer.SetDisplayListVRect(effect, idx, x1, 0.0, x2, 0.5,
                                   xlBLACK, orig);
        buffer.SetDisplayListVRect(effect, idx + 4, x1, 0.5, x2, 1.0,
                                   orig, xlBLACK);
    } else {
        effect->GetBackgroundDisplayList().resize((buffer.curEffEndPer - buffer.curEffStartPer + 1) * 4);
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;
        buffer.CopyPixelsToDisplayListX(effect, midY, midX, midX);
    }

}