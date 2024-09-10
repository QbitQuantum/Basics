// JsExtV8Archive Interface
dmz::V8Value
dmz::JsExtV8Archive::_archive_observe (
      const v8::Arguments &Args,
      JsExtV8Archive &self,
      HashTableHandleTemplate<CallbackTable> &preTable,
      HashTableHandleTemplate<CallbackTable> &table,
      HashTableHandleTemplate<CallbackTable> &postTable) {

   v8::HandleScope scope;

   V8Value result = v8::Undefined ();

   if (self._core) {

      const int Length = Args.Length ();

      V8Object obj = v8_to_object (Args[0]);
      const Handle Instance (self._core->get_instance_handle (obj));
      const String Name (self._core->get_instance_name (obj));
      Handle archive (self._defaultArchive);
      String type;
      V8Function func;

      if (Length == 2) { func = v8_to_function (Args[1]); }
      else if (Length == 3) {

         archive = self._to_handle (Args[1]);
         func = v8_to_function (Args[2]);
      }
      else if (Length >= 4) {

         archive = self._to_handle (Args[1]);
         type = v8_to_string (Args[2]);
         func = v8_to_function (Args[3]);
      }

      if (self._register_callback (
            Instance,
            Name,
            archive,
            obj,
            func,
            (type == LocalPre ? preTable : (type == LocalPost ? postTable : table)))) {

         result = func;
      }
   }

   return scope.Close (result);
}