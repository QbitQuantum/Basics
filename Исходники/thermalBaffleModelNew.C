autoPtr<thermalBaffleModel> thermalBaffleModel::New(const fvMesh& mesh)
{
    word modelType;
    {
        IOdictionary thermalBafflePropertiesDict
        (
            IOobject
            (
                "thermalBaffleProperties",
                mesh.time().constant(),
                mesh,
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        );

        word modelType =
            thermalBafflePropertiesDict.lookupOrDefault<word>
            (
                "thermalBaffleModel",
                "thermalBaffle"
            );
    }

    meshConstructorTable::iterator cstrIter =
        meshConstructorTablePtr_->find(modelType);

    if (cstrIter == meshConstructorTablePtr_->end())
    {

        FatalErrorIn("thermalBaffleModel::New(const fvMesh&)")
            << "Unknown thermalBaffleModel type " << modelType
            << nl << nl
            <<  "Valid thermalBaffleModel types are:" << nl
            << meshConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<thermalBaffleModel>(cstrIter()(modelType, mesh));
}