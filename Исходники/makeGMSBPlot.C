void cmsPrelim(double intLumi, bool prelim)
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextFont(62);
        if(prelim) latex.SetTextSize(0.04);
        else       latex.SetTextSize(0.045);

        latex.SetTextAlign(11); // align left
        //if(prelim) latex.DrawLatex(0.13,0.92,"CMS Preliminary");
        //else       latex.DrawLatex(0.13,0.92,"CMS");

        if(prelim) latex.DrawLatex(0.19,0.92,"CMS Preliminary");
        else       latex.DrawLatex(0.19,0.92,"CMS");

        latex.SetTextAlign(31); // align right
        //latex.DrawLatex(0.89, 0.92, Form("#sqrt{s} = 7 TeV, L_{int} = %4.2f fb^{-1}", intLumi));
        latex.DrawLatex(0.92, 0.92, Form("#sqrt{s} = 8 TeV, L_{int} = %4.1f fb^{-1}", intLumi));
}