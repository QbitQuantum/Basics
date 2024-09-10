bool MaekawaAlgorithm::receiveLocked(Packet locked){
    
    printf("----Node %d has received LOCKED message from %d \n",processID,locked.ORIGIN);
//    //Compare and maximize the sequence number
//    if(sequenceNo < locked.SEQ)
//        sequenceNo = locked.SEQ;
    
    //Increase hasReceivedLockedMessage by 1. If this variable reaches K-1, then the node can enter the critical section.
    //hasReceivedLockedMessage++;
    
    //Update quorumVote table
    
    int temp = -1;
    for(int i = 0; i < quorumsize; i++){
        if(quorumVote[i][0] == locked.ORIGIN) temp = i;
    }
    quorumVote[temp][1] = 1;
    
    hasReceivedLockedMessage = 0;
    
    printf("--^^--quorumVote Table--^^-- \n");
    
    //Check if the current node has received all the locked messages
    for(int i = 0; i < quorumsize; i++){
        printf("%d , %d \n",quorumVote[i][0],quorumVote[i][1]);
        if(quorumVote[i][1] == 1){
            hasReceivedLockedMessage++;
        }
    }
    printf("----Node %d has received %d LOCKED messages \n",processID,hasReceivedLockedMessage);
    
    if(hasReceivedLockedMessage == quorumsize){
        
        printf("----Node %d has entered critical section \n",processID);
        enterCriticalSection();
        //printf("Node %d has exited critical section \n",processID);
        return true;
    }
    return true;
}