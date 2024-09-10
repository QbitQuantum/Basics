void setResultForContribution<FaFieldValuePluginFunction>(
    const fvMesh &mesh,
    ExpressionResult &result,
    const scalarField &values
) {
    autoPtr<areaScalarField> pResult(
        new areaScalarField(
            IOobject(
                "contributionFrom_", // +Driver::driverName(),
                mesh.time().timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            FaCommonValueExpressionDriver::faRegionMesh(mesh),
            dimensionedScalar("contribution",dimless,0)
        )
    );

    pResult->internalField()=values;
    pResult->correctBoundaryConditions();

    result.setObjectResult(pResult);
}