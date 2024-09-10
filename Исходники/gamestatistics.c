/*******************************************************************************
 * GAMEUX_buildStatisticsFilePath
 * Creates path to file containing statistics of game with given id.
 *
 * Parameters:
 *  lpApplicationId                         [I]     application id of game,
 *                                                  as string
 *  lpStatisticsFile                        [O]     array where path will be
 *                                                  stored. Its size must be
 *                                                  at least MAX_PATH
 */
static HRESULT GAMEUX_buildStatisticsFilePath(
        LPCWSTR lpApplicationId,
        LPWSTR lpStatisticsFile)
{
    static const WCHAR sBackslash[] = {'\\',0};
    static const WCHAR sStatisticsDir[] = {'\\','M','i','c','r','o','s','o','f','t',
            '\\','W','i','n','d','o','w','s','\\','G','a','m','e','E','x','p',
            'l','o','r','e','r','\\','G','a','m','e','S','t','a','t','i','s',
            't','i','c','s','\\',0};
    static const WCHAR sDotGamestats[] = {'.','g','a','m','e','s','t','a','t','s',0};

    HRESULT hr;

    hr = SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, lpStatisticsFile);

    if(SUCCEEDED(hr))
    {
        lstrcatW(lpStatisticsFile, sStatisticsDir);
        lstrcatW(lpStatisticsFile, lpApplicationId);
        lstrcatW(lpStatisticsFile, sBackslash);
        lstrcatW(lpStatisticsFile, lpApplicationId);
        lstrcatW(lpStatisticsFile, sDotGamestats);
    }

    return hr;
}