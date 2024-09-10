// Build the segments with the energized frames
unsigned long selectFrames(FeatureServer &fs,SegServer & segServer,double threshold,SegCluster &selectedSeg,SegCluster &outputSeg,String labelOutput,String fileName)
{
  unsigned long countFrames=0;
  fs.reset();                                                       // feature server reset
  unsigned long ind=0;
  unsigned long begin=0;
  bool in=false;
  Seg *seg;                                                         // current selectd segment
  selectedSeg.rewind();                                             // reset the reader at the begin of the input stream
  while((seg=selectedSeg.getSeg())!=NULL){                          // For each input segments
    for (unsigned long idx=seg->begin();idx<seg->begin()+seg->length();idx++){ // for each frame
      Feature f;
      fs.seekFeature(idx);
      fs.readFeature(f);
      if (f[0]>threshold){                                         // the frame is selected
	countFrames++;
	if (in==false){                                             // Begin of a new segment         
	  in=true;                                                  
	  begin=ind;
	}
      }
      else if (in){                                                // End of a segment
	in=false;
	Seg & segFake=segServer.createSeg(begin,ind-begin,0,       // Create a segment - Take care : length=end-begin+1 but ind =end+1 !!
					  labelOutput,fileName);
	outputSeg.add(segFake);                                  // Add a segment 	
      }
      ind++;                                                       // Increment the frame index
    }                                                              // end of one input segment
    if (in){                                                       // deal with the last energized segmeent inside the current input segment
      in=false;
      Seg & segFake=segServer.createSeg(begin,ind-begin+1,0,       // Create a segment 
					labelOutput,fileName);
      outputSeg.add(segFake);                                    // Add a segment  - Take care : length=end-begin+1 and ind=end in this case !!
    }                 
  }                                                              // end feature loop                   
  
  return countFrames;
}