MStatus uninitializePlugin( MObject obj)
{
    MStatus status;
    MFnPlugin plugin( obj );

    status = plugin.deregisterCommand("exportF3d");
    if (!status)
    {
        status.perror("deregisterCommand");
        return status;
    }

    return status;
    
}