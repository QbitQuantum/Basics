//_________________________________________________
void TestJeffreysGaussMean(){
  RooWorkspace w("w");
  w.factory("Gaussian::g(x[0,-20,20],mu[0,-5,5],sigma[1,0,10])");
  w.factory("n[10,.1,200]");
  w.factory("ExtendPdf::p(g,n)");
  w.var("sigma")->setConstant();
  w.var("n")->setConstant();

  RooDataHist* asimov = w.pdf("p")->generateBinned(*w.var("x"),ExpectedData());

  RooFitResult* res = w.pdf("p")->fitTo(*asimov,Save(),SumW2Error(kTRUE));

  asimov->Print();
  res->Print();
  TMatrixDSym cov = res->covarianceMatrix();
  cout << "variance = " << (cov.Determinant()) << endl;
  cout << "stdev = " << sqrt(cov.Determinant()) << endl;
  cov.Invert();
  cout << "jeffreys = " << sqrt(cov.Determinant()) << endl;

  //  w.defineSet("poi","mu,sigma");
  w.defineSet("poi","mu");
  w.defineSet("obs","x");

  RooJeffreysPrior pi("jeffreys","jeffreys",*w.pdf("p"),*w.set("poi"),*w.set("obs"));
  //  pi.specialIntegratorConfig(kTRUE)->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D")  ;
  //  pi.specialIntegratorConfig(kTRUE)->getConfigSection("RooIntegrator1D").setRealValue("maxSteps",3);

  const RooArgSet* temp = w.set("poi");
  pi.getParameters(*temp)->Print();

  //  return;
  RooGenericPdf* test = new RooGenericPdf("test","test","1",*w.set("poi"));

  TCanvas* c1 = new TCanvas;
  RooPlot* plot = w.var("mu")->frame();
  pi.plotOn(plot);
  test->plotOn(plot,LineColor(kRed),LineStyle(kDotted));
  plot->Draw();


}