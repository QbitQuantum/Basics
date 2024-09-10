void menu::interaccion_point(ofVec2f ptF, bool isNeg) {
	float minDis = ofGetHeight()/3.0;// (isNeg)? 400 : 200;
	
	float minDis2 = minDis*minDis;
	
	float ff = 1.0;

	float fFuerza = 45.0;
	if(ptF.distance(centro)<distConf) {
//	if(ptF.squareDistance(centro)<distConf) {
		if(isNeg) {
			// Atrae circulos y repele boxes
			for(int i=0; i<circles.size(); i++) {
//				float dis = ptF.distance(circles[i].get()->getPosition());
				float dis2 = ptF.squareDistance(circles[i].get()->getPosition());
//				if(dis < minDis) 
//				if(dis2 < minDis2) 
//					circles[i].get()->addRepulsionForce(ptF, ff*1.4f*fFuerza/dis2);//3, 9);
//				else 
//					circles[i].get()->addAttractionPoint(ptF, ff*2.2*fFuerza/dis2);//4.0);
				
				circles[i].get()->addAttractionPoint(ptF, ff*2.2*fFuerza/dis2);//4.0);
				
			}
			for(int i=0; i<boxes.size(); i++) {
				float dis = ptF.distance(boxes[i].get()->getPosition());
				float dis2 = dis*dis;//ptF.squareDistance(boxes[i].get()->getPosition());
//				if(dis < minDis) 
//				if(dis2 < minDis2) 
//					boxes[i].get()->addAttractionPoint(ptF, ff*1.2*fFuerza/dis2);
//				else 
//					boxes[i].get()->addRepulsionForce(ptF, ff*0.8*fFuerza/dis2);//4.0);
				boxes[i].get()->addRepulsionForce(ptF, ff*0.9*fFuerza/dis2);//4.0);
			}
		}
		else {
			// Mouse Pressed
			// Atrae boxes y repele circulos
			for(int i=0; i<circles.size(); i++) {
//				float dis = ptF.distance(circles[i].get()->getPosition());
				float dis2 = ptF.squareDistance(circles[i].get()->getPosition());
//				if(dis < minDis) 
//				if(dis2 < minDis2) 
//					circles[i].get()->addAttractionPoint(ptF, ff*1.2*fFuerza/dis2);//3, 9);
//				else 
					circles[i].get()->addRepulsionForce(ptF, ff*0.8*fFuerza/dis2);//4.0);
			}
			for(int i=0; i<boxes.size(); i++) {
				float dis = ptF.distance(boxes[i].get()->getPosition());
				float dis2 = ptF.squareDistance(boxes[i].get()->getPosition());
//				if(dis < minDis) 
				if(dis2 < minDis2) 
//					boxes[i].get()->addRepulsionForce(ptF, ff*1.4*fFuerza/dis);
//				else 
					boxes[i].get()->addAttractionPoint(ptF, ff*2.2*fFuerza/dis2);//4.0);
			}
		}
	}

}