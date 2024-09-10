int determinant(int n, int *matrix)
{

if(n==1)
{
return *matrix;

}

if(n==2)
{
//printf("end\n");
return *matrix*(*(matrix+3)) - *(matrix+1)*(*(matrix+2)); 

}

int x,y,z,sum=0,count=0;

for(x=0; x<n; x++)
{
	int a = *(matrix+x);
	int *add = matrix;
	add += n;
	int *p;
	int arr[(n-1)*(n-1)];
	int m;
	for(m=0; m<(n-1)*(n-1); m++){
	arr[m]=0;	
	}	
	p = &arr[0];
	int *e = p;

	for(y=1; y<n; y++)
	{

	
	for(z=0; z<n; z++)
	{
		if (z != x)
		{
			*p = *add;
			p+=1;
		}
		add+=1;
	}
	

	}
	
	//printf("a =  %d and n= %d \n",a,n); 
	//printMatrix(n-1,e);
	//printf("------------------------\n");
	
	if(count%2==0)
	{
		sum += a *  determinant(n-1,e);
	}
	if(count%2==1)
	{
		sum -= a * determinant(n-1,e);
	}

	count++;
}		
return sum;


}