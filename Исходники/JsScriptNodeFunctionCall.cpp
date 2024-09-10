ScriptValue
ScriptNodeFunctionCall::execute(
   ScriptExecutionContext* theContext)
{
   try
   {
      theContext->countNodeExecution(this);
      ScriptValue fctRef = functionM->execute(theContext);
      ScriptObject* object = fctRef.getBase();

      // Create argument array
      ScriptValueArray arguments;
      arguments.reserve(argumentListM.size());

      // Evaluate function call arguments
      for (ScriptNodeArray::iterator iter = argumentListM.begin();
           iter != argumentListM.end();
           iter++)
      {
         ScriptValue result((*iter)->execute(theContext));
         if (result.getDataType() == ScriptValue::ReferenceE)
         {
            result = result.getReferenceValue();
         }
         arguments.push_back(result);
      }

      const std::string fctName = fctRef.getPropertyName();

      theContext->traceFunctionCall(object, fctName, arguments);
      
      if (object != 0)
      {
         return object->call(fctName, 
                             theContext, 
                             arguments, 
                             isConstructorM);
      }
      else
      {
         ScriptValue fct = fctRef.getValue();
         if (fct.getDataType() != ScriptValue::ObjectE)
         {
            std::string errorMessage("Identifier '");
            errorMessage += fctName;
            errorMessage += "' does not refer to a function."; 
            throw ScriptTypeError(errorMessage, getFile(), getLine());
         }
         object = fct.toObject();
         if (object->getObjectType() != ScriptObject::FunctionE)
         {
            std::string errorMessage("Identifier '");
            errorMessage += fctName;
            errorMessage += "' does not refer to a function."; 
            throw ScriptTypeError(errorMessage, getFile(), getLine());
         }
         
         ScriptObjectActivation* activationObject = new ScriptObjectActivation;
         
         if (isConstructorM == false)
         {
            // Function is not used as a constructor. 
            theContext->addObjectToScopeChain(activationObject);
            
            ScriptValue result(object->call(theContext, arguments));
            
            theContext->removeObjectFromScopeChain();
            
            return result;      
         }
         else
         {
            // Function is used as a constructor.
            // Create a new object
            ScriptObject* newObject = new ScriptObject(ScriptObject::ObjectE);
            ScriptValue result(newObject);
            newObject->putProperty(
               PrototypeC,
               ScriptValue(object),
               ScriptProperty::DontEnumE | 
               ScriptProperty::DontDeleteE | 
               ScriptProperty::ReadOnlyE);
            
            activationObject->putProperty(ThisC, newObject);
            
            theContext->addObjectToScopeChain(activationObject);
            
            object->call(theContext, arguments);
            
            theContext->removeObjectFromScopeChain();
            
            return result;      
         }
      }
   }
   catch (ScriptReferenceError& e)
   {
      if (e.getLine() == 0)
      {
         e.setLineAndFile(getLine(), getFile());
      }
      throw e;
   }
   catch (ScriptTypeError& e)
   {
      if (e.getLine() == 0)
      {
         e.setLineAndFile(getLine(), getFile());
      }
      throw e;
   }
   catch (ScriptUserDefinedException& e)
   {
      if (e.getLine() == 0)
      {
         e.setLineAndFile(getLine(), getFile());
      }
      throw e;
   }
}