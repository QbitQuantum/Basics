 void Method_init(LPCOLESTR _name, DISPID dispid) 
  {
   name= _wcsdup(_name);
   this->dispid=dispid;
   putJavaIndex= getJavaIndex=  methodJavaIndex=0;
      
  };