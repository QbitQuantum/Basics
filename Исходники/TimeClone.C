label TimeClone::copyObjects(const objectRegistry &src,objectRegistry &dst)
{
    Dbug << "Copying stuff from " << src.name() << " to " << dst.name() << endl;
    Dbug << "t=" << src.time().timeName() << endl;
    Dbug << "Dst AUTO_WRITE: " << (dst.writeOpt()==IOobject::AUTO_WRITE) << endl;

    label cnt=0;

    forAllConstIter(objectRegistry,src,it) {
	const word &name=it.key();
        const regIOobject &obj=*(*it);

        Dbug << name << " is class " << obj.headerClassName() << endl;

        if(isA<objectRegistry>(obj)) {
            Dbug << name << " is objectRegistry. Creating new and cloning" << endl;
            const objectRegistry &orig=dynamicCast<const objectRegistry>(obj);
            if(&src==&orig) {
                Dbug << name << "==" << src.name() << " -> Skipping" << endl;
            } else {
                word dbName=orig.name();
                if(dbName==polyMesh::defaultRegion) {
                    dbName="";
                }
                autoPtr<objectRegistry> newSubp(
                    new objectRegistry(
                        IOobject(
                            dbName,
                            src.time().timeName(),
                            src.local(),
                            dst
                        )
                    )
                );
                objectRegistry &newSub=newSubp();
                Dbug << "AUTO_WRITE: " << (newSub.writeOpt()==IOobject::AUTO_WRITE) << endl;
                Dbug << "old path: " << obj.objectPath() << endl;
                Dbug << "new Path: " << newSub.objectPath() << endl;
                Dbug << "Created registry owned by parent: " << newSub.ownedByRegistry() << endl;
                cnt+=copyObjects(orig,newSub);
                dst.store(newSubp.ptr());
                Dbug << "New registry owned by parent: " << newSub.ownedByRegistry() << endl;
            }
        } else if(obj.writeOpt()==IOobject::AUTO_WRITE) {
            Dbug << name << " set to AUTO_WRITE. Creating copy" << endl;
            autoPtr<regIOobject> newObjP;

            // work around because there is no virtual clone method in IObobject

#define tryClone(Type)                                                  \
            if(!newObjP.valid() && isA<Type>(obj)) {                    \
                newObjP.set(                                            \
                    new Type(                                           \
                        IOobject(                                       \
                            obj.name(),                                 \
                            src.time().timeName(),                      \
                            obj.local(),               \
                            dst                                         \
                        ),                                              \
                        dynamicCast<const Type>(obj)));                 \
            }

            tryClone(volScalarField);
            tryClone(volVectorField);
            tryClone(volTensorField);
            tryClone(volSymmTensorField);
            tryClone(volSphericalTensorField);

            tryClone(surfaceScalarField);
            tryClone(surfaceVectorField);
            tryClone(surfaceTensorField);
            tryClone(surfaceSymmTensorField);
            tryClone(surfaceSphericalTensorField);

            tryClone(pointScalarField);
            tryClone(pointVectorField);
            tryClone(pointTensorField);
            tryClone(pointSymmTensorField);
            tryClone(pointSphericalTensorField);

            tryClone(diagTensorIOField);
            tryClone(labelIOField);
            tryClone(pointIOField);
            tryClone(scalarIOField);
            tryClone(sphericalTensorIOField);
            tryClone(symmTensorIOField);
            tryClone(tensorIOField);
            tryClone(vector2DIOField);
            tryClone(vectorIOField);
            //            tryClone(polyBoundaryMesh);

#undef tryClone

            if(newObjP.valid()) {
                regIOobject &newObj=dynamicCast<regIOobject&>(newObjP());
                Dbug << "Adding " << name << " to registry " << dst.name()
                    << " Class: " << newObj.headerClassName() << endl;
                Dbug << "Owned by old Registry: " << newObj.ownedByRegistry() << endl;
                Dbug << "AUTO_WRITE: " << (newObj.writeOpt()==IOobject::AUTO_WRITE) << endl;
                Dbug << "Old Path: " << obj.objectPath() << endl;
                Dbug << "New Path: " << newObj.objectPath() << endl;
                Dbug << "Local: " << obj.local() << " -> " << newObj.local() << endl;
                newObj.writeOpt()=IOobject::AUTO_WRITE;
                regIOobject *ptr=static_cast<regIOobject*>(newObjP.ptr());
                dst.store(ptr);
                Dbug << "Owned by new Registry: " << newObj.ownedByRegistry() << endl;
                cnt++;
            } else {
                Dbug << "No fitting type found for " << name << endl;
            }
        } else {
            Dbug << name << " not copied" << endl;
        }
    }

    Dbug << "Copying to " << dst.name() << " ended " << cnt << endl;
    Dbug << dst.names() << endl;

    return cnt;
}