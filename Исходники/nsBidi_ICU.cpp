nsresult nsBidi::ReorderVisual(const nsBidiLevel* aLevels, int32_t aLength,
                               int32_t* aIndexMap)
{
  ubidi_reorderVisual(aLevels, aLength, aIndexMap);
  return NS_OK;
}