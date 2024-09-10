void PeakMeter::paint(Graphics& g)
{
    int x = 0;
    int y = 1;
    int width = TraKmeter::TRAKMETER_LABEL_WIDTH - 14;
    int height = 13;

    g.setColour(Colours::grey.brighter(0.6f));
    g.fillRect(x, y, width + 3, height);

    g.setColour(Colours::black);
    g.drawRect(x, y, width + 3, height);

    int x_2 = TraKmeter::TRAKMETER_LABEL_WIDTH + nInputChannels * (TraKmeter::TRAKMETER_SEGMENT_WIDTH + 6) - 1;
    g.setColour(Colours::grey.brighter(0.6f));
    g.fillRect(x + x_2, y, width + 3, height);

    g.setColour(Colours::black);
    g.drawRect(x + x_2 + x, y, width + 3, height);

    String strMarker = "dB";

    g.setColour(Colours::black);
    g.setFont(12.0f);
    drawMarkers(g, strMarker, x + 1, y + 1, width, height, Colours::black);

    g.setColour(Colours::grey.brighter(0.6f));
    g.fillRect((nWidth - 32) / 2, y, 32, height);

    g.setColour(Colours::black);
    g.drawRect((nWidth - 32) / 2, y, 32, height);

    g.setColour(Colours::black);
    g.drawFittedText("Peak", (nWidth - 32) / 2, y, 32, height, Justification::centred, 1, 1.0f);

    y = nMeterPositionTop;
    strMarker = "OVR";

    g.setFont(12.0f);
    g.setColour(Colour(0.00f, 1.0f, 1.0f, 1.0f));
    drawMarkers(g, strMarker, x + 1, y, width, height, Colour(0.00f, 1.0f, 1.0f, 1.0f));

    y -= round_to_int(nSegmentHeight / 2.0f);

    for (int n = nNumberOfBars; n > 2; n -= 2)
    {
        int nLevel = nCrestFactor + n - 19;

        if (nLevel > 0)
        {
            strMarker = "+" + String(nLevel);
        }
        else
        {
            strMarker = String(nLevel);
        }

        y += 2 * nSegmentHeight;

        if (nLevel == nCrestFactor - 10)
        {
            g.setColour(Colours::white);
            drawMarkers(g, strMarker, x + 1, y, width, height, Colours::white.darker(0.5f));
        }
        else
        {
            g.setColour(Colours::grey.brighter(0.1f));
            drawMarkers(g, strMarker, x + 1, y, width, height, Colours::grey.darker(0.1f));
        }
    }

    y -= round_to_int(nSegmentHeight / 2.0f);
    strMarker = "LOW";

    g.setColour(Colour(0.58f, 1.0f, 1.0f, 1.0f));
    drawMarkers(g, strMarker, x + 1, y + 2 * nSegmentHeight, width, height, Colour(0.58f, 1.0f, 1.0f, 1.0f));

    for (int nChannel = 0; nChannel < nInputChannels; nChannel++)
    {
        int nPositionX = TraKmeter::TRAKMETER_LABEL_WIDTH + nChannel * (TraKmeter::TRAKMETER_SEGMENT_WIDTH + 6) - 3;
        nPositionX += (nChannel % 2) ? -2 : 2;

        g.setColour(Colours::black.brighter(0.15f));
        g.fillRect(nPositionX - 1, nMeterPositionTop - 1, TraKmeter::TRAKMETER_SEGMENT_WIDTH + 2, nHeight);

        g.setColour(Colours::black);
        g.fillRect(nPositionX, nMeterPositionTop, TraKmeter::TRAKMETER_SEGMENT_WIDTH, nSegmentHeight + 1);
    }
}