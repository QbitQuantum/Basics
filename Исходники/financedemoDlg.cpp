/// <summary>
/// Draw the chart according to user selection and display it in the ChartViewer.
/// </summary>
/// <param name="viewer">The ChartViewer object to display the chart.</param>
void CFinancedemoDlg::drawChart(CChartViewer *viewer)
{
    // In this demo, we just assume we plot up to the latest time. So endDate is now.
    double endDate = Chart::chartTime2((int)time(0));

    // If the trading day has not yet started (before 9:30am), or if the end date is on
    // on Sat or Sun, we set the end date to 4:00pm of the last trading day     
    while ((fmod(endDate, 86400) < 9 * 3600 + 30 * 60) || 
        (Chart::getChartWeekDay(endDate) == 0)
        || (Chart::getChartWeekDay(endDate) == 6))
        endDate = endDate - fmod(endDate, 86400) - 86400 + 16 * 3600;

     // The duration selected by the user
    int durationInDays = (int)_tcstol((const TCHAR *)m_TimeRange.GetItemDataPtr(
        m_TimeRange.GetCurSel()), 0, 0);

    // Compute the start date by subtracting the duration from the end date.
    double startDate;
    if (durationInDays >= 30)
    {
        // More or equal to 30 days - so we use months as the unit
        int YMD = Chart::getChartYMD(endDate);
        int startMonth = (YMD / 100) % 100 - durationInDays / 30;
        int startYear = YMD / 10000;
        while (startMonth < 1)
        {
            --startYear;
            startMonth += 12;
        }
        startDate = Chart::chartTime(startYear, startMonth, 1);
    }
    else
    {
        // Less than 30 days - use day as the unit. The starting point of the axis is
        // always at the start of the day (9:30am). Note that we use trading days, so
        // we skip Sat and Sun in counting the days.
        startDate = endDate - fmod(endDate, 86400) + 9 * 3600 + 30 * 60;
        for (int i = 1; i < durationInDays; ++i)
        {
            if (Chart::getChartWeekDay(startDate) == 1)
                startDate -= 3 * 86400;
            else
                startDate -= 86400;
        }
    }

    // The first moving average period selected by the user.
    CString avgText;
    m_MovAvg1.GetWindowText(avgText);
    m_avgPeriod1 = (int)_tcstol(avgText, 0, 0);
    if (m_avgPeriod1 < 0)
        m_avgPeriod1 = 0;
    if (m_avgPeriod1 > 300)
        m_avgPeriod1 = 300;

    // The second moving average period selected by the user.
    m_MovAvg2.GetWindowText(avgText);
    m_avgPeriod2 = (int)_tcstol(avgText, 0, 0);
    if (m_avgPeriod2 < 0)
        m_avgPeriod2 = 0;
    if (m_avgPeriod2 > 300)
        m_avgPeriod2 = 300;

    // We need extra leading data points in order to compute moving averages.
    int extraPoints = (m_avgPeriod1 > m_avgPeriod2) ? m_avgPeriod1 : m_avgPeriod2;
    if (extraPoints < 25)
        extraPoints = 25;

    // The data series we want to get.
    CString tickerKey = 
        (const TCHAR *)m_TickerSymbol.GetItemDataPtr(m_TickerSymbol.GetCurSel());

    // In this demo, we can get 15 min, daily, weekly or monthly data depending on
    // the time range.
    int resolution;
    if (durationInDays <= 10) 
    {
        // 10 days or less, we assume 15 minute data points are available
        resolution = 900;

        // We need to adjust the startDate backwards for the extraPoints. We assume 
        // 6.5 hours trading time per day, and 5 trading days per week.
        double dataPointsPerDay = 6.5 * 3600 / resolution;
        double adjustedStartDate = startDate - fmod(startDate, 86400) - 
            (int)(extraPoints / dataPointsPerDay * 7 / 5 + 2.9999999) * 86400;

        // Get the required 15 min data
        get15MinData(tickerKey, adjustedStartDate, endDate);
    }
    else if (durationInDays >= 4.5 * 360)
    {
        // 4 years or more - use monthly data points.
        resolution = 30 * 86400;
            
        // Adjust startDate backwards to cater for extraPoints
        int YMD = Chart::getChartYMD(startDate);
        int adjustedMonth = (YMD / 100) % 100 - extraPoints;
        int adjustedYear = YMD / 10000;
        while (adjustedMonth < 1)
        {
            --adjustedYear;
            adjustedMonth += 12;
        }
        double adjustedStartDate = Chart::chartTime(adjustedYear, adjustedMonth, 1);
        
        // Get the required monthly data
        getMonthlyData(tickerKey, adjustedStartDate, endDate);
    }
    else if (durationInDays >= 1.5 * 360)
    {
        // 1 year or more - use weekly points. 
        resolution = 7 * 86400;
 
        //Note that we need to add extra points by shifting the starting weeks backwards
        double adjustedStartDate = startDate - (extraPoints * 7 + 6) * 86400;
            
        // Get the required weekly data
        getWeeklyData(tickerKey, adjustedStartDate, endDate);
    }
    else
    {
        // Default - use daily points
        resolution = 86400;
            
        // Adjust startDate backwards to cater for extraPoints. We multiply the days 
        // by 7/5 as we assume 1 week has 5 trading days.
        double adjustedStartDate = startDate - fmod(startDate, 86400) - 
            ((extraPoints * 7 + 4) / 5 + 2) * 86400;

        // Get the required daily data
        getDailyData(tickerKey, adjustedStartDate, endDate);
    }
    
    // We now confirm the actual number of extra points (data points that are before
    // the start date) as inferred using actual data from the database.
    for (extraPoints = 0; extraPoints < m_noOfPoints; ++extraPoints)
    {
        if (m_timeStamps[extraPoints] >= startDate)
            break;
    }

    // Check if there is any valid data
    if (extraPoints >= m_noOfPoints)
    {
        // No data - just display the no data message.
        MultiChart errMsg(400, 50);
        errMsg.addTitle(Chart::TopLeft, "No data available for the specified time period", 
            "arial.ttf", 10);
        viewer->setChart(&errMsg);
        return;
    }

    // In some finance chart presentation style, even if the data for the latest day 
    // is not fully available, the axis for the entire day will still be drawn, where
    // no data will appear near the end of the axis.
    int extraTrailingPoints = 0;
    if (resolution <= 86400)
    {
        // Add extra points to the axis until it reaches the end of the day. The end
        // of day is assumed to be 16:00 (it depends on the stock exchange).
        double lastTime = m_timeStamps[m_noOfPoints - 1];
        int extraTrailingPoints = (int)((16 * 3600 - fmod(lastTime, 86400)) / resolution);
        if (extraTrailingPoints > 0)
        {
            double *extendedTimeStamps = new double[m_noOfPoints + extraTrailingPoints];
            memcpy(extendedTimeStamps, m_timeStamps, sizeof(double) * m_noOfPoints);
            for (int i = 0; i < extraTrailingPoints; ++i)
                extendedTimeStamps[m_noOfPoints + i] = lastTime + resolution * (i + 1);
            delete[] m_timeStamps;
            m_timeStamps = extendedTimeStamps;
        }
    }

    //
    // At this stage, all data is available. We can draw the chart as according to 
    // user input.
    //

    //
    // Determine the chart size. In this demo, user can select 4 different chart sizes.
    // Default is the large chart size.
    //
    int width = 780;
    int mainHeight = 250;
    int indicatorHeight = 80;

    CString selectedSize = (const TCHAR *)m_ChartSize.GetItemDataPtr(m_ChartSize.GetCurSel());
    if (selectedSize == _T("S"))
    {
        // Small chart size
        width = 450;
        mainHeight = 160;
        indicatorHeight = 60;
    }
    else if (selectedSize == _T("M"))
    {
        // Medium chart size
        width = 620;
        mainHeight = 210;
        indicatorHeight = 65;
    }
    else if (selectedSize == _T("H"))
    {
        // Huge chart size
        width = 1000;
        mainHeight = 320;
        indicatorHeight = 90;
    }

    // Create the chart object using the selected size
    FinanceChart m(width);

    // Set the data into the chart object
    m.setData(DoubleArray(m_timeStamps, m_noOfPoints + extraTrailingPoints), 
        DoubleArray(m_highData, m_noOfPoints), DoubleArray(m_lowData, m_noOfPoints), 
        DoubleArray(m_openData, m_noOfPoints), DoubleArray(m_closeData, m_noOfPoints),
        DoubleArray(m_volData, m_noOfPoints), extraPoints);

    //
    // We configure the title of the chart. In this demo chart design, we put the
    // company name as the top line of the title with left alignment.
    //
    CString companyName;
    m_TickerSymbol.GetLBText(m_TickerSymbol.GetCurSel(), companyName);
    m.addPlotAreaTitle(Chart::TopLeft, TCHARtoUTF8(companyName));

    // We displays the current date as well as the data resolution on the next line.
    const char *resolutionText = "";
    if (resolution == 30 * 86400)
        resolutionText = "Monthly";
    else if (resolution == 7 * 86400)
        resolutionText = "Weekly";
    else if (resolution == 86400)
        resolutionText = "Daily";
    else if (resolution == 900)
        resolutionText = "15-min";

    char buffer[1024];
    sprintf(buffer, "<*font=arial.ttf,size=8*>%s - %s chart", 
        m.formatValue(Chart::chartTime2((int)time(0)), "mmm dd, yyyy"), resolutionText);
    m.addPlotAreaTitle(Chart::BottomLeft, buffer);

    // A copyright message at the bottom left corner the title area
    m.addPlotAreaTitle(Chart::BottomRight, 
        "<*font=arial.ttf,size=8*>(c) Advanced Software Engineering");

    //
    // Set the grid style according to user preference. In this simple demo user
    // interface, the user can enable/disable grid lines. The grid line colors are
    // hard coded to 0xdddddd (light grey), and the plot area background color is 
    // hard coded to 0xfffff0 (pale yellow).
    //
    int vGridColor = m_VGrid.GetCheck() ? 0xdddddd : Chart::Transparent;
    int hGridColor = m_HGrid.GetCheck() ? 0xdddddd : Chart::Transparent;
    m.setPlotAreaStyle(0xfffff0, hGridColor, vGridColor, hGridColor, vGridColor);

    //
    // Set log or linear scale according to user preference
    //
    m.setLogScale(m_LogScale.GetCheck() != 0);

    //
    // Add the first techical indicator according. In this demo, we draw the first
    // indicator on top of the main chart.
    //
    addIndicator(&m, (const TCHAR *)m_Indicator1.GetItemDataPtr(m_Indicator1.GetCurSel()), 
        indicatorHeight);

    // Add the main chart
    m.addMainChart(mainHeight);

    //
    // Draw the main chart depending on the chart type the user has selected
    //
    CString selectedType = (const TCHAR *)m_ChartType.GetItemDataPtr(m_ChartType.GetCurSel());
    if (selectedType == _T("Close"))
        m.addCloseLine(0x40);
    else if (selectedType == _T("TP"))
        m.addTypicalPrice(0x40);
    else if (selectedType == _T("WC"))
        m.addWeightedClose(0x40);
    else if (selectedType == _T("Median"))
        m.addMedianPrice(0x40);

    //
    // Add moving average lines.
    //
    addMovingAvg(&m, (const TCHAR *)m_AvgType1.GetItemDataPtr(m_AvgType1.GetCurSel()), 
        m_avgPeriod1, 0x663300);
    addMovingAvg(&m, (const TCHAR *)m_AvgType2.GetItemDataPtr(m_AvgType2.GetCurSel()), 
        m_avgPeriod2, 0x9900ff);

    //
    // Draw the main chart if the user has selected CandleStick or OHLC. We
    // draw it here to make sure it is drawn behind the moving average lines
    // (that is, the moving average lines stay on top.)
    //
    if (selectedType == _T("CandleStick"))
        m.addCandleStick(0x33ff33, 0xff3333);
    else if (selectedType == _T("OHLC"))
        m.addHLOC(0x8000, 0x800000);

    //
    // Add price band/channel/envelop to the chart according to user selection
    //
    CString selectedBand = (const TCHAR *)m_Band.GetItemDataPtr(m_Band.GetCurSel());
    if (selectedBand == _T("BB"))
        m.addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);
    else if (selectedBand == _T("DC"))
        m.addDonchianChannel(20, 0x9999ff, 0xc06666ff);
    else if (selectedBand == _T("Envelop"))
        m.addEnvelop(20, 0.1, 0x9999ff, 0xc06666ff);

    //
    // Add volume bars to the main chart if necessary
    //
    if (m_Volume.GetCheck())
        m.addVolBars(indicatorHeight, 0x99ff99, 0xff9999, 0xc0c0c0);

    //
    // Add additional indicators as according to user selection.
    //
    addIndicator(&m, (const TCHAR *)m_Indicator2.GetItemDataPtr(m_Indicator2.GetCurSel()), 
        indicatorHeight);
    addIndicator(&m, (const TCHAR *)m_Indicator3.GetItemDataPtr(m_Indicator3.GetCurSel()), 
        indicatorHeight);
    addIndicator(&m, (const TCHAR *)m_Indicator4.GetItemDataPtr(m_Indicator4.GetCurSel()), 
        indicatorHeight);

    // Set the chart to the viewer
    viewer->setChart(&m);

    // Set image map (for tool tips) to the viewer
    sprintf(buffer, "title='%s {value|G}'", m.getToolTipDateFormat());
    viewer->setImageMap(m.getHTMLImageMap("", "", buffer));
}