void TextBlock::CalculateCacheParams()
{
    if (text.empty())
    {
        cacheFinalSize = Vector2(0.f, 0.f);
        cacheW = 0;
        cacheDx = 0;
        cacheDy = 0;

        return;
    }

    bool useJustify = ((align & ALIGN_HJUSTIFY) != 0);
    font->SetSize(originalFontSize);
    Vector2 drawSize = rectSize;
    
    if(requestedSize.dx > 0)
    {
        drawSize.x = requestedSize.dx;
    }
    if(requestedSize.dy > 0)
    {
        drawSize.y = requestedSize.dy;
    }
    
    int32 w = (int32)drawSize.x;
    int32 h = (int32)drawSize.y;
    
    Size2i textSize;
    stringSizes.clear();
    
    // This is a temporary fix to correctly handle long multiline texts
    // which can't be broken to the separate lines.
    if (isMultilineEnabled)
    {
        if(isMultilineBySymbolEnabled)
        {
            font->SplitTextBySymbolsToStrings(text, drawSize, multilineStrings);
        }
        else
        {
            font->SplitTextToStrings(text, drawSize, multilineStrings);
        }
        
        treatMultilineAsSingleLine = multilineStrings.size() == 1;
    }
    
    if(!isMultilineEnabled || treatMultilineAsSingleLine)
    {
        textSize = font->GetStringSize(text);
        pointsStr.clear();
        if(fittingType & FITTING_POINTS)
        {
            if(drawSize.x < textSize.dx)
            {
                Size2i textSizePoints;
                
                int32 length = (int32)text.length();
                for(int32 i = length - 1; i > 0; --i)
                {
                    pointsStr.clear();
                    pointsStr.append(text, 0, i);
                    pointsStr += L"...";
                    
                    textSize = font->GetStringSize(pointsStr);
                    if(textSize.dx <= drawSize.x)
                    {
                        break;
                    }
                }
            }
        }
        else if(!((fittingType & FITTING_REDUCE) || (fittingType & FITTING_ENLARGE)) && (drawSize.x < textSize.dx) && (requestedSize.x >= 0))
        {
            Size2i textSizePoints;
            int32 length = (int32)text.length();
            if(ALIGN_RIGHT & align)
            {
                for(int32 i = 1; i < length - 1; ++i)
                {
                    pointsStr.clear();
                    pointsStr.append(text, i, length - i);
                    
                    textSize = font->GetStringSize(pointsStr);
                    if(textSize.dx <= drawSize.x)
                    {
                        break;
                    }
                }
            }
            else if(ALIGN_HCENTER & align)
            {
                int32 endPos = length / 2;
                int32 startPos = endPos - 1;
                
                int32 count = endPos;
                WideString savedStr = L"";
                
                for(int32 i = 1; i < count; ++i)
                {
                    pointsStr.clear();
                    pointsStr.append(text, startPos, endPos - startPos);
                    
                    textSize = font->GetStringSize(pointsStr);
                    if(drawSize.x <= textSize.dx)
                    {
                        break;
                    }
                    
                    --startPos;
                    ++endPos;
                }
            }
        }
        else if(((fittingType & FITTING_REDUCE) || (fittingType & FITTING_ENLARGE)) && (requestedSize.dy >= 0 || requestedSize.dx >= 0))
        {
            bool isChanged = false;
            float prevFontSize = font->GetRenderSize();
            while (true)
            {
                float yMul = 1.0f;
                float xMul = 1.0f;
                
                bool xBigger = false;
                bool xLower = false;
                bool yBigger = false;
                bool yLower = false;
                if(requestedSize.dy >= 0)
                {
                    h = textSize.dy;
                    if((isChanged || fittingType & FITTING_REDUCE) && textSize.dy > drawSize.y)
                    {
                        if (prevFontSize < font->GetRenderSize())
                        {
                            font->SetRenderSize(prevFontSize);
                            textSize = font->GetStringSize(text);
                            h = textSize.dy;
                            if (requestedSize.dx >= 0)
                            {
                                w = textSize.dx;
                            }
                            break;
                        }
                        yBigger = true;
                        yMul = drawSize.y / textSize.dy;
                    }
                    else if((isChanged || fittingType & FITTING_ENLARGE) && textSize.dy < drawSize.y * 0.9)
                    {
                        yLower = true;
                        yMul = (drawSize.y * 0.9f) / textSize.dy;
                        if(yMul < 1.01f)
                        {
                            yLower = false;
                        }
                    }
                }
                
                if(requestedSize.dx >= 0)
                {
                    w = textSize.dx;
                    if((isChanged || fittingType & FITTING_REDUCE) && textSize.dx > drawSize.x)
                    {
                        if (prevFontSize < font->GetRenderSize())
                        {
                            font->SetRenderSize(prevFontSize);
                            textSize = font->GetStringSize(text);
                            w = textSize.dx;
                            if (requestedSize.dy >= 0)
                            {
                                h = textSize.dy;
                            }
                            break;
                        }
                        xBigger = true;
                        xMul = drawSize.x / textSize.dx;
                    }
                    else if((isChanged || fittingType & FITTING_ENLARGE) && textSize.dx < drawSize.x * 0.95)
                    {
                        xLower = true;
                        xMul = (drawSize.x * 0.95f) / textSize.dx;
                        if(xMul < 1.01f)
                        {
                            xLower = false;
                        }
                    }
                }
                
                
                if((!xBigger && !yBigger) && (!xLower || !yLower))
                {
                    break;
                }
                
                float finalSize = font->GetRenderSize();
                prevFontSize = finalSize;
                isChanged = true;
                if(xMul < yMul)
                {
                    finalSize *= xMul;
                }
                else
                {
                    finalSize *= yMul;
                }
                font->SetRenderSize(finalSize);
                textSize = font->GetStringSize(text);
            };
        }
        
        if (treatMultilineAsSingleLine)
        {
            // Another temporary solution to return correct multiline strings/
            // string sizes.
            multilineStrings.clear();
            stringSizes.clear();
            multilineStrings.push_back(text);
            stringSizes.push_back(font->GetStringSize(text).dx);
        }
    }
    else //if(!isMultilineEnabled)
    {
        if(fittingType && (requestedSize.dy >= 0/* || requestedSize.dx >= 0*/) && text.size() > 3)
        {
            //				Logger::FrameworkDebug("Fitting enabled");
            Vector2 rectSz = rectSize;
            if(requestedSize.dx > 0)
            {
                rectSz.dx = requestedSize.dx;
            }
            if(isMultilineBySymbolEnabled)
                font->SplitTextBySymbolsToStrings(text, rectSz, multilineStrings);
            else
                font->SplitTextToStrings(text, rectSz, multilineStrings);
            
            textSize.dx = 0;
            textSize.dy = 0;
            
            int32 yOffset = font->GetVerticalSpacing();
            //				int32 fontHeight = font->GetFontHeight() + 1 + yOffset;
            //				textSize.dy = yOffset*2 + fontHeight * (int32)multilineStrings.size();
            int32 fontHeight = font->GetFontHeight() + yOffset;
            textSize.dy = fontHeight * (int32)multilineStrings.size() - yOffset;
            float lastSize = font->GetRenderSize();
            float lastHeight = (float32)textSize.dy;
            
            bool isChanged = false;
            while (true)
            {
                float yMul = 1.0f;
                
                bool yBigger = false;
                bool yLower = false;
                if(requestedSize.dy >= 0)
                {
                    h = textSize.dy;
                    if((isChanged || fittingType & FITTING_REDUCE) && textSize.dy > drawSize.y)
                    {
                        yBigger = true;
                        yMul = drawSize.y / textSize.dy;
                        if(lastSize < font->GetRenderSize())
                        {
                            font->SetRenderSize(lastSize);
                            h = (int32)lastHeight;
                            break;
                        }
                    }
                    else if((isChanged || fittingType & FITTING_ENLARGE) && textSize.dy < drawSize.y * 0.95)
                    {
                        yLower = true;
                        if(textSize.dy < drawSize.y * 0.75f)
                        {
                            yMul = (drawSize.y * 0.75f) / textSize.dy;
                        }
                        else if(textSize.dy < drawSize.y * 0.8f)
                        {
                            yMul = (drawSize.y * 0.8f) / textSize.dy;
                        }
                        else if(textSize.dy < drawSize.y * 0.85f)
                        {
                            yMul = (drawSize.y * 0.85f) / textSize.dy;
                        }
                        else if(textSize.dy < drawSize.y * 0.9f)
                        {
                            yMul = (drawSize.y * 0.9f) / textSize.dy;
                        }
                        else
                        {
                            yMul = (drawSize.y * 0.95f) / textSize.dy;
                        }
                        if (yMul == 1.0f)
                        {
                            yMul = 1.05f;
                        }
                    }
                }
                
                if(!yBigger && !yLower)
                {
                    break;
                }
                
                lastHeight = (float32)textSize.dy;
                
                float finalSize = lastSize = font->GetRenderSize();
                isChanged = true;
                finalSize *= yMul;
                
                font->SetRenderSize(finalSize);
                //					textSize = font->GetStringSize(text);
                
                if(isMultilineBySymbolEnabled)
                    font->SplitTextBySymbolsToStrings(text, rectSz, multilineStrings);
                else
                    font->SplitTextToStrings(text, rectSz, multilineStrings);
                
                textSize.dy = 0;
                
                int32 yOffset = font->GetVerticalSpacing();
                //					int32 fontHeight = font->GetFontHeight() + 1 + yOffset;
                //					textSize.dy = yOffset*2 + fontHeight * (int32)multilineStrings.size();
                int32 fontHeight = font->GetFontHeight() + yOffset;
                textSize.dy = fontHeight * (int32)multilineStrings.size() - yOffset;
                
            };
            
        }
        //			Logger::FrameworkDebug("Font size: %.4f", font->GetSize());
        
        
        Vector2 rectSz = rectSize;
        if(requestedSize.dx > 0)
        {
            rectSz.dx = requestedSize.dx;
        }
        if(isMultilineBySymbolEnabled)
            font->SplitTextBySymbolsToStrings(text, rectSz, multilineStrings);
        else
            font->SplitTextToStrings(text, rectSz, multilineStrings);
        
        textSize.dx = 0;
        textSize.dy = 0;
        
        int32 yOffset = font->GetVerticalSpacing();
        //			Logger::FrameworkDebug("yOffset = %.4d", yOffset);
        //			int32 fontHeight = font->GetFontHeight() + 1 + yOffset;
        //			textSize.dy = yOffset*2 + fontHeight * (int32)multilineStrings.size();
        int32 fontHeight = font->GetFontHeight() + yOffset;
        //			Logger::FrameworkDebug("fontHeight = %.4d", fontHeight);
        textSize.dy = fontHeight * (int32)multilineStrings.size() - yOffset;
        
        stringSizes.reserve(multilineStrings.size());
        for (int32 line = 0; line < (int32)multilineStrings.size(); ++line)
        {
            Size2i stringSize = font->GetStringSize(multilineStrings[line]);
            stringSizes.push_back(stringSize.dx);
            if(requestedSize.dx >= 0)
            {
                textSize.dx = Max(textSize.dx, Min(stringSize.dx, (int)drawSize.x));
            }
            else
            {
                textSize.dx = Max(textSize.dx, stringSize.dx);
            }
        }
    }
    
    if(requestedSize.dx == 0)
    {
        w = Min(w, textSize.dx);
        //			Logger::FrameworkDebug("On size not requested: w = %d", w);
    }
    else if(requestedSize.dx < 0)
    {
        w = textSize.dx;
        //			Logger::FrameworkDebug("On size automated: w = %d", w);
    }
    if(requestedSize.dy == 0)
    {
        h = Min(h, textSize.dy);
        //			Logger::FrameworkDebug("On size not requested: h = %d", h);
    }
    else if(requestedSize.dy < 0)
    {
        h = textSize.dy;
        //			Logger::FrameworkDebug("On size automated: h = %d", w);
    }
    
    if (requestedSize.dx >= 0 && useJustify)
    {
        w = (int32)drawSize.dx;
    }
    
    
    
    //calc texture size
    int32 dx = (int32)ceilf(Core::GetVirtualToPhysicalFactor() * w);
    int32 dy = (int32)ceilf(Core::GetVirtualToPhysicalFactor() * h);
    
    cacheUseJustify = useJustify;
    cacheDx = dx;
    EnsurePowerOf2(cacheDx);
    
    cacheDy = dy;
    EnsurePowerOf2(cacheDy);
    
    cacheW = w;
    cacheFinalSize.x = (float32)dx / Core::GetVirtualToPhysicalFactor();
    cacheFinalSize.y = (float32)dy / Core::GetVirtualToPhysicalFactor();
}