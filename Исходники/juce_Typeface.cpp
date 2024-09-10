    void applyVerticalHintingTransform (float fontSize, Path& path)
    {
        if (cachedSize != fontSize)
        {
            cachedSize = fontSize;
            cachedScale = Scaling (top, middle, bottom, fontSize);
        }

        if (bottom < top + 3.0f / fontSize)
            return;

        Path result;

        for (Path::Iterator i (path); i.next();)
        {
            switch (i.elementType)
            {
                case Path::Iterator::startNewSubPath:  result.startNewSubPath (i.x1, cachedScale.apply (i.y1)); break;
                case Path::Iterator::lineTo:           result.lineTo (i.x1, cachedScale.apply (i.y1)); break;
                case Path::Iterator::quadraticTo:      result.quadraticTo (i.x1, cachedScale.apply (i.y1),
                                                                           i.x2, cachedScale.apply (i.y2)); break;
                case Path::Iterator::cubicTo:          result.cubicTo (i.x1, cachedScale.apply (i.y1),
                                                                       i.x2, cachedScale.apply (i.y2),
                                                                       i.x3, cachedScale.apply (i.y3)); break;
                case Path::Iterator::closePath:        result.closeSubPath(); break;
                default:                               jassertfalse; break;
            }
        }

        result.swapWithPath (path);
    }