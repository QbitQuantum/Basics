// on a cluster
void computeWarp(Histo *histoT,Histo &destH, FeatureServer & fs, SegCluster & selectedSegments, Config & config){
  Seg *seg;                                                             // current selectd segment
  selectedSegments.rewind();                                            // reset the reader at the begin of the input stream
  while((seg=selectedSegments.getSeg())!=NULL)                          // For each of the selected segments
    computeWarp(histoT,destH,fs,seg,config);                            // Normalize the features
}