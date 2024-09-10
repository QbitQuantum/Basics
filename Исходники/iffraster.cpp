OperationImplementation::State IffRaster::prepare(ExecutionContext *, const SymbolTable &)
{
    QString raster = _expression.parm(0).value();

    if (!_inputGC.prepare(raster)) {
        ERROR2(ERR_COULD_NOT_LOAD_2,raster,"");
        return sPREPAREFAILED;
    }
    DataDefinition outputDataDef = findOutputDataDef(_expression);


    OperationHelperRaster helper;
    helper.initialize(_inputGC, _outputGC, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF);

    _outputGC->datadefRef() = outputDataDef;

    return sPREPARED;
}