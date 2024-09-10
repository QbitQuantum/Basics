void IsisMain() {
  // We will be processing by line
  ProcessByBrick p;
  UserInterface &ui = Application::GetUserInterface();

  // Use the def file for filter constants
  Pvl uvvisDef("$clementine1/calibration/uvvis/uvvis.def");

  // Setup the input and output cubes
  Cube *icube = p.SetInputCube("FROM");

  Cube *dccube;
  if(ui.WasEntered("DCFILE")) {
    dccube = p.SetInputCube("DCFILE");
  }
  else {
    QString dcfileloc = "$clementine1/calibration/uvvis/";
    dcfileloc += "dark_5_15_96.cub";
    CubeAttributeInput cubeAtt;
    dccube = p.SetInputCube(dcfileloc, cubeAtt);
  }

  QString filter = (QString)(icube->group("BandBin"))["FilterName"];
  filter = filter.toLower();

  Cube *ffcube;
  if(ui.WasEntered("FFFILE")) {
    ffcube = p.SetInputCube("FFFILE");
  }
  else {
    // compute default fffile
    double compressRatio = (icube->group("Instrument"))["EncodingCompressionRatio"];

    // check to see if cube is compressed or uncompressed
    if(compressRatio == 1.0) {
      QString fffileLoc = "$clementine1/calibration/uvvis/";
      fffileLoc += "lu" + filter + "_uncomp_flat_long.cub";
      CubeAttributeInput cubeAtt;
      ffcube = p.SetInputCube(fffileLoc, cubeAtt);
    }
    else {
      QString fffileLoc = "$clementine1/calibration/uvvis/";
      fffileLoc += "lu" + filter + "_comp_flat_long.cub";
      CubeAttributeInput cubeAtt;
      ffcube = p.SetInputCube(fffileLoc, cubeAtt);
    }
  }

  Cube *ocube = p.SetOutputCube("TO");

  avgFF = uvvisDef.findGroup("Filter" + filter.toUpper())["AVGFF"];
  cr = uvvisDef.findGroup("Filter" + filter.toUpper())["CO"];
  gain = uvvisDef.findGroup(QString("GainModeID") + QString(icube->group("Instrument")["GainModeID"][0]))["GAIN"];

  useDcconst = ui.WasEntered("DCCONST");
  if(useDcconst) {
    dcconst = ui.GetDouble("DCCONST");
  }
  else {
    dcconst = 0.0;
  }

  conv = ui.GetBoolean("CONV");
  exposureDuration = icube->group("Instrument")["ExposureDuration"];
  offsetModeID = icube->group("Instrument")["OffsetModeID"];

  if(((QString)icube->group("Instrument")["FocalPlaneTemperature"]).compare("UNK") == 0) {
    //if FocalPlaneTemp is unknown set it to zero
    focalPlaneTemp = 0.0;
  }
  else {
    focalPlaneTemp = icube->group("Instrument")["FocalPlaneTemperature"];
  }

  Camera *cam = icube->camera();
  bool camSuccess = cam->SetImage(icube->sampleCount() / 2, icube->lineCount() / 2);

  if(!camSuccess) {
    throw IException(IException::Unknown, "Unable to calculate the Solar Distance for this cube.", _FILEINFO_);
  }

  dist = cam->SolarDistance();

  // If temp. correction set to true, or focal plane temp is zero then use temperature correction
  if(ui.GetBoolean("TCOR") || abs(focalPlaneTemp) <= DBL_EPSILON) {
    // Temperature correction requires the use of the mission phase
    //   (PRELAUNCH, EARTH, LUNAR) and the product ID.
    QString productID = (QString)(icube->group("Archive")["ProductID"]);
    QChar missionPhase = ((QString)((icube->group("Archive"))["MissionPhase"])).at(0);
    QString n1subQString(productID.mid(productID.indexOf('.') + 1, productID.length() - 1));
    QString n2subQString(productID.mid(4, productID.indexOf('.') - 5));
    int n1 = toInt(n1subQString);
    int n2 = toInt(n2subQString);
    int phase = 0;

    if(missionPhase == 'L') {
      phase = 0;
    }
    else if(missionPhase == 'E') {
      phase = 1;
    }
    else if(missionPhase == 'P') {
      phase = 2;
    }
    else {
      throw IException(IException::Unknown, "Invalid Mission Phase", _FILEINFO_);
    }

    // This formula makes the primary search critera the original product ID's extension,
    //   the secondary search criteria the mission phase and finally the numerical part of the
    //   original product ID.
    int imageID = (100000 * n1) + (10000 * phase) + n2;
    FixTemp(imageID);
  }

  if(focalPlaneTemp <= 0.0) {
    focalPlaneTemp = 272.5;
  }

  // Start the processing
  p.SetBrickSize(icube->sampleCount(), icube->lineCount(), 1);
  p.StartProcess(UvVisCal);

  // Add the radiometry group
  PvlGroup calgrp("Radiometry");
  calgrp += PvlKeyword("FlatFieldFile", ffcube->fileName());

  if(ui.GetString("DARKCURRENT").compare("DCFILE") == 0) {
    calgrp += PvlKeyword("DarkCurrentFile", dccube->fileName());
  }
  else {
    calgrp += PvlKeyword("DarkCurrentConstant", toString(dcconst));
  }

  calgrp += PvlKeyword("CorrectedFocalPlaneTemp", toString(focalPlaneTemp));
  calgrp += PvlKeyword("C1", toString(avgFF));
  calgrp += PvlKeyword("C2", toString(C2));
  calgrp += PvlKeyword("C3", toString(C3));
  calgrp += PvlKeyword("C4", toString(C4));
  calgrp += PvlKeyword("C5", toString(C5));
  calgrp += PvlKeyword("CR", toString(cr));
  calgrp += PvlKeyword("FrameTransferTimePerRow", toString(cr));
  calgrp += PvlKeyword("Gain", toString(gain));
  calgrp += PvlKeyword("CorrectedExposureDuration", toString(correctedExposureDuration));
  calgrp += PvlKeyword("ConvertToRadiance", toString(conv));

  calgrp += PvlKeyword("ACO", toString(ACO));
  calgrp += PvlKeyword("BCO", toString(BCO));
  calgrp += PvlKeyword("CCO", toString(CCO));
  calgrp += PvlKeyword("DCO", toString(DCO));

  ocube->putGroup(calgrp);
  p.EndProcess();
}