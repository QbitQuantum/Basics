/* fill_marshbuf_ptr: fills the buffer 'marshbuf' at offset 'marshoff' with
 * the contents of 'tocopy'. In this case, 'tocopy' contains a pointer 
 * Here, the contents of the void * location are suposed to be the pointer.
 * That is, the void * is not the pointer itself.
 */
void fill_marshbuf_ptr (const char *function_name,
                        void **marshbuf,
                        int *marshoff,
                        const void *tocopy)
{
    int ptrsz = sizeof (void *);
#ifdef MARSH_PRINT    
    printk ("In fill_marshbuf_ptr for marshbuff %p, marshoff %p, functions name %s and tocopy %p.\n", marshbuf, marshoff, function_name, tocopy);
#endif
    if (tocopy == 0)
    {
        PRINT ("fill_marshbuf_ptr: Don't pass a NULL value.  Things are going fail.\n");
        TERMINATE();
    }
    
    //validate_pointer (tocopy);
    //full_slab_verify();
    // The mouse device copies a size_t as a void * (sigh!)
    //validate_pointer (*(const void **) tocopy);
    fill_marshbuf (function_name, marshbuf, marshoff, tocopy, ptrsz);
}