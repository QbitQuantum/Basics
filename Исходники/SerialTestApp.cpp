void SerialTestApp::mouseDrag( MouseEvent event )
{
    mousePos = event.getPos();
    Vec2f offset = mousePos - getWindowCenter();

    float speed = offset.length();
    offset.normalize();
    float amtLeftWheel = 0;
    float amtRightWheel = 0;
    
    // Turning scheme:
    // 0-90°
    // 0 == other wheel moves forward @ speed
    // 90 == other wheel moves backwards @ speed
    
    // Never account for moving backwards.
    // Hard left or right is all we can do.
    float yRange = (MAX((offset.y*-1), 0.0)*2.0f) - 1.0f; // -1..1
    //yRange*=-1;
    
    // Always having one wheel moving forward ensures we're
    // driving forward. We can't drive backwards.
    if(offset.x < 0){
        amtRightWheel = 1;
        amtLeftWheel = yRange;// -1..1 //offset.y*-1;
    }else{
        amtLeftWheel = 1;
        amtRightWheel = yRange;// -1..1 //offset.y*-1;
    }
    
    // Making the lw / rw amount a function of the speed
    const static int MAX_SPEED = 200;
    float speedScalar = MIN((speed/(float)MAX_SPEED), 1.0);
    amtLeftWheel *= speedScalar;
    amtRightWheel *= speedScalar;
    
    int lw = 255+(amtLeftWheel*255); // 0..255..500
    int rw = 255+(amtRightWheel*255); // 0..255..500
    string directions = "" + boost::lexical_cast<string>((int)lw) + "," +
                             boost::lexical_cast<string>((int)rw) + ",\n";

    console() << directions << "\n";
    serial.writeString(directions);
    
    // SIM Arduino code
    long val = (lw*(long)1000)+rw;
    int rVal = val % 1000;
    int lVal = (val - rVal) * 0.001;
    
    int lDirection = lVal >= 255 ? 1 : -1;
    int rDirection = rVal >= 255 ? 1 : -1;
    int lAbsVal = abs(lVal-255);
    int rAbsVal = abs(rVal-255);

    console() << "lw : " << lw << " rw: " << rw;
    console() << " lAbsVal : " << lAbsVal << " rAbsVal: " << rAbsVal << "\n";
    
    
    _ardLDir = lDirection;
    _ardRDir = rDirection;
    _ardLVal = lAbsVal;
    _ardRVal = rAbsVal;

}