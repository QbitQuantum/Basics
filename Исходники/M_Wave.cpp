//===========================================================================
void TWave::DrawElementFace()
{
    TCanvas    *dbCanvas = VisualElementParam->Bitmap->Canvas;
    int         aw       = VisualElementParam->Width;
    int         ah       = VisualElementParam->Height;

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
    // -------------- Отрисовка ресурса если он есть ----------
    dbCanvas->Draw((aw - ResourseBitmapFaceElement->Width) / 2, (ah - ResourseBitmapFaceElement->Height) / 2,ResourseBitmapFaceElement);
}