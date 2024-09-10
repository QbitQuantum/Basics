//Generate a random map
void HM::randomize(){
	make_circle(50);
	//Calculate the normal
	for(int i =0;i<map_size-1;i+=1){ 
		for(int j = 0;j<map_size-1;j+=1){
			Vector3D x =  height_map[i+1][j]-height_map[i][j] ;
			Vector3D y =  height_map[i+1][j+1] - height_map[i+1][j];
			Vector3D n = x.cross(y);
			n.normalize();
			normal_map[i][j] = n;
		}
	}
}