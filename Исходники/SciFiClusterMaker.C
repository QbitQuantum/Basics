void SciFiClusterMaker::run(TestBeamEvent *event, Clipboard *clipboard)
{
    double pcut=0.;
    double residCut=parameters->residualmaxx;
    //std::cout << " residCut is " << residCut;
    TestBeamTracks* tracks=(TestBeamTracks*)clipboard->get("Tracks");
    if(!tracks) return;
    int nTracks=0;
    int timeStampedTracks=0;
    int timeStampedSciFi=0;
    //std::vector<SciFiCluster*>* scifiClusters = new std::vector<SciFiCluster*>;
    double prevfibreTrackerClock=0;
    double prevtimeAfterShutterOpen=0;

    for(TestBeamTracks::iterator it=tracks->begin(); it<tracks->end(); it++) {
        nTracks++;
        TestBeamTrack* track= *it;
        TDCTrigger *itr = track->tdcTrigger();
        double currentfibreTrackerClock=0;

        if(!itr)continue;
        timeStampedTracks++;

        std::string chip="SciFi";

        //get intersection point of track with that sensor
        TestBeamTransform* mytransform = new TestBeamTransform(parameters->alignment[chip]->displacementX(),
                parameters->alignment[chip]->displacementY(),
                parameters->alignment[chip]->displacementZ(),
                parameters->alignment[chip]->rotationX(),
                parameters->alignment[chip]->rotationY(),
                parameters->alignment[chip]->rotationZ());

        PositionVector3D< Cartesian3D<double> > planePointLocalCoords(0,0,0);
        PositionVector3D< Cartesian3D<double> > planePointGlobalCoords = (mytransform->localToGlobalTransform())*planePointLocalCoords;
        PositionVector3D< Cartesian3D<double> > planePoint2LocalCoords(0,0,1);
        PositionVector3D< Cartesian3D<double> > planePoint2GlobalCoords = (mytransform->localToGlobalTransform())*planePoint2LocalCoords;

        float normal_x=planePoint2GlobalCoords.X()-planePointGlobalCoords.X();
        float normal_y=planePoint2GlobalCoords.Y()-planePointGlobalCoords.Y();
        float normal_z=planePoint2GlobalCoords.Z()-planePointGlobalCoords.Z();

        float length=((planePointGlobalCoords.X()-track->firstState()->X())*normal_x+
                      (planePointGlobalCoords.Y()-track->firstState()->Y())*normal_y+
                      (planePointGlobalCoords.Z()-track->firstState()->Z())*normal_z)/
                     (track->direction()->X()*normal_x+track->direction()->Y()*normal_y+track->direction()->Z()*normal_z);
        float x_inter=track->firstState()->X()+length*track->direction()->X();
        float y_inter=track->firstState()->Y()+length*track->direction()->Y();
        float z_inter=track->firstState()->Z()+length*track->direction()->Z();


        //change to local coordinates of that plane
        PositionVector3D< Cartesian3D<double> > intersect_global(x_inter,y_inter,z_inter);
        PositionVector3D< Cartesian3D<double> > intersect_local = (mytransform->globalToLocalTransform())*intersect_global;



        SciFiCluster* cluster;

        bool current_cluster=false;
        int prev_fibreTrackChannel=0;

        if(itr->nFibreTrackerHits()!=0) {
            timeStampedSciFi++;
        }

        for(int ih=0; ih<itr->nFibreTrackerHits(); ih++) {


            if((itr)->fibreTrackerADC(ih)<pcut) {
                continue;
            }

            if( abs((itr)->fibreTrackerChannel(ih)-89) < 3 ||
                    abs((itr)->fibreTrackerChannel(ih)-65) < 3 ||
                    abs((itr)->fibreTrackerChannel(ih)-67) < 3 )continue;


            channel->Fill((itr)->fibreTrackerChannel(ih));
            channel_ADC->Fill((itr)->fibreTrackerADC(ih));

            if(m_debug) {
                std::cout<<"HIT! chan: "<<(itr)->fibreTrackerChannel(ih)<<" = "<<(itr)->fibreTrackerADC(ih)<<std::endl;
            }
            if (m_debug) std::cout << "sci fi hit " << ih << " channel " << (itr)->fibreTrackerChannel(ih) << " clock " << (itr)->fibreTrackerClock(ih) << std::endl;
            currentfibreTrackerClock=(itr)->fibreTrackerClock(ih);
            if (m_debug) std::cout << " currentfibreTrackerClock updated to " << currentfibreTrackerClock << std::endl;

            scifisyncdelay->Fill((itr)->syncDelay());

            if(!current_cluster) {
                cluster = new SciFiCluster();
                cluster->addHit((itr)->fibreTrackerChannel(ih),(itr)->fibreTrackerADC(ih));
                if (m_debug)
                    std::cout<<"Making new cluster"<<std::endl;
                current_cluster=true;
                prev_fibreTrackChannel=(itr)->fibreTrackerChannel(ih);
                continue;
            }

            if(abs((itr)->fibreTrackerChannel(ih)-prev_fibreTrackChannel) < 3) {
                if(m_debug)
                    std::cout<<"Adding hit to cluster"<<std::endl;
                cluster->addHit((itr)->fibreTrackerChannel(ih),(itr)->fibreTrackerADC(ih));
                prev_fibreTrackChannel=(itr)->fibreTrackerChannel(ih);
            }
            else {
                if(m_debug)
                    std::cout<<"Saving previous cluster and making new one"<<std::endl;
                cluster_ADC->Fill(cluster->getADC());
                cluster_size->Fill(cluster->getClusterSize());
                setClusterCentre(cluster);
                if (m_debug)
                    std::cout << " cluster position " << (cluster)->getPosition() << " cluster_ADC " << cluster->getADC() << " cluster_size " << cluster->getClusterSize() << std::endl;
                if(fabs(intersect_local.X()-(cluster)->getPosition())<residCut) {
                    residualPlot->Fill(intersect_local.X()-(cluster)->getPosition());
                    scifiresidvschan->Fill((cluster)->getPosition()/(-0.25),intersect_local.X()-(cluster)->getPosition());
                    if (m_debug) std::cout << " Adding scifi alignment cluster to track " << std::endl;

                    if (((cluster)->getPosition()/(-0.25))<61.) {
                        track->addSciFiAlignmentClusterToTrack(cluster);
                    }
                }
                correlation_x->Fill(intersect_local.X()-(cluster)->getPosition());
                //scifiClusters->push_back(cluster);
                cluster = new SciFiCluster();
                cluster->addHit((itr)->fibreTrackerChannel(ih),(itr)->fibreTrackerADC(ih));
                prev_fibreTrackChannel=(itr)->fibreTrackerChannel(ih);
            }
        }

        if(current_cluster) {
            setClusterCentre(cluster);
            if(fabs(intersect_local.X()-(cluster)->getPosition())<residCut) {
                residualPlot->Fill(intersect_local.X()-(cluster)->getPosition());
                scifiresidvschan->Fill((cluster)->getPosition()/(-0.25),intersect_local.X()-(cluster)->getPosition());
                if (((cluster)->getPosition()/(-0.25))<61.) {
                    track->addSciFiAlignmentClusterToTrack(cluster);
                }
            }
            if (m_debug) std::cout<<"Saving current cluster"<<std::endl;
            if (m_debug) std::cout << " cluster position " << (cluster)->getPosition() << " cluster_ADC " << cluster->getADC() << " cluster_size " << cluster->getClusterSize() << std::endl;
            correlation_x->Fill(intersect_local.X()-(cluster)->getPosition());
//				scifiClusters->push_back(cluster);
            cluster_ADC->Fill(cluster->getADC());
            cluster_size->Fill(cluster->getClusterSize());
        }

        if (prevtimeAfterShutterOpen>0.&&currentfibreTrackerClock>0.) {
            if (m_debug) std::cout << " Filling scifitime resid: Previous shutter time " << prevtimeAfterShutterOpen << " current shutter time " << (itr)->timeAfterShutterOpen() << " previous fibre trackerclock " << prevfibreTrackerClock << " current fibre tracker clock " << currentfibreTrackerClock << std::endl;
            scifitimeresid->Fill(((itr)->timeAfterShutterOpen()-prevtimeAfterShutterOpen)-(currentfibreTrackerClock-prevfibreTrackerClock));
        }
        if (currentfibreTrackerClock==0) {
            prevtimeAfterShutterOpen=0.;
        } else {
            prevtimeAfterShutterOpen=(itr)->timeAfterShutterOpen();
            prevfibreTrackerClock=currentfibreTrackerClock;
        }
        //place track correlation here based on time stamp on track


    }

    timeStampedTracksPlot->Fill(timeStampedTracks);
    nTracksPlot->Fill(nTracks);

    nTracksPlot_perEvent->Fill(eventNum,nTracks);
    timeStampedTracksPlot_perEvent->Fill(eventNum,timeStampedTracks);

    timeStampedSciFiPlot_perEvent->Fill(eventNum,timeStampedSciFi);
    //*/





    int timeStampedSciFi2=0;

    for(unsigned int j=0; j<event->nTDCElements(); j++) {
        TestBeamEventElement *ele=event->getTDCElement(j);
        std::string chip = ele->detectorId();
        if(chip!=std::string("SciFi")) continue;
        TDCFrame* frame = (TDCFrame*)ele;

        TDCTriggers* triggers=frame->triggers();

        for(TDCTriggers::iterator itr=triggers->begin(); itr!=triggers->end(); itr++) {

            if((*itr)->nFibreTrackerHits()!=0) {
                timeStampedSciFi2++;
            }
        }
    }

    timeStampedSciFiPlot2_perEvent->Fill(eventNum,timeStampedSciFi2);





    /*

    	if(parameters->dut != "SciFi") return;
      if(event->nTDCElements() == 0) return;
      if(m_debug) std::cout << "In SciFiClusterMaker"<<std::endl;
    	double pcut=20.;
      std::vector<SciFiCluster*>* scifiClusters = new std::vector<SciFiCluster*>;
      scifiClusters->clear();
      for(unsigned int j=0;j<event->nTDCElements();j++){
        TestBeamEventElement *ele=event->getTDCElement(j);
        std::string chip = ele->detectorId();
        if(chip!=std::string("SciFi")) continue;
        TDCFrame* frame = (TDCFrame*)ele;
        if(m_debug) std::cout<<" Indexed TDC frame "<<frame->positionInSpill()
    			<<" at "<<std::cout.precision(15)<<std::cout.width(18)<<frame->timeStamp()
    			<<" with "<<frame->nTriggersInFrame()<<" triggers in "<<int(frame->timeShutterIsOpen()/1000)
    			<<"us ("<<frame->nTriggersUnmatchedInSpill()<<" mismatch in frame)"<<std::endl;
        //to reject those frames which number of triggers is not the same in the Telescope and in the TDC:
        //if(frame->nTriggersUnmatchedInSpill()) continue;
    		TDCTriggers* triggers=frame->triggers();

        for(TDCTriggers::iterator itr=triggers->begin();itr!=triggers->end();itr++){

          if(m_debug) std::cout<<"        trigger "<<(itr-triggers->begin())<<"/"<<frame->nTriggersInFrame()
    				<<" which occured "<<(*itr)->timeAfterShutterOpen()<<" ns after shutter-open, "
    				<<(*itr)->timeAfterShutterOpen()-frame->timeShutterIsOpen()<<" ns before shutter-closed"<<std::endl;

    			//			std::cout<<"Looking at trigger with "<<(*itr)->nFibreTrackerHits()<<" fibre tracker hits"<<std::endl;
    			SciFiCluster* cluster;

    			bool current_cluster=false;
    			int prev_fibreTrackChannel=0;
          for(int ih=0;ih<(*itr)->nFibreTrackerHits();ih++){

    				if((*itr)->fibreTrackerADC(ih)<pcut){
    					continue;
    				}

    				if( abs((*itr)->fibreTrackerChannel(ih)-89) < 3 ||
    					 abs((*itr)->fibreTrackerChannel(ih)-65) < 3 ||
    					 abs((*itr)->fibreTrackerChannel(ih)-67) < 3 )continue;


    				channel->Fill((*itr)->fibreTrackerChannel(ih));
    				channel_ADC->Fill((*itr)->fibreTrackerADC(ih));

    				if(m_debug){std::cout<<"HIT! chan: "<<(*itr)->fibreTrackerChannel(ih)<<" = "<<(*itr)->fibreTrackerADC(ih)<<std::endl;}

    				if(!current_cluster){
    					cluster = new SciFiCluster();
    					cluster->addHit((*itr)->fibreTrackerChannel(ih),(*itr)->fibreTrackerADC(ih));
    					if(m_debug) std::cout<<"Making new cluster"<<std::endl;
    					current_cluster=true;
    					prev_fibreTrackChannel=(*itr)->fibreTrackerChannel(ih);
    					continue;
    				}

    				if(abs((*itr)->fibreTrackerChannel(ih)-prev_fibreTrackChannel) < 3){
    					if(m_debug) std::cout<<"Adding hit to cluster"<<std::endl;
    					cluster->addHit((*itr)->fibreTrackerChannel(ih),(*itr)->fibreTrackerADC(ih));
    					prev_fibreTrackChannel=(*itr)->fibreTrackerChannel(ih);
    				}
    				else{
    					if(m_debug) std::cout<<"Saving previous cluster and making new one"<<std::endl;
    					cluster_ADC->Fill(cluster->getADC());
    					cluster_size->Fill(cluster->getClusterSize());
    					setClusterCentre(cluster);
    					scifiClusters->push_back(cluster);
    					cluster = new SciFiCluster();
    					cluster->addHit((*itr)->fibreTrackerChannel(ih),(*itr)->fibreTrackerADC(ih));
    					prev_fibreTrackChannel=(*itr)->fibreTrackerChannel(ih);
    				}
    			}

    			if(current_cluster){
    				setClusterCentre(cluster);
    				scifiClusters->push_back(cluster);
    				cluster_ADC->Fill(cluster->getADC());
    				cluster_size->Fill(cluster->getClusterSize());
    			}

    			//place track correlation here based on time stamp on track

    		}
    	}



    	TestBeamTracks* tracks=(TestBeamTracks*)clipboard->get("Tracks");
    	if(!tracks) return;
    	for(TestBeamTracks::iterator it=tracks->begin(); it<tracks->end(); it++){
    		TestBeamTrack* track= *it;

    		std::string chip="SciFi";

    		//get intersection point of track with that sensor
    		TestBeamTransform* mytransform = new TestBeamTransform(parameters->alignment[chip]->displacementX(),
    																													 parameters->alignment[chip]->displacementY(),
    																													 parameters->alignment[chip]->displacementZ(),
    																													 parameters->alignment[chip]->rotationX(),
    																													 parameters->alignment[chip]->rotationY(),
    																													 parameters->alignment[chip]->rotationZ());

    		PositionVector3D< Cartesian3D<double> > planePointLocalCoords(0,0,0);
    		PositionVector3D< Cartesian3D<double> > planePointGlobalCoords = (mytransform->localToGlobalTransform())*planePointLocalCoords;
    		PositionVector3D< Cartesian3D<double> > planePoint2LocalCoords(0,0,1);
    		PositionVector3D< Cartesian3D<double> > planePoint2GlobalCoords = (mytransform->localToGlobalTransform())*planePoint2LocalCoords;

    		float normal_x=planePoint2GlobalCoords.X()-planePointGlobalCoords.X();
    		float normal_y=planePoint2GlobalCoords.Y()-planePointGlobalCoords.Y();
    		float normal_z=planePoint2GlobalCoords.Z()-planePointGlobalCoords.Z();

    		float length=((planePointGlobalCoords.X()-track->firstState()->X())*normal_x+
    									(planePointGlobalCoords.Y()-track->firstState()->Y())*normal_y+
    									(planePointGlobalCoords.Z()-track->firstState()->Z())*normal_z)/
    		(track->direction()->X()*normal_x+track->direction()->Y()*normal_y+track->direction()->Z()*normal_z);
    		float x_inter=track->firstState()->X()+length*track->direction()->X();
    		float y_inter=track->firstState()->Y()+length*track->direction()->Y();
    		float z_inter=track->firstState()->Z()+length*track->direction()->Z();


    		//change to local coordinates of that plane
    		PositionVector3D< Cartesian3D<double> > intersect_global(x_inter,y_inter,z_inter);
    		PositionVector3D< Cartesian3D<double> > intersect_local = (mytransform->globalToLocalTransform())*intersect_global;


    		for(SciFiClusters::iterator cs=scifiClusters->begin(); cs!=scifiClusters->end(); cs++){
    			//place if on timestamp between cluster and track
    			correlation_x->Fill(intersect_local.X()-(*cs)->getPosition());
    		}

    	}

    //*/



    eventNum++;
    //  clipboard->put("SciFiClusters",(TestBeamObjects*)scifiClusters,CREATED);
}