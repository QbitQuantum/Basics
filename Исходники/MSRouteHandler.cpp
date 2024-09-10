void
MSRouteHandler::openRoute(const SUMOSAXAttributes& attrs) {
    // check whether the id is really necessary
    std::string rid;
    if (myCurrentRouteDistribution != 0) {
        myActiveRouteID = myCurrentRouteDistributionID + "#" + toString(myCurrentRouteDistribution->getProbs().size()); // !!! document this
        rid =  "distribution '" + myCurrentRouteDistributionID + "'";
    } else if (myVehicleParameter != 0) {
        // ok, a vehicle is wrapping the route,
        //  we may use this vehicle's id as default
        myActiveRouteID = "!" + myVehicleParameter->id; // !!! document this
        if (attrs.hasAttribute(SUMO_ATTR_ID)) {
            WRITE_WARNING("Ids of internal routes are ignored (vehicle '" + myVehicleParameter->id + "').");
        }
    } else {
        bool ok = true;
        myActiveRouteID = attrs.getStringReporting(SUMO_ATTR_ID, 0, ok, false);
        if (!ok) {
            return;
        }
        rid = "'" + myActiveRouteID + "'";
    }
    if (myVehicleParameter != 0) { // have to do this here for nested route distributions
        rid =  "for vehicle '" + myVehicleParameter->id + "'";
    }
    bool ok = true;
    if (attrs.hasAttribute(SUMO_ATTR_EDGES)) {
        MSEdge::parseEdgesList(attrs.getStringReporting(SUMO_ATTR_EDGES, myActiveRouteID.c_str(), ok), myActiveRoute, rid);
    }
    myActiveRouteRefID = attrs.getOptStringReporting(SUMO_ATTR_REFID, myActiveRouteID.c_str(), ok, "");
    if (attrs.hasAttribute(SUMO_ATTR_REFID__DEPRECATED)) {
        myActiveRouteRefID = attrs.getOptStringReporting(SUMO_ATTR_REFID__DEPRECATED, myActiveRouteID.c_str(), ok, "");
        if (!myHaveWarnedAboutDeprecatedRefID) {
            myHaveWarnedAboutDeprecatedRefID = true;
            WRITE_WARNING("'" + toString(SUMO_ATTR_REFID__DEPRECATED) + "' is deprecated, please use '" + toString(SUMO_ATTR_REFID) + "' instead.");
        }
    }
    if (myActiveRouteRefID != "" && MSRoute::dictionary(myActiveRouteRefID) == 0) {
        WRITE_ERROR("Invalid reference to route '" + myActiveRouteRefID + "' in route " + rid + ".");
    }
    myActiveRouteProbability = attrs.getOptSUMORealReporting(SUMO_ATTR_PROB, myActiveRouteID.c_str(), ok, DEFAULT_VEH_PROB);
    myActiveRouteColor = attrs.hasAttribute(SUMO_ATTR_COLOR) ? RGBColor::parseColorReporting(attrs.getString(SUMO_ATTR_COLOR), attrs.getObjectType(),  myActiveRouteID.c_str(), true, ok) : RGBColor::getDefaultColor();
}