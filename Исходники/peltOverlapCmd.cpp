MStatus peltOverlap::parseArgs( const MArgList& args )
{
    MStatus		status = MS::kSuccess;
    MArgDatabase	argData(syntax(), args);

    if (argData.isFlagSet(kExitFlag)) {
        status = argData.getFlagArgument(kExitFlag, 0, fNthPairs);
        if (status != MS::kSuccess) {
            MGlobal::displayError("-ea/exitAfterNthPairs is missing an int argument");
            return status;
        }
    }

    status = argData.getObjects(fShadingGroups);
    if (status != MS::kSuccess || fShadingGroups.length() < 1) {
        MGlobal::displayError("Missing shading group(s) input");
        status = MS::kFailure;
    }

    return status;
}