void ProjectGuiSerialization::initialize(const ProjectGui* projectGui) { 
     std::list<boost::shared_ptr<NodeGui> > activeNodes = projectGui->getVisibleNodes();
     _serializedNodes.clear();
     for (std::list<boost::shared_ptr<NodeGui> >::iterator it = activeNodes.begin();it!=activeNodes.end();++it) {
         NodeGuiSerialization state;
         (*it)->serialize(&state);
         _serializedNodes.push_back(state);
         
         if ((*it)->getNode()->pluginID() == "Viewer") {
             ViewerInstance* viewer = dynamic_cast<ViewerInstance*>((*it)->getNode()->getLiveInstance());
             assert(viewer);
             ViewerTab* tab = projectGui->getGui()->getViewerTabForInstance(viewer);
             assert(tab);
             ViewerData viewerData;
             tab->getViewer()->getProjection(&viewerData.zoomLeft, &viewerData.zoomBottom, &viewerData.zoomFactor, &viewerData.zoomPAR);
             viewerData.userRoI = tab->getViewer()->getUserRegionOfInterest();
             viewerData.userRoIenabled = tab->getViewer()->isUserRegionOfInterestEnabled();
             viewerData.isClippedToProject = tab->isClippedToProject();
             viewerData.autoContrastEnabled = tab->isAutoContrastEnabled();
             viewerData.gain = tab->getGain();
             viewerData.colorSpace = tab->getColorSpace();
             viewerData.channels = tab->getChannelsString();
             viewerData.renderScaleActivated = tab->getRenderScaleActivated();
             viewerData.mipMapLevel = tab->getMipMapLevel();
             viewerData.zoomOrPanSinceLastFit = tab->getZoomOrPannedSinceLastFit();
             viewerData.wipeCompositingOp = (int)tab->getCompositingOperator();
             _viewersData.insert(std::make_pair(viewer->getNode()->getName_mt_safe(),viewerData));
         }
     }
     
    std::list<TabWidget*> tabWidgets = projectGui->getGui()->getPanes_mt_safe();
     for (std::list<TabWidget*>::const_iterator it = tabWidgets.begin(); it!= tabWidgets.end(); ++it) {
         QString widgetName = (*it)->objectName_mt_safe();
         if(widgetName.isEmpty()){
             qDebug() << "Warning: attempting to save the layout of an unnamed TabWidget, discarding.";
             continue;
         }
         
         PaneLayout layout;
         layout.parentingCreated = false;
         std::map<TabWidget*,bool> userSplits = (*it)->getUserSplits();
         for (std::map<TabWidget*,bool>::const_iterator split = userSplits.begin(); split!=userSplits.end(); ++split) {
             layout.splits.push_back(split->second);
         }
         layout.floating = (*it)->isFloating();
         if(layout.floating){
             QPoint pos = (*it)->pos_mt_safe();
             layout.posx = pos.x();
             layout.posy = pos.y();
         }else{
             //not releveant since the tab is not floating
             layout.posx = -1;
             layout.posy = -1;
         }
         
         QStringList tabNames = (*it)->getTabNames();
         for (int i = 0; i < tabNames.size(); ++i) {
             if(tabNames[i].isEmpty()){
                 qDebug() << "Warning: attempting to save the position of an unnamed tab, discarding.";
                 continue;
             }
             layout.tabs.push_back(tabNames[i].toStdString());
         }
         _layout.insert(std::make_pair(widgetName.toStdString(),layout));
     }
     
     ///now we do a second pass to insert for each layout what are its children splits
     for (std::map<std::string,PaneLayout>::iterator it = _layout.begin(); it!= _layout.end(); ++it) {
         if(!it->second.parentingCreated){
             createParenting(it);
         }
     }
     
     ///save application's splitters states
    std::list<Splitter*> splitters = projectGui->getGui()->getSplitters();
     for (std::list<Splitter*>::const_iterator it = splitters.begin(); it!= splitters.end(); ++it) {
         QByteArray ba = (*it)->saveState();
         ba = ba.toBase64();
         QString str(ba);
         _splittersStates.insert(std::make_pair((*it)->objectName_mt_safe().toStdString(),str.toStdString()));

     }
     
     _arePreviewTurnedOffGlobally = projectGui->getGui()->getNodeGraph()->areAllPreviewTurnedOff();
     
     
     ///save histograms
    std::list<Histogram*> histograms = projectGui->getGui()->getHistograms_mt_safe();
     for (std::list<Histogram*>::const_iterator it = histograms.begin(); it != histograms.end(); ++it) {
         _histograms.push_back((*it)->objectName().toStdString());
     }
    
    std::list<NodeBackDrop*> backdrops = projectGui->getGui()->getNodeGraph()->getActiveBackDrops();
    for (std::list<NodeBackDrop*>::iterator it = backdrops.begin(); it!=backdrops.end();++it) {
        NodeBackDropSerialization s;
        s.initialize(*it);
        _backdrops.push_back(s);
    }
     
}