void DynSuffixArray::Qsort(int* array, int begin, int end)
{
  if(end > begin) {
    int index;
    {
      index = begin + (rand() % (end - begin + 1));
      int pivot = array[index];
      {
        int tmp = array[index];
        array[index] = array[end];
        array[end] = tmp;
      }
      for(int i=index=begin; i < end; ++i) {
        if (Compare(array[i], pivot, 20) <= 0) {
          {
            int tmp = array[index];
            array[index] = array[i];
            array[i] = tmp;
            index++;
          }
        }
      }
      {
        int tmp = array[index];
        array[index] = array[end];
        array[end] = tmp;
      }
    }
    Qsort(array, begin, index - 1);
    Qsort(array, index + 1,  end);
  }
}