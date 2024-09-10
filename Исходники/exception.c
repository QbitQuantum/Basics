static struct vm_object *
new_exception(struct vm_class *vmc, const char *message)
{
	struct vm_object *message_str;
	struct vm_method *vmm;
	struct vm_object *obj;

	obj = vm_object_alloc(vmc);
	if (!obj)
		return rethrow_exception();

	if (message == NULL)
		message_str = NULL;
	else {
		message_str = vm_object_alloc_string_from_c(message);
		if (!message_str)
			return rethrow_exception();
	}

	vmm = vm_class_get_method(vmc, "<init>", "(Ljava/lang/String;)V");
	if (vmm) {
		vm_call_method(vmm, obj, message_str);

		return obj;
	}

	vmm = vm_class_get_method(vmc, "<init>", "()V");
	if (!vmm)
		error("constructor not found for %s", vmc->name);

	vm_call_method(vmm, obj);

	return obj;
}