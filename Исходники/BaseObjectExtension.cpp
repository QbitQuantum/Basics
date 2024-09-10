            virtual std::string GenerateCode(gd::Instruction & instruction, gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext & context)
            {
                std::string outputCode;

                std::vector<std::string> realObjects = codeGenerator.ExpandObjectsName(instruction.GetParameter(0).GetPlainString(), context);
                for (unsigned int i = 0;i<realObjects.size();++i)
                {
                    context.SetCurrentObject(realObjects[i]);
                    context.ObjectsListNeeded(realObjects[i]);

                    std::string newX, newY;

                    std::string expression1Code;
                    {
                        gd::CallbacksForGeneratingExpressionCode callbacks(expression1Code, codeGenerator, context);
                        gd::ExpressionParser parser(instruction.GetParameters()[2].GetPlainString());
                        if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || expression1Code.empty())
                            expression1Code = "0";
                    }

                    std::string expression2Code;
                    {
                        gd::CallbacksForGeneratingExpressionCode callbacks(expression2Code, codeGenerator, context);
                        gd::ExpressionParser parser(instruction.GetParameters()[4].GetPlainString());
                        if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || expression2Code.empty())
                            expression2Code = "0";
                    }

                    std::string op1 = instruction.GetParameter(1).GetPlainString();
                    if ( op1 == "=" || op1.empty() )
                        newX = expression1Code;
                    else if ( op1 == "/" || op1 == "*" || op1 == "-" || op1 == "+" )
                        newX = codeGenerator.GetObjectListName(realObjects[i], context)+"[i].getX() "+op1 + expression1Code;
                    else
                        return "";
                    std::string op2 = instruction.GetParameter(3).GetPlainString();
                    if ( op2 == "=" || op2.empty() )
                        newY = expression2Code;
                    else if ( op2 == "/" || op2 == "*" || op2 == "-" || op2 == "+" )
                        newY = codeGenerator.GetObjectListName(realObjects[i], context)+"[i].getY() "+op2 + expression2Code;
                    else
                        return "";

                    std::string call = codeGenerator.GetObjectListName(realObjects[i], context)+"[i].setPosition("+newX+","+newY+")";

                    outputCode += "for(var i = 0, len = "+codeGenerator.GetObjectListName(realObjects[i], context)+".length ;i < len;++i) {\n";
                    outputCode += "    "+call+";\n";
                    outputCode += "}\n";

                    context.SetNoCurrentObject();
                }

                return outputCode;
            };