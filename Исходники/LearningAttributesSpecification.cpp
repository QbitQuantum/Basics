  std::string DEGU_CORNER::getValue(SpMObject mobile, Datapool& datapool) {
      if(checked) {
         checked = true;
         valid = true;
         //First check zones
         std::vector< QSharedPointer<world::ZoneH> > &zones = datapool.sceneModel->ZonesH;
         if (zones.empty())
             valid = false;
         else {
            int num = 0;
            std::vector< QSharedPointer<world::ZoneH> >::iterator zone_it, zone_end = zones.end();
            for(zone_it = zones.begin(); zone_it != zone_end; zone_it++ ) {
                if(values.count((*zone_it)->name.toStdString()) == 1) {
                    num++;
                    DEGU_CORNER::zones[(*zone_it)->name.toStdString()] = (*zone_it);
                }
            }
            if(num != values.size() - 1)
                valid = false;
         }
      }

      SpReliabilitySingleModelInterface m = mobile->getSubModel("BaseModel");
      if(m.isNull())
          return "NONE";

      if(valid) {
          double dist, X, Y, min_dist = DBL_MAX;
          std::string nearest;
          if(datapool.sceneModel->hmatrix_filled) {
            datapool.sceneModel->imgToHomographyCoords(datapool.sceneModel->h_matrix,
                                                       nearbyint(m->dynamics.dynamics["X"].att.value),
                                                       nearbyint(m->dynamics.dynamics["Y"].att.value),
                                                       &X, &Y);
            QSharedPointer<world::ZoneH> z;
            std::map< std::string, QSharedPointer<world::ZoneH> >::iterator it, it_end = zones.end();
            for(it = zones.begin();it != it_end; it++) {
                z = (*it).second;
                if(z->pointInZone(X,Y)) {
                    dist = z->distanceToCenter(X,Y);
                    if(dist < min_dist) {
                        min_dist = dist;
                        nearest = (*it).first;
                    }
                }
            }
            if(min_dist < DBL_MAX)
                return nearest;
         }
      }
      return "NONE";
  }