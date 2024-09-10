void PlotController::handleData(QString qid) {
    RtDataID id;
    id.setFromString(qid.toStdString());

    if (id.getDataName() == NAME_DESIGN) {
        baseline_box->topLeft->setCoords(0, 10);
        baseline_box->bottomRight->setCoords(getNumDataPointsForErrEst(), -10);

        RtDesignMatrix *design =
            static_cast<RtDesignMatrix*>(getDataStore().getData(id));
        updateTRIndicators();
        plotDesign(design);

        roi_plot->xAxis->setRange(0, design->getNumRows());
        roi_plot->replot();
        motion_plot->xAxis->setRange(0, design->getNumRows());
        motion_plot->replot();
    }
    else if (id.getModuleID() == ID_ROICOMBINE) {
        map<string, int>::const_iterator it = roi_graphs.find(id.getRoiID());
        if (it == roi_graphs.end()) {
            it = roi_graphs.insert(
                     pair<string, int>(id.getRoiID(), roi_plot->graphCount())).first;
            roi_plot->addGraph();
            roi_plot->graph(it->second)->setPen(QPen(roi_colormap.getColorForName(
                                                    id.getRoiID())));
            roi_plot->graph(it->second)->setName(QString(id.getRoiID().c_str()));
            roi_plot->legend->setVisible(true);
        }

        RtActivation *val = static_cast<RtActivation*>(getDataStore().getData(id));
        roi_plot->graph(roi_graphs[id.getRoiID()])->addData(id.getTimePoint(),
                val->getPixel(0));
        roi_plot->replot();
    }
    else if (id.getModuleID() == ID_MOTION) {
        plotMotion(static_cast<RtMotion*>(getDataStore().getData(id)));
    }

    if (id.getTimePoint() != DATAID_NUM_UNSET_VALUE &&
            id.getTimePoint() > current_tr) {
        current_tr = id.getTimePoint();
        updateTRIndicators();
    }
}