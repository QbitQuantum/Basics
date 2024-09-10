gd::String EventsCodeGenerator::GenerateExternalEventsCompleteCode(gd::Project & project, gd::ExternalEvents & events, bool compilationForRuntime)
{
    DependenciesAnalyzer analyzer(project, events);
    gd::String associatedSceneName = analyzer.ExternalEventsCanBeCompiledForAScene();
    if ( associatedSceneName.empty() || !project.HasLayoutNamed(associatedSceneName) )
    {
        std::cout << "ERROR: Cannot generate code for an external event: No unique associated scene." << std::endl;
        return "";
    }
    gd::Layout & associatedScene = project.GetLayout(project.GetLayoutPosition(associatedSceneName));

    gd::String output;

    //Prepare the global context ( Used to get needed header files )
    gd::EventsCodeGenerationContext context;
    EventsCodeGenerator codeGenerator(project, associatedScene);
    codeGenerator.PreprocessEventList(events.GetEvents());
    codeGenerator.SetGenerateCodeForRuntime(compilationForRuntime);

    //Generate whole events code
    gd::String wholeEventsCode = codeGenerator.GenerateEventsListCode(events.GetEvents(), context);

    //Generate default code around events:
    //Includes
    output += "#include <vector>\n#include <map>\n#include <string>\n#include <algorithm>\n#include <SFML/System/Clock.hpp>\n#include <SFML/System/Vector2.hpp>\n#include <SFML/Graphics/Color.hpp>\n#include \"GDCpp/RuntimeContext.h\"\n#include \"GDCpp/RuntimeObject.h\"\n";
    for ( set<gd::String>::iterator include = codeGenerator.GetIncludeFiles().begin() ; include != codeGenerator.GetIncludeFiles().end(); ++include )
        output += "#include \""+*include+"\"\n";

    //Extra declarations needed by events
    for ( set<gd::String>::iterator declaration = codeGenerator.GetCustomGlobalDeclaration().begin() ; declaration != codeGenerator.GetCustomGlobalDeclaration().end(); ++declaration )
        output += *declaration+"\n";

    output +=
    codeGenerator.GetCustomCodeOutsideMain()+
    "\n"
    "void "+EventsCodeNameMangler::Get()->GetExternalEventsFunctionMangledName(events.GetName())+"(RuntimeContext * runtimeContext)\n"
    "{\n"
	+codeGenerator.GetCustomCodeInMain()
    +wholeEventsCode+
    "return;\n"
    "}\n";

    return output;
}