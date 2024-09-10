// Handler for touch-up message.
// in:
//      hWnd        window handle
//      ti          TOUCHINPUT structure (info about contact)
void OnTouchUpHandler(HWND hWnd, const TOUCHINPUT& ti)
{

    // Find the stroke in the collection of the strokes being drawn.
	int iStrk = g_StrkColDrawing.FindStrokeById(ti.dwID);

    // Add the finished stroke to the collection of finished strokes.
    g_StrkColFinished.AddStroke(g_StrkColDrawing[iStrk]);

    // Remove finished stroke from the collection of strokes being drawn.
    g_StrkColDrawing.RemoveStroke(iStrk);

    // Redraw the window.
    InvalidateRect(hWnd, NULL, FALSE);
}