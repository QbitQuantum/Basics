//===========================================================================
void TSigCorection::DrawElementFace()
{
    TCanvas    *dbCanvas = VisualElementParam->Bitmap->Canvas;
    int         aw       = VisualElementParam->Width ;
    int         ah       = VisualElementParam->Height;
    AnsiString  as       = "A B";

    dbCanvas->Brush->Color = clWhite;
    dbCanvas->Pen  ->Color = clBlack;

    dbCanvas->Rectangle(0, 0, aw, ah);

    // --------- Отрисовка прямоугольника --- (прямокгольник процесса разработки) -----
    if (DesignPhase != dpAllreadyTesting) {
        if (DesignPhase == dpNotTesting  ) {
            dbCanvas->Pen  ->Color = clRed;
        }
        if (DesignPhase == dpNeedModified) {
            dbCanvas->Pen  ->Color = clRed;
            dbCanvas->Pen  ->Style = psDot;
        }

        dbCanvas->Rectangle(2, 2, VisualElementParam->Width - 2, VisualElementParam->Height - 2);

        dbCanvas->Pen->Color = clBlack;
        dbCanvas->Pen->Style = psSolid;
    }

    dbCanvas->TextOut((aw - dbCanvas->TextWidth(as))/2, (ah - dbCanvas->TextHeight(as))/2, as);
    dbCanvas->Ellipse(aw / 2 - 1, ah / 2 - 1, aw / 2 + 1, ah / 2 + 1);
}