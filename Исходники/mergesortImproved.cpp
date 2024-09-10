void mergesortImproved(vector<Comparable> &a) 
{
	int counter = 2;
	int size = a.size();
	vector<Comparable> b(size);  // this is only one temporary array. 
	//splits each array into lengths of multiples of 2
	for (int i = 1; i < size; i *= 2)
    {
        for (int j = 0; j < size; j += 2 * i)
        {
			//counter switches roles of a and b
			if(counter % 2 == 0)
				MergeIt(a, b, j, min(j+i, size), min(j+2*i, size));
			if(counter % 2 != 0)
				MergeIt(b, a, j, min(j+i, size), min(j+2*i, size));
			
        }
		//increments to change the role of a and b 
		counter++;	
    }
	//if last iteration ends on b, moves contents to a
   if(counter % 2 != 0)
	   a.swap(b);
  // implement a nonrecursive mergesort only using vectors a and b.
}