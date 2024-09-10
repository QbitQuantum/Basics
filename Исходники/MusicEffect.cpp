void MusicEffect::RenderCollide(RenderBuffer &buffer, int x, int bars, int startNote, int endNote, bool in, std::list<MusicEvent*>& events, int colourTreatment, bool fade)
{
    int event = -1;
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        event++;
        if ((*it)->IsEventActive(buffer.curPeriod))
        {
            float progress = (*it)->OffsetInDuration(buffer.curPeriod);

            int mid = buffer.BufferHt / 2;
            int length = buffer.BufferHt;
            int leftstart, leftend;

            if (!in)
            {
                progress = 1.0 - progress;
            }

            leftstart = 0 - mid - 1 + progress * length;
            leftend = leftstart + mid;
            if (leftend > mid)
            {
                leftend = mid;
            }

            int loopstart = leftstart;
            if (loopstart < 0)
            {
                loopstart = 0;
            }

            for (int y = loopstart; y < leftend; y++)
            {
                xlColor c = xlWHITE;
                float proportion = ((float)y - (float)leftstart) / (float)mid;
                if (colourTreatment == 1)
                {
                    // distinct
                    float percolour = 1.0 / (float)buffer.GetColorCount();
                    for (int i = 0; i < buffer.GetColorCount(); i++)
                    {
                        if (proportion <= ((float)i + 1.0)*percolour)
                        {
                            buffer.palette.GetColor(i, c);
                            break;
                        }
                    }
                }
                else if (colourTreatment == 2)
                {
                    // blend
                    buffer.GetMultiColorBlend(proportion, false, c);
                }
                else if (colourTreatment == 3)
                {
                    buffer.palette.GetColor(event % buffer.GetColorCount(), c);
                }

                if (fade)
                {
                    c.alpha = progress * 255;
                }

                buffer.SetPixel(x, y, c);
                buffer.SetPixel(x, mid - y + mid - 1, c);
            }
        }
    }
}