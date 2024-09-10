void Queue<const char*>::push(const char *const &val)
{
    // allocate a new character array and copy characters from val
    char* new_item = new char[strlen(val) + 1];
    strncpy(new_item, val, strlen(val) + 1);

    // store pointer to newly allocated and initialized element
    QueueItem<const char*> *pt =
        new QueueItem<const char*>(new_item); 

    // put item onto existing queue
    if (empty())
        head = tail = pt;   // queue has only one element
    else {
        tail->next = pt;    // add new element to end of queue
        tail = pt;
    }
}