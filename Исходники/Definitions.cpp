PCB* MainProcess::TreeSearch(str pID, PCB* p){

	if (p->getPID() != pID){

		PCB* temp;
		if (!p->children.empty()){
			for (PCB* q : p->children){
				temp = TreeSearch(pID, q);

				if (temp->getPID() == pID)
					return temp;
			}
		}
	}


	
	return p;
		

}