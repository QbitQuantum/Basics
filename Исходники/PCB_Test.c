int main(void) {
    
    srand ( time(NULL) );
    //create a new PCB with priority between 0 - 15 and test getters
    printf ("Create PCB:\n");
    PCB_p PCBTest1 = create("PCB1", 1, rand()%15);
    printf ("Name: %s and Process ID: %d and Priority: %d\n", getName(PCBTest1), getPid(PCBTest1), getPriority(PCBTest1));
    // test toString() method
    printf("Test toString()\n");
    toString(PCBTest1); printf("\n");
    //free PCB
    printf ("Free PCB:\n");
    freePCB(PCBTest1);
    toString(PCBTest1); printf("\n");
    
    //test create PCB with wrong type for NAME --- EXECUTION FAILS
 //   PCB_p PCBTest2 = create(5, 1, 4);
 //   toString(PCBTest2); printf("\n");
    //test create PCB with wrong type PID   --- Creates PCB and RETURNS RANDOM VALUE
    PCB_p PCBTest3 = create("PCB3", "1", rand()%15);
    toString(PCBTest3); printf("\n");
    //test create PCB with non-int priority   
    PCB_p PCBTest4 = create("PCB4", 1, "c");
    toString(PCBTest4); printf("\n");
    //test create PCB with priority value > 15  
    PCB_p PCBTest5 = create("PCB5", 1, 16);
    toString(PCBTest5); printf("\n");
    //test create PCB with priority value < 0 
    PCB_p PCBTest6 = create("PCB6", 1, -1);
    toString(PCBTest6); printf("\n");
    

    
    return 0;
}