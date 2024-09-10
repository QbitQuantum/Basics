 void ArrayObject::ThrowItemNotConfigurableError(PropertyId propId /*= Constants::NoProperty*/)
 {
     ScriptContext* scriptContext = GetScriptContext();
     JavascriptError::ThrowTypeError(scriptContext, JSERR_DefineProperty_NotConfigurable,
         propId != Constants::NoProperty ?
             scriptContext->GetThreadContext()->GetPropertyName(propId)->GetBuffer() : nullptr);
 }