/** 
 *
 * Initialize a VMArray
 *
 */
void _VMArray_init(void* _self, ...) {
    pVMArray self = (pVMArray)_self;
    
    va_list args;
    va_start(args, _self);
    size_t fields = SEND(self, _get_offset) + va_arg(args, size_t);
    va_end(args);
    SUPER(VMObject, _self, init, fields);
}