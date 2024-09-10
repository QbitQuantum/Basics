		SEM::Value GetStaticMethod(Context& context, SEM::Value rawValue, const String& methodName, const Debug::SourceLocation& location) {
			auto value = derefOrBindValue(context, std::move(rawValue));
			assert(value.type()->isRef() && value.type()->isBuiltInReference());
			assert(value.type()->refTarget()->isStaticRef());
			const auto targetType = value.type()->refTarget()->staticRefTarget()->resolveAliases();
			
			if (!targetType->isObjectOrTemplateVar()) {
				throw ErrorException(makeString("Cannot get static method '%s' for non-object type '%s' at position %s.",
					methodName.c_str(), targetType->toString().c_str(), location.toString().c_str()));
			}
			
			const auto methodSet = getTypeMethodSet(context, targetType);
			
			const auto canonicalMethodName = CanonicalizeMethodName(methodName);
			const auto methodIterator = methodSet->find(canonicalMethodName);
			
			if (methodIterator == methodSet->end()) {
				throw ErrorException(makeString("Cannot find static method '%s' for type '%s' at position %s.",
					methodName.c_str(),
					targetType->toString().c_str(),
					location.toString().c_str()));
			}
			
			const auto& methodElement = methodIterator->second;
			
			if (!methodElement.isStatic()) {
				throw ErrorException(makeString("Cannot call non-static method '%s' for type '%s' at position %s.",
					methodName.c_str(),
					targetType->toString().c_str(),
					location.toString().c_str()));
			}
			
			if (targetType->isObject()) {
				// Get the actual function so we can refer to it.
				const auto& function = targetType->getObjectType()->functions().at(canonicalMethodName);
				const auto functionTypeTemplateMap = targetType->generateTemplateVarMap();
				
				const auto functionType = simplifyFunctionType(context, function->type().substitute(functionTypeTemplateMap));
				const auto functionRefType = createFunctionPointerType(context, functionType);
				
				auto functionRef = addDebugInfo(SEM::Value::FunctionRef(targetType, function.get(), {}, functionRefType), location);
				
				if (targetType->isInterface()) {
					const auto interfaceMethodType = createStaticInterfaceMethodType(context, functionType);
					return addDebugInfo(SEM::Value::StaticInterfaceMethodObject(std::move(functionRef), std::move(value), interfaceMethodType), location);
				} else {
					return functionRef;
				}
			} else {
				const bool isTemplated = true;
				const auto functionType = createFunctionPointerType(context, methodElement.createFunctionType(isTemplated));
				return addDebugInfo(SEM::Value::TemplateFunctionRef(targetType, methodName, functionType), location);
			}
		}