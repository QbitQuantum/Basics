	void Ship (int room, std::string index,QVector pos,Vector Q, Vector R) {
		BaseInterface::Room *newroom=CheckRoom(room);
		if (!newroom) return;
		Vector P = R.Cross(Q);
		P.Normalize();
		newroom->objs.push_back(new BaseInterface::Room::BaseShip(P.i,P.j,P.k,Q.i,Q.j,Q.k,R.i,R.j,R.k,pos,index));
//		return BaseInterface::CurrentBase->rooms[BaseInterface::CurrentBase->curroom]->links.size()-1;
	}