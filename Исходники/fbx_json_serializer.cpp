void FBXJSONSerializer::serialize(const std::string& input_filename, const std::string& output_filename) {
  KFbxSdkManager* manager = KFbxSdkManager::Create();

  KFbxIOSettings* ios = KFbxIOSettings::Create(manager, IOSROOT);
  manager->SetIOSettings(ios);

  KFbxImporter* importer = KFbxImporter::Create(manager, "");

  if(!importer->Initialize(input_filename.c_str(), -1, manager->GetIOSettings())) {
    std::cerr << "failed to import %s" << input_filename << std::endl;
    std::cerr << importer->GetLastErrorString() << std::endl;
    return;
  }

  KFbxScene* scene = KFbxScene::Create(manager, "scene");
  importer->Import(scene);
  importer->Destroy();

  KFbxNode* root_node = scene->GetRootNode();
  KFbxGeometryConverter converter(root_node->GetFbxSdkManager());
    Object json_root;
    
    Array meshes;  
    this->recurse_over_model(root_node, meshes);

    json_root["meshes"] = meshes;

    std::ofstream stream(output_filename.c_str());
    Writer::Write(json_root, stream);
}