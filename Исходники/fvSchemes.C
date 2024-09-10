Foam::fvSchemes::fvSchemes(const objectRegistry& obr)
:
    IOdictionary
    (
        IOobject
        (
            "fvSchemes",
            obr.time().system(),
            obr,
//             IOobject::MUST_READ,
            IOobject::READ_IF_PRESENT,  // Allow default dictionary creation
            IOobject::NO_WRITE
        )
    ),
    ddtSchemes_
    (
        ITstream
        (
            objectPath() + "::ddtSchemes",
            tokenList()
        )()
    ),
    defaultDdtScheme_
    (
        ddtSchemes_.name() + "::default",
        tokenList()
    ),
    d2dt2Schemes_
    (
        ITstream
        (
            objectPath() + "::d2dt2Schemes",
            tokenList()
        )()
    ),
    defaultD2dt2Scheme_
    (
        d2dt2Schemes_.name() + "::default",
        tokenList()
    ),
    interpolationSchemes_
    (
        ITstream
        (
            objectPath() + "::interpolationSchemes",
            tokenList()
        )()
    ),
    defaultInterpolationScheme_
    (
        interpolationSchemes_.name() + "::default",
        tokenList()
    ),
    divSchemes_
    (
        ITstream
        (
            objectPath() + "::divSchemes",
            tokenList()
        )()
    ),
    defaultDivScheme_
    (
        divSchemes_.name() + "::default",
        tokenList()
    ),
    gradSchemes_
    (
        ITstream
        (
            objectPath() + "::gradSchemes",
            tokenList()
        )()
    ),
    defaultGradScheme_
    (
        gradSchemes_.name() + "::default",
        tokenList()
    ),
    snGradSchemes_
    (
        ITstream
        (
            objectPath() + "::snGradSchemes",
            tokenList()
        )()
    ),
    defaultSnGradScheme_
    (
        snGradSchemes_.name() + "::default",
        tokenList()
    ),
    laplacianSchemes_
    (
        ITstream
        (
            objectPath() + "::laplacianSchemes",
            tokenList()
        )()
    ),
    defaultLaplacianScheme_
    (
        laplacianSchemes_.name() + "::default",
        tokenList()
    ),
    fluxRequired_
    (
        ITstream
        (
            objectPath() + "::fluxRequired",
            tokenList()
        )()
    ),
    defaultFluxRequired_(false),
    cacheFields_
    (
        ITstream
        (
            objectPath() + "::cacheFields",
            tokenList()
        )()
    )
{
    if (!headerOk())
    {
        if (debug)
        {
            InfoIn
            (
                "fvSchemes::fvSchemes(const objectRegistry& obr)"
            )   << "fvSchemes dictionary not found.  Creating default."
                << endl;
        }

        regIOobject::write();
    }

    read();
}