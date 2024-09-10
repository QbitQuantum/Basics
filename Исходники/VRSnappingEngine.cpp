void VRSnappingEngine::update() {
    for (auto dev : VRSetupManager::getCurrent()->getDevices()) { // get dragged objects
        VRTransformPtr obj = dev.second->getDraggedObject();
        VRTransformPtr gobj = dev.second->getDraggedGhost();
        if (obj == 0 || gobj == 0) continue;
        if (objects.count(obj) == 0) continue;

        Matrix m = gobj->getWorldMatrix();
        Vec3f p = Vec3f(m[3]);

        bool lastEvent = event->snap;
        event->snap = 0;

        for (auto ri : rules) {
            Rule* r = ri.second;
            if (r->csys == obj) continue;

            if (anchors.count(obj)) {
                for (auto a : anchors[obj]) {
                    Matrix maL = a->getMatrix();
                    Matrix maW = m; maW.mult(maL);
                    Vec3f pa = Vec3f(maW[3]);
                    Vec3f paL = r->local( Vec3f(maW[3]) );
                    Vec3f psnap = r->getSnapPoint(pa);
                    float D = (psnap-paL).length(); // check distance
                    //cout << "dist " << D << " " << pa[1] << " " << paL[1] << " " << psnap[1] << endl;
                    if (!r->inRange(D)) continue;

                    r->snap(m);
                    maL.invert();
                    m.mult(maL);
                    event->set(obj, r->csys, m, dev.second, 1);
                    break;
                }
            } else {
                Vec3f p2 = r->getSnapPoint(p);
                float D = (p2-p).length(); // check distance
                if (!r->inRange(D)) continue;
                r->snap(m);
                event->set(obj, r->csys, m, dev.second, 1);
            }
        }

        obj->setWorldMatrix(m);
        if (lastEvent != event->snap) {
            if (event->snap) snapSignal->trigger<EventSnap>(event);
            else if (obj == event->o1) snapSignal->trigger<EventSnap>(event);
        }
    }

    // update geo
    if (!hintGeo->isVisible()) return;
}