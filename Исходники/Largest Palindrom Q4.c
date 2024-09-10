int isPalindrome_num(long long int n){
	/*
	  ****<string.h>
	   Used to check number is palindrome or not
	   """
	     isPalindrome_num(n)
	     return 1 if palindrome
	     return 0 if not palindrome
	   """
	*/
	char a[30];
	char b[30];
	sprintf(a,"%d",n); //convert number in string & store it in array a
	strcpy(b,a); //copy b<-a
	_strrev(b);  //reverse b
	if(strcmp(a,b)==0) //compare
	    return 1;
	else
	    return 0;
}