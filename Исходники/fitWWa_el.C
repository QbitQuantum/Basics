////CMS Preliminary label and lumu -- upper left corner
void cmsPrelim2()
{
    const float LUMINOSITY = IntLUMI;
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(0.04);

    latex.SetTextAlign(31); // align right
    latex.DrawLatex(0.90,0.96,"#sqrt{s} = 13 TeV");
    if (LUMINOSITY > 0.) {
        latex.SetTextAlign(11); // align left
        latex.DrawLatex(0.21,0.85,Form("#int #font[12]{L} dt = %.1f fb^{-1}", LUMINOSITY));
    }
    latex.SetTextAlign(11); // align left
    latex.DrawLatex(0.18,0.96,"CMS preliminary");
}