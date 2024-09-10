static void TabElementSize(
    void *clientData, void *elementRecord, Tk_Window tkwin,
    int *widthPtr, int *heightPtr, Ttk_Padding *paddingPtr)
{
    *heightPtr = GetThemeMetric(kThemeMetricLargeTabHeight, heightPtr);
    *paddingPtr = Ttk_MakePadding(0, 0, 0, 2);

}