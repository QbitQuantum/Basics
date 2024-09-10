SUMOVehicleClass
SUMOVehicleParserHelper::parseVehicleClass(const SUMOSAXAttributes& attrs,
        const std::string& id) {
    SUMOVehicleClass vclass = SVC_IGNORING;
    try {
        bool ok = true;
        std::string vclassS = attrs.getOpt<std::string>(SUMO_ATTR_VCLASS, id.c_str(), ok, "");
        if (vclassS == "") {
            return vclass;
        }
        const SUMOVehicleClass result = getVehicleClassID(vclassS);
        const std::string& realName = SumoVehicleClassStrings.getString(result);
        if (realName != vclassS) {
            WRITE_WARNING("The vehicle class '" + vclassS + "' for " + attrs.getObjectType() + " '" + id + "' is deprecated, use '" + realName + "' instead.");
        }
        return result;
    } catch (...) {
        WRITE_ERROR("The class for " + attrs.getObjectType() + " '" + id + "' is not known.");
    }
    return vclass;
}