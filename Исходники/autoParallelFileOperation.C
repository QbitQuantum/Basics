Foam::fileNameList
Foam::fileOperations::autoParallelFileOperation::readObjects
(
    const objectRegistry& db,
    const fileName& instance,
    const fileName& local,
    word& newInstance
) const
{
    fileNameList objects;

    if (!Pstream::parRun())
    {
        objects = uncollatedFileOperation::readObjects
        (
            db,
            instance,
            local,
            newInstance
        );
    }
    else
    {
        // tbd: lagrangian. dbDir="", local = "lagrangian/KinematicCloud"
        fileName path
        (
            filePath
            (
                db.rootPath()
               /db.time().globalCaseName()
               /instance
               /db.dbDir()
               /local
            )
        );

        if (Foam::isDir(path))
        {
            newInstance = instance;
            objects = Foam::readDir(path, fileType::file);

            if (debug)
            {
                Pout<< indent
                    << "autoParallelFileOperation::readObjects :"
                    << " Returning parent directory searching:"
                    << endl << indent
                    << "    path     :" << path << endl << indent
                    << "    objects  :" << objects << endl << endl;
            }

            return objects;
        }
        else
        {
            objects = uncollatedFileOperation::readObjects
            (
                db,
                instance,
                local,
                newInstance
            );
        }
    }

    if (debug)
    {
        Pout<< indent
            << "autoParallelFileOperation::readObjects :"
            << " Returning from directory searching:" << endl << indent
            << "    path     :" << db.path(instance, db.dbDir()/local)
            << endl << indent
            << "    objects  :" << objects << endl << indent
            << "    newInst  :" << newInstance << endl << endl;
    }
    return objects;
}