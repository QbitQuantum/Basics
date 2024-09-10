HWND
Tooltip_WindowFromPoint ( HWND hTooltip, TOOLTIPDATA* pTooltip, POINT* ppt )
{
	return WindowFromPoint ( *ppt ); 
}