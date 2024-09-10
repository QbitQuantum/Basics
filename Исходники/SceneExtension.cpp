            virtual std::string GenerateCode(gd::Instruction & instruction, gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext & context)
            {
                std::string value1Code;
                {
                    gd::CallbacksForGeneratingExpressionCode callbacks(value1Code, codeGenerator, context);
                    gd::ExpressionParser parser(instruction.GetParameters()[0].GetPlainString());
                    if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || value1Code.empty()) value1Code = "0";
                }

                std::string value2Code;
                {
                    gd::CallbacksForGeneratingExpressionCode callbacks(value2Code, codeGenerator, context);
                    gd::ExpressionParser parser(instruction.GetParameters()[2].GetPlainString());
                    if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || value2Code.empty()) value2Code = "0";
                }

                std::string resultingBoolean = codeGenerator.GenerateBooleanFullName("conditionTrue", context)+".val";

                if ( instruction.GetParameters()[1].GetPlainString() == "=" || instruction.GetParameters()[1].GetPlainString().empty() )
                    return resultingBoolean + " = ("+value1Code+" == "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == ">")
                    return resultingBoolean + " = ("+value1Code+" > "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "<")
                    return resultingBoolean + " = ("+value1Code+" < "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "<=")
                    return resultingBoolean + " = ("+value1Code+" <= "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == ">=")
                    return resultingBoolean + " = ("+value1Code+" >= "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "!=")
                    return resultingBoolean + " = ("+value1Code+" != "+value2Code+");\n";

                return "";
            };