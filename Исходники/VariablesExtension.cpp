            virtual std::string GenerateCode(gd::Instruction & instruction, gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext & context)
            {
                std::string expressionCode;
                {
                    gd::CallbacksForGeneratingExpressionCode callbacks(expressionCode, codeGenerator, context);
                    gd::ExpressionParser parser(instruction.GetParameters()[2].GetPlainString());
                    if (!parser.ParseStringExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || expressionCode.empty())
                        expressionCode = "\"\"";
                }

                std::string varGetter;
                {
                    VariableCodeGenerationCallbacks callbacks(varGetter, codeGenerator, context, VariableCodeGenerationCallbacks::LAYOUT_VARIABLE);
                    gd::VariableParser parser(instruction.GetParameters()[0].GetPlainString());
                    if ( !parser.Parse(callbacks) )
                        varGetter = "runtimeScene.getVariables().get(\"\")";
                }

                std::string op = instruction.GetParameters()[1].GetPlainString();
                if ( op == "=" )
                    return varGetter+".setString("+expressionCode+");\n";
                else if ( op == "+" )
                    return varGetter+".concatenate("+expressionCode+");\n";

                return "";
            };