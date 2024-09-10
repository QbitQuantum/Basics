void try_(int cul){
	int i;
	for(i=0;i<8;i++)
		if(IS_SAFE(i,cul)){
			SET(i,cul);
			if(cul==7)
				get_result();
			else
				try_(cul+1);
			REMOVE(i,cul);
		}
}