//_________________________________________________________________________________________________
void OccupancyInTimeBins(const char* input, const char* output)
{
  timeResolutions.push_back(1);
  timeResolutions.push_back(10);
  timeResolutions.push_back(100);
  
  AliRawReader* rawReader = AliRawReader::Create(input);
  
  AliMUONRawStreamTrackerHP stream(rawReader);
  
  stream.DisableWarnings();
  stream.TryRecover(kTRUE);
  
  int numberOfUsedEvents(0);
  int numberOfBadEvents(0);
  int numberOfEvents(0);
  int numberOfPhysicsEvent(0);
  int numberOfCalibrationEvent(0);
  int numberOfEventsWithMCH(0);
  int numberOfEventsWithoutCDH(0);
  
  int runNumber(-1);
  
  time_t runStart, runEnd;
  AliMergeableCollection* hc(0x0);
  
  AliCDBManager* cdbm = AliCDBManager::Instance();
  
  if (!cdbm->IsDefaultStorageSet())
  {
    cdbm->SetDefaultStorage("local:///cvmfs/alice-ocdb.cern.ch/calibration/data/2015/OCDB");
  }
  
  cdbm->SetRun(0);
  
  AliMpCDB::LoadAll();


  while (rawReader->NextEvent() ) //&& numberOfEvents < 1000 )
  {
    rawReader->Reset();
    ++numberOfEvents;
    
    if ( !rawReader->GetDataHeader() )
    {
      ++numberOfEventsWithoutCDH;
    }
    
    if (rawReader->GetType() != AliRawEventHeaderBase::kPhysicsEvent)
    {
      if ( rawReader->GetType() == AliRawEventHeaderBase::kCalibrationEvent )
      {
        ++numberOfCalibrationEvent;
      }
      continue;
    }
    
    if (runNumber<0)
    {
      runNumber = rawReader->GetRunNumber();
      GetTimeRange(runNumber,runStart,runEnd);

      hc = new AliMergeableCollection("occ");
      
      for ( std::vector<int>::size_type is = 0; is < timeResolutions.size(); ++is )
      {
        FillCollection(*hc,runStart,runEnd,timeResolutions[is]);
      }
      
      FillNumberOfPads(*hc);
      
    }
    
    ++numberOfPhysicsEvent;
    
    if ( numberOfPhysicsEvent % 5000 == 0 )
      cout << Form("%12d events processed : %12d physics %d used ones %d bad ones [ %d with MCH information ]",
                   numberOfEvents,numberOfPhysicsEvent,numberOfUsedEvents,numberOfBadEvents,numberOfEventsWithMCH) << endl;
    
    Bool_t mchThere(kFALSE);
    
    for ( int iDDL = 0; iDDL < AliDAQ::NumberOfDdls("MUONTRK") && !mchThere; ++iDDL )
    {
      rawReader->Reset();
      rawReader->Select("MUONTRK",iDDL,iDDL);
      if (rawReader->ReadHeader() )
      {
        if (rawReader->GetEquipmentSize() ) mchThere = kTRUE;
      }
    }
    
    if ( mchThere)
    {
      ++numberOfEventsWithMCH;
    }
    else
    {
      continue;
    }
    
    Int_t buspatchId;
    UShort_t  manuId;
    UChar_t manuChannel;
    UShort_t adc;
    
    stream.First();
    
    std::map<int,int> bpValues;
    
    while ( stream.Next(buspatchId,manuId,manuChannel,adc,kTRUE) )
    {
      bpValues[buspatchId]++;
    }
    
    for ( std::map<int,int>::const_iterator it = bpValues.begin(); it != bpValues.end(); ++it )
    {
      const int& buspatchId = it->first;
      const int& bpvalue = it->second;
      
      TString bpName = Form("BP%04d",buspatchId);
      
      for ( std::vector<int>::size_type is = 0; is < timeResolutions.size(); ++is )
      {
        TH1* h = hc->Histo(Form("/BUSPATCH/HITS/%ds/%s",timeResolutions[is],bpName.Data()));
        
        if (!h)
        {
          cout << "histogram not found" << endl;
          continue;
        }
        
        h->Fill(rawReader->GetTimestamp(),bpvalue);
      }
    }
    
    for ( std::vector<int>::size_type is = 0; is < timeResolutions.size(); ++is )
    {
      TH1* h = hc->Histo(Form("Nevents%ds",timeResolutions[is]));
      
      if (!h)
      {
        cout << "histogram not found" << endl;
        continue;
      }
      
      h->Fill(rawReader->GetTimestamp());
    }
    
  }
  
  // Group BP histograms per DE then DDL then Chamber then Station
  
  for ( std::vector<int>::size_type is = 0; is < timeResolutions.size(); ++is )
  {
    GroupByDE(*hc,timeResolutions[is]);
    GroupByDDL(*hc,timeResolutions[is]);
    GroupByChamber(*hc,timeResolutions[is]);
    GroupByStation(*hc,timeResolutions[is]);
  }
  
  // make normalized versions of the histograms
  Normalize(*hc);
  
  TFile* fout = new TFile(output,"RECREATE");
  hc->Write("occ");
  delete fout;
}