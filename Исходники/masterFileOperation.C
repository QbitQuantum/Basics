Foam::fileName Foam::fileOperations::masterFileOperation::objectPath
(
    const IOobject& io,
    const pathType& searchType,
    const word& instancePath
)
{
    // Replacement for IOobject::objectPath()

    switch (searchType)
    {
        case fileOperation::ABSOLUTE:
        {
            return io.instance()/io.name();
        }
        break;

        case fileOperation::OBJECT:
        {
            return io.path()/io.name();
        }
        break;

        case fileOperation::PROCESSORSOBJECT:
        {
            return processorsPath(io, io.instance())/io.name();
        }
        break;

        case fileOperation::PARENTOBJECT:
        {
            return
                io.rootPath()/io.time().globalCaseName()
               /io.instance()/io.db().dbDir()/io.local()/io.name();
        }
        break;

        case fileOperation::FINDINSTANCE:
        {
            return
                io.rootPath()/io.caseName()
               /instancePath/io.db().dbDir()/io.local()/io.name();
        }
        break;

        case fileOperation::PROCESSORSFINDINSTANCE:
        {
            return processorsPath(io, instancePath)/io.name();
        }
        break;

        case fileOperation::NOTFOUND:
        {
            return fileName::null;
        }
        break;

        default:
        {
            NotImplemented;
            return fileName::null;
        }
    }
}