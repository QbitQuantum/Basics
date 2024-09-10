/******************************************************************************
 *		MapVirtualKey (KEYBOARD.131)
 *
 * MapVirtualKey translates keycodes from one format to another
 */
UINT16 WINAPI MapVirtualKey16(UINT16 wCode, UINT16 wMapType)
{
    return MapVirtualKeyA(wCode,wMapType);
}