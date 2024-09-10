//大小写分开
void func1(char a[], int low, int high)
{
    while (low < high)
    {
        while (isUpper(a[high]) && low < high) high--;
        while (isLower(a[low]) && low < high) low++;
        swap(a[low], a[high]);
    }
}