// For new macro - all variables to plot
void addVariable(TString newvar, TString newxtitle, TString newytitle, unsigned int newBins, double newFirstBin, double newLastBin, bool drawThis = true, bool printThis = true) {
  variables.push_back(newvar);
  if(drawThis) allVarsToPlot.push_back(newvar);
  if(printThis) allVarsToPrint.push_back(newvar);
  xTitles[newvar] = newxtitle;
  if(newytitle.Length()>0) 
    yTitles[newvar] = newytitle;
  else
    yTitles[newvar] = "Events/";
  binsUInt[newvar] = newBins;
  firstBinsDouble[newvar] = newFirstBin;
  lastBinsDouble[newvar] = newLastBin;
  drawVar[newvar] = drawThis;
  printVar[newvar] = printThis;
  nVars=variables.size();
  return;
}