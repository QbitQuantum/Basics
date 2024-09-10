void CSModuleWriter::GenerateManagedEnumsAndConstants(String& source)
{
    Vector<SharedPtr<JSBEnum>> enums = module_->enums_.Values();

    Indent();

    for (unsigned i = 0; i < enums.Size(); i++)
    {
        JSBEnum* jenum = enums[i];

        source += "\n";
        String line = "public enum " + jenum->GetName() + "\n";
        source += IndentLine(line);
        source += IndentLine("{\n");

        HashMap<String, String>& values = jenum->GetValues();

        HashMap<String, String>::ConstIterator itr = values.Begin();

        Indent();

        while (itr != values.End())
        {
            String name = (*itr).first_;
            String value = (*itr).second_;

            if (value.Length())
            {
                line = name + " = " + value;
            }
            else
            {
                line = name;
            }

            itr++;

            if (itr != values.End())
                line += ",";

            line += "\n";

            source += IndentLine(line);

        }

        Dedent();

        source += IndentLine("}\n");

    }

    // constants

    HashMap<String, JSBModule::Constant>& constants = module_->GetConstants();

    if (constants.Size())
    {

        source += "\n";

        String line = "public static partial class Constants\n";
        source += IndentLine(line);
        source += IndentLine("{\n");

        const Vector<String>& constantsName = constants.Keys();

        Indent();

        for (unsigned i = 0; i < constantsName.Size(); i++)
        {
            const String& cname = constantsName.At(i);

            JSBModule::Constant& constant = constants[cname];

            String managedType = GetManagedPrimitiveType(constant.type);

            String value = constant.value;

            if (!value.Length())
                continue;

            //static const unsigned M_MIN_UNSIGNED = 0x00000000;
//            /static const unsigned M_MAX_UNSIGNED = 0xffffffff;

            if (cname == "M_MIN_INT")
                value = "int.MinValue";

            if (cname == "M_INFINITY")
                value = "float.MaxValue";

            if (value == "M_MAX_UNSIGNED")
                value = "0xffffffff";

            // Input stuff

            if (module_->GetName() == "Input")
            {
                if (cname.StartsWith("KEY_"))
                {
                    if (value.Length() == 1 && (IsAlpha(value[0]) || IsDigit(value[0])))
                        value = "'" + value + "'";
                }

                // https://raw.githubusercontent.com/flibitijibibo/SDL2-CS/master/src/SDL2.cs

                if (value.StartsWith("SDL_BUTTON_") || value.StartsWith("SDL_HAT_"))
                {
                    value = "(int) SDL." + value;
                }
                else if (value.StartsWith("SDLK_"))
                {
                    value = "(int) SDL.SDL_Keycode." + value;
                }
                else if (value.StartsWith("SDL_SCANCODE_"))
                {
                    value = "(int) SDL.SDL_Scancode." + value;
                }
                else if (value.StartsWith("SDL_CONTROLLER_BUTTON_"))
                {
                    value = "(int) SDL.SDL_GameControllerButton." + value;
                }
                else if (value.StartsWith("SDL_CONTROLLER_AXIS_"))
                {
                    value = "(int) SDL.SDL_GameControllerAxis." + value;
                }
            }

            String line = "public const " + managedType + " " + cname + " = " + value;

            if (managedType == "float" && !line.EndsWith("f") && IsDigit(line[line.Length()-1]))
                line += "f";

            line += ";\n";

            source += IndentLine(line);

        }

        Dedent();

        source += "\n";
        line = "}\n";
        source += IndentLine(line);

    }

    source += "\n";

    Dedent();

}