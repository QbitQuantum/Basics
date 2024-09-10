/**
 * Generic atomic list append operation
 * @param list The list to which an item is being appended
 * @param item THe item to append to the list
 *
 * The contents of the item are copied to the end of the list.
 * Currently assumes the list is at the end of its parent.
 */
int
of_list_append(of_object_t *list, of_object_t *item)
{
    int new_len;

    new_len = list->length + item->length;

    if (!of_object_can_grow(list, new_len)) {
        return OF_ERROR_RESOURCE;
    }

    of_wire_buffer_grow(list->wbuf,
                        OF_OBJECT_ABSOLUTE_OFFSET(list, new_len));

    MEMCPY(OF_OBJECT_BUFFER_INDEX(list, list->length),
           OF_OBJECT_BUFFER_INDEX(item, 0), item->length);

    /* Update the list's length */
    of_object_parent_length_update(list, item->length);

    OF_LENGTH_CHECK_ASSERT(list);

    return OF_ERROR_NONE;
}