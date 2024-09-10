/**
 *PrintText
 *  打印文本.
 *Params:
 *  sText[in] - 需要打印的文本
 *  X[in] - 相对打印区域左上角(X坐标), 单位: mm
 *  Y[in] - 相对打印区域左上角(Y坐标), 单位: mm
 *  FontSize[in] - 字体大小, 缺省：10
 *  FontColor[in] - 字体颜色, 缺省：clBlack(黑色)
 */
void __fastcall CPrinter::PrintText(AnsiString sText, Extended X, Extended Y, int FontSize, TColor FontColor)
{
    if (PPRN == NULL)
    {
        return ;
    }
    if (!PPRN->Printing)
    {
        return;
    }

    int px = Ceil(Ceil((X + eOffsX) * HPointsPerInch() * 10000 / 25.4) / 10000);
    int py = Ceil(Ceil((Y + eOffsY) * VPointsPerInch() * 10000 / 25.4) / 10000);
    px = px + 2 * AvgCharWidth();
    py = py - GetOffSetY();                 //绝对坐标, 不用换算成相对于Y轴坐标
    PPRN->Canvas->Font->Name = "宋体";
    PPRN->Canvas->Font->Size = FontSize;
    PPRN->Canvas->Font->Color = FontColor;
    PPRN->Refresh();
    PPRN->Canvas->TextOut(px, py, sText);
}