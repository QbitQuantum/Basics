//==============================================================================
void RectangleList::add (const Rectangle<int>& rect)
{
    if (! rect.isEmpty())
    {
        if (rects.size() == 0)
        {
            rects.add (rect);
        }
        else
        {
            bool anyOverlaps = false;

            int i;
            for (i = rects.size(); --i >= 0;)
            {
                Rectangle<int>& ourRect = rects.getReference (i);

                if (rect.intersects (ourRect))
                {
                    if (rect.contains (ourRect))
                        rects.remove (i);
                    else if (! ourRect.reduceIfPartlyContainedIn (rect))
                        anyOverlaps = true;
                }
            }

            if (anyOverlaps && rects.size() > 0)
            {
                RectangleList r (rect);

                for (i = rects.size(); --i >= 0;)
                {
                    const Rectangle<int>& ourRect = rects.getReference (i);

                    if (rect.intersects (ourRect))
                    {
                        r.subtract (ourRect);

                        if (r.rects.size() == 0)
                            return;
                    }
                }

                for (i = r.getNumRectangles(); --i >= 0;)
                    rects.add (r.rects.getReference (i));
            }
            else
            {
                rects.add (rect);
            }
        }
    }
}