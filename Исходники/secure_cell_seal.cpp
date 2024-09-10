void SecureCellSeal::encrypt(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
    themis_status_t status = THEMIS_FAIL;
    SecureCellSeal* obj = Nan::ObjectWrap::Unwrap<SecureCellSeal>(args.This());
    if (args.Length() < 1) {
        ThrowParameterError("Secure Cell (Seal) failed to encrypt",
                            "not enough arguments, expected message");
        args.GetReturnValue().SetUndefined();
        return;
    }
    if (!args[0]->IsUint8Array()) {
        ThrowParameterError("Secure Cell (Seal) failed to encrypt",
                            "message is not a byte buffer, use ByteBuffer or Uint8Array");
        args.GetReturnValue().SetUndefined();
        return;
    }
    if (node::Buffer::Length(args[0]) == 0) {
        ThrowParameterError("Secure Cell (Seal) failed to encrypt", "message is empty");
        args.GetReturnValue().SetUndefined();
        return;
    }
    size_t length = 0;
    const uint8_t* context = NULL;
    size_t context_length = 0;
    if (args.Length() == 2) {
        if (!args[1]->IsUint8Array()) {
            ThrowParameterError("Secure Cell (Seal) failed to encrypt",
                                "context is not a byte buffer, use ByteBuffer or Uint8Array");
            args.GetReturnValue().SetUndefined();
            return;
        }
        context = (const uint8_t*)(node::Buffer::Data(args[1]));
        context_length = node::Buffer::Length(args[1]);
    }
    status = themis_secure_cell_encrypt_seal(&(obj->key_)[0],
                                             obj->key_.size(),
                                             context,
                                             context_length,
                                             (const uint8_t*)(node::Buffer::Data(args[0])),
                                             node::Buffer::Length(args[0]),
                                             NULL,
                                             &length);
    if (status != THEMIS_BUFFER_TOO_SMALL) {
        ThrowError("Secure Cell (Seal) failed to encrypt", status);
        args.GetReturnValue().SetUndefined();
        return;
    }
    uint8_t* data = (uint8_t*)(malloc(length));
    status = themis_secure_cell_encrypt_seal(&(obj->key_)[0],
                                             obj->key_.size(),
                                             context,
                                             context_length,
                                             (const uint8_t*)(node::Buffer::Data(args[0])),
                                             node::Buffer::Length(args[0]),
                                             data,
                                             &length);
    if (status != THEMIS_SUCCESS) {
        ThrowError("Secure Cell (Seal) failed to encrypt", status);
        free(data);
        args.GetReturnValue().SetUndefined();
        return;
    }
    args.GetReturnValue().Set(Nan::NewBuffer((char*)(data), length).ToLocalChecked());
}