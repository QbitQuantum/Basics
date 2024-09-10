Foam::radiation::greyMeanAbsorptionEmissionSoot::greyMeanAbsorptionEmissionSoot
(
    const dictionary& dict,
    const fvMesh& mesh
)
:
    absorptionEmissionModel(dict, mesh),
    coeffsDict_((dict.subDict(typeName + "Coeffs"))),
    speciesNames_(0),
    specieIndex_(0),
    lookUpTable_
    (
        fileName(coeffsDict_.lookup("lookUpTableFileName")),
        mesh.time().constant(),
        mesh
    ),
    thermo_(mesh.lookupObject<basicThermo>("thermophysicalProperties")),
    EhrrCoeff_(readScalar(coeffsDict_.lookup("EhrrCoeff"))),
    Yj_(nSpecies_)
{
    label nFunc = 0;
    const dictionary& functionDicts = dict.subDict(typeName + "Coeffs");

    forAllConstIter(dictionary, functionDicts, iter)
    {
        // safety:
        if (!iter().isDict())
        {
            continue;
        }
        const word& key = iter().keyword();
        speciesNames_.insert(key, nFunc);
        const dictionary& dict = iter().dict();
        coeffs_[nFunc].initialise(dict);
        nFunc++;
    }

    // Check that all the species on the dictionary are present in the
    // look-up table and save the corresponding indices of the look-up table

    label j = 0;
    forAllConstIter(HashTable<label>, speciesNames_, iter)
    {
        if (mesh.foundObject<volScalarField>("ft"))
        {
            if (lookUpTable_.found(iter.key()))
            {
                label index = lookUpTable_.findFieldIndex(iter.key());

                Info<< "specie: " << iter.key() << " found on look-up table "
                    << " with index: " << index << endl;

                specieIndex_[iter()] = index;
            }
            else if (mesh.foundObject<volScalarField>(iter.key()))
            {
                volScalarField& Y =
                    const_cast<volScalarField&>
                    (
                        mesh.lookupObject<volScalarField>(iter.key())
                    );
                Yj_.set(j, &Y);
                specieIndex_[iter()] = 0;
                j++;
                Info<< "specie: " << iter.key() << " is being solved" << endl;
            }
            else
            {
                FatalErrorIn
                (
                    "Foam::radiation::greyMeanAbsorptionEmissionSoot(const"
                    "dictionary& dict, const fvMesh& mesh)"
                )   << "specie: " << iter.key()
                    << " is neither in look-up table: "
                    << lookUpTable_.tableName()
                    << " nor is being solved" << nl
                    << exit(FatalError);
            }
        }
        else
        {
            FatalErrorIn
            (
                "Foam::radiation::greyMeanAbsorptionEmissionSoot(const"
                "dictionary& dict, const fvMesh& mesh)"
            )   << "specie ft is not present " << nl
                << exit(FatalError);

        }
    }
}