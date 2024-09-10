/**
 * @brief Dumps contest results
 *
 * @param type The type of the contest to dump
 */
void CTestContest::Dump(const CContestMgr::TType type) const
{
    CContestMgr::CResult result = _contestMgr.Result(type, true);
    const CPointGPSArray &array = result.PointArray();
    unsigned distance = 0;
    if(array.size()) {
        bool triangle = (type == CContestMgr::TYPE_OLC_FAI || type == CContestMgr::TYPE_OLC_FAI_PREDICTED);
        for(unsigned i=0; i<array.size() - 1; i++) {
            if((i==0 || i==array.size() - 2) && triangle)
                continue;
            distance += array[i].Distance(array[i+1]);
        }
        if(triangle)
            distance += array[3].Distance(array[1]);
    }

    std::cout << std::endl;
    std::wstring typeStr = CContestMgr::TypeToString(type);
    std::cout << "Contest '" << std::string(typeStr.begin(), typeStr.end()) << "':" << std::endl;
    std::cout << " - Distance: " << result.Distance() << " (error: " << (int)distance - (int)result.Distance() << ")" << std::endl;
    std::cout << " - Score: " << result.Score() << std::endl;
    std::cout << " - Predicted: " << result.Predicted() << std::endl;
    for(CPointGPSArray::const_iterator it=result.PointArray().begin(); it!=result.PointArray().end(); ++it)
        std::cout << " - " << TimeToString(it->Time()) << std::endl;

    _kml.Dump(result);
}