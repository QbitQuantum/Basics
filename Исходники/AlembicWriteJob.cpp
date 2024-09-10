MStatus AlembicExportCommand::doIt(const MArgList &args)
{
  ESS_PROFILE_SCOPE("AlembicExportCommand::doIt");

  MStatus status = MS::kFailure;

  MTime currentAnimStartTime = MAnimControl::animationStartTime(),
        currentAnimEndTime = MAnimControl::animationEndTime(),
        oldCurTime = MAnimControl::currentTime(),
        curMinTime = MAnimControl::minTime(),
        curMaxTime = MAnimControl::maxTime();
  MArgParser argData(syntax(), args, &status);

  if (argData.isFlagSet("help")) {
    // TODO: implement help for this command
    // MGlobal::displayInfo(util::getHelpText());
    return MS::kSuccess;
  }

  unsigned int jobCount = argData.numberOfFlagUses("jobArg");
  MStringArray jobStrings;
  if (jobCount == 0) {
    // TODO: display dialog
    MGlobal::displayError("[ExocortexAlembic] No jobs specified.");
    MPxCommand::setResult(
        "Error caught in AlembicExportCommand::doIt: no job specified");
    return status;
  }
  else {
    // get all of the jobstrings
    for (unsigned int i = 0; i < jobCount; i++) {
      MArgList jobArgList;
      argData.getFlagArgumentList("jobArg", i, jobArgList);
      jobStrings.append(jobArgList.asString(0));
    }
  }

  // create a vector to store the jobs
  std::vector<AlembicWriteJob *> jobPtrs;
  double minFrame = 1000000.0;
  double maxFrame = -1000000.0;
  double maxSteps = 1;
  double maxSubsteps = 1;

  // init the curve accumulators
  AlembicCurveAccumulator::Initialize();

  try {
    // for each job, check the arguments
    bool failure = false;
    for (unsigned int i = 0; i < jobStrings.length(); ++i) {
      double frameIn = 1.0;
      double frameOut = 1.0;
      double frameSteps = 1.0;
      double frameSubSteps = 1.0;
      MString filename;
      bool purepointcache = false;
      bool normals = true;
      bool uvs = true;
      bool facesets = true;
      bool bindpose = true;
      bool dynamictopology = false;
      bool globalspace = false;
      bool withouthierarchy = false;
      bool transformcache = false;
      bool useInitShadGrp = false;
      bool useOgawa = false;  // Later, will need to be changed!

      MStringArray objectStrings;
      std::vector<std::string> prefixFilters;
      std::set<std::string> attributes;
      std::vector<std::string> userPrefixFilters;
      std::set<std::string> userAttributes;
      MObjectArray objects;
      std::string search_str, replace_str;

      // process all tokens of the job
      MStringArray tokens;
      jobStrings[i].split(';', tokens);
      for (unsigned int j = 0; j < tokens.length(); j++) {
        MStringArray valuePair;
        tokens[j].split('=', valuePair);
        if (valuePair.length() != 2) {
          MGlobal::displayWarning(
              "[ExocortexAlembic] Skipping invalid token: " + tokens[j]);
          continue;
        }

        const MString &lowerValue = valuePair[0].toLowerCase();
        if (lowerValue == "in") {
          frameIn = valuePair[1].asDouble();
        }
        else if (lowerValue == "out") {
          frameOut = valuePair[1].asDouble();
        }
        else if (lowerValue == "step") {
          frameSteps = valuePair[1].asDouble();
        }
        else if (lowerValue == "substep") {
          frameSubSteps = valuePair[1].asDouble();
        }
        else if (lowerValue == "normals") {
          normals = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "uvs") {
          uvs = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "facesets") {
          facesets = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "bindpose") {
          bindpose = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "purepointcache") {
          purepointcache = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "dynamictopology") {
          dynamictopology = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "globalspace") {
          globalspace = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "withouthierarchy") {
          withouthierarchy = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "transformcache") {
          transformcache = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "filename") {
          filename = valuePair[1];
        }
        else if (lowerValue == "objects") {
          // try to find each object
          valuePair[1].split(',', objectStrings);
        }
        else if (lowerValue == "useinitshadgrp") {
          useInitShadGrp = valuePair[1].asInt() != 0;
        }

        // search/replace
        else if (lowerValue == "search") {
          search_str = valuePair[1].asChar();
        }
        else if (lowerValue == "replace") {
          replace_str = valuePair[1].asChar();
        }
        else if (lowerValue == "ogawa") {
          useOgawa = valuePair[1].asInt() != 0;
        }
        else if (lowerValue == "attrprefixes") {
          splitListArg(valuePair[1], prefixFilters);
        }
        else if (lowerValue == "attrs") {
          splitListArg(valuePair[1], attributes);
        }
        else if (lowerValue == "userattrprefixes") {
          splitListArg(valuePair[1], userPrefixFilters);
        }
        else if (lowerValue == "userattrs") {
          splitListArg(valuePair[1], userAttributes);
        }
        else {
          MGlobal::displayWarning(
              "[ExocortexAlembic] Skipping invalid token: " + tokens[j]);
          continue;
        }
      }

      // now check the object strings
      for (unsigned int k = 0; k < objectStrings.length(); k++) {
        MSelectionList sl;
        MString objectString = objectStrings[k];
        sl.add(objectString);
        MDagPath dag;
        for (unsigned int l = 0; l < sl.length(); l++) {
          sl.getDagPath(l, dag);
          MObject objRef = dag.node();
          if (objRef.isNull()) {
            MGlobal::displayWarning("[ExocortexAlembic] Skipping object '" +
                                    objectStrings[k] + "', not found.");
            break;
          }

          // get all parents
          MObjectArray parents;

          // check if this is a camera
          bool isCamera = false;
          for (unsigned int m = 0; m < dag.childCount(); ++m) {
            MFnDagNode child(dag.child(m));
            MFn::Type ctype = child.object().apiType();
            if (ctype == MFn::kCamera) {
              isCamera = true;
              break;
            }
          }

          if (dag.node().apiType() == MFn::kTransform && !isCamera &&
              !globalspace && !withouthierarchy) {
            MDagPath ppath = dag;
            while (!ppath.node().isNull() && ppath.length() > 0 &&
                   ppath.isValid()) {
              parents.append(ppath.node());
              if (ppath.pop() != MStatus::kSuccess) {
                break;
              }
            }
          }
          else {
            parents.append(dag.node());
          }

          // push all parents in
          while (parents.length() > 0) {
            bool found = false;
            for (unsigned int m = 0; m < objects.length(); m++) {
              if (objects[m] == parents[parents.length() - 1]) {
                found = true;
                break;
              }
            }
            if (!found) {
              objects.append(parents[parents.length() - 1]);
            }
            parents.remove(parents.length() - 1);
          }

          // check all of the shapes below
          if (!transformcache) {
            sl.getDagPath(l, dag);
            for (unsigned int m = 0; m < dag.childCount(); m++) {
              MFnDagNode child(dag.child(m));
              if (child.isIntermediateObject()) {
                continue;
              }
              objects.append(child.object());
            }
          }
        }
      }

      // check if we have incompatible subframes
      if (maxSubsteps > 1.0 && frameSubSteps > 1.0) {
        const double part = (frameSubSteps > maxSubsteps)
                                ? (frameSubSteps / maxSubsteps)
                                : (maxSubsteps / frameSubSteps);
        if (abs(part - floor(part)) > 0.001) {
          MString frameSubStepsStr, maxSubstepsStr;
          frameSubStepsStr.set(frameSubSteps);
          maxSubstepsStr.set(maxSubsteps);
          MGlobal::displayError(
              "[ExocortexAlembic] You cannot combine substeps " +
              frameSubStepsStr + " and " + maxSubstepsStr +
              " in one export. Aborting.");
          return MStatus::kInvalidParameter;
        }
      }

      // remember the min and max values for the frames
      if (frameIn < minFrame) {
        minFrame = frameIn;
      }
      if (frameOut > maxFrame) {
        maxFrame = frameOut;
      }
      if (frameSteps > maxSteps) {
        maxSteps = frameSteps;
      }
      if (frameSteps > 1.0) {
        frameSubSteps = 1.0;
      }
      if (frameSubSteps > maxSubsteps) {
        maxSubsteps = frameSubSteps;
      }

      // check if we have a filename
      if (filename.length() == 0) {
        MGlobal::displayError("[ExocortexAlembic] No filename specified.");
        for (size_t k = 0; k < jobPtrs.size(); k++) {
          delete (jobPtrs[k]);
        }
        MPxCommand::setResult(
            "Error caught in AlembicExportCommand::doIt: no filename "
            "specified");
        return MStatus::kFailure;
      }

      // construct the frames
      MDoubleArray frames;
      {
        const double frameIncr = frameSteps / frameSubSteps;
        for (double frame = frameIn; frame <= frameOut; frame += frameIncr) {
          frames.append(frame);
        }
      }

      AlembicWriteJob *job =
          new AlembicWriteJob(filename, objects, frames, useOgawa,
              prefixFilters, attributes, userPrefixFilters, userAttributes);
      job->SetOption("exportNormals", normals ? "1" : "0");
      job->SetOption("exportUVs", uvs ? "1" : "0");
      job->SetOption("exportFaceSets", facesets ? "1" : "0");
      job->SetOption("exportInitShadGrp", useInitShadGrp ? "1" : "0");
      job->SetOption("exportBindPose", bindpose ? "1" : "0");
      job->SetOption("exportPurePointCache", purepointcache ? "1" : "0");
      job->SetOption("exportDynamicTopology", dynamictopology ? "1" : "0");
      job->SetOption("indexedNormals", "1");
      job->SetOption("indexedUVs", "1");
      job->SetOption("exportInGlobalSpace", globalspace ? "1" : "0");
      job->SetOption("flattenHierarchy", withouthierarchy ? "1" : "0");
      job->SetOption("transformCache", transformcache ? "1" : "0");

      // check if the search/replace strings are valid!
      if (search_str.length() ? !replace_str.length()
                              : replace_str.length())  // either search or
                                                       // replace string is
                                                       // missing or empty!
      {
        ESS_LOG_WARNING(
            "Missing search or replace parameter. No strings will be "
            "replaced.");
        job->replacer = SearchReplace::createReplacer();
      }
      else {
        job->replacer = SearchReplace::createReplacer(search_str, replace_str);
      }

      // check if the job is satifsied
      if (job->PreProcess() != MStatus::kSuccess) {
        MGlobal::displayError("[ExocortexAlembic] Job skipped. Not satisfied.");
        delete (job);
        failure = true;
        break;
      }

      // push the job to our registry
      MGlobal::displayInfo("[ExocortexAlembic] Using WriteJob:" +
                           jobStrings[i]);
      jobPtrs.push_back(job);
    }

    if (failure) {
      for (size_t k = 0; k < jobPtrs.size(); k++) {
        delete (jobPtrs[k]);
      }
      return MS::kFailure;
    }

    // compute the job count
    unsigned int jobFrameCount = 0;
    for (size_t i = 0; i < jobPtrs.size(); i++)
      jobFrameCount += (unsigned int)jobPtrs[i]->GetNbObjects() *
                       (unsigned int)jobPtrs[i]->GetFrames().size();

    // now, let's run through all frames, and process the jobs
    const double frameRate = MTime(1.0, MTime::kSeconds).as(MTime::uiUnit());
    const double incrSteps = maxSteps / maxSubsteps;
    double nextFrame = minFrame + incrSteps;

    for (double frame = minFrame; frame <= maxFrame;
         frame += incrSteps, nextFrame += incrSteps) {
      MAnimControl::setCurrentTime(MTime(frame / frameRate, MTime::kSeconds));
      MAnimControl::setAnimationEndTime(
          MTime(nextFrame / frameRate, MTime::kSeconds));
      MAnimControl::playForward();  // this way, it forces Maya to play exactly
      // one frame! and particles are updated!

      AlembicCurveAccumulator::StartRecordingFrame();
      for (size_t i = 0; i < jobPtrs.size(); i++) {
        MStatus status = jobPtrs[i]->Process(frame);
        if (status != MStatus::kSuccess) {
          MGlobal::displayError("[ExocortexAlembic] Job aborted :" +
                                jobPtrs[i]->GetFileName());
          for (size_t k = 0; k < jobPtrs.size(); k++) {
            delete (jobPtrs[k]);
          }
          restoreOldTime(currentAnimStartTime, currentAnimEndTime, oldCurTime,
                         curMinTime, curMaxTime);
          return status;
        }
      }
      AlembicCurveAccumulator::StopRecordingFrame();
    }
  }
  catch (...) {
    MGlobal::displayError(
        "[ExocortexAlembic] Jobs aborted, force closing all archives!");
    for (std::vector<AlembicWriteJob *>::iterator beg = jobPtrs.begin();
         beg != jobPtrs.end(); ++beg) {
      (*beg)->forceCloseArchive();
    }
    restoreOldTime(currentAnimStartTime, currentAnimEndTime, oldCurTime,
                   curMinTime, curMaxTime);
    MPxCommand::setResult("Error caught in AlembicExportCommand::doIt");
    status = MS::kFailure;
  }
  MAnimControl::stop();
  AlembicCurveAccumulator::Destroy();

  // restore the animation start/end time and the current time!
  restoreOldTime(currentAnimStartTime, currentAnimEndTime, oldCurTime,
                 curMinTime, curMaxTime);

  // delete all jobs
  for (size_t k = 0; k < jobPtrs.size(); k++) {
    delete (jobPtrs[k]);
  }

  // remove all known archives
  deleteAllArchives();
  return status;
}