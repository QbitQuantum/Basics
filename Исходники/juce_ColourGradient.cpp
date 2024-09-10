//==============================================================================
int ColourGradient::createLookupTable (const AffineTransform& transform, HeapBlock <PixelARGB>& lookupTable) const
{
   #if JUCE_DEBUG
    // trying to use the object without setting its co-ordinates? Have a careful read of
    // the comments for the constructors.
    jassert (point1.getX() != 987654.0f);
   #endif

    const int numEntries = jlimit (1, jmax (1, (colours.size() - 1) << 8),
                                   3 * (int) point1.transformedBy (transform)
                                                .getDistanceFrom (point2.transformedBy (transform)));
    lookupTable.malloc ((size_t) numEntries);

    if (colours.size() >= 2)
    {
        jassert (colours.getReference(0).position == 0); // the first colour specified has to go at position 0

        PixelARGB pix1 (colours.getReference (0).colour.getPixelARGB());
        int index = 0;

        for (int j = 1; j < colours.size(); ++j)
        {
            const ColourPoint& p = colours.getReference (j);
            const int numToDo = roundToInt (p.position * (numEntries - 1)) - index;
            const PixelARGB pix2 (p.colour.getPixelARGB());

            for (int i = 0; i < numToDo; ++i)
            {
                jassert (index >= 0 && index < numEntries);

                lookupTable[index] = pix1;
                lookupTable[index].tween (pix2, (uint32) (i << 8) / numToDo);
                ++index;
            }

            pix1 = pix2;
        }

        while (index < numEntries)
            lookupTable [index++] = pix1;
    }
    else
    {
        jassertfalse; // no colours specified!
    }

    return numEntries;
}