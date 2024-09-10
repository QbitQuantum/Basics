void ScriptNode::updateFields() {

#ifdef SUPPORT_JSAI
	if (hasScript()) {
		JScript *jscript = getJavaNode();
		jscript->setValue(this);
		jscript->processEvent(NULL);
		jscript->getValue(this);
	}
#endif

}