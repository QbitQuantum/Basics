void test_allEvt::ComputeAllVarPietro(TLorentzVector lepP,TLorentzVector lepN){
  // Preliminary definitions:

  const double pbeam = 7000.; // exact number irrelevant as long as pbeam >> Mprot
  const double Mprot = 0.9382720;
  const double Mlepton = 0.10566;  // (muon)
  const double gPI = TMath::Pi();
  const double Ebeam = sqrt( pbeam*pbeam + Mprot*Mprot );
  TLorentzVector beam1_LAB( 0., 0., pbeam, Ebeam );
  TLorentzVector beam2_LAB( 0., 0., -pbeam, Ebeam );


  // assuming that we have a TTree "data" (data ntuple) containing the 4-vectors lepP and lepN of lepton and antilepton

  // event by event (in some loop over dilepton events in the data ntuple):


  // data->GetEvent( i_event );

  // double lepP_pT  = lepP->Pt();
  // double lepN_pT  = lepN->Pt();

  // double lepP_eta = lepP->PseudoRapidity();
  // double lepN_eta = lepN->PseudoRapidity();

  // dilepton 4-vector:

  TLorentzVector dilepton = lepP + lepN;
  double pT   = dilepton.Pt();
  double rap  = dilepton.Rapidity();
  double mass = dilepton.M();

  // calculation of decay angles in three polarization frames

  // reference directions to calculate angles:

  TVector3 lab_to_dilep = -dilepton.BoostVector();

  TLorentzVector beam1_DILEP = beam1_LAB;
  beam1_DILEP.Boost(lab_to_dilep);         // beam1 in the dilepton rest frame
  TLorentzVector beam2_DILEP = beam2_LAB;
  beam2_DILEP.Boost(lab_to_dilep);         // beam2 in the dilepton rest frame

  TVector3 beam1_direction     = beam1_DILEP.Vect().Unit();
  TVector3 beam2_direction     = beam2_DILEP.Vect().Unit();
  TVector3 dilep_direction     = dilepton.Vect().Unit();
  TVector3 beam1_beam2_bisect  = ( beam1_direction - beam2_direction ).Unit();


  // all polarization frames have the same Y axis = the normal to the plane formed by
  // the directions of the colliding hadrons:

  TVector3 Yaxis = ( beam1_direction.Cross( beam2_direction ) ).Unit();

  // flip of y axis with rapidity:

  if ( rap < 0. ) Yaxis = - Yaxis;

  TVector3 perpendicular_to_beam = ( beam1_beam2_bisect.Cross( Yaxis ) ).Unit();


  // positive lepton in the dilepton rest frame:

  TLorentzVector lepton_DILEP = lepP;
  lepton_DILEP.Boost(lab_to_dilep);

  // CS frame angles:

  TVector3 newZaxis = beam1_beam2_bisect;
  TVector3 newYaxis = Yaxis;
  TVector3 newXaxis = newYaxis.Cross( newZaxis );

  TRotation rotation;
  rotation.SetToIdentity();
  rotation.RotateAxes( newXaxis, newYaxis, newZaxis );
  rotation.Invert();  // transforms coordinates from the "xyz" frame to the new frame
  TVector3 lepton_DILEP_rotated = lepton_DILEP.Vect();
  lepton_DILEP_rotated.Transform(rotation);

  /* double */ costh_CS = lepton_DILEP_rotated.CosTheta();
  /* double */ phi_CS   = lepton_DILEP_rotated.Phi() * 180. / gPI;
  double phith_CS;
  if ( costh_CS < 0. ) phith_CS = phi_CS - 135.;
  if ( costh_CS > 0. ) phith_CS = phi_CS - 45.;
  if ( phith_CS < -180. ) phith_CS = 360. + phith_CS;
  phi_CS   = phi_CS / 180. * gPI;


  // HELICITY frame angles:

  newZaxis = dilep_direction;
  newYaxis = Yaxis;
  newXaxis = newYaxis.Cross( newZaxis );

  rotation.SetToIdentity();
  rotation.RotateAxes( newXaxis, newYaxis, newZaxis );
  rotation.Invert();
  lepton_DILEP_rotated = lepton_DILEP.Vect();
  lepton_DILEP_rotated.Transform(rotation);

  /* double */ costh_HX = lepton_DILEP_rotated.CosTheta();
  /* double */ phi_HX   = lepton_DILEP_rotated.Phi() * 180. / gPI;
  double phith_HX;
  if ( costh_HX < 0. ) phith_HX = phi_HX - 135.;
  if ( costh_HX > 0. ) phith_HX = phi_HX - 45.;
  if ( phith_HX < -180. ) phith_HX = 360. + phith_HX;
  phi_HX   = phi_HX / 180. * gPI;


  // // PERPENDICULAR HELICITY frame angles:

  // newZaxis = perpendicular_to_beam;
  // newYaxis = Yaxis;
  // newXaxis = newYaxis.Cross( newZaxis );

  // rotation.SetToIdentity();
  // rotation.RotateAxes( newXaxis, newYaxis, newZaxis );
  // rotation.Invert();
  // lepton_DILEP_rotated = lepton_DILEP.Vect();
  // lepton_DILEP_rotated.Transform(rotation);

  // double costh_PX = lepton_DILEP_rotated.CosTheta();
  // double phi_PX   = lepton_DILEP_rotated.Phi() * 180. / gPI;
  // double phith_PX;
  // if ( costh_PX < 0. ) phith_PX = phi_PX - 135.;
  // if ( costh_PX > 0. ) phith_PX = phi_PX - 45.;
  // if ( phith_PX < -180. ) phith_PX = 360. + phith_PX;
  // phi_PX   = phi_PX / 180. * gPI;



}