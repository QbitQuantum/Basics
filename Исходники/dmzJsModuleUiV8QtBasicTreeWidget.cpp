dmz::V8Value
dmz::JsModuleUiV8QtBasic::_tree_resize_col_contents (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QTreeWidget *tree = self->v8_to_qobject<QTreeWidget> (Args.This ());
      if (tree && Args.Length ()) { tree->resizeColumnToContents (v8_to_uint32 (Args[0])); }
   }

   return scope.Close (result);
}