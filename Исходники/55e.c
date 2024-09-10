int main(){

//number of lychrel numbers
unsigned long lychrel;
unsigned long b=1,f=1;
unsigned long test=10;
char buf[40];
char flip [40];
unsigned long sum=0;
unsigned long i=test,j=0;

while(i<20){
  /* converts initial test case to a string called buf */
  sprintf(buf, "%lu", test);
  /* flip the string */
  strrev(buf,flip);

  /* convert the strings to integers */
  b = atoi(buf);
  f = atoi(flip);
  printf("testing %lu: ",i);
  /*test the numbers */
  if(j==5){  //possibly lychrel!
    printf("%lu is possibly lychrel after %lu iterations",i,j);
    j=0; //reset tester counter

    i++; //try a new number!
    test=i;
    }
  if((f==b)&&(j!=5)){   //definitely not a lychrel number; move on!
    printf("%lu is NOT lychrel after %lu iterationsi. ",i,j);
    printf(" This is because %lu = %lu\n",b,j);
    j=0; //reset tester counter

    i++; //try a new number!
    test=i;
    }
  else{       //add the two numbers
    sum=b+f;
    printf("%lu+%lu=%lu, testing new candidate\n",b,f,sum);
    //sets sum to the new test candidate
    test=sum; //new test number!
    j++;      //increment the iteration counter.
    }
  }
  return 0;
}