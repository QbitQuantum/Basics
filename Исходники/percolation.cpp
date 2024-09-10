void Percolation:: init(int width,int height,double p)
{
	int probability = (int)(p*100);
	cout<<"probability is: "<<probability<<"%"<<endl;
	srand(time(0));// pseudo random

Width=width;
Height=height;

sites=new site[width*height];

for(int i=0;i<width;i++)
{
	for(int j=0;j<height;j++)
	{
		sites[dsetIndex(i,j)].rightWall=true;	// exist
		sites[dsetIndex(i,j)].downWall=true;
		sites[dsetIndex(i,j)].status=false;
		//sites[dsetIndex(i,j)].dist=0;
		//sites[dsetIndex(i,j)].path=NULL;
	}
}

// the first site--- center
//	sites[dsetIndex(Width/2,0)].rightWall=true;
//	sites[dsetIndex(Width/2,0)].downWall=true;
// the last row:
	for (int i=0;i<Width;i++)
	{
		sites[dsetIndex(i,Height-1)].downWall=false;
		sites[dsetIndex(i,Height-1)].status=false;
	}

//DisjointSets dset;
dset.addelements(width*height);//there are width*height vertices in total

///index of (x,y) in the dset = y*width+x;

int xCur=0;
int yCur=0;


//the first time
for(int i=0;i<width;i++)
{
	for(int j=0;j<height;j++)// (height-1)  and (width-1) because they are on the edge
	{
		sites[dsetIndex(i,j)].x=i;
		sites[dsetIndex(i,j)].y=j;
	if(random()%100<=probability){
		if(j!=height-1){
			sites[dsetIndex(i,j)].downWall=false;//delete the down wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i,j+1));//set union
		}
	}
	if(random()%100<=probability){
		if(i!=width-1){
			sites[dsetIndex(i,j)].rightWall=false;//delete the wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i+1,j));//set union
		
		}
	}
	}
}

//delete the rest
/*
for(int i=0;i<width-1;i++)
{
	for(int j=0;j<height-1;j++)// (height-1)  and (width-1) because they are on the edge
	{

		if(j!=height-1){
		if(dset.find(dsetIndex(i,j))!=dset.find(dsetIndex(i,j+1)))// no cycle after delete down wall
		{
			sites[dsetIndex(i,j)].downWall=false;//delete the down wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i,j+1));//set union
		}
		}

		if(i!=width-1){
		if(dset.find(dsetIndex(i,j))!=dset.find(dsetIndex(i+1,j)))//no cycle after delete right wall
		{
			sites[dsetIndex(i,j)].rightWall=false;//delete the wall
			dset.setunion(dsetIndex(i,j),dsetIndex(i+1,j));//set union
		}
		}
	}
}
*/

}