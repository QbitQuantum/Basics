void _VMClass_add_instance_primitive(void* _self, pVMPrimitive value, bool warn) {
    pVMClass self = (pVMClass)_self;
    if(SEND(self, add_instance_invokable, (pVMObject)value) && warn) {
        pVMSymbol sym = TSEND(VMInvokable, value, get_signature);
        debug_warn("Primitive %s is not in class definition for class %s.\n",
                   sym->chars,
                   self->name->chars);
    }
}