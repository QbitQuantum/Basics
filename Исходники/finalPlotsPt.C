void cmsPrel(double intLumi){
   TLatex latex;
   latex.SetNDC();
   latex.SetTextSize(0.04);

   latex.SetTextAlign(31); // align right
   //latex.DrawLatex(0.98,0.965,"#font[22]{#sqrt{s} = 7 TeV}");
   latex.DrawLatex(0.98,0.965,"#sqrt{s} = 7 TeV");
   if (intLumi > 0.) {
     latex.SetTextAlign(31); // align right
     latex.DrawLatex(0.98,0.88,Form("#int #font[12]{L}dt = %.1f  nb^{-1}",intLumi));
   }
   latex.SetTextAlign(11); // align left
   //latex.DrawLatex(0.02,0.965,"#font[22]{CMS preliminary 2010}");
   latex.DrawLatex(0.02,0.965,"CMS preliminary 2010");
   //latex.DrawLatex(0.20,0.20,"-0.4 < #eta < 0.4");
   return;
}