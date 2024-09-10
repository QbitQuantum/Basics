/* 释放本技能相关 ui 资源 */
void SkillItem::releaseUI() {
    CCTextureCache* pTextureCache = CCTextureCache::sharedTextureCache();
    CCSpriteFrameCache* pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    // 获取大文件名
    
    std::string c = getC();
    std::string pvrFile = c + ".pvr.ccz";
    std::string plistFile = c + ".plist";
    
    pTextureCache->removeTextureForKey(pvrFile.c_str());
    pSpriteFrameCache->removeSpriteFramesFromFile(plistFile.c_str());
}