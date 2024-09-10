void DrawingSurface_DrawRectangle(ScriptDrawingSurface *sds, int x1, int y1, int x2, int y2)
{
    sds->MultiplyCoordinates(&x1, &y1);
    sds->MultiplyCoordinates(&x2, &y2);

    Bitmap *ds = sds->StartDrawing();
    ds->FillRect(Rect(x1,y1,x2,y2), sds->currentColour);
    sds->FinishedDrawing();
}