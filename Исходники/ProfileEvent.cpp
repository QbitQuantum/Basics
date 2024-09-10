gd::String ProfileEvent::GenerateEventCode(gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext & parentContext)
{
    const gd::Layout & scene = codeGenerator.GetLayout();
    codeGenerator.AddIncludeFile("GDCpp/BuiltinExtensions/ProfileTools.h");

    ProfileLink profileLink;
    profileLink.originalEvent = originalEvent;
    std::cout << scene.GetProfiler() << std::endl;
    if ( scene.GetProfiler() ) //Should always be not NULL
    {
        scene.GetProfiler()->profileEventsInformation.push_back(profileLink);
        index = scene.GetProfiler()->profileEventsInformation.size()-1;
    }
    gd::String code;

    if ( previousProfileEvent )
        code += "EndProfileTimer(*runtimeContext->scene, "+gd::String::From(previousProfileEvent->index)+");\n";

    code += "StartProfileTimer(*runtimeContext->scene, "+gd::String::From(index)+");\n";

    return code;
}