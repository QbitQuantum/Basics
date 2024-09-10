OperationImplementation::State UnaryMathRasterAndNumber::prepare(ExecutionContext *ctx,const SymbolTable &st)
{
    OperationImplementation::prepare(ctx,st);
    IlwisTypes ptype = _expression.parm(0).valuetype();


    if ( hasType(ptype,itNUMBER) ) {
        _case = otNUMBER;
        bool ok;
        _number = _expression.parm(0).value().toDouble(&ok);
        if (!ok) {
            ERROR2(ERR_NO_OBJECT_TYPE_FOR_2,"Numerical value", "UnaryMathRasterAndNumber operation");
            _number = rUNDEF;
            return sPREPAREFAILED;
        }
        return sPREPARED;

    } else if ( hasType(ptype,itRASTER)) {
        QString raster = _expression.parm(0).value();

        if (!_inputGC.prepare(raster)) {
            ERROR2(ERR_COULD_NOT_LOAD_2,raster,"");
            return sPREPAREFAILED;
        }
        OperationHelperRaster helper;
        _box = helper.initialize(_inputGC, _outputGC, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF);
        if ( !_outputGC.isValid()) {
            ERROR1(ERR_NO_INITIALIZED_1, "output rastercoverage");
            return sPREPAREFAILED;
        }
        QString outputName = _expression.parm(0,false).value();
        if ( outputName != sUNDEF)
            _outputGC->name(outputName);

        auto nrange = _inputGC->datadef().range<NumericRange>();
        if (nrange.isNull())
            return sPREPAREFAILED;

        NumericRange *newRange = constructRangeFrom(nrange);

        IDomain dom;
         if(!dom.prepare(_outputDomain))
             return sPREPAREFAILED;

         _outputGC->datadefRef().domain(dom);
         _outputGC->datadefRef().range(newRange);
        for(quint32 i=0; i<_outputGC->size().zsize(); ++i){
                QString index = _outputGC->stackDefinition().index(i);
             _outputGC->setBandDefinition(index,{dom, newRange->clone()});
         }
        _case = otSPATIAL;
        return sPREPARED;
    }
    return sNOTPREPARED;
}