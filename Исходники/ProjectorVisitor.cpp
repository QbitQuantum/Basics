void ProjectVisitor::apply(osg::Geode& node) 
{
    if (_clearEveryDrawable)
        _projector.clear();

    std::vector<osg::Drawable*> toremove;
    std::vector<osg::ref_ptr<osg::Geometry> > toadd;
    for (int i = 0; i < node.getNumDrawables(); i++) {

        osg::Timer_t t0 = osg::Timer::instance()->tick();
        node.getDrawable(i)->accept(_projector);
        double duration = osg::Timer::instance()->delta_s(t0, osg::Timer::instance()->tick());

        if (_projector.hasGeometry()) {
            toremove.push_back(node.getDrawable(i));
            std::stringstream ss;
            ss << "projected_" << _index << ".osg";
            osg::notify(osg::INFO) <<  "duration " << duration << " " << ss.str() << std::endl;
            if (_writeResultOnDisk)
                _projector.write(ss.str());
            
            if (!_mergeGeometry) {
                osg::ref_ptr<osg::Geometry> result = _projector._result.get();
                result->setUserData(node.getDrawable(i)->getUserData());
                toadd.push_back(result);
                _projector.clear();
            }
        }
        _index++;
        _cummulatedTime += duration;
    }

    if (_mergeGeometry) {
        if (_projector.hasGeometry()) {
            toadd.push_back(_projector._result.get());
        }
    }

    for (int i = 0; i < toremove.size(); i++) // remove only where success to project data
        node.removeDrawable(toremove[i]);

    for (int i = 0; i < toadd.size(); i++) {// remove only where success to project data
        node.addDrawable(toadd[i]);
    }

    if (_projectToXYZ) {
        osg::ref_ptr<LatLongHeight2xyz> visitor = new LatLongHeight2xyz();
        node.accept(*visitor);
    }

    // smooth after project
    if (_smooth) {
        osgUtil::SmoothingVisitor smooth;
        for (int i = 0; i < toadd.size(); i++) {// remove only where success to project data
            smooth.smooth(*toadd[i]);
        }
    }

}