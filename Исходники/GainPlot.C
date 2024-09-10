void DrawStatBox(TObject** Histos, std::vector<char*> legend, bool Mean, double X, double Y, double W, double H)
{
   int    N             = legend.size();
   char   buffer[255];

   if(Mean)H*=3;
   for(int i=0;i<N;i++){
           TPaveText* stat = new TPaveText(X,Y-(i*H), X+W, Y-(i+1)*H, "NDC");
	   TH1* Histo = (TH1*)Histos[i];
           sprintf(buffer,"Entries : %i\n",(int)Histo->GetEntries());
           stat->AddText(buffer);

           if(Mean){
           sprintf(buffer,"Mean    : %6.2f\n",Histo->GetMean());
           stat->AddText(buffer);

           sprintf(buffer,"RMS     : %6.2f\n",Histo->GetRMS());
           stat->AddText(buffer);
           }

           stat->SetFillColor(0);
           stat->SetLineColor(Color[i]);
           stat->SetTextColor(Color[i]);
           stat->SetBorderSize(0);
           stat->SetMargin(0.05);
           stat->SetTextAlign(12);
           stat->Draw();
   }
}