void postprocess(TCanvas* c2, const char* name, Int_t rWrite, Int_t rPerformance) {

        if (rPerformance){

                TLatex *alice = new TLatex(0.65,0.47,"Performance");
                alice->SetNDC();
                alice->SetTextColor(myDarkRed);
                alice->SetTextFont(42);
                alice->SetTextSize(0.05);
                alice->SetLineWidth(2);
                alice->Draw();

                TLatex *alice2 = new TLatex(0.62,0.41,"LHC10h - Pass2");
                alice2->SetNDC();
                alice2->SetTextColor(myDarkRed);
                alice->SetTextFont(42);
                alice2->SetTextSize(0.05);
                alice2->SetLineWidth(2);
                alice2->Draw();

                TText *date = new TText(0.68,0.35,cStamp2);
                date->SetNDC();
                date->SetTextFont(42);
                date->SetTextSize(0.04);
                date->Draw();

                //Acquire canvas proportions
                Double_t AliLogo_LowX = 0.67;
                Double_t AliLogo_LowY = 0.53;
                Double_t AliLogo_Height = 0.22;
                //ALICE logo is a png file that is 821x798 pixels->should be wider than a square
                Double_t AliLogo_Width  = (821./798.) * AliLogo_Height * gPad->GetWh() / gPad->GetWw();

                TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo",AliLogo_LowX,AliLogo_LowY,AliLogo_LowX+AliLogo_Width,AliLogo_LowY+AliLogo_Height);
                //    myPadLogo->SetFillColor(2); // color to first figure out where is the pad then comment !
                myPadSetUp(myPadLogo,0,0,0,0);
                //myPadLogo->SetFixedAspectRatio(1);
                myPadLogo->Draw();
                myPadLogo->cd();
                TASImage *myAliceLogo = new TASImage("alice_logo_transparent.png");
                myAliceLogo->Draw();
        }

        if (rWrite == 1)
                c2->SaveAs(Form("%s.png",name));

        if (rWrite == 2)
                c2->SaveAs(Form("%s.eps",name));

}