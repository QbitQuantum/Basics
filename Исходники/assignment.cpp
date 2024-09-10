Ilwis::OperationImplementation::State Assignment::prepare(ExecutionContext *, const SymbolTable &)
{
    if ( _expression.parameterCount() != 1) {
        ERROR3(ERR_ILLEGAL_NUM_PARM3,"assignment","1",QString::number(_expression.parameterCount()));
        return sPREPAREFAILED;
    }

    bool ok;
    _number = _expression.parm(0).value().toDouble(&ok);
    if ( !ok) {
        _number = rILLEGAL;
        QString coverage = _expression.parm(0).value();
        Resource resource = mastercatalog()->name2Resource(coverage);
        if ( !resource.isValid()) {
            ERROR1(ERR_COULD_NOT_OPEN_READING_1,coverage);
            return sPREPAREFAILED;
        }
        _inputObj.prepare(coverage, resource.ilwisType());
        OperationHelperRaster helper;
        _outputObj = helper.initialize(_inputObj, resource.ilwisType(),
                                       itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF | itDOMAIN | itTABLE);
        QString outname = _expression.parm(0,false).value();
        if ( outname != sUNDEF)
            _outputObj->setName(outname);
    } else {
        _varName = _expression.parm(0,false).value();
    }

    return sPREPARED;
}