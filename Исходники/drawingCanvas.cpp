//--------------------------------------------------------------
void drawingCanvas::makeLine(ofVec2f mouse){
	int intersect=0;
	vector< ofPoint > points = myPolyline->getVertices();
	int size = points.size();

	if(mouse.distance(lastMouse) > 3){
		//check for intersection first!!
		if(size > 10){
			//check lines on the ofPolyline
			if(drawDummy==false){
				for(int i=0; i< myPolyline->size()-2; i ++){
					//only check if line is close to mouse
					//if((points[i].x > mouse.x-6) && (points[i].x < mouse.x+6)){
					//	if((points[i].y > mouse.y-6) && (points[i].y < mouse.y+6)){
							intersect = intersection(points[i],points[i+1],lastMouse,mouse);
							if(intersect == 2){
								//intersection found
								i = myPolyline->size();//escape for loop
							}
					//	}
					//}
				}
				if(intersect == 0){
					//no intersection
					myPolyline->addVertex(mouse);
					//fix offset of point since they are in in the "middle" of the screen
					//they have to be where the slicing takes place
					myPolyline2->addVertex(ofVec2f(mouse.x-posCanvas.x,mouse.y-posCanvas.y));
					drawDummy = false;
				}else if(intersect == 2){
					//YES intersection
					//draw the segment to the mouse but not saving it into the polyline
					drawDummy = true;
					myDummyLine = new ofPolyline();//////////////////////////////////////////////////////////////remember to dlete this *memory
					myDummyLine->addVertex(points[points.size()-1]);
					myDummyLine->addVertex(mouse);

					//dummyA = points[points.size()-1];
					//dummyB = mouse;
				}
			}else{
				//do comparison wih dummyline, until there is no intersection with dummy line, there is no more adition to the real polyline
				/*intersect = intersection(,lastMouse,mouse);*/
				vector< ofPoint > pointsDummy = myDummyLine->getVertices();
				for(int i=0; i< myPolyline->size()-2; i ++){
					//only check if line is close to mouse
					intersect = intersection(points[i],points[i+1],pointsDummy[0],pointsDummy[1]);
					if(intersect == 2){
						//intersection found
						i = myPolyline->size();//escape for loop
					}
				}
				if(intersect == 2){
					//YES intersection
					//draw the segment to the mouse but not saving it into the polyline
					drawDummy = true;
					myDummyLine->clear();
					myDummyLine->addVertex(points[points.size()-1]);
					myDummyLine->addVertex(mouse);

					//dummyA = points[points.size()-1];
					//dummyB = mouse;

				}else{
					//no intersection
					//return to real polyline
					drawDummy = false;
					myDummyLine->clear();
				}
			}
		}else{
			//not looking for intersection
			myPolyline->addVertex(mouse);
			//fix offset of point since they are in in the "middle" of the screen
			//they have to be where the slicing takes place
			myPolyline2->addVertex(ofVec2f(mouse.x-posCanvas.x,mouse.y-posCanvas.y));
			drawDummy = false;
		}
	}
}