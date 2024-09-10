/** read:
* read data from the current bufer to a new buffer object
* 
* @param int togo
*	bytes to be read
*
* @return object
*	New Buffer containing the read data
*/
void CJSBuffer::FxRead(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	v8::HandleScope HandleScope(v8::Isolate::GetCurrent());
	CJSBuffer* jBuffer = GetJSObject<CJSBuffer>(args.Holder());
	CBufferObj* pBuffer = jBuffer->m_pBuffer;
	if (args.Length() < 1)
	{
		args.GetIsolate()->ThrowException(v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), (uint8_t*)"Invalid Argument"));
		return;
	}

	BUFFER_TRY
	size_t ToGo = args[0]->Uint32Value();
	CBuffer Buffer(ToGo);
	Buffer.WriteData(pBuffer->ReadData(ToGo), ToGo);
	CJSObject* jObject = CJSBuffer::New(new CBufferObj(Buffer), jBuffer->m_pScript);
	args.GetReturnValue().Set(jObject->GetInstance());
	BUFFER_CATCH
}