ptr stack::pop(void)
{    ptr p;
	 if(top==null){
	 cout<<"\n there are no elements in the stack";
	 _cexit();}
  else{ if(no==2){p=top; top=top->next;top->next=null;no--;return(p);}
       else{p=top; top=top->next;no--;return(p);}
  }
 }