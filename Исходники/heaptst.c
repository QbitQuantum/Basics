/*Testing heap data stracure*/
int main(){

	int * head = heapCreate(15);
	int i;

	for(i=1;i<10;i++)
		heapInsert(i,head);

	heapPrint(head);

	printf("\nremove element : %d\n",heapRemove(head));
	printf("\n\n");
	heapPrint(head);

	printf("\nremove element : %d\n",heapRemove(head));
	printf("\n\n");

	heapInsert(120,head);
	heapInsert(6,head);
	heapInsert(5,head);

	heapPrint(head);

	int arr[] = {46, 109, 711, 275, 196, 367,545,256,789,267,552};

	int * head1= heapify(arr,11);

	printf("\n\n");	
	heapPrint(head1);

	return 0;
}