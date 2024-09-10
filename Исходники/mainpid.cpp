int main() {


    // MPU6050 object "MPU6050.h"
    MPU6050 accelgyro;
    // Kalman filter Object "Kalman.h"
    Kalman kalman;

    // Xbee serial baudrate
    xBee.baud(38400);
    pc.baud(9600);

    // Initialize timers
    Timer timer, code, encTimer;
    // Start timers
    timer.start(); 
    code.start();
    encTimer.start();
    // Reset timer values
    timer.reset();
    code.reset();
    encTimer.reset();

    //Encoder 1 interrupts
    enc1a.rise(&incrementEnc1a);
    enc1b.rise(&incrementEnc1b);
    enc1a.fall(&setEnc1aFall);
    enc1b.fall(&setEnc1bFall);

    enc2a.rise(&incrementEnc2a);
    enc2b.rise(&incrementEnc2b);
    enc2a.fall(&setEnc2aFall);
    enc2b.fall(&setEnc2bFall);

    // Debug leds
    myled1 = 0;
    myled2 = 0;
    myled3 = 0;

    // Encoder 1 initializations
    newTime =0; oldTime = 0; lastEncTime = 0;
    enc1Speed = 0; enc2Speed = 0;

    // MPU6050 initializations
    accelgyro.initialize();
    accelgyro.setFullScaleGyroRange(0);
    accelgyro.setFullScaleAccelRange(0);

    // Initialize MotorShield object
    shield.init();

    float measuredTheta , measuredRate, newTheta,calcRate;
    float position= 0, velocity = 0, lastPosition = 0, lastVelocity =0;
    float angleOffset = 0, positionOffset = 0,lastAngleoffset = 0;


    // Position control constants, if necessary
    float zoneA = 16000.0f, zoneB = 8000.0f, zoneC = 2000.0f;
    float multiplier = 1.0f;
    float zoneAscale = 600*2*multiplier, 
        zoneBscale = 800*2*multiplier, 
        zoneCscale = 1000*2*multiplier,
        zoneDscale =  1500*2*multiplier,
        velocityScale = 60*2*multiplier;

    // Serial communication buffer
    char buffer[40];
    int i, strSize;

    // Control parameters
    float k0,k1,k2,k3,tref;
    float x, dotx, deltaX, deltaT, lastX = 0;

    // Helper variables
    float waittime , u, diff, dt;

    float error = 0,lastError = 0;
    int counter = 0;
    float pTerm = 0,dTerm = 0,iTerm = 0;


    
    while(1) {

        ///////////////////////////////////////////
        // Read serial data and update constants //
        ///////////////////////////////////////////
        i = 0;
        char a;
        while(pc.readable()){
            a = pc.getc();
            buffer[i++] = a;
            printf("%c\n", a );
            myled1 = 1;
            wait(0.001);
         }

        strSize = i;
        string receive(buffer,strSize); // Changes from char to string
        if(strSize > 0){
            printf("%s\n", receive);
            assignGainsFromString(&k[0], &k[1], &k[2], &k[3], &k[4],receive);
        }

        // Below is an attempt to control the robot position, 
        // by dividing it into "zones" and changing the angle accordingly.
        // 
        /////////////////////////////
        // Generate encoder offset //
        /////////////////////////////

        // position = (float)enc2total;
        // positionOffset = position;

        // //if((encTimer.read_us() - lastEncTime) > 0.0f ) {   // every 100 ms
            
        //     float sign = 0;
        //     if(positionOffset > 0) sign= 1;
        //     else sign = -1;


        //     if(abs(positionOffset) > zoneA) angleOffset += 1.0f/zoneAscale*positionOffset;
        //     else if(abs(positionOffset) > zoneB) angleOffset += 1.0f/zoneBscale*positionOffset;
        //     else if(abs(positionOffset) > zoneC) angleOffset += 1.0f/zoneCscale*positionOffset;
        //     else angleOffset += positionOffset/zoneDscale;

        //     printf("angleOffset: %f, positionoffset: %f\n", angleOffset, positionOffset );
        //     // Estimate velocity
        //     // 
        //     velocity = (position - lastPosition);
        //     lastPosition = position;

        //     angleOffset += velocity/velocityScale;

        //     angleOffset = constrain(angleOffset,-10, 10);
            
        //     lastAngleoffset = angleOffset;
        // //}

        // angleOffset = constrain(angleOffset,lastAngleoffset - 1, lastAngleoffset + 1);
        
        timer.reset();
        ///////////////////////////
        // Get gyro/accel values //
        ///////////////////////////
        
        accelgyro.getAcceleration(&ax,&ay,&az);
        measuredRate = accelgyro.getRotationX()*1.0/131.0f;  // Units depend on config. Right now 250o/s
        measuredTheta = -atan(1.0*ay/az);   
        measuredTheta = measuredTheta*180/PI;  // measured in degrees
        
        ///////////////////
        // Kalman Filter //
        ///////////////////
        dt = (double)(code.read_us() - oldTime)/1000000.0f;
        newTheta = kalman.getAngle(measuredTheta,
            -measuredRate, dt);
        
        //DEBUG: printf("%g \n",  (double)(code.read_us() - oldTime)/1000000.0f);
        oldTime = code.read_us();

        //////////////////
        // Control loop //
        //////////////////

        // Set control variable to zero
        u = 0;
        
        // Extract constants from k vector, which has the serial readings.
        float kp = k[0];
        float ki = k[1];
        float kd = k[2];
        tref = k[3] - angleOffset;
        waittime = k[4];

        if(newTheta >= 50 || newTheta <= -50){
            u = 0;
        }else{

            // Define error term
            error = newTheta - tref;
            // Proportional term
            pTerm = kp*error;
            //Integral term
            iTerm += ki*error*dt*100.0f;
            // Prevent integration windup:
            if(iTerm >= 100) iTerm = 100; 
            else if (iTerm <= -100) iTerm = -100;

            u = -(iTerm + pTerm);
            
            // Calculated derivative based on smoothened angle.
            // There are two other sources for the angle here: kalman.getRate(); and measuredRate.
            calcRate = -(error-lastError)/dt;

            // Derivative term
            if(kd !=  0)
            dTerm = kd*calcRate/100.0f;
            lastError = error;

            u += dTerm;

            // Correct for dead zone --- Did not have successful results but I'll leave it here.
            // int deadzone = 20;
            // if(u < -deadzone) u = u + deadzone;
            // else if(u > deadzone) u = u - deadzone; 
            // else u = 0;
            
            // // Include saturation
            u = constrain(u,-400,400);
            
            // Flash LED to indicate loop
            if(counter % 50 == 0){
                myled3 = !myled3;    
                counter = 0;
            }
            counter++;
        }
        
        lastError = error; // update angle

        if(counter % 50 == 0){
            myled3 = !myled3;    
            // xBee.printf("%f,%f\n", newTheta,u);
            counter = 0;
        } 

        // Set motor speed
        shield.setM1Speed(-(int)u);
        shield.setM2Speed((int)u);

        // DEBUG over serial port. Use with MATLAB program "serialPlot.m" to plot these results.
        printf("%f,%f,%f\n", measuredTheta, newTheta , u);
        
        // Hold the timer until desired sampling time is reached.
        while(timer.read_us() < waittime*1000);

        // Turn off serial transmission LED
        myled1 = 0;

    }
}