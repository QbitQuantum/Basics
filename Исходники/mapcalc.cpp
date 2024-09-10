OperationImplementation::State MapCalc::prepare(ExecutionContext *ctx,const SymbolTable &st) {

    OperationImplementation::prepare(ctx,st);
    QString expr = _expression.input<QString>(0);

    RasterStackDefinition stackdef;
    for(int parmIndex = 1 ; parmIndex < _expression.parameterCount(); ++parmIndex){
        Parameter parm = _expression.parm(parmIndex);
        if ( hasType(parm.valuetype(), itRASTER)){
            QString url = parm.value();
            IRasterCoverage raster;
            if(!raster.prepare(url)){
                return sPREPAREFAILED;
            }
            if ( stackdef.isValid()){
                if(!stackdef.checkStackDefintion(raster->stackDefinition())){
                    kernel()->issues()->log(TR("Incompatible stack definition for ") +raster->name() ) ;
                    return sPREPAREFAILED;
                }
            }else if ( raster->stackDefinition().domain()->code().indexOf("count") == -1)
                stackdef = raster->stackDefinition();
            _inputRasters[parmIndex] = PixelIterator(raster);
        }else if ( hasType(parm.valuetype(), itNUMBER)){
            bool ok;
            double v = parm.value().toDouble(&ok);
            if (!ok){
                return sPREPAREFAILED;
            }
            _inputNumbers[parmIndex] = v;
        }
    }
    OperationHelperRaster helper;
    helper.initialize((*_inputRasters.begin()).second.raster(), _outputRaster, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF);
    if ( stackdef.isValid()){
        _outputRaster->stackDefinitionRef() = stackdef;
    }
    IDomain outputDomain;
    try {
        outputDomain = linearize(shuntingYard(expr));
        if( !outputDomain.isValid())
            return sPREPAREFAILED;
    } catch(ErrorObject& err){
        return sPREPAREFAILED;
    }

    _outputRaster->datadefRef().domain(outputDomain);

    for(quint32 i = 0; i < _outputRaster->size().zsize(); ++i){
        QString index = _outputRaster->stackDefinition().index(i);
        _outputRaster->setBandDefinition(index,DataDefinition(outputDomain));
    }
    initialize(_outputRaster->size().linearSize());

    return sPREPARED;
}