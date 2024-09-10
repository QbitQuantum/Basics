std::string Array3DEvent::CodeGenerator::Generate(gd::BaseEvent & event_, gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext &context)
{
    arr::threeDim::Array3DEvent &event = dynamic_cast<arr::threeDim::Array3DEvent&>(event_);

            // Adding needed includes
            codeGenerator.AddIncludeFile("stack");
            codeGenerator.AddIncludeFile("Array/ArrayValue.h");
            codeGenerator.AddIncludeFile("Array/Array3D.h");
            codeGenerator.AddIncludeFile("Array/ArrayTools.h");

            //Adding the main code of the event
            std::string code("// 3D-Array Iterate Event\n");

            std::string arrayNameExpr;
            gd::CallbacksForGeneratingExpressionCode callbacks(arrayNameExpr, codeGenerator, context);
            gd::ExpressionParser parser(event.GetArrayName());
            parser.ParseStringExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks);
            if (arrayNameExpr.empty()) arrayNameExpr = "\"\""; //If generation failed, we make sure output code is not empty.

            code += "arr::Array3D &currentArray = arr::ArrayManager::GetInstance()->GetArray3D(runtimeContext->scene->game, " + arrayNameExpr + ");\n";
            code += "for(unsigned int x = 0; x < currentArray.GetSize(1); x++)\n";
            code += "{\n";
            {
                code += "for(unsigned int y = 0; y < currentArray.GetSize(2); y++)\n";
                code += "{\n";
                {
                    code += "for(unsigned int z = 0; z < currentArray.GetSize(3); z++)\n";
                    code += "{\n";
                    {

                        code += "arr::ArrayManager::GetInstance()->GetArray3DEventInfo(runtimeContext->scene->game).PushNewEventInfo(x, y, z, currentArray.GetValue(x, y, z));";

                        // Generating condition/action/sub-event //
                        code += codeGenerator.GenerateConditionsListCode(event.GetConditions(), context);

                        std::string ifPredicat;
                        for (unsigned int i = 0;i<event.GetConditions().size();++i)
                        {
                            if (i!=0)
                                ifPredicat += " && ";
                            ifPredicat += "condition"+ToString(i)+"IsTrue";
                        }

                        if ( !ifPredicat.empty() ) code += "if (" +ifPredicat+ ")\n";

                        code += "{\n";
                        code += codeGenerator.GenerateActionsListCode(event.GetActions(), context);

                        if ( event.HasSubEvents() )
                        {
                            code += "\n{\n";
                            code += codeGenerator.GenerateEventsListCode(event.GetSubEvents(), context);
                            code += "}\n";
                        }

                        code += "}\n";
                        ///////////////////////////////////////////

                        code += "arr::ArrayManager::GetInstance()->GetArray3DEventInfo(runtimeContext->scene->game).PopEventInfo();";
                    }
                    code += "}\n";
                }
                code += "}\n";
            }
            code += "}\n";


            return code;
}