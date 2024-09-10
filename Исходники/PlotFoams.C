void DrawCell( TMVA::PDEFoamCell *cell, TMVA::PDEFoam *foam,
	       Double_t x, Double_t y,
	       Double_t xscale,  Double_t yscale )
{
   // recursively draw cell and it's daughters

   Float_t xsize = xscale*1.5;
   Float_t ysize = yscale/3;
   if (xsize > 0.15) xsize=0.1; //xscale/2;
   if (cell->GetDau0() != NULL) {
      TLine *a1 = new TLine(x-xscale/4, y-ysize, x-xscale, y-ysize*2);
      a1->SetLineWidth(2);
      a1->Draw();
      DrawCell(cell->GetDau0(), foam, x-xscale, y-yscale, xscale/2, yscale);
   }
   if (cell->GetDau1() != NULL){
      TLine *a1 = new TLine(x+xscale/4, y-ysize, x+xscale, y-ysize*2);
      a1->SetLineWidth(2);
      a1->Draw();
      DrawCell(cell->GetDau1(), foam, x+xscale, y-yscale, xscale/2, yscale);
   }

   TPaveText *t = new TPaveText(x-xsize, y-ysize, x+xsize, y+ysize, "NDC");

   t->SetBorderSize(1);
   t->SetFillStyle(1);

   // draw all cell elements
   t->AddText( Form("Intg=%.5f", cell->GetIntg()) );
   t->AddText( Form("Var=%.5f", cell->GetDriv()) );
   TVectorD *vec = (TVectorD*) cell->GetElement();
   if (vec != NULL){
      for (Int_t i = 0; i < vec->GetNrows(); ++i) {
	 t->AddText( Form("E[%i]=%.5f", i, vec(i)) );
      }
   }

   if (cell->GetStat() != 1) {
      // cell is inactive --> draw split point
      t->SetFillColor( TColor::GetColor("#BBBBBB") );
      t->SetTextColor( TColor::GetColor("#000000") );

      // cell position and size
      TMVA::PDEFoamVect cellPosi(foam->GetTotDim()), cellSize(foam->GetTotDim());
      cell->GetHcub(cellPosi, cellSize);
      Int_t    kBest = cell->GetBest(); // best division variable
      Double_t xBest = cell->GetXdiv(); // best division point
      t->AddText( Form("dim=%i", kBest) );
      t->AddText( Form("cut=%.5g", foam->VarTransformInvers(kBest,cellPosi[kBest] + xBest*cellSize[kBest])) );
   } else {
      t->SetFillColor( TColor::GetColor("#DD0033") );
      t->SetTextColor( TColor::GetColor("#FFFFFF") );
   }

   t->Draw();

   return;
}