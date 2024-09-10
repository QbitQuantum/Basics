bool BinaryMathRaster::prepareCoverageNumber(IlwisTypes ptype1, IlwisTypes ptype2) {

    int mindex = (ptype1 & itNUMBER) == 0 ? 0 : 1;
    int nindex = mindex ? 0 : 1;

    _firstorder = mindex > nindex;
    QString raster =  _expression.parm(mindex).value();
    if (!_inputGC1.prepare(raster)) {
        kernel()->issues()->log(TR(ERR_COULD_NOT_LOAD_2).arg(raster, ""));
        return false;
    }
    if(_inputGC1->datadef().domain<>()->ilwisType() != itNUMERICDOMAIN)
        return false;

    _number1 = _expression.parm(nindex).value().toDouble();

    OperationHelperRaster helper;
    _box = helper.initialize(_inputGC1, _outputGC,itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF);

    auto nrange = _inputGC1->datadef().range<NumericRange>();
    if (nrange.isNull())
        return false;

    NumericRange *newRange = constructRangeFrom(nrange, _number1);

    IDomain dom;
    dom.prepare("value");
    _outputGC->datadefRef().domain(dom);
    _outputGC->datadefRef().range(newRange);

    for(quint32 i = 0; i < _outputGC->size().zsize(); ++i){
        QString index = _outputGC->stackDefinition().index(i);
        _outputGC->setBandDefinition(index,DataDefinition(dom,newRange->clone()));
    }

    return true;
}