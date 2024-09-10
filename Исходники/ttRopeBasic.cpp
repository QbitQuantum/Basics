void ttRopeBasic::update(ofPoint AccFrc,ofPoint StartPos){

    accFrc = AccFrc;
    startPos = StartPos;
    endPos = StartPos;
    

    if(num_char == 0){
        if (accFrc.y<-0.15){
            endPos.y += ofMap(accFrc.y, -0.15, -0.6,  0, 1024-endPos.y, true);
            length = StartPos.distance(endPos);
            bFixedMove = true;
        }else{
            endPos.y = StartPos.y;
            length = StartPos.distance(endPos);
            bFixedMove = false;
        }
    }

    if (num_char == 1) {
        if (accFrc.y>0.15) {
            endPos.y -= ofMap(accFrc.y, 0.15, 0.6, 0, endPos.y,true);
            length = StartPos.distance(endPos);
            bFixedMove = true;
        }else{
            endPos.y = StartPos.y;
            length = StartPos.distance(endPos);
            bFixedMove = false;
        }
    }
    
    
    getPos = startPos;
    getLength = length;
}