// ######################################################################
void SimulationViewerStats::save1(const ModelComponentSaveInfo& sinfo)
{
  // Use a LINFO here since we are already slowed down by writing
  // stats, we should at least have a short debug on this fact
  LINFO("SAVING STATS TO %s",itsStatsFname.getVal().c_str());

  // Lock the file. We put this here to support multi-process in the
  // future. However, this will not work on NFS mounts.
  struct flock fl; int fd;
  lockFile(itsStatsFname.getVal().c_str(),fd,fl);

  // Since this is more or less debug info we open and flush every iteration.
  // rather than once each run.
  std::ofstream statsFile;
  statsFile.open(itsStatsFname.getVal().c_str(),std::ios_base::app);

  // get the OFS to save to, assuming sinfo is of type
  // SimModuleSaveInfo (will throw a fatal exception otherwise):
  nub::ref<FrameOstream> ofs =
    dynamic_cast<const SimModuleSaveInfo&>(sinfo).ofs;

  // also get the SimEventQueue:
  SimEventQueue *q    = dynamic_cast<const SimModuleSaveInfo&>(sinfo).q;

  // initialize our stats dump file if desired:
  if(itsFrameIdx == 0)
  {
    rutz::shared_ptr<SimReqVCXmaps> vcxm(new SimReqVCXmaps(this));
    q->request(vcxm); // VisualCortex is now filling-in the maps...

    if (itsStatsFname.getVal().size())
    {
      itsStatsFile = new std::ofstream(itsStatsFname.getVal().c_str());
      if (itsStatsFile->is_open() == false)
        LFATAL("Failed to open '%s' for writing.",
               itsStatsFname.getVal().c_str());

      // dump the settings of the model:
      getRootObject()->printout(*itsStatsFile, "# ");

      // list all our channels:
      //LFATAL("FIXME");
      // also get the SimEventQueue:

      rutz::shared_ptr<ChannelMaps> chm        = vcxm->channelmaps();
      uint                          numSubmaps = chm->numSubmaps();

      *itsStatsFile << "# CHANNELS: ";

      for(uint i = 0; i < numSubmaps; i++)
      {
        NamedImage<float> smap = chm->getRawCSmap(i);
        *itsStatsFile << smap.name() << ", ";
      }
      *itsStatsFile << std::endl;
    }
  }

  // We flush frequently since this output is debuggy in nature or it's being used
  // to collect information which needs assurance of accuracy for instance in
  // RSVP analysis. It is better to err on the side of caution.
  (*itsStatsFile).flush();
  (*itsStatsFile).close();

  // get the basic input frame info
  if (SeC<SimEventInputFrame> e = q->check<SimEventInputFrame>(this))
  {
    itsSizeX       = e->frame().getWidth();
    itsSizeY       = e->frame().getHeight();
    itsFrameNumber = (unsigned int)e->frameNum();
    itsFrameIdx    = itsFrameNumber;
  }
  else
  {
    itsFrameNumber = itsFrameIdx;
    itsFrameIdx++;
  }

  // get the latest input frame:
  // Since we are only using it's basic statistics (Height / Width) , we don't care about it's
  // blackboard status. Use SEQ_ANY then. Otherwise, this will not fetch at any rate.
  Image< PixRGB<byte> > input;
  if (SeC<SimEventRetinaImage> e = q->check<SimEventRetinaImage>(this,SEQ_ANY))
    input = e->frame().colorByte();
  else
    LINFO("No input? Check the SimEventCue.");

  // Get the current frame number or keep track on your own
  /*
  if (SeC<SimEventInputFrame> e = q->check<SimEventInputFrame>(this))
    itsFrameIdx = e->frameNum();
  else
    itsFrameIdx++;
  */

  // get the latest raw AGM:
  Image<float> agm;
  if (SeC<SimEventAttentionGuidanceMapOutput> e =
      q->check<SimEventAttentionGuidanceMapOutput>(this))
    agm = e->agm(1.0F);
  else
    LINFO("No AGM? Check the SimEventCue.");

  // if we are missing input or agm, return:
  // We also need to warn so that we know why the stats file may be empty
  bool quit = false;
  if (input.initialized() == false)
    {
      LINFO("WARNING!!! Input seems not to be initialized, so detailed stats cannot be saved.");
      quit = true;
    }
  if(agm.initialized() == false)
    {
      LINFO("WARNING!!! NO Attention Guidance MAP \"AGM\" so detailed stats cannot be saved.");
      quit = true;
    }

  if(quit == true) return;

  // update the trajectory:
  Image< PixRGB<byte> > res;
  const int w = input.getWidth();

  // save image results? if so let's prepare it
  if (itsSaveXcombo.getVal() || itsSaveYcombo.getVal())
    {
      Image<float> nagm = getMap(*q);
      res = colGreyCombo(input, nagm, itsSaveXcombo.getVal(),
                         itsDisplayInterp.getVal());
    }

  // if we are saving single channel stats save saliency stats using a compatable format
  // SEE: SingleChannel.C / saveStats(..) for more info on format
  if (itsGetSingleChannelStats.getVal())
    saveCompat(agm);

  // Save a bunch of stats?
  if (statsFile)
    {
      // start with the current simulation time:
       statsFile <<std::endl<<"= "<<q->now().msecs()
                     <<" # time of frame in ms"<<std::endl;

      // get min/max/avg and stdev and number of peaks in AGM:
      float mi, ma, av; getMinMaxAvg(agm, mi, ma, av);
      double sdev = stdev(agm);
      double peaksum; int npeaks = findPeaks(agm, 0.0f, 255.0f, peaksum);

      // find the location of max in the AGM, at scale of original input:
      float maxval; Point2D<int> maxloc;
      findMax(agm, maxloc, maxval);
      float scale = float(w) / float(agm.getWidth());
      maxloc.i = int(maxloc.i * scale + 0.4999F);
      maxloc.j = int(maxloc.j * scale + 0.4999F);
      if (res.initialized())
        {
          drawPatch(res, maxloc, 4, COL_YELLOW);
          drawPatch(res, maxloc + Point2D<int>(w, 0), 4, COL_YELLOW);
        }

      // find the location of min in the AGM, at scale of original input:
      float minval; Point2D<int> minloc;
      findMin(agm, minloc, minval);
      minloc.i = int(minloc.i * scale + 0.4999F);
      minloc.j = int(minloc.j * scale + 0.4999F);
      if (res.initialized())
        {
          drawPatch(res, minloc, 4, COL_GREEN);
          drawPatch(res, minloc + Point2D<int>(w, 0), 4, COL_GREEN);
        }

      // save some stats for that location:
       statsFile  <<maxloc.i<<' '<<maxloc.j<<' '<<minloc.i<<' '
                  <<minloc.j<<' '<<ma<<' '<<mi<<' '<<av<<' '<<sdev
                  <<' '<<npeaks<<' '<<peaksum
                  <<" # Xmax Ymax Xmin Ymin max min avg std npeaks peaksum"
                  <<std::endl;

      // build a vector of points where we will save samples. First is
      // the max, second the min, then a bunch of random locations:
      std::vector<Point2D<int> > loc;
      loc.push_back(maxloc);
      loc.push_back(minloc);
      for (uint n = 0; n < 100; n ++)
        loc.push_back(Point2D<int>(randomUpToNotIncluding(input.getWidth()),
                              randomUpToNotIncluding(input.getHeight())));

      // Get all the conspicuity maps:
      ImageSet<float> cmap;
      //LFATAL("FIXME");
      rutz::shared_ptr<SimReqVCXmaps> vcxm(new SimReqVCXmaps(this));
      q->request(vcxm); // VisualCortex is now filling-in the maps...
      rutz::shared_ptr<ChannelMaps> chm = vcxm->channelmaps();
      uint numSubmaps = chm->numSubmaps();
      for(uint i=0;i < numSubmaps; i++)
      {
        NamedImage<float> tempMap = chm->getRawCSmap(i);
        Image<float> m = tempMap;
        cmap.push_back(m);

        // also store sample points at the min/max locations:
        Point2D<int> p; float v;
        findMax(m, p, v); loc.push_back(p);
        findMin(m, p, v); loc.push_back(p);
      }
      /*
      for (uint i = 0; i < itsBrain->getVC()->numChans(); i ++)
        {
          Image<float> m = itsBrain->getVC()->subChan(i)->getOutput();
          cmap.push_back(m);

          // also store sample points at the min/max locations:
          Point2D<int> p; float v;
          findMax(m, p, v); loc.push_back(p);
          findMin(m, p, v); loc.push_back(p);
        }
      */

      // Go over all sample points and save feature map and
      // conspicuity map values at those locations:
      for (uint i = 0; i < loc.size(); i ++)
        {
          Point2D<int> p = loc[i];
          Point2D<int> pp(int(p.i / scale), int(p.j / scale));

           statsFile <<p.i<<' '<<p.j<<"     ";

          // do the conspicuity maps first. Since they are all at the
          // scale of the AGM, we use pp:
          for (uint j = 0; j < cmap.size(); j ++)
          {
            if((int(p.i / scale) < agm.getWidth()) &&
               (int(p.j / scale) < agm.getHeight()))
            {
              (statsFile)<<cmap[j].getVal(pp)<<' ';
              (statsFile)<<"    ";
            }
            else
            {
              (statsFile)<<"-1"<<' ';
              (statsFile)<<"    ";
            }
          }

          // now the feature maps, we use coordinates p:
          /* TOO BOGUS - disabled for now
          std::vector<double> f;
          itsBrain->getVC()->getFeatures(p, f);
          for (uint j = 0; j < f.size(); j ++) (*statsFile)<<f[j]<<' ';
          */

           statsFile  <<"# features "<<i<<" at ("<<p.i
                         <<", "<<p.j<<')'<<std::endl;
        }
  }

  statsFile.flush();
  statsFile.close();
  unlockFile(itsStatsFname.getVal().c_str(),fd,fl);
  // save results?
  if (res.initialized())
    ofs->writeRGB(res, "T",
                  FrameInfo("SimulationViewerStats trajectory", SRC_POS));

  // Should we compute attention gate stats
  // If we have AG stats we will save the basic LAM stats anyways
  if(itsComputeAGStats.getVal())
    computeAGStats(*q);
  else if (SeC<SimEventAttentionGateOutput> ag =
           q->check<SimEventAttentionGateOutput>(this))
    computeLAMStats(ag->lam());

  //! Save the overlap image
  if(itsOverlap.initialized())
    ofs->writeRGB(itsOverlap, "AG-STAT-MASK",
                  FrameInfo("Stats mask overlap", SRC_POS));

  if(itsVisualSegments.initialized())
    ofs->writeRGB(itsVisualSegments, "AG-STAT-SEGS",
                  FrameInfo("Stats segments", SRC_POS));

  if(itsVisualCandidates.initialized())
    ofs->writeGray(itsVisualCandidates, "AG-STAT-CAND",
                   FrameInfo("Stats candidates", SRC_POS));

}