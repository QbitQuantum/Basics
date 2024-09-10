Item get_first_item(Queue q)
{
    if (is_empty(q))
        terminate("Error, no items to get\n\n");
    return q->first->data;
}