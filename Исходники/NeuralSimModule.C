void NeuralSimModule<T>::setModel(const std::string& model_name, const Dims& dims, const SimTime& starttime)
{
  //set our border policy based on wether we are using space variant boundaries or not
  BorderPolicy bp = (itsUseSpaceVariantBoundary.getVal()) ? CROSS_HEMI : NONE;
  
  //change any factory parameters
  uint w = dims.w(); uint h = dims.h();
  nsu::setParameter(nsu::SimStructure::Factory::instance(), bp, itsSCtimestep.getVal(), w, h);
  
  //reset the module
  LINFO("model type: %s", model_name.c_str());
  itsStructure.reset(nsu::SimStructure::Factory::instance().createConvert<T*>(model_name));
  itsStructure->setTime(starttime);
  
  //setup plotting range
  nsu::NormalizeType ntype;
  Range<double> itsRange = itsDisplayRange.getVal();
  if ((itsRange.min() < 0) && (itsRange.max() < 0))//if both are less than 0 scale
    {
      ntype = nsu::SCALE;
      itsRange = Range<double>(0.0,0.0);
    }
  else if ((itsRange.min() == 0) && (itsRange.max() == 0))//set to min/max of data
    ntype = nsu::RANGE;
  else //set to auto scale at each time
    ntype = nsu::SET_RANGE;
  
  //set a decode if desired and initialize plotting
  if (itsDecoderType.getVal().compare("None") != 0)
    {
      nsu::NeuralDecoder* nd = nsu::NeuralDecoder::Factory::instance().create(itsDecoderType.getVal());
      itsPlot.reset(new nsu::StructurePlot(*itsStructure, *nd, its2DPlotDepth.getVal(), ntype, 
                                           itsRange.min(), itsRange.max()));
      delete nd;
    }
  else
    itsPlot.reset(new nsu::StructurePlot(*itsStructure, its2DPlotDepth.getVal(), ntype, 
                                         itsRange.min(), itsRange.max()));

  //update our probe position and set sampling rate for display text
  itsPlot->setSamplingRate(itsStructure->getTimeStep()); 
  nsu::Location location(itsProbe.getVal()); 
  itsPlot->setProbe(location);

  //setup image set to hold input
  const uint depth = (itsStructure->numSubs() < 1) ? 2 : itsStructure->numSubs()+1;
  itsInput = ImageSet<double>(depth);
  itsInputGain = std::vector<double>(depth, 1.0);
}