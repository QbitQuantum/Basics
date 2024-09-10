bool GfxReadAnimationDescFrom(const JsonElement& jsonSource, GfxAnimationDesc& animationDesc)
{
    assert(!!jsonSource);
    if (!jsonSource)
    {
        return false;
    }

    animationDesc = {};
    if (!jsonSource.GetElementName(animationDesc.animationName))
    {
        Logf("Warning: cannot find animation name");
        return false;
    }
    // parse common animation propertices
    animationDesc.animationDuration = JsonGet(jsonSource, "duration", 0.0f);
    animationDesc.spriteSheetImageName = JsonGet(jsonSource, "sprite_sheet", "");
    animationDesc.directionCount = JsonGet(jsonSource, "direction_count", 0);
            
    // read frame size
    std::vector<int32_t> intArray;
    JsonReadArray(jsonSource.FindElement("frame_size"), intArray);
    if (intArray.size() > 1)
    {
        animationDesc.frameWidth = intArray[0];
        animationDesc.frameHeight = intArray[1];
    }

    // read frame indices
    JsonReadArray(jsonSource.FindElement("frames"), intArray);

    animationDesc.frameCount = intArray.size();
    if (animationDesc.frameCount > MAX_ANIMATION_FRAME_COUNT)
        animationDesc.frameCount = MAX_ANIMATION_FRAME_COUNT;

    for (int32_t iframe = 0; iframe < animationDesc.frameCount; ++iframe)
    {
        animationDesc.frameIndices[iframe] = intArray[iframe];
    }
    return true;
}