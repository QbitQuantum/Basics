static chunk get_chunk(value_table_t vt,value_index_t idx){
    int len;
    char* data=SIgetC(vt->index,idx,&len);
    if (data==NULL) {
        if (HREme(vt->ctx)==0) Abort("chunk %d does not exist",idx);
        Debug("looking up index %d",idx);
        if (vt->msg_pending) HREyieldWhile(vt->ctx,&vt->msg_pending);
        vt->task=idx;
        memcpy(vt->msg->buffer,&idx,4);
        vt->msg->tail=4;
        vt->task_pending=1;
        vt->msg_pending=1;
        HREpostSend(vt->msg);
        HREyieldWhile(vt->ctx,&vt->task_pending);
        data=SIgetC(vt->index,idx,&len);
        data[len]=0;
        Debug("got %s (%d)",data,vt->msg_pending);
    }
    return chunk_ld(len,data);
}