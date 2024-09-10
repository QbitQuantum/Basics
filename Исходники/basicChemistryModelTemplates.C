Foam::autoPtr<ChemistryModel> Foam::basicChemistryModel::New
(
    const fvMesh& mesh
)
{
    IOdictionary chemistryDict
    (
        IOobject
        (
            "chemistryProperties",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    );

    word chemistryTypeName;

    if (chemistryDict.isDict("chemistryType"))
    {
        const dictionary& chemistryTypeDict
        (
            chemistryDict.subDict("chemistryType")
        );

        Info<< "Selecting chemistry type " << chemistryTypeDict << endl;

        const int nCmpt = 8;
        const char* cmptNames[nCmpt] =
        {
            "chemistrySolver",
            "chemistryModel",
            "chemistryThermo",
            "transport",
            "thermo",
            "equationOfState",
            "specie",
            "energy"
        };

        IOdictionary thermoDict
        (
            IOobject
            (
                "thermophysicalProperties",
                mesh.time().constant(),
                mesh,
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        );

        word thermoTypeName;

        if (thermoDict.isDict("thermoType"))
        {
            const dictionary& thermoTypeDict(thermoDict.subDict("thermoType"));
            thermoTypeName =
                word(thermoTypeDict.lookup("transport")) + '<'
              + word(thermoTypeDict.lookup("thermo")) + '<'
              + word(thermoTypeDict.lookup("equationOfState")) + '<'
              + word(thermoTypeDict.lookup("specie")) + ">>,"
              + word(thermoTypeDict.lookup("energy")) + ">";
        }
        else
        {
             FatalIOErrorIn
             (
                 (ChemistryModel::typeName + "::New(const mesh&)").c_str(),
                 thermoDict
             )   << "thermoType is in the old format and must be upgraded"
                 << exit(FatalIOError);
        }

        Switch isTDAC(chemistryTypeDict.lookupOrDefault("TDAC",false));

        // Construct the name of the chemistry type from the components
        if (isTDAC)
        {
            chemistryTypeName =
                word(chemistryTypeDict.lookup("chemistrySolver")) + '<'
              + "TDACChemistryModel<"
              + word(chemistryTypeDict.lookup("chemistryThermo")) + ','
              + thermoTypeName + ">>";
        }
        else
        {
            chemistryTypeName =
                word(chemistryTypeDict.lookup("chemistrySolver")) + '<'
              + "chemistryModel<"
              + word(chemistryTypeDict.lookup("chemistryThermo")) + ','
              + thermoTypeName + ">>";
        }
        typename ChemistryModel::fvMeshConstructorTable::iterator cstrIter =
            ChemistryModel::fvMeshConstructorTablePtr_->find(chemistryTypeName);

        if (cstrIter == ChemistryModel::fvMeshConstructorTablePtr_->end())
        {

            FatalErrorIn(ChemistryModel::typeName + "::New(const mesh&)")
                << "Unknown " << ChemistryModel::typeName << " type " << nl
                << "chemistryType" << chemistryTypeDict << nl << nl
                << "Valid " << ChemistryModel ::typeName << " types are:"
                << nl << nl;


            // Get the list of all the suitable chemistry packages available
            wordList validChemistryTypeNames
            (
                ChemistryModel::fvMeshConstructorTablePtr_->sortedToc()
            );


            // Build a table of the thermo packages constituent parts
            // Note: row-0 contains the names of constituent parts
            List<wordList> validChemistryTypeNameCmpts
            (
                validChemistryTypeNames.size() + 1
            );

            validChemistryTypeNameCmpts[0].setSize(nCmpt);
            forAll(validChemistryTypeNameCmpts[0], j)
            {
                validChemistryTypeNameCmpts[0][j] = cmptNames[j];
            }

            // Split the thermo package names into their constituent parts
            forAll(validChemistryTypeNames, i)
            {
                validChemistryTypeNameCmpts[i+1] = basicThermo::splitThermoName
                (
                    validChemistryTypeNames[i],
                    nCmpt
                );
            }

            // Print the table of available packages
            // in terms of their constituent parts
            printTable(validChemistryTypeNameCmpts, FatalError);

            FatalError<< exit(FatalError);
        }