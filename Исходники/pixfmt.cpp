BYTE * AddLAVFrameSideData(LAVFrame *pFrame, GUID guidType, size_t size)
{
  BYTE * ptr = (BYTE *)CoTaskMemRealloc(pFrame->side_data, sizeof(LAVFrameSideData) * (pFrame->side_data_count + 1));
  if (!ptr)
    return NULL;

  pFrame->side_data = (LAVFrameSideData *)ptr;
  pFrame->side_data[pFrame->side_data_count].guidType = guidType;
  pFrame->side_data[pFrame->side_data_count].data = (BYTE *)CoTaskMemAlloc(size);
  pFrame->side_data[pFrame->side_data_count].size = size;

  if (!pFrame->side_data[pFrame->side_data_count].data)
    return NULL;

  pFrame->side_data_count++;

  return pFrame->side_data[pFrame->side_data_count - 1].data;
}