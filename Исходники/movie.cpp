 void unite (int x, int y)
 {
     while(ufvals.length() <= max(x, y)) ufvals.add();
     x = compressfind(x);
     y = compressfind(y);
     if(x==y) return;
     ufval &xval = ufvals[x], &yval = ufvals[y];
     if(xval.rank < yval.rank) xval.next = y;
     else
     {
         yval.next = x;
         if(xval.rank==yval.rank) yval.rank++;
     }
 }