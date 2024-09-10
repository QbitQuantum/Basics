int main() {
    Gradebook gb;
    int num;
    int i,j,k,l;
    srand(time(NULL));
    printf("Enter the number of grades: ");
    scanf("%d", &num);
    for(i=0; i<num; i++)
    {
        gb.grade[i]=60+rand()%41;
    }
    ListGrade(&gb,num);
    printf("\n");
    Stat(&gb,num);
    system("pause");
    return 1;
}