int main()
{
  int arr1[500] = {0,};
  int arr2[5000] = {0,};
  int arr3[50000] = {0,};
  int idx;

  idx = BSearch(arr1, sizeof(arr1)/sizeof(int), 7);
  if(idx == -1)
    printf("탐색 실패 \n");
  else
    printf("타겟 저장 인덱스: %d \n", idx);

  idx = BSearch(arr2, sizeof(arr2)/sizeof(int), 4);
  if(idx == -1)
    printf("탐색 실패 \n");
  else
    printf("타겟 저장 인덱스> %d \n", idx);

  idx = BSearch(arr3, sizeof(arr3)/sizeof(int), 7);
  if(idx == -1)
    printf("탐색 실패 \n");
  else
    printf("타겟 저장 인덱스: %d \n", idx);
  
  return 0;
}