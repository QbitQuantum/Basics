 Car(const FunctionCallbackInfo<Value> &info)
 {
     /* This constructor requires at least one argument.
      Calling Signature:
      Car(string format [, int km [, int ... ]] )
      
      It can reminds us the add() method in the functions_v8_args.cpp example.
      */
     
     if (info.Length() == 0)
     {
         throw std::runtime_error("The add function must receive at least one argument.");
     }
     
     if (!JsToNative(Isolate::GetCurrent(), this->m_color, info[0]))
     {
         throw std::runtime_error("The first constructor argument must be a string (car color).");
     }
     
     this->m_km = 0;
     for (int i = 1; i < info.Length(); i++)
     {
         if (!info[i]->IsInt32())
         {
             throw std::runtime_error("All of the function passed arguments should be integers.");
         }
         
         this->m_km += info[i]->Int32Value();
     }
 }