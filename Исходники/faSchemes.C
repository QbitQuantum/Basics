faSchemes::faSchemes(const objectRegistry& obr)
    :
    IOdictionary
    (
       IOobject
       (
           "faSchemes",
           obr.time().system(),
           obr,
//             IOobject::MUST_READ,
           IOobject::READ_IF_PRESENT,  // Allow default dictionary creation
           IOobject::NO_WRITE
       )
    ),
    ddtSchemes_(ITstream("ddtSchemes", tokenList())()),
    defaultDdtScheme_("default", tokenList()),
    d2dt2Schemes_(ITstream("d2dt2Schemes", tokenList())()),
    defaultD2dt2Scheme_("default", tokenList()),
    interpolationSchemes_(ITstream("interpolationSchemes", tokenList())()),
    defaultInterpolationScheme_("default", tokenList()),
    divSchemes_(ITstream("divSchemes", tokenList())()),
    defaultDivScheme_("default", tokenList()),
    gradSchemes_(ITstream("gradSchemes", tokenList())()),
    defaultGradScheme_("default", tokenList()),
    lnGradSchemes_(ITstream("lnGradSchemes", tokenList())()),
    defaultLnGradScheme_("default", tokenList()),
    laplacianSchemes_(ITstream("laplacianSchemes", tokenList())()),
    defaultLaplacianScheme_("default", tokenList()),
    fluxRequired_(ITstream("fluxRequired", tokenList())())
{
    if (!headerOk())
    {
        if (debug)
        {
            InfoIn
            (
                "faSchemes::faSchemes(const objectRegistry& obr)"
            )   << "faSchemes dictionary not found.  Creating default."
                << endl;
        }
    }

    read();
}