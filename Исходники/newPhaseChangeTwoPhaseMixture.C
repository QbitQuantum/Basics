Foam::autoPtr<Foam::phaseChangeTwoPhaseMixture>
Foam::phaseChangeTwoPhaseMixture::New
(
    const volVectorField& U,
    const surfaceScalarField& phi,
    const word& alpha1Name
)
{
    IOdictionary transportPropertiesDict
    (
        IOobject
        (
            "transportProperties",
            U.time().constant(),
            U.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    );

    word phaseChangeTwoPhaseMixtureTypeName
    (
        transportPropertiesDict.lookup("phaseChangeTwoPhaseMixture")
    );

    Info<< "Selecting phaseChange model "
        << phaseChangeTwoPhaseMixtureTypeName << endl;

    componentsConstructorTable::iterator cstrIter =
        componentsConstructorTablePtr_
            ->find(phaseChangeTwoPhaseMixtureTypeName);

    if (cstrIter == componentsConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "phaseChangeTwoPhaseMixture::New"
        )   << "Unknown phaseChangeTwoPhaseMixture type "
            << phaseChangeTwoPhaseMixtureTypeName << endl << endl
            << "Valid  phaseChangeTwoPhaseMixtures are : " << endl
            << componentsConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<phaseChangeTwoPhaseMixture>(cstrIter()(U, phi, alpha1Name));
}