void geugd_riordan() {
	gROOT->SetStyle("HALLA");
	TCanvas *cn = new TCanvas("cn");
	cn->Draw();
	cn->UseCurrentStyle();
	TH1F *frm = new TH1F("frm","",100,0.,12.);
	frm->GetXaxis()->SetTitle("Q^{2}  [GeV^{2}]");
	frm->GetXaxis()->CenterTitle();
	frm->GetYaxis()->SetTitle("G_{E}^{u}/G_{D}");
	frm->GetYaxis()->CenterTitle();
	frm->SetMinimum(.40);
	frm->SetMaximum(2.4);
	//frm->SetMaximum(0.3);
	frm->UseCurrentStyle();
	frm->Draw();
	frm->SetAxisRange(0.10,12.,"X");

	TF1* galster = new TF1("galster",
			"x/(4.*0.938*.938)*1.91/(1.+x/.71)^2/(1.+5.6*x/(4.*.938*.938))",
			0.,4.);
	galster->SetLineColor(kBlack);
	galster->SetLineStyle(kBlack);
	galster->SetLineWidth(2);

	TF1* gen0 = new TF1("gen0", f1dugen0, 0.,12.);
	gen0->SetLineColor(kBlack);
	gen0->SetLineStyle(kBlack);
	gen0->SetLineWidth(1);



	TF1 *genf = new TF1("genf",genff,1.,10.,1);
	genf->SetLineColor(kBlue);
	genf->SetLineStyle(1);
	genf->SetParameter(0,1.);
	// match to Madey point just below 1.5
	// genf->SetParameter(0,.0411/genf->Eval(1.45));
	//  genf->SetParameter(0,-0.558645);
	genf->SetParameter(0,-0.182645);

	TF1 *roberts_curve = new TF1("roberts",roberts_gen,0.035,12.344,1);
	roberts_curve->SetLineColor(kRed);
	roberts_curve->SetLineStyle(9);

	TF1 *ourfit = new TF1("ourfit",gen_ourfit,0.,10.,0);
	ourfit->SetLineColor(kBlue);
	ourfit->SetLineStyle(0);

	/*
	   TF1 *bbba05 = new TF1("BBBA05",gen_bbba05,0.,10.,0);
	   bbba05->SetLineColor(kGreen);
	   bbba05->SetLineStyle(3);
	   */

	//  TF1 *lomon = new TF1("Lomon",Lomon_GEn,0.,10.,0);
	// lomon->SetLineColor(7);
	// lomon->SetLineStyle(4);




	TMultiGraph* mgrDta = new TMultiGraph("Data","G_{E}^{n}");
	//TLegend *legDta = new TLegend(.3448,.6123,.6810,.9110,"","brNDC");
	TLegend *legDta = new TLegend(.6020,.4004,.9382,.9089,"","brNDC");

	TMultiGraph* wgr = mgrDta;
	TLegend *wlg = legDta;

	// the data
	legDta->SetBorderSize(0); // turn off border
	legDta->SetFillStyle(0);

	datafile_t *f = datafiles;
	TGraph* gr=0;
	TGraph* ogr=0;
	while ( f && f->filename ) {
		ogr=OneGraph(f);
		if (ogr) {
			gr = fromGEntransform(ogr);
			gr->SetLineStyle(0);
			if (f->lnpt) {
				mgrDta->Add(gr,f->lnpt);
				if( f->label[0] != 'x' )
					legDta->AddEntry(gr,f->label,f->lnpt);
			}
			mgrDta->Add(gr,"p");
			if( f->label[0] != 'x' )
				legDta->AddEntry(gr,f->label,"p");

			/*
			   else if (gr->GetMarkerStyle()>=20) {
			   mgrDta->Add(gr,"p");
			   if( f->label[0] != 'x' )
			   legDta->AddEntry(gr,f->label,"p");
			   }	
			   else {
			   mgrDta->Add(gr,"l");
			   if( f->label[0] != 'x' )
			   legDta->AddEntry(gr,f->label,"l");
			   }
			   */
		}
		f++;
	}


	mgrDta->Draw("p");
	legDta->Draw();

	TMultiGraph* mgrThry = new TMultiGraph("Theory","G_{E}^{n}");
	//  TLegend *legThry = new TLegend(.546,.6208,.8822,.9195,"","brNDC");
	//	TLegend *legThry = new TLegend(.2055,.7013,.6020,.8893,"","brNDC");
	TLegend *legThry = new TLegend(.4267,.8453,.6236,.8962,"","brNDC");

	wgr = mgrThry;
	wlg = legThry;

	// the theory
	wlg->SetBorderSize(0); // turn off border
	wlg->SetFillStyle(0);

	f = theoryfiles1;
	gr=0;
	Bool_t isfill;
	while ( f && f->filename ) {
		gr=OneGraph(f);
		gr->SetLineWidth(2);
		isfill = kFALSE;
		if (gr) {
			TGraphAsymmErrors *egr = dynamic_cast<TGraphAsymmErrors*>(gr);
			if (egr && egr->GetN()>1 && egr->GetEYhigh() && egr->GetEYhigh()[1]>0) {
				gr = toerror_band(egr);
				gr->SetFillStyle(3000+f->style);
				gr->SetFillStyle(1);
				gr->SetFillColor(gr->GetLineColor());
				isfill = kTRUE;
			}
			if (f->lnpt) {
				wgr->Add(gr,f->lnpt);
				if( f->label[0] != 'x' )
					wlg->AddEntry(gr,f->label,f->lnpt);
			}
			else if (gr->GetMarkerStyle()>=20) {
				wgr->Add(gr,"p");
				if( f->label[0] != 'x' )
					wlg->AddEntry(gr,f->label,"p");
			}	
			else {
				if( isfill ){
					gr->SetLineStyle(0);
					wgr->Add(gr,"f");
					//				  wgr->Add( new TGraph(*egr),"l");
					if( f->label[0] != 'x' )
						wlg->AddEntry(gr,f->label,"lf");
				} else {
					wgr->Add(gr,"l");
					if( f->label[0] != 'x' )
						wlg->AddEntry(gr,f->label,"l");
				}
			}

		}
		f++;
	}


	TPaveLabel *prelim = new TPaveLabel( 0.3204, 0.1886, 0.9310, 0.4643, "PRELIMINARY", "NDC" );
	prelim->SetTextAngle(0);
	TColor *pink = new TColor(300, 1.0, 0.7, 0.7, "pink");
	prelim->SetTextColor(300);
	prelim->SetFillStyle(0);
	prelim->SetBorderSize(0);


#ifdef FAKE_SCHIAVILLA
	TGraph *schiagraph = draw_schiavilla();
	schiagraph->Draw("F");
	schiagraph = draw_schiavilla(1);
	schiagraph->Draw("C");
	legThry->AddEntry(schiagraph, "d(e,e'd) T_{20} - Schiavilla & Sick", "LF");
#endif

#ifdef PRELIMINARY
	prelim->Draw("same");
#endif

	TPaveLabel *nofsilab = new TPaveLabel( 0.4569, 0.1674, 0.7514, 0.2415, "No FSI Corrections", "NDC" );
	nofsilab->SetFillStyle(0);
	nofsilab->SetBorderSize(0);
	nofsilab->SetTextColor(kRed);

#ifdef NOFSI
	//  nofsilab->Draw("same");
#endif

#ifdef PQCD
	genf->Draw("same");
#endif
	mgrThry->Draw("c");
#ifdef GALSTER
	galster->Draw("same");
#endif
//	gen0->Draw("same");

#ifdef NEW_ROBERTS
	roberts_curve->Draw("same");
#endif
	//  ourfit->Draw("same");
	//  bbba05->Draw("same");
	//lomon->Draw("same");
	// bandi->Draw("same");
#ifdef PQCD  
	legThry->AddEntry(genf,"F_{2}/F_{1} #propto ln^{2}(Q^{2}/#Lambda^{2})/Q^{2}","l");
#endif
#ifdef GALSTER
	legThry->AddEntry(galster,"Galster fit (1971)","l");
#endif
//	legThry->AddEntry(gen0,"G_{E}^{n} = 0","l");
#ifdef NEW_ROBERTS
	legThry->AddEntry(roberts_curve,"q(qq) Faddeev -  I. Cloet, ANL","l");
#endif
	//  legThry->AddEntry(bbba05,"BBBA05","l");
	//  legThry->AddEntry(lomon, "Lomon", "l");
	// legThry->AddEntry(ourfit, "Our Fit", "l");
	legThry->Draw();
	legDta->Draw();

	mgrDta->Draw("p");
	legDta->Draw();

	TEllipse *cir1 = new TEllipse(1.31, 0.0, 0.17, 0.0065);
	TEllipse *cir2 = new TEllipse(2.4, 0.0, 0.17, 0.0065);
	cir1->SetFillStyle(0);
	cir2->SetFillStyle(0);

#ifdef PLOTKIN1
	cir1->Draw("same");
	//  cir2->Draw("same");

	//  TPaveLabel *exacc = new TPaveLabel( 0.3779, 0.2691, 0.5963, 0.3114, "Expected Accuracy", "NDC");
	TPaveLabel *exacc = new TPaveLabel( 0.2716, 0.2733, 0.4899, 0.3136, "Expected Accuracy", "NDC");
	exacc->SetFillStyle(0);
	exacc->SetBorderSize(0);
	exacc->Draw("same");
#endif


	// draw a line at 1
	cn->Modified();

	cn->Update();
	cn->SaveAs(Form("%s.pdf",psfile));
	cn->SaveAs(Form("%s.eps",psfile));
	//  cn->SaveAs(Form("%s.root",psfile));
	//  gSystem->Exec(Form("./replace_symbols.pl %s.eps",psfile));

	//  cn->SaveAs("bogdan_gen.eps");
	return;  // LEAVING HERE

	// now an overlay, hopefully matching dimensions

	// remove everything but the graph
	cn->Update();
	TList *clist = cn->GetListOfPrimitives();
	TFrame* frame = cn->GetFrame();
	for (int i=0; i<clist->GetSize(); ) {
		if (clist->At(i) != frame) {
			clist->RemoveAt(i);
		} else i++;
	}
	// draw markers in the corners
	TMarker *mkr = new TMarker(frame->GetX1(),frame->GetY1(),2);
	mkr->Draw();
	mkr = new TMarker(frame->GetX2(),frame->GetY1(),2);
	mkr->Draw();
	mkr = new TMarker(frame->GetX1(),frame->GetY2(),2);
	mkr->Draw();
	mkr = new TMarker(frame->GetX2(),frame->GetY2(),2);
	mkr->Draw();
	frame->SetLineColor(10);
	cn->Update();

	datafile_t miller = { "figure_input/Miller/lattice.GEn.rtf","Miller",
		"[0]","[1]","[1]-[3]","[2]-[1]",0,0,1,3,"F" };

	gr = OneGraph(&miller);
	TGraphAsymmErrors* egr = dynamic_cast<TGraphAsymmErrors*>(gr);
	if (egr && egr->GetEYhigh() && egr->GetEYhigh()[egr->GetN()/2]>0) {
		gr = toerror_band(egr);
		gr->SetLineStyle(1);
		gr->SetFillColor(gr->GetLineColor());
		gr->SetFillStyle(3000+miller.style);
	}

	gr->Draw("F");

	cn->Update();
	cn->SaveAs("gen_Miller_Overlay.pdf");
	cn->SaveAs("gen_Miller_Overlay.root");

}