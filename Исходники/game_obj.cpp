void GameObj::spawn_new_obj(string type, btVector3 pos, btVector3 trav_dir, GameObj* s_obj) {
	if(type == "las_shoot"){
		//TODO check if z-axis is the trav_dir
		btVector3 z_vec(0,0,1);

		btVector3 xaxis = z_vec.cross(trav_dir);
		xaxis.normalize();

		btVector3 zaxis = trav_dir.cross(-xaxis);
		zaxis.normalize();

		btMatrix3x3 mat = btMatrix3x3( xaxis.x(), trav_dir.x(), zaxis.x(),
									   xaxis.y(), trav_dir.y(), zaxis.y(),
									   xaxis.z(), trav_dir.z(), zaxis.z());

        btTransform temp_trans(mat);

		new_objs.push_back(new GameObj("../res/laser_shot1.obj", "fullb", "GameObj", Y_AXIS, pos, temp_trans.getRotation() ));

        new_objs.back()->set_spawn_obj(s_obj);

		btRigidBody* body = new_objs.back()->get_body();
		body->setGravity(btVector3(0,0,0));

		body->setLinearVelocity(trav_dir*75);   
	}
}