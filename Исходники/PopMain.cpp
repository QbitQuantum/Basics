void loopMain() {
    refreshWatchdog();
    unsigned long startMicros = micros();

    updateAccelerometer();

    // display lights
    lights->reset();
    controller->paint(*lights);
    capOverallBrightness(*lights);
    lights->show();
    
    
    unsigned long endMicros = micros();
    avgTime = (15*avgTime + endMicros - startMicros)/16;
    
    int timeToDelay = (int)(10 - (endMicros - startMicros)/1000);
    if (timeToDelay > 0)
        delay(timeToDelay);
    int blink = (millis() /100)%2;
    digitalWrite(ONBOARD_LED_PIN, blink);
    if (count++ >= 100) {
        
        // Print head size for debugging.
#ifdef RN_PRINT_HEAP_SIZE
        info->printf("Avg time = %5d, delay = %dms, heapSize = %d\n",
                     avgTime, timeToDelay, heapSize());
        count = 0;
#endif /* RN_PRINT_HEAP_SIZE */
        
    }
    // Serial.println(millis()/10);
}