void MyScene::castRayAgainstSubgraph(Point3 p, Vector3 v, Tree* graph, HitRecord* hits){
	for (Node* n : graph->rootNodes){
		Matrix4 trans = transformStack.back();
		trans = trans*n->transformations;

		Matrix4 invTrans = trans.inverse();

		if (n->object){
			Vector4 pObj4 = invTrans*Vector4(p[0], p[1], p[2], 1);
			Vector4 vObj4 = invTrans*Vector4(v[0], v[1], v[2], 0);
			vObj4.normalize();
			Shape* s;
			switch (n->object->type){
				case CUBE:{
					s = cube;
				} break;
				case SPHERE:{
					s = sphere;
				} break;
				case CONE:{
					s = cone;
				} break;
				case CYLINDER:{
					s = cylinder;
				} break;
			}

			Point3 pObj = Point3(pObj4[0], pObj4[1], pObj4[2]);
			Vector3 vObj = Vector3(vObj4[0], vObj4[1], vObj4[2]);
			HitRecord* hr = s->intersect(pObj, vObj);
			hr->sortHits();
			
			bool gotHit;
			double tH,uH,vH;
			Point3 pH;
			Vector3 nH;
			gotHit = hr->getFirstHit(tH, uH, vH, pH, nH);
			delete hr;

			if (gotHit && tH > 0){
				pH = trans * pH;
				nH = invTrans.transpose() * nH;
				nH.normalize();

				tH = (pH - p).length();
				
				if (tH < hits->getMinT()){
					hits->clear();
					hits->addHit(tH, uH, vH, pH, nH, (void*)n->object);
				}
			}
		}
		else if (n->subgraph){
			transformStack.push_back(trans);
			castRayAgainstSubgraph(p, v, n->subgraph, hits);
			transformStack.pop_back();
		}
	}
}