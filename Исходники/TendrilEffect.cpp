void TendrilEffect::Render(RenderBuffer &buffer, int movement,
                            int tunemovement, int movementSpeed, int thickness,
                           float friction, float dampening,
                           float tension, int trails, int length)
{
    buffer.drawingContext->Clear();

    if (friction < 0.4)
    {
        friction = 0.4;
    }
    if (friction > 0.6)
    {
        friction = 0.6;
    }
    if (dampening < 0)
    {
        dampening = 0;
    }
    if (dampening > 0.5)
    {
        dampening = 0.5;
    }
    if (tension < 0.96)
    {
        tension = 0.96;
    }
    if (tension > 0.999)
    {
        tension = 0.999;
    }
    TendrilRenderCache *cache = (TendrilRenderCache*)buffer.infoCache[id];
    if (cache == nullptr) {
        cache = new TendrilRenderCache();
        buffer.infoCache[id] = cache;
    }

    int &_movement = cache->_movement;
    int &_tunemovement = cache->_tunemovement;
    int &_mv1 = cache->_mv1;
    int &_mv2 = cache->_mv2;
    int &_mv3 = cache->_mv3;
    int &_mv4 = cache->_mv4;
    int &_thickness = cache->_thickness;
    int &_trails = cache->_trails;
    int &_length = cache->_length;
    float &_friction = cache->_friction;
    float &_dampening = cache->_dampening;
    float &_tension = cache->_tension;
    xlColor &_colour = cache->_colour;
    Tendril* &_tendril = cache->_tendril;
    xlColor color1;
    buffer.palette.GetColor(0, color1);

    if (_tendril == NULL ||
        _movement != movement ||
        _tunemovement != tunemovement ||
        _thickness != thickness ||
        _friction != friction ||
        _dampening != dampening ||
        _tension != tension ||
        _trails != trails ||
        _length != length ||
        _colour != color1)
    {
        if (_tendril != NULL)
        {
            delete _tendril;
        }
        _thickness = thickness;
        _friction = friction;
        _dampening = dampening;
        _tension = tension;
        _trails = trails;
        _length = length;
        _colour = color1;
        wxPoint start(buffer.BufferWi/2, buffer.BufferHt/2);
        _tendril = new Tendril(_friction, _trails, _length, _dampening, _tension, -1, -1, &start, _colour, _thickness, buffer.BufferWi, buffer.BufferHt);

        if (_movement != movement || _tunemovement != tunemovement)
        {
            switch(movement)
            {
            case 1:
                // random
                // no initialisation
                break;
            case 2:
                // corners
                _mv1 = 0; // current x
                _mv2 = 0; // current y
                _mv3 = 0; // corner
                _mv4 = tunemovement; // movement amount
                if (_mv4 == 0)
                {
                    _mv4 = 1;
                }
                break;
            case 3:
                // circles
                _mv1 = 0; // radians
                _mv2 = std::min(buffer.BufferWi, buffer.BufferHt) / 2; // radius
                _mv3 = tunemovement * 3;
                if (_mv3 == 0)
                {
                    _mv3 = 1;
                }
                break;
            case 4:
                // horizontal zig zag
                _mv1 = 0; // current y
                _mv2 = (double)tunemovement * 1.5;
                if (_mv2 == 0)
                {
                    _mv2 = 1;
                }
                _mv3 = 1; // direction
                break;
            case 5:
                // vertical zig zag
                _mv1 = 0; // current x
                _mv2 = (double)tunemovement * 1.5;
                _mv3 = 1; // direction
                break;
            }
        }
        _movement = movement;
        _tunemovement = tunemovement;
    }

    const double PI  = 3.141592653589793238463;
    int speed = 10 - movementSpeed;
    if (speed <= 0 || buffer.curPeriod % speed == 0)
    {
        switch(_movement)
        {
            case 1:
                _tendril->UpdateRandomMove(_tunemovement);
                break;
            case 2:
                switch(_mv3)
                {
                case 0:
                    _mv1+=std::max(buffer.BufferWi/_mv4,1);
                    if (_mv1 >= buffer.BufferWi - buffer.BufferWi / _mv4)
                    {
                        _mv3++;
                    }
                    break;
                case 1:
                    _mv2+=std::max(buffer.BufferHt/_mv4,1);
                    if (_mv2 >= buffer.BufferHt - buffer.BufferHt / _mv4)
                    {
                        _mv3++;
                    }
                    break;
                case 2:
                    _mv1-=std::max(buffer.BufferWi/_mv4,1);
                    if (_mv1 <= buffer.BufferWi / _mv4)
                    {
                        _mv3++;
                    }
                    break;
                case 3:
                    _mv2-=std::max(buffer.BufferHt/_mv4,1);
                    if (_mv2 <= buffer.BufferHt / _mv4)
                    {
                        _mv3 = 0;
                    }
                    break;
                }
                _tendril->Update(_mv1, _mv2);
                break;
            case 3:
                _mv1++;
                if (_mv1 > _mv3)
                {
                    _mv1 = 0;
                }
                {
                    int x = (double)_mv2 * cos((double)_mv1 * 2.0 * PI / (double)_mv3) + (double)buffer.BufferWi / 2.0;
                    int y = (double)_mv2 * sin((double)_mv1 * 2.0 * PI / (double)_mv3) + (double)buffer.BufferHt / 2.0;
                    _tendril->Update(x, y);
                }
                break;
            case 4:
                {
                    _mv1 = _mv1 + _mv3;
                    int x = sin(std::max((double)buffer.BufferHt / (double)_mv2, 0.5) * PI * (double)_mv1 / (double)buffer.BufferHt) * (double)buffer.BufferWi / 2.0 + (double)buffer.BufferWi / 2.0;
                    if (_mv1 >= buffer.BufferHt || _mv1 <= 0)
                    {
                        _mv3 = _mv3 * -1;
                    }
                    if (_mv3 < 0)
                    {
                        x = buffer.BufferWi - x;
                    }
                    _tendril->Update(x, _mv1);
                }
                break;
            case 5:
                {
                    _mv1 = _mv1 + _mv3;
                    int y = sin(std::max((double)buffer.BufferWi / (double)_mv2, 0.5) * PI * (double)_mv1 / (double)buffer.BufferWi) * (double)buffer.BufferHt / 2.0 + (double)buffer.BufferHt / 2.0;
                    if (_mv1 >= buffer.BufferWi || _mv1 <= 0)
                    {
                        _mv3 = _mv3 * -1;
                    }
                    if (_mv3 < 0)
                    {
                        y = buffer.BufferHt - y;
                    }
                    _tendril->Update(_mv1, y);
                }
                break;
        }
    }

    _tendril->Draw(buffer.drawingContext);
    wxImage * image = buffer.drawingContext->FlushAndGetImage();
    bool hasAlpha = image->HasAlpha();

    xlColor c;
    for(int y=0; y<buffer.BufferHt; y++)
    {
        for(int x=0; x< buffer.BufferWi; x++)
        {
            if (hasAlpha)
            {
                c.Set(image->GetRed(x,y),image->GetGreen(x,y),image->GetBlue(x,y),image->GetAlpha(x,y));
            }
            else
            {
                c.Set(image->GetRed(x,y),image->GetGreen(x,y),image->GetBlue(x,y), 255);
            }
            buffer.SetPixel(x, y, c);
        }
    }
}