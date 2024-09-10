 v8::Local<v8::Value> DISubprogram::Create(llvm::DISubprogram* llvm_disubprogram) {
   Nan::EscapableHandleScope scope;
   Local<Object> new_instance = Nan::NewInstance(Nan::New(DISubprogram::constructor_func)).ToLocalChecked();
   DISubprogram* new_disubprogram = new DISubprogram(llvm_disubprogram);
   new_disubprogram->Wrap(new_instance);
   return scope.Escape(new_instance);
 }