    /*
    Executes the underlying algorithm to create the MVP model.
    @param factory : visualisation factory to use.
    @param loadingProgressUpdate : Handler for GUI updates while algorithm progresses.
    @param drawingProgressUpdate : Handler for GUI updates while vtkDataSetFactory::create occurs.
    */
    vtkDataSet* MDEWEventNexusLoadingPresenter::execute(vtkDataSetFactory* factory, ProgressAction& loadingProgressUpdate, ProgressAction& drawingProgressUpdate)
    {
      using namespace Mantid::API;
      using namespace Mantid::Geometry;

      if(this->shouldLoad())
      {
        Poco::NObserver<ProgressAction, Mantid::API::Algorithm::ProgressNotification> observer(loadingProgressUpdate, &ProgressAction::handler);
        AnalysisDataService::Instance().remove("MD_EVENT_WS_ID");

        IAlgorithm_sptr alg = AlgorithmManager::Instance().create("LoadMD");
        alg->initialize();
        alg->setPropertyValue("Filename", this->m_filename);
        alg->setPropertyValue("OutputWorkspace", "MD_EVENT_WS_ID");
        alg->setProperty("FileBackEnd", !this->m_view->getLoadInMemory()); //Load from file by default.
        alg->addObserver(observer);
        alg->execute();
        alg->removeObserver(observer);
      }

      Workspace_sptr result=AnalysisDataService::Instance().retrieve("MD_EVENT_WS_ID");
      Mantid::API::IMDEventWorkspace_sptr eventWs = boost::dynamic_pointer_cast<Mantid::API::IMDEventWorkspace>(result);

      factory->setRecursionDepth(this->m_view->getRecursionDepth());
      //Create visualisation in one-shot.
      vtkDataSet* visualDataSet = factory->oneStepCreate(eventWs, drawingProgressUpdate);
      
      /*extractMetaData needs to be re-run here because the first execution of this from ::executeLoadMetadata will not have ensured that all dimensions
        have proper range extents set.
      */
      this->extractMetadata(eventWs);

      this->appendMetadata(visualDataSet, eventWs->getName());
      return visualDataSet;
    }