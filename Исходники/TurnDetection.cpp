void TurnDetection(Config& config, SegCluster& cluster,SegServer& segOutputServer,
		  StatServer& ss,FeatureServer &fs,MixtureServer&
		  ms,LabelServer& labelServer){

SegServer segTemp;	

segOutputServer.removeAllClusters();
segOutputServer.removeAllSegs();

SegServer actualSeg;	
String et_temp="speech";
Label l(et_temp);
SegCluster& clusterSeg=actualSeg.createCluster(labelServer.addLabel(l),et_temp," "); //Create the cluster L


String crit="DGLR";
if(config.existsParam("clusteringCrit")) 
	crit=config.getParam("clusteringCrit");

double threshold=0.0;
if(config.existsParam("clusteringCritThresh"))
	threshold=config.getParam("clusteringCritThresh").toDouble();

unsigned long winSize=50;
if(config.existsParam("winSize")) winSize=config.getParam("winSize").toLong();
unsigned long winStep=5;
if(config.existsParam("winStep")) winStep=config.getParam("winStep").toLong();
double alpha=0.7;
if(config.existsParam("alpha")) alpha=config.getParam("alpha").toDouble();

unsigned long start1=0, end1=0;
unsigned long start2=0, end2=0;
unsigned long accu=0;


for(unsigned long iseg=0; iseg<cluster.getCount(); iseg++){
	
	
	Seg& segment=(Seg&)cluster.get(iseg);
	if(verbose)
		cout << "Segment" << iseg << ": " << segment.begin() << " " << endSeg(&segment) << endl; 
	if(segment.length() <= 2*winSize){
		clusterSeg.add(actualSeg.createSeg(segment.begin(),endSeg(&segment)-segment.begin()+1,0,segment.string(),segment.sourceName()));
		if(debug) cout << "add: " << segment.begin() << " " << endSeg(&segment) << endl;		
	}
	else{
		ObjectRefVector res;
		start1=segment.begin();
		end1=start1+winSize-1;
		start2=end1+1;
		end2=start2+winSize-1;
		accu = start1;
	
		while(end2 < endSeg(&segment)){
			if(verbose){
				cout << "Computation between: " << start1 << " " << end1; 
				cout << " and " << start2 << " " << end2 << endl; 
			}
			SegCluster& c1=segTemp.createCluster();
			c1.add(segTemp.createSeg(start1,winSize,0,"null",segment.sourceName()));
			SegCluster& c2=segTemp.createCluster();
			c2.add(segTemp.createSeg(start2,winSize,0,"null",segment.sourceName()));
			CritInfo *resCrit=new CritInfo(clusteringCriterionWithoutWorldInitOneGaus(config, c1, c2, ss, fs,crit),false,end1);
			
			res.addObject((Object&)*resCrit);	
			start1+=winStep;
			end1+=winStep;
			start2+=winStep;
			end2+=winStep;	
			
		}	
		
	
		/* smoothing */
	/*	for(unsigned long i=1; i<res.size()-1; i++){
			CritInfo &resCrit=(CritInfo&)(res.getObject(i));
			CritInfo &resCritP=(CritInfo&)(res.getObject(i-1));
			CritInfo &resCritN=(CritInfo&)(res.getObject(i+1));
		
			resCrit.setValue(0.25*resCritP.getValue()+0.25*resCritN.getValue()+0.5*resCrit.getValue());
		}	
	*/

           	DoubleVector score_buffer;
           	score_buffer.setSize(2);
           	score_buffer[0 % 2]=((CritInfo&)(res.getObject(0))).getValue();

           	for(unsigned long i=1; i<res.size()-1; i++)
           	{
               		CritInfo &resCrit=(CritInfo&)(res.getObject(i));
               		CritInfo &resCritN=(CritInfo&)(res.getObject(i+1));//right window

               		score_buffer[i % 2]=resCrit.getValue();
               		resCrit.setValue(0.25*score_buffer[(i-1) % 2]+0.25*resCritN.getValue()+0.5*resCrit.getValue());

           	}

		/* to look for maxima in the criterion value curve */
		/* if difference on left and right of a point with neighboor points is over alpha*standard deviation => maxima is found ! */
	
		double sum=0.0;
		double sum2=0.0;
		for(unsigned long i=0; i<res.size(); i++){
			CritInfo &resCrit=(CritInfo&)res.getObject(i);
			sum += resCrit.getValue();
			sum2+=resCrit.getValue()*resCrit.getValue();
		}
		double mean=sum/(double)res.size();
		double std=sqrt((sum2/(double)(res.size())-(mean*mean)));
	
		if(verbose){
			cout << "Mean and std: " << mean << " " << std << endl;
		}
	
		CritInfo &resCrit=(CritInfo&)res.getObject(0);
		resCrit.setDec(false);
		for(unsigned long i=1, j=0; i<res.size()-1; i++){
			/* for each value */
			/* search left min */
			j=i-1;
			double minL=((CritInfo&)res.getObject(i)).getValue();
			bool ok=true;
			while(ok && (j > 0)){
				if(((CritInfo&)res.getObject(j)).getValue() < minL){
					minL =((CritInfo&)res.getObject(j)).getValue();
					j--;
				}else{	
					ok = false;
				}
			}	
		
			if(myabs(((CritInfo&)res.getObject(i)).getValue()-minL) > alpha*std){
			// search right min 
		
				j=i+1;
				double minR=((CritInfo&)res.getObject(i)).getValue();
				ok=true;
				while(ok && (j < res.size())){
					if(((CritInfo&)res.getObject(j)).getValue() < minR){
						minR = ((CritInfo&)res.getObject(j)).getValue();
						j++;
					}else{
						ok = false;
					}
				}
		
				if(myabs(((CritInfo&)res.getObject(i)).getValue()-minR) > alpha*std){
					((CritInfo&)res.getObject(i)).setDec(true);				
				}else{
					((CritInfo&)res.getObject(i)).setDec(false);				
				}
			}else{
				((CritInfo&)res.getObject(i)).setDec(false);					
			}
			/*double max=((CritInfo&)res.getObject(i)).getValue();
			double minL=((CritInfo&)res.getObject(i-1)).getValue();
			double minR=((CritInfo&)res.getObject(i+1)).getValue();
			if((minL < max) && (minR < max) && (max > mean+std))
				((CritInfo&)res.getObject(i)).setDec(true);
			else
				((CritInfo&)res.getObject(i)).setDec(false);
			*/
		}
	
		start1 = segment.begin();
		for(unsigned long i=0; i<res.size(); i++){
			cout << ((CritInfo&)res.getObject(i)).getFrame() << " " << ((CritInfo&)res.getObject(i)).getValue() << " => " << ((CritInfo&)res.getObject(i)).getDec() << endl;
			if(((CritInfo&)res.getObject(i)).getDec()){
				clusterSeg.add(actualSeg.createSeg(start1,((CritInfo&)res.getObject(i)).getFrame()-start1+1,0,segment.string(),segment.sourceName()));
				if(verbose) cout << "add: " << start1 << " " << ((CritInfo&)res.getObject(i)).getFrame() << endl;
				start1=((CritInfo&)res.getObject(i)).getFrame()+1;
			}
		}
		// last point
		cout << "last point: " << start1 << " fin segment: " <<  endSeg(&segment) << endl;
		if(start1 < endSeg(&segment)){
			clusterSeg.add(actualSeg.createSeg(start1,endSeg(&segment)-start1+1,0,segment.string(),segment.sourceName()));
			if(verbose) cout << "add: " << start1 << " " << endSeg(&segment) << endl;	
		}

	}
}


displayAllClusters(config, actualSeg);
segOutputServer=actualSeg;
}