int main(){
	Node* nodes[20];
	LinkedList list;
	
	for(int i=0;i<20;i++){
		nodes[i] = new Node(i);
		list.add(nodes[i]);
	}
	
	list.print();
	
	printf("Removing odd-numbered nodes\n");
	
	for(int i=1;i<20;i+=2){
		list.remove(i);
	}
	
	list.print();
	
	list.reverse();
	list.print();
	
	for(int i=0;i<20;i++){
		delete(nodes[i]);
	}
	
	return 0;
}