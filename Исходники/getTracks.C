Tracks * getTracks(Int_t Runs, Int_t dataType, Int_t frameType, Float_t energy, Float_t *x, Float_t *y) {
   run_energy = energy;

   DataInterface   * di = new DataInterface();
   Misalign        * m = new Misalign();
   Int_t             nClusters = kEventsPerRun * 5 * nLayers;
   Int_t             nHits = kEventsPerRun * 50;
   Int_t             nTracks = kEventsPerRun * 2;
   Bool_t            breakSignal = false;
   CalorimeterFrame *cf = new CalorimeterFrame();
   Clusters        * clusters = new Clusters(nClusters);
   Clusters        * trackerClusters = new Clusters(nClusters);
   Hits            * hits = new Hits(nHits);
   Hits            * eventIDs = new Hits(kEventsPerRun * sizeOfEventID);
   Int_t             eventID = -1;
   Hits            * trackerHits = new Hits(nHits);
   Tracks          * calorimeterTracks = nullptr;
   Tracks          * trackerTracks = new Tracks(nTracks);
   Tracks          * allTracks = new Tracks(nTracks * Runs);
   TRandom3        * gRandom = new TRandom3(0);
   TStopwatch        t1, t2, t3, t4, t5, t6;
   ofstream          file("OutputFiles/efficiency.csv", ofstream::out | ofstream::app);
   Int_t             totalNumberOfFrames = 0;
   Int_t             tracksTotalNumberAfterRecon = 0;
   Int_t             tracksRemovedDueToBadChannels = 0;
   Int_t             tracksGivenToReconstruction = 0;
   Int_t             tracksRemovedDueToLeavingDetector = 0;
   Int_t             tracksRemovedDueToNuclearInteractions = 0;
   Int_t             clustersInFirstLayer = 0;
   Int_t             tracksRemovedDueToCollisions = 0;

   // file: np; number of reconstructed tracks; tracks after removeTracksLeavingDetector; tracks after removeTrackCollisions
   
   for (Int_t i=0; i<Runs; i++) {

      cout << "Finding track " << (i+1)*kEventsPerRun << " of " << Runs*kEventsPerRun << "... ";
      
      if (dataType == kMC) {
         t1.Start();

         eventID = di->getMCFrame(i, cf, x, y);
         di->getEventIDs(i, eventIDs);

         t1.Stop(); t2.Start();
         showDebug("Start diffuseFrame\n");

         cf->diffuseFrame(gRandom);

         showDebug("End diffuseFrame, start findHits\n");
         t2.Stop(); t3.Start();

         hits = cf->findHits(eventID);

         showDebug("Number of hits in frame: " << hits->GetEntriesFast() << endl);
         t3.Stop(); t4.Start();

         clusters = hits->findClustersFromHits(); // badly optimized
         
         cout << "Found " << clusters->GetEntriesInLayer(0) << " clusters in the first layer.\n";
         cout << "Found " << clusters->GetEntriesInLayer(1) << " clusters in the second layer.\n";

         clusters->removeSmallClusters(2);
         cout << "Found " << clusters->GetEntriesInLayer(0) << " clusters in the first layer after removeSmallClusters.\n";

         t4.Stop();

         clusters->matchWithEventIDs(eventIDs);
         eventIDs->Clear();
      }
      
      else if (dataType == kData) {
         t1.Start(); di->getDataFrame(i, cf, energy); t1.Stop();
         t3.Start(); hits = cf->findHits(); t3.Stop();
         t4.Start(); clusters = hits->findClustersFromHits(); t4.Stop();
         clusters->removeSmallClusters(2);
         clusters->removeAllClustersAfterLayer(8); // bad data in layer 10 and 11
         cout << "Found " << clusters->GetEntriesInLayer(0) << " clusters in the first layer.\n";
         cout << "Found " << clusters->GetEntriesInLayer(1) << " clusters in the second layer.\n";

         m->correctClusters(clusters);
      }
      
      t5.Start();
      calorimeterTracks = clusters->findCalorimeterTracks();
      t5.Stop();
      
      tracksTotalNumberAfterRecon += calorimeterTracks->GetEntries();

      if (calorimeterTracks->GetEntriesFast() == 0) breakSignal = kTRUE; // to stop running

      // Track improvements
      Int_t nTracksBefore = 0, nTracksAfter = 0;
      Int_t nIsInelastic = 0, nIsNotInelastic = 0;
      
      calorimeterTracks->extrapolateToLayer0();
      calorimeterTracks->splitSharedClusters();
      nTracksBefore = calorimeterTracks->GetEntries();
      calorimeterTracks->removeTracksLeavingDetector();
      nTracksAfter = calorimeterTracks->GetEntries();
      
      tracksRemovedDueToLeavingDetector += nTracksBefore - nTracksAfter;
      
      cout << "Of " << nTracksBefore << " tracks, " << nTracksBefore - nTracksAfter << " (" << 100* ( nTracksBefore - nTracksAfter) / ( (float) nTracksBefore ) << "%) were lost when leaving the detector.\n";
      
      nTracksBefore = calorimeterTracks->GetEntries();
      calorimeterTracks->removeTrackCollisions();
      nTracksAfter = calorimeterTracks->GetEntries();
      
      tracksRemovedDueToCollisions += nTracksBefore - nTracksAfter;

      if (kDataType == kData) {
         nTracksBefore = calorimeterTracks->GetEntries();
         calorimeterTracks->removeTracksEndingInBadChannels();
         nTracksAfter = calorimeterTracks->GetEntries();
         cout << "Of " << nTracksBefore << " tracks, " << nTracksBefore - nTracksAfter << " (" << 100* ( nTracksBefore - nTracksAfter) / ( (float) nTracksBefore ) << "%) were removed due to ending just before a bad channel.\n";
         tracksRemovedDueToBadChannels += nTracksBefore - nTracksAfter;

      }
      
      for (Int_t k=0; k<calorimeterTracks->GetEntriesFast(); k++) {
         if (calorimeterTracks->At(k)) {
            if (calorimeterTracks->At(k)->doesTrackEndAbruptly()) {
               nIsInelastic++;
            }
            else nIsNotInelastic++;
         }
      }
      
      tracksRemovedDueToNuclearInteractions += nIsInelastic;
      cout << "Of these, " << nIsInelastic << " end abruptly and " << nIsNotInelastic << " does not.\n";

      file << energy << " " << kEventsPerRun << " " << nTracksBefore << " " << nTracksAfter << " " << calorimeterTracks->GetEntries() << " " <<  nIsInelastic << " " << nIsNotInelastic << endl;

      // calorimeterTracks->retrogradeTrackImprovement(clusters);

      calorimeterTracks->Compress();
      calorimeterTracks->CompressClusters();
      
      for (Int_t j=0; j<calorimeterTracks->GetEntriesFast(); j++) {
         if (!calorimeterTracks->At(j)) continue;

         allTracks->appendTrack(calorimeterTracks->At(j));
         tracksGivenToReconstruction++;
      }

      allTracks->appendClustersWithoutTrack(clusters->getClustersWithoutTrack());

      cout << Form("Timing: getMCframe (%.2f sec), diffuseFrame (%.2f sec), findHits (%.2f sec), findClustersFromHits (%.2f sec), findTracks (%.2f sec)\n",
              t1.RealTime(), t2.RealTime(), t3.RealTime(), t4.RealTime(), t5.RealTime());

      cf->Reset();
      hits->clearHits();
      trackerHits->clearHits();
      clusters->clearClusters();
      trackerClusters->clearClusters();
      calorimeterTracks->Clear();
      trackerTracks->Clear();

      if (breakSignal) break;
   }
   printf("\033[1mTrack statics for article. Clusters found in first layer (= N protons) = %d. Total number of tracks found = %d. Total number of tracks given to reconstruction = %d. Tracks removed due to bad channels = %d. Tracks removed due to nuclear interactions = %d. Tracks removed due to leaving the detector laterally = %d. Tracks removed due to collisions = %d. Sum = %d.\033[0m\n", clustersInFirstLayer, tracksTotalNumberAfterRecon, tracksGivenToReconstruction, tracksRemovedDueToBadChannels, tracksRemovedDueToNuclearInteractions, tracksRemovedDueToLeavingDetector, tracksRemovedDueToCollisions, tracksGivenToReconstruction + tracksRemovedDueToBadChannels + tracksRemovedDueToLeavingDetector + tracksRemovedDueToCollisions); 

   file.close();

   delete cf;
   delete clusters;
   delete trackerClusters;
   delete hits;
   delete trackerHits;
   delete calorimeterTracks;
   delete trackerTracks;
   delete di;

   return allTracks;
}