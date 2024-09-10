Ilwis::OperationImplementation::State SetAttributeTable::prepare(ExecutionContext *ctx, const SymbolTable &st)
{
    OperationImplementation::prepare(ctx,st);

    OperationHelper::check([&] ()->bool { return _inputTable.prepare(_expression.input<QString>(0), itTABLE); },
    {ERR_COULD_NOT_LOAD_2,_expression.input<QString>(0), "" } );

    OperationHelper::check([&] ()->bool { return _inputRaster.prepare(_expression.input<QString>(1), itRASTER); },
    {ERR_COULD_NOT_LOAD_2,_expression.input<QString>(1), "" } );

    _primaryKey = _expression.input<QString>(2);

    int index = _inputTable->columnIndex(_primaryKey);
    if ( index == iUNDEF){
        kernel()->issues()->log(TR("Table doesnt contain column ") + _primaryKey);
        return sPREPAREFAILED;
    }
    std::vector<QVariant> values = _inputTable->column(_primaryKey);
    std::set<QVariant> uniques;
    int undefs = 0;
    for(QVariant v : values){
        if ( isNumericalUndef(v.toDouble()))
            ++undefs;
        else
            uniques.insert(v);
    }
    if ( (uniques.size() + undefs ) != values.size()){
        kernel()->issues()->log(TR("Key column must not contain duplicate values"));
        return sPREPAREFAILED;
    }

    ColumnDefinition coldef = _inputTable->columndefinition(index);
    if ( !coldef.datadef().domain()->isCompatibleWith(_inputRaster->datadef().domain().ptr())){
        kernel()->issues()->log(TR("Key column doesnt match raster domain ") + _primaryKey);
        return sPREPAREFAILED;
    }

    OperationHelperRaster helper;
    helper.initialize(_inputRaster, _outputRaster, itRASTERSIZE | itENVELOPE | itCOORDSYSTEM | itGEOREF|itDOMAIN);

    for(quint32 i = 0; i < _outputRaster->size().zsize(); ++i){
        QString index = _outputRaster->stackDefinition().index(i);
        DataDefinition datadef = _outputRaster->datadef(i);
        _outputRaster->setBandDefinition(index,DataDefinition(datadef.domain(), datadef.range()->clone()));
    }
    return sPREPARED;
}