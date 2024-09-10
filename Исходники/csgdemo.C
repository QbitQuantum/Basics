void s_difference()
{
   gROOT->GetListOfCanvases()->Delete();
   TCanvas *c = new TCanvas("composite shape", "Difference boolean operation", 700, 1000);

   c->Divide(1,2,0,0);
   c->cd(2);
   gPad->SetPad(0,0,1,0.4);
   c->cd(1);
   gPad->SetPad(0,0.4,1,1);
   
   if (gGeoManager) delete gGeoManager;
   
   new TGeoManager("xtru", "poza12");
   TGeoMaterial *mat = new TGeoMaterial("Al", 26.98,13,2.7);
   TGeoMedium *med = new TGeoMedium("MED",1,mat);
   TGeoVolume *top = gGeoManager->MakeBox("TOP",med,100,100,100);
   gGeoManager->SetTopVolume(top);

   // define shape components with names
   TGeoTorus *tor = new TGeoTorus("tor", 45., 15., 20., 45., 145.); 
   TGeoSphere *sph = new TGeoSphere("sph", 20., 45., 0., 180., 0., 270.);
   // create the composite shape based on a Boolean expression
   TGeoCompositeShape *cs = new TGeoCompositeShape("mir", "sph - tor");

   TGeoVolume *vol = new TGeoVolume("COMP3",cs);
   top->AddNode(vol,1);
   gGeoManager->CloseGeometry();
   gGeoManager->SetNsegments(60);
   top->Draw();
   MakePicture();

   c->cd(2);

   TPaveText *pt = new TPaveText(.01, .01, .99, .99);

   pt->SetLineColor(1);

   TText *text = pt->AddText("TGeoCompositeShape - composite shape class");

   text->SetTextColor(2);

   pt->AddText("----- It's an example of boolean difference: A - B");
   pt->AddText("----- A == part of sphere (0-180, 0-270), B == partial torus (45-145)");
   pt->AddText(" ");
   pt->SetAllWith("-----","color",4);
   pt->SetAllWith("-----","font",72);
   pt->SetAllWith("-----","size",0.04);
   pt->SetTextAlign(12);
   pt->SetTextSize(0.044);
   pt->Draw();
   c->cd(1);
}