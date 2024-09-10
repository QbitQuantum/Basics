bool AndroidExporter::ExportMainFile(gd::Project& project,
                                     gd::String outputDir) {
  gd::String layoutFunctionDeclarations;
  gd::String functionAssignmentCode;

  for (std::size_t i = 0; i < project.GetLayoutsCount(); ++i) {
    auto layout = project.GetLayout(i);
    gd::String layoutFunctionName =
        "GDSceneEvents" +
        gd::SceneNameMangler::GetMangledSceneName(layout.GetName());

    gd::EventsCodeGenerator codeGenerator(project, layout, CppPlatform::Get());
    layoutFunctionDeclarations += "extern \"C\" int  " + layoutFunctionName +
                                  "(RuntimeContext * runtimeContext);\n";
    functionAssignmentCode += "\t\tif (scene.GetName() == \"" +
                              codeGenerator.ConvertToString(layout.GetName()) +
                              "\") function = &" + layoutFunctionName + ";\n";
  }

  gd::String mainFile = fs.ReadFile(GetAndroidProjectPath() + "/jni/main.cpp")
                            .FindAndReplace("/* GDCPP_EVENTS_DECLARATIONS */",
                                            layoutFunctionDeclarations)
                            .FindAndReplace("/* GDCPP_EVENTS_ASSIGNMENTS */",
                                            functionAssignmentCode);

  return fs.WriteToFile(outputDir + "/jni/main.cpp", mainFile);
}