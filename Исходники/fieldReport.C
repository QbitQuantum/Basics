void reportValues(
    const word &fieldName,
    const fvMesh &mesh,
    CommonValueExpressionDriver &driver,
    const string &entName
) {
    startLine(
        mesh.time(),
        entName
    );

    Field<Type> result(
        driver.evaluate<Type>(fieldName)
    );

    AccumulationCalculation<Type> calculator(
        result,
        false,
        driver
    );

    writeData(Info,calculator.size(),"Size | Weight Sum","size");
    Info << " | ";
    writeData(Info,calculator.weightSum(),"","weight_sum",true);

    writeData(Info,calculator.minimum(),"Range (min-max)","minimum");
    Info << " | ";
    writeData(Info,calculator.maximum(),"","maximum",true);

    writeData(
        Info,calculator.average(),
        "Average | weighted","average");
    Info << " | ";
    writeData(
        Info,calculator.weightedAverage(),
        "","average_weighted",true);

    writeData(
        Info,calculator.sum(),
        "Sum | weighted","sum");
    Info << " | ";
    writeData(
        Info,calculator.weightedSum(),
        "","sum_weighted",true);

    writeData(
        Info,calculator.distribution().median(),
        "Median | weighted","median");
    Info << " | ";
    writeData(
        Info,calculator.weightedDistribution().median(),
        "","median_weighted",true);

    if(nrOfQuantiles) {
        scalar dx=1./nrOfQuantiles;
        for(label i=1;i<nrOfQuantiles;i++) {
            scalar thisQuantile=dx*i;
            NumericAccumulationNamedEnum::accuSpecification quant(
                NumericAccumulationNamedEnum::numQuantile,
                thisQuantile
            );
            NumericAccumulationNamedEnum::accuSpecification wquant(
                NumericAccumulationNamedEnum::numWeightedQuantile,
                thisQuantile
            );
            OStringStream annotation;
            annotation << thisQuantile << " quantile | weighted";

            writeData(
                Info,calculator(quant),
                annotation.str(),NumericAccumulationNamedEnum::toString(quant));
            Info << " | ";
            writeData(
                Info,calculator(wquant),
                "",NumericAccumulationNamedEnum::toString(wquant),true);
        }
    }

    forAll(fractionSmallerThan,i) {
        scalar value=fractionSmallerThan[i];
        NumericAccumulationNamedEnum::accuSpecification smaller(
            NumericAccumulationNamedEnum::numSmaller,
            value
        );
        NumericAccumulationNamedEnum::accuSpecification wsmaller(
            NumericAccumulationNamedEnum::numWeightedSmaller,
            value
        );
        OStringStream annotation;
        annotation << "x <= " << value << " | weighted";

        writeData(
            Info,calculator(smaller),
            annotation.str(),NumericAccumulationNamedEnum::toString(smaller));
        Info << " | ";
        writeData(
            Info,calculator(wsmaller),
            "",NumericAccumulationNamedEnum::toString(wsmaller),true);
    }