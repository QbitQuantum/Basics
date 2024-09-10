static void Test_NonClientMetrics()
{
    NONCLIENTMETRICS NonClientMetrics;

    /* WARNING: this test requires themes and dwm to be disabled */

    SetCursorPos(0,0);

    /* Retrieve th non client metrics */
    NonClientMetrics.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &NonClientMetrics, 0);
    FlushMessages();
    COMPARE_CACHE(empty_chain);

    /* Set the non client metric without making any change */
    SystemParametersInfo(SPI_SETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &NonClientMetrics, 0);
    FlushMessages();
    COMPARE_CACHE(NcMetricsChange_chain);

    /* Set the same metrics again with the SPIF_SENDCHANGE param */
    SystemParametersInfo(SPI_SETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &NonClientMetrics, SPIF_SENDCHANGE|SPIF_UPDATEINIFILE );
    FlushMessages();
    COMPARE_CACHE(NcMetricsChange1_chain);

    /* Slightly change the caption height */
    NonClientMetrics.iCaptionHeight += 1;
    SystemParametersInfo(SPI_SETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &NonClientMetrics, 0);
    FlushMessages();
    COMPARE_CACHE(CaptionHeight_chain);

    /* Restore the original caption height */
    NonClientMetrics.iCaptionHeight -= 1;
    SystemParametersInfo(SPI_SETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &NonClientMetrics, 0);
    FlushMessages();
    COMPARE_CACHE(CaptionHeight_chain);
}