void formatForCmsPublic(TPad * c, TLegend *leg, TString title, int nsamp, float legx, float legy, float legw, float legh, TString legopt)
{
    if(title.Length()!=0)
    {
        TPaveText *pave = new TPaveText(0.5,0.96,0.94,0.99,"NDC");
        pave->SetBorderSize(0);
        pave->SetFillStyle(0);
        pave->SetTextAlign(32);
        pave->SetTextFont(42);

        TObjArray * tokens = title.Tokenize("\\\\");
        int nt = tokens->GetEntries();
        for(int it=0; it<nt; ++it)
        {
            TObjString * t = (TObjString *)tokens->At(it);
            pave->AddText(t->GetString());
        }

        pave->Draw("same");
    }

    float legx1=legx, legx2=legx+legw;
    float legy1 = legy, legy2 = legy-legh*(float)(nsamp);
    if(leg==0) leg = ((TPad *)c)->BuildLegend(legx1,legy1,legx2,legy2);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetLineWidth(1);
    leg->SetTextFont(42);
    leg->SetEntryOption(legopt);
    leg->SetX1NDC(legx1);
    leg->SetY1NDC(legy1);//-nsamp*legh);
    leg->SetX2NDC(legx2);
    leg->SetY2NDC(legy2);
}