Ilwis::OperationImplementation::State SetValueRange::prepare(ExecutionContext *ctx, const SymbolTable &st)
{
    OperationImplementation::prepare(ctx,st);
    QString objectName = _expression.parm(0).value();
    if ( !_raster.prepare(objectName)) {
        ERROR2(ERR_COULD_NOT_LOAD_2, "raster", objectName);
        return sPREPAREFAILED;
    }
    OperationHelperRaster helper;
    _box = helper.initialize(_raster, _outputRaster, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF|itDOMAIN);

    QString minTxt = _expression.parm(1).value();
    QString maxTxt = _expression.parm(2).value();

    bool ok = true;
    _step = _raster->datadef().domain()->range<NumericRange>()->resolution();
    if ( minTxt.trimmed() != ""){
        _min = minTxt.toDouble(&ok);
    }
    if ( maxTxt.trimmed() != ""){
        _max = maxTxt.toDouble(&ok);
    }
    if ( _expression.parameterCount() == 4) {
        QString stepTxt = _expression.parm(3).value();
        if ( stepTxt.trimmed() != ""){
            _step = stepTxt.toDouble(&ok);
        }
    }
    auto indexes = _raster->stackDefinition().indexes();
    _raster->setDataDefintions(_raster->datadef().domain(),indexes);
    if ( !ok) {
        ERROR2(ERR_ILLEGAL_VALUE_2, TR("parameter"),TR("expression"));
        return sPREPAREFAILED;
    }
    initialize(_outputRaster->size().linearSize());
    return sPREPARED;
}