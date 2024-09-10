/*
 Executes the underlying algorithm to create the MVP model.
 @param factory : visualisation factory to use.
 @param loadingProgressUpdate : Handler for GUI updates while algorithm
 progresses.
 @param drawingProgressUpdate : Handler for GUI updates while
 vtkDataSetFactory::create occurs.
 */
vtkSmartPointer<vtkDataSet>
EventNexusLoadingPresenter::execute(vtkDataSetFactory *factory,
                                    ProgressAction &loadingProgressUpdate,
                                    ProgressAction &drawingProgressUpdate) {
  using namespace Mantid::API;
  using namespace Mantid::Geometry;

  this->m_view->getLoadInMemory(); // TODO, nexus reader algorithm currently has
                                   // no use of this.

  if (this->shouldLoad()) {
    Poco::NObserver<ProgressAction,
                    Mantid::API::Algorithm::ProgressNotification>
        observer(loadingProgressUpdate, &ProgressAction::handler);
    AnalysisDataService::Instance().remove("MD_EVENT_WS_ID");

    Algorithm_sptr loadAlg =
        AlgorithmManager::Instance().createUnmanaged("LoadEventNexus");
    loadAlg->initialize();
    loadAlg->setChild(true);
    loadAlg->setPropertyValue("Filename", this->m_filename);
    loadAlg->setPropertyValue("OutputWorkspace", "temp_ws");
    loadAlg->addObserver(observer);
    loadAlg->executeAsChildAlg();
    loadAlg->removeObserver(observer);

    Workspace_sptr temp = loadAlg->getProperty("OutputWorkspace");
    IEventWorkspace_sptr tempWS =
        boost::dynamic_pointer_cast<IEventWorkspace>(temp);

    Algorithm_sptr convertAlg = AlgorithmManager::Instance().createUnmanaged(
        "ConvertToDiffractionMDWorkspace", 1);
    convertAlg->initialize();
    convertAlg->setChild(true);
    convertAlg->setProperty("InputWorkspace", tempWS);
    convertAlg->setProperty<bool>("ClearInputWorkspace", false);
    convertAlg->setProperty<bool>("LorentzCorrection", true);
    convertAlg->setPropertyValue("OutputWorkspace", "converted_ws");
    convertAlg->addObserver(observer);
    convertAlg->executeAsChildAlg();
    convertAlg->removeObserver(observer);

    IMDEventWorkspace_sptr outWS = convertAlg->getProperty("OutputWorkspace");
    AnalysisDataService::Instance().addOrReplace("MD_EVENT_WS_ID", outWS);
  }

  Workspace_sptr result =
      AnalysisDataService::Instance().retrieve("MD_EVENT_WS_ID");
  Mantid::API::IMDEventWorkspace_sptr eventWs =
      boost::dynamic_pointer_cast<Mantid::API::IMDEventWorkspace>(result);
  m_wsTypeName = eventWs->id();

  factory->setRecursionDepth(this->m_view->getRecursionDepth());
  auto visualDataSet = factory->oneStepCreate(
      eventWs, drawingProgressUpdate); // HACK: progressUpdate should be
                                       // argument for drawing!

  this->extractMetadata(*eventWs);
  this->appendMetadata(visualDataSet, eventWs->getName());

  return visualDataSet;
}