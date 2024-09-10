JSObjectRef JSFunction::MakeFunction(const JSContext& js_context, const JSString& body, const std::vector<JSString>& parameter_names, const JSString& function_name, const JSString& source_url, int starting_line_number) {
	JSValueRef exception { nullptr };
	JSStringRef source_url_ref = (source_url.length() > 0) ? static_cast<JSStringRef>(source_url) : nullptr;
	JSObjectRef js_object_ref = nullptr;
	if (!parameter_names.empty()) {
		std::vector<JSStringRef> parameter_name_array = detail::to_vector(parameter_names);
		js_object_ref = JSObjectMakeFunction(static_cast<JSContextRef>(js_context), static_cast<JSStringRef>(function_name), static_cast<unsigned>(parameter_name_array.size()), &parameter_name_array[0], static_cast<JSStringRef>(body), source_url_ref, starting_line_number, &exception);
	} else {
		js_object_ref = JSObjectMakeFunction(static_cast<JSContextRef>(js_context), static_cast<JSStringRef>(function_name), 0, nullptr, static_cast<JSStringRef>(body), source_url_ref, starting_line_number, &exception);
	}
	
	if (exception) {
		// If this assert fails then we need to JSValueUnprotect
		// js_object_ref.
		assert(!js_object_ref);
		detail::ThrowRuntimeError("JSFunction", JSValue(js_context, exception));
	}

	return js_object_ref;
}