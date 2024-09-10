std::unordered_map<std::string, ModuleManifest::AssetDiff> ModuleManifest::genDiff()
{
    std::unordered_map<std::string, AssetDiff> diff_map;
    
    std::string key;
    Asset valueA;
    std::unordered_map<std::string, Asset>::const_iterator valueIt, it;
    
    int64_t diffLen = 0;
    for (it = _assets.begin(); it != _assets.end(); ++it)
    {
        key = it->first;
        valueA = it->second;
        
        if (valueA.compressed) {
            int64_t maxExistTime = 0;
            int64_t maxNoFileTime = 0;
            
            for (auto bit : valueA.content) {
                auto fLen = getFileLen(FileUtils::getInstance()->getWritablePath() + bit.second.path);
                if (fLen >= 0) {
                    auto fTime = getFileTime(FileUtils::getInstance()->getWritablePath() + bit.second.path);
                    if (fTime > maxExistTime) {
                        maxExistTime = fTime;
                    }
                }
                else {
                    auto fTime = bit.second.timestamp;
                    if (fTime > maxNoFileTime) {
                        maxNoFileTime = fTime;
                    }
                }
            }
            
            for (auto bit : valueA.content) {
                auto fLen = getFileLen(FileUtils::getInstance()->getWritablePath() + bit.second.path);
                if (fLen >= 0) {
                    if (fLen != bit.second.len) {
                        cocos2d::log("ModuleManifest::genDiff path: %s fTime: %lld bit.second.timestamp: %lld", bit.second.path.c_str(), getFileTime(FileUtils::getInstance()->getWritablePath() + bit.second.path) + 60, bit.second.timestamp);
                        auto fTime = getFileTime(FileUtils::getInstance()->getWritablePath() + bit.second.path) + 60;
                        if (fTime < bit.second.timestamp) {
                            AssetDiff diff;
                            diff.asset = valueA;
                            diff.type = DiffType::MODIFIED;
                            diff_map.emplace(key, diff);
                            diffLen += valueA.len;
                            break;
                        }
                    }
                }
                else {
                    cocos2d::log("ModuleManifest::genDiff path: %s file not exist bit.second.timestamp: %lld maxNoFileTime %lld maxExistTime %lld", bit.second.path.c_str(), bit.second.timestamp, maxNoFileTime, maxExistTime);
                    if (maxNoFileTime > maxExistTime) {
                        AssetDiff diff;
                        diff.asset = valueA;
                        diff.type = DiffType::MODIFIED;
                        diff_map.emplace(key, diff);
                        diffLen += valueA.len;
                        break;
                    }
                }
            }
        }
        else {
            auto fLen = getFileLen(FileUtils::getInstance()->getWritablePath() + valueA.path);
            if (fLen != valueA.len) {
                cocos2d::log("ModuleManifest::genDiff path: %s fTime: %lld valueA.timestamp: %lld", valueA.path.c_str(), getFileTime(FileUtils::getInstance()->getWritablePath() + valueA.path) + 60, valueA.timestamp);
                auto fTime = getFileTime(FileUtils::getInstance()->getWritablePath() + valueA.path) + 60;
                if (fTime < valueA.timestamp) {
                    AssetDiff diff;
                    diff.asset = valueA;
                    diff.type = DiffType::MODIFIED;
                    diff_map.emplace(key, diff);
                    diffLen += valueA.len;
                }
            }
        }
    }
    
    CCLOG("ModuleManifest::genDiff diff_map");
    for (auto it : diff_map) {
        CCLOG("ModuleManifest::genDiff %s", it.first.c_str());
    }
    
    setDiffLength(diffLen);
    return diff_map;
}