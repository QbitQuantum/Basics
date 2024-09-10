bool BinaryLogical::prepareCoverageNumber(IlwisTypes ptype1, IlwisTypes ptype2) {

    int mindex = (ptype1 & itNUMBER) == 0 ? 0 : 1;
    int nindex = mindex ? 0 : 1;

    QString raster =  _expression.parm(mindex).value();
    if (!_inputGC1.prepare(raster)) {
        kernel()->issues()->log(TR(ERR_COULD_NOT_LOAD_2).arg(raster, ""));
        return false;
    }
    if(_inputGC1->datadef().domain<>()->ilwisType() != itNUMERICDOMAIN)
        return false;

    _number = _expression.parm(nindex).value().toDouble();

    OperationHelperRaster helper;
    _box = helper.initialize(_inputGC1, _outputGC, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF);

     IDomain dom;
    dom.prepare("boolean");
    _outputGC->datadefRef().domain(dom);

    return true;
}