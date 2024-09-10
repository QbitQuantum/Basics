    //==============================================================================
    void parsePathString (Path& path, const String& pathString) const
    {
        String::CharPointerType d (pathString.getCharPointer().findEndOfWhitespace());

        Point<float> subpathStart, last, last2, p1, p2, p3;
        juce_wchar lastCommandChar = 0;
        bool isRelative = true;
        bool carryOn = true;

        const CharPointer_ASCII validCommandChars ("MmLlHhVvCcSsQqTtAaZz");

        while (! d.isEmpty())
        {
            if (validCommandChars.indexOf (*d) >= 0)
            {
                lastCommandChar = d.getAndAdvance();
                isRelative = (lastCommandChar >= 'a' && lastCommandChar <= 'z');
            }

            switch (lastCommandChar)
            {
            case 'M':
            case 'm':
            case 'L':
            case 'l':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    if (isRelative)
                        p1 += last;

                    if (lastCommandChar == 'M' || lastCommandChar == 'm')
                    {
                        subpathStart = p1;
                        path.startNewSubPath (p1);
                        lastCommandChar = 'l';
                    }
                    else
                        path.lineTo (p1);

                    last2 = last;
                    last = p1;
                }
                break;

            case 'H':
            case 'h':
                if (parseCoord (d, p1.x, false, true))
                {
                    if (isRelative)
                        p1.x += last.x;

                    path.lineTo (p1.x, last.y);

                    last2.x = last.x;
                    last.x = p1.x;
                }
                else
                {
                    ++d;
                }
                break;

            case 'V':
            case 'v':
                if (parseCoord (d, p1.y, false, false))
                {
                    if (isRelative)
                        p1.y += last.y;

                    path.lineTo (last.x, p1.y);

                    last2.y = last.y;
                    last.y = p1.y;
                }
                else
                {
                    ++d;
                }
                break;

            case 'C':
            case 'c':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p2, false)
                     && parseCoordsOrSkip (d, p3, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p2 += last;
                        p3 += last;
                    }

                    path.cubicTo (p1, p2, p3);

                    last2 = p2;
                    last = p3;
                }
                break;

            case 'S':
            case 's':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p3, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p3 += last;
                    }

                    p2 = last + (last - last2);
                    path.cubicTo (p2, p1, p3);

                    last2 = p1;
                    last = p3;
                }
                break;

            case 'Q':
            case 'q':
                if (parseCoordsOrSkip (d, p1, false)
                     && parseCoordsOrSkip (d, p2, false))
                {
                    if (isRelative)
                    {
                        p1 += last;
                        p2 += last;
                    }

                    path.quadraticTo (p1, p2);

                    last2 = p1;
                    last = p2;
                }
                break;

            case 'T':
            case 't':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    if (isRelative)
                        p1 += last;

                    p2 = last + (last - last2);
                    path.quadraticTo (p2, p1);

                    last2 = p2;
                    last = p1;
                }
                break;

            case 'A':
            case 'a':
                if (parseCoordsOrSkip (d, p1, false))
                {
                    String num;

                    if (parseNextNumber (d, num, false))
                    {
                        const float angle = num.getFloatValue() * (180.0f / float_Pi);

                        if (parseNextNumber (d, num, false))
                        {
                            const bool largeArc = num.getIntValue() != 0;

                            if (parseNextNumber (d, num, false))
                            {
                                const bool sweep = num.getIntValue() != 0;

                                if (parseCoordsOrSkip (d, p2, false))
                                {
                                    if (isRelative)
                                        p2 += last;

                                    if (last != p2)
                                    {
                                        double centreX, centreY, startAngle, deltaAngle;
                                        double rx = p1.x, ry = p1.y;

                                        endpointToCentreParameters (last.x, last.y, p2.x, p2.y,
                                                                    angle, largeArc, sweep,
                                                                    rx, ry, centreX, centreY,
                                                                    startAngle, deltaAngle);

                                        path.addCentredArc ((float) centreX, (float) centreY,
                                                            (float) rx, (float) ry,
                                                            angle, (float) startAngle, (float) (startAngle + deltaAngle),
                                                            false);

                                        path.lineTo (p2);
                                    }

                                    last2 = last;
                                    last = p2;
                                }
                            }
                        }
                    }
                }

                break;

            case 'Z':
            case 'z':
                path.closeSubPath();
                last = last2 = subpathStart;
                d = d.findEndOfWhitespace();
                lastCommandChar = 'M';
                break;

            default:
                carryOn = false;
                break;
            }

            if (! carryOn)
                break;
        }

        // paths that finish back at their start position often seem to be
        // left without a 'z', so need to be closed explicitly..
        if (path.getCurrentPosition() == subpathStart)
            path.closeSubPath();
    }