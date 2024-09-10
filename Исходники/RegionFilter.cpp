  TyErrorId processWithLock(CAS &tcas, ResultSpecification const &res_spec)
  {
    MEASURE_TIME;
    outInfo("process begins");
    rs::SceneCas cas(tcas);
    rs::Scene scene = cas.getScene();

    cas.get(VIEW_CLOUD, *cloud);
    cas.get(VIEW_COLOR_IMAGE, color);
    cas.get(VIEW_DEPTH_IMAGE, depth);
    cas.get(VIEW_CAMERA_INFO, cameraInfo);

    indices->clear();
    indices->reserve(cloud->points.size());

    camToWorld.setIdentity();
    if(scene.viewPoint.has())
    {
      rs::conversion::from(scene.viewPoint.get(), camToWorld);
    }
    else
    {
      outWarn("No camera to world transformation, no further processing!");
      throw rs::FrameFilterException();
    }
    worldToCam = tf::StampedTransform(camToWorld.inverse(), camToWorld.stamp_, camToWorld.child_frame_id_, camToWorld.frame_id_);
    computeFrustum();

    //default place to look for objects is counter tops except if we got queried for some different place
    //message comes from desigantor and is not the same as the entries from the semantic map so we need
    //to transform them
    rs::Query qs = rs::create<rs::Query>(tcas);
    std::vector<std::string> regionsToLookAt;
    regionsToLookAt.assign(defaultRegions.begin(),defaultRegions.end());
    regions.clear();
    if(cas.getFS("QUERY", qs))
    {
      outWarn("loaction set in query: " << qs.location());
      if(std::find(defaultRegions.begin(), defaultRegions.end(), qs.location()) == std::end(defaultRegions) && qs.location()!="")
      {
        regionsToLookAt.clear();
        regionsToLookAt.push_back(qs.location());
      }
    }

    if(regions.empty())
    {
      std::vector<rs::SemanticMapObject> semanticRegions;
      getSemanticMapEntries(cas, regionsToLookAt, semanticRegions);

      regions.resize(semanticRegions.size());
      for(size_t i = 0; i < semanticRegions.size(); ++i)
      {

        Region &region = regions[i];
        region.width = semanticRegions[i].width();
        region.depth = semanticRegions[i].depth();
        region.height = semanticRegions[i].height();
        region.name = semanticRegions[i].name();
        rs::conversion::from(semanticRegions[i].transform(), region.transform);
      }
    }

    for(size_t i = 0; i < regions.size(); ++i)
    {
      if(frustumCulling(regions[i]) || !frustumCulling_)
      {
        outInfo("region inside frustum: " << regions[i].name);
        filterRegion(regions[i]);
      }
      else
      {
        outInfo("region outside frustum: " << regions[i].name);
      }
    }

    pcl::ExtractIndices<PointT> ei;
    ei.setKeepOrganized(true);
    ei.setIndices(indices);
    ei.filterDirectly(cloud);

    cas.set(VIEW_CLOUD, *cloud);

    if(changeDetection && !indices->empty())
    {
      ++frames;
      if(lastImg.empty())
      {
        lastMask = cv::Mat::ones(color.rows, color.cols, CV_8U);
        lastImg = cv::Mat::zeros(color.rows, color.cols, CV_32FC4);
      }

      uint32_t secondsPassed = camToWorld.stamp_.sec - lastTime.sec;
      bool change = checkChange() || cas.has("QUERY") || secondsPassed > timeout;

      if(!change)
      {
        ++filtered;
      }
      else
      {
        lastTime = camToWorld.stamp_;
      }
      outInfo("filtered frames: " << filtered << " / " << frames << "(" << (filtered / (float)frames) * 100 << "%)");

      if(!change)
      {
        outWarn("no changes in frame detected, no further processing!");
        throw rs::FrameFilterException();
      }
    }

    return UIMA_ERR_NONE;
  }