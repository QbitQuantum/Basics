static void *jit_jni_trampoline(struct compilation_unit *cu)
{
	struct vm_method *method = cu->method;
	struct buffer *buf;
	void *target;

	target = vm_jni_lookup_method(method->class->name, method->name, method->type);
	if (!target) {
		signal_new_exception(vm_java_lang_UnsatisfiedLinkError, "%s.%s%s",
				     method->class->name, method->name, method->type);
		return rethrow_exception();
	}