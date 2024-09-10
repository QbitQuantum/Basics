int main(int argc, char *argv[])
{
  int a;
  int b;

  scanf("%d", &a);
  // printf("%d\n", a);

  while(a != 0)
  {
    int i;
    int num_digits_in_binary = 0;
    int start = 0, end = 0;

    for(i=0; i<20; i++)
    {
        binary[i] = 0;
    }


    num_digits_in_binary = get_binary_from_decimal(a);

    // printf("n digits : %d\n", num_digits_in_binary);

    // for(i=0; i<num_digits_in_binary; i++)
    //   printf("%d", binary[i]);
    //
    // printf("\n");

    for(i=0; i< num_digits_in_binary; i++)
    {
      if(binary[i] == 1)
      {
        start = i;
        break;
      }
    }


    for(i=start; i< num_digits_in_binary; i++)
    {
      if(i == num_digits_in_binary -1)
      {
        end = i;
        num_digits_in_binary++;
        break;
      }

      if(binary[i+1] == 0 )
      {
        end = i;
        break;
      }
    }

    // printf("%d, %d\n", start, end);

    if(start == end)
    {
      binary[start + 1] = 1;
      binary[start] = 0;
    }
    else
    {
      int x = start;

      while(x <= end)
      {
        binary[x] = 0;
        x++;
      }

      binary[end+1] = 1;

      x = 0;

      while(x < (end-start))
      {
        binary[x] = 1;
        x++;
      }
    }

    // for(i=0; i<num_digits_in_binary; i++)
    //   printf("%d", binary[i]);
    //
    // printf("\n");

    int n = binary_to_decimal(num_digits_in_binary);

    printf("%d\n", n);


    // printf("\n\n");

    scanf("%d", &a);
    // printf("%d\n", a);
  }

  return 0;
}