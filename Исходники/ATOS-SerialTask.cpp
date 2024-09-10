//this task will flash the 1st LED
int flashLed1(void *params) {
    LED1status ^= 1;
    digitalWrite(LED1, LED1status);
    tos.sleep(500);
    return TASK_RET_INPROG;
}