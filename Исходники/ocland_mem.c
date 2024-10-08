/** Thread that receives image from client.
 * @param data struct dataTransfer casted variable.
 * @return NULL
 */
void *asyncDataRecvImage_thread(void *data)
{
    struct dataSend* _data = (struct dataSend*)data;
    // Provide a server for the data transfer
    int fd = accept(_data->fd, (struct sockaddr*)NULL, NULL);
    if(fd < 0){
        // we can't work, disconnect the client
        printf("ERROR: Can't listen on binded port.\n"); fflush(stdout);
        shutdown(_data->fd, 2);
        return CL_SUCCESS;
    }
    // We may wait manually for the events generated by ocland,
    // and then we can wait for the OpenCL generated ones.
    if(_data->num_events_in_wait_list){
        oclandWaitForEvents(_data->num_events_in_wait_list, _data->event_wait_list);
    }
    // Receive the data
    Recv(&fd, _data->ptr, _data->cb, MSG_WAITALL);
    // Writre it into the buffer
    clEnqueueWriteImage(_data->command_queue,_data->mem,CL_FALSE,
                        _data->buffer_origin,_data->region,
                        _data->buffer_row_pitch,_data->buffer_slice_pitch,
                        _data->ptr,0,NULL,&(_data->event->event));
    // Wait until the data is copied before start cleaning up
    clWaitForEvents(1,&(_data->event->event));
    // Clean up
    free(_data->ptr); _data->ptr = NULL;
    if(_data->event){
        _data->event->status = CL_COMPLETE;
    }
    if(_data->want_event != CL_TRUE){
        free(_data->event); _data->event = NULL;
    }
    if(_data->event_wait_list) free(_data->event_wait_list); _data->event_wait_list=NULL;
    // shutdown(fd, 2);
    // shutdown(_data->fd, 2); // Destroy the server to free the port
    close(fd);
    close(_data->fd);
    free(_data); _data=NULL;
    pthread_exit(NULL);
    return NULL;
}