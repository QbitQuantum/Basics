void ByteUtil::QSort(byte *arr, int min, int max) {
	
	if(min >= max - 1)
        return;
    // Initially find a random pivot
    int pivotIndex = min + rand() % (max - min);
    int pivot = arr[pivotIndex];

	byte *begin = arr + min;
	byte *end = arr + (max - 1);

	// While begin != end 
    while(begin != end)
    {
        // Find the lowest bound number to swap
        while(*begin < pivot && begin < end)
            begin++;
        while(*end >= pivot && begin < end)
            end--;

            // Do the swap
        SwapBytes(begin, end);
    }

    // Here begin and end are equal and equal to point from where left side is lower and right side is greater or equal to pivot

    // Partition left
    QSort(arr, min, begin - arr);
    // Partiion right
    QSort(arr, end - arr, max);	
};