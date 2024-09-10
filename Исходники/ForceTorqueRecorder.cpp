void TorqueRecorder::action(){
	totalTorque=0;
	Vector3r tmpAxis = rotationAxis.normalized();
	
	FOREACH(Body::id_t id, ids){
		if (!(scene->bodies->exists(id))) continue;
		Body* b=Body::byId(id,scene).get();
		
		Vector3r tmpPos = b->state->pos;
		Vector3r radiusVector = tmpAxis.cross(tmpAxis.cross(tmpPos - zeroPoint));
		
		totalTorque+=tmpAxis.dot(scene->forces.getTorque(id)+radiusVector.cross(scene->forces.getForce(id)));
	};
	
	//Save data to a file
	out<<scene->iter<<" "<<totalTorque<<"\n";
	out.close();
}