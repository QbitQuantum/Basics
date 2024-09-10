/******************************************************************************
Description: function for sending back the result
Input Value.:
Return Value:
******************************************************************************/
void server_result (int sock, string userID)
{
    // printf("result thread\n\n");

    int n;
    char response[BUFFER_SIZE] = "ok";
    char defMsg[BUFFER_SIZE] = "none";
    int matchedIndex;
    char sendInfo[BUFFER_SIZE];
    vector<float> coord;
    sem_t *sem_match = new sem_t(); // create a new semaphore in heap
    queue<string> *imgQueue = 0;    // queue storing the file names 

    //  Init semaphore and put the address of semaphore into map
    if (sem_init(sem_match, 0, 0) != 0)
    {
        errorSocket("ERROR semaphore init failed", sock);
    }
    // grap the lock
    pthread_mutex_lock(&sem_map_lock);
    sem_map[userID] = sem_match;
    pthread_mutex_unlock(&sem_map_lock);

    // reponse to the client
    if (!orbit)
    {
        n = write(sock, response, sizeof(response));
        if (n < 0)
        {
            error("ERROR writting to socket");
        }
    }
    else
    {
        MsgD.send(sock, response, BUFFER_SIZE);
    }

    while(!global_stop) 
    {
        sem_wait(sem_match);
        // get the address of image queue
        if (imgQueue == 0)
        {
            imgQueue = queue_map[userID];
        }

        // check if the queue is empty
        if (imgQueue->empty())
        {
            sem_map.erase(userID);
            queue_map.erase(userID);
            user_map.erase(userID);
            delete(sem_match);
            delete(imgQueue);
            sem_destroy(sem_match);
            MsgD.close(sock, 0);
            printf("[server] client disconnectted\n");
            pthread_exit(NULL); //terminate calling thread!
        }

        if (debug) printf("\n----------- start matching -------------\n");
        string file_name = imgQueue->front(); 
        if (debug) printf("file name: %s\n", file_name.c_str());
        imgQueue->pop();

        // start matching the image
        imgM.matchImg(file_name);
        matchedIndex = imgM.getMatchedImgIndex();
        if (matchedIndex == 0) 
        {   
            // write none to client
            if (!orbit) {
                if (write(sock, defMsg, sizeof(defMsg)) < 0)
                {
                   errorSocket("ERROR writting to socket", sock);
                }

            }
            else
            {
                MsgD.send(sock, defMsg, BUFFER_SIZE);
            }

            if (debug) printf("not match\n");            
        }
        else
        {
            // write index to client
            coord = imgM.calLocation();
            sprintf(sendInfo, "%d,%f,%f,%f,%f,%f,%f,%f,%f", matchedIndex, coord.at(0), coord.at(1), coord.at(2), coord.at(3), coord.at(4), coord.at(5), coord.at(6), coord.at(7));
            if (debug) printf("sendInfo: %s\n", sendInfo);
            if (!orbit)
            {
                if (write(sock, sendInfo, sizeof(sendInfo)) < 0)
                {
                    errorSocket("ERROR writting to socket", sock);
                }
            }
            else
            {
                MsgD.send(sock, sendInfo, BUFFER_SIZE);
            }
            if (debug) printf("matched image index: %d\n", matchedIndex);

        }

        if (debug) printf("------------- end matching -------------\n");
    }

    if (!orbit)
    {
        close(sock);    
    }
    printf("[server] Connection closed. --- result\n\n");
    delete(sem_match);
    pthread_exit(NULL); //terminate calling thread!

}