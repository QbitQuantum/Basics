// ------------------------------------------------
// 
//  FUNCTION: gui_SetSysColor( PA_PluginParameters params )
//
//  PURPOSE:  Set the color of the specified display element.
//        
//	DATE:	  MJG 12/1/03 (3.5.6)
//
void gui_SetSysColor( PA_PluginParameters params )
{
	LONG_PTR returnValue;
	INT_PTR displayElement[1];
	COLORREF rgbValue[1];
	BYTE rValue, gValue, bValue;

	returnValue = 0;
	displayElement[0] = (INT_PTR) PA_GetLongParameter( params, 1); 
	rValue = (BYTE) PA_GetLongParameter( params, 2);
	gValue = (BYTE) PA_GetLongParameter( params, 3);
    bValue = (BYTE) PA_GetLongParameter( params, 4);

	rgbValue[0] = RGB(rValue, gValue, bValue);

    returnValue = SetSysColors(1, displayElement, rgbValue);

	if(returnValue != 0)
		returnValue = 1;
 
	PA_ReturnLong( params, returnValue );
}