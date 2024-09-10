static void
generateData(CMistTGroup & tGroup, const TMistParameters & parameters,
    std::string& result)
{
    if (mist_tg_clear_values(&tGroup) != MIST_OK 
        || mist_tg_set_values(&tGroup, 
                &parameters[0], parameters.size()) != MIST_OK)
    {
        throw CGenerator::CGeneratorError(errSetValuesFailed);
    }

    const char** presult;
    size_t nvals;
    
    if (mist_tg_evaluate(&tGroup, &presult, &nvals) != MIST_OK) {
        throw CGenerator::CGeneratorError(errGenFailed);
    }
    assert(nvals != 0);
    
    if (nvals > 1) {
        throw CGenerator::CGeneratorError(errMultivaluedMain);
    }
    
    string s = presult[0];
    result.swap(s);
    return;
}