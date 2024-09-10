void multi(dym tdim,MatrixXf &c)
{
 	 if(dim==tdim)
 	     data=data*c.transpose();
     else
         rotate_top(tdim),data=c*data;
}