void checklala(int i,int j,int *arr[3][3],int player,int *arr2[9][8],int *a)
{
    if(player==shortcut2(i,arr))// player 2 1 a zete parbena & player 1 2 te zete parbena.
    {



        i=i-1;

        if(i>8||i<0)
        {
            printf("Error..! You have range between 1 to 9\n");
            Beep(250,250);

        }
        else if(i==4)
        {
            if(j==arr2[i][0]||j==arr2[i][1]||j==arr2[i][2]||j==arr2[i][3]||j==arr2[i][4]||j==arr2[i][5]||j==arr2[i][6]||j==arr2[i][7])
            {
                if(shortcut2(j,arr)==0)
                {
                    move(arr,i+1,j,player);
                    printf("A=%d\n",++*a);
                }
                else
                {
                    printf("Error\n");
                    Beep(250,250);
                }
            }
            else
            {
                printf("Error\n");
                Beep(250,250);
            }
        } else {

            if(j==arr2[i][0]||j==arr2[i][1]||j==arr2[i][2]) {


                if(shortcut2(j,arr)==0)
                {
                    move(arr,i+1,j,player);
                    printf("A=%d\n",++*a);


                }
                else
                {
                    printf("Error\n");
                    Beep(250,250);
                }

            }   else
            {
                printf("Error\n");
                Beep(250,250);

            }
        }

    }
    system("cls");
}