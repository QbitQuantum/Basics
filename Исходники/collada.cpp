int ColladaParser::load( const char* filename, Scene* scene ) {

  ifstream in( filename );
  if ( !in.is_open() ) {
    return -1;
  } in.close();
  
  XMLDocument doc;
  doc.LoadFile( filename );
  if ( doc.Error() ) {
    doc.PrintError();
    exit( 1 );
  }

  XMLElement* root = doc.FirstChildElement("COLLADA");
  if ( !root ) {
    stat("Error: not a COLLADA file!")
    exit( 1 );
  } else {
    stat("Loading COLLADA file...");
  }

  // save COLLADA library entry points
  e_scenes     = root->FirstChildElement("library_visual_scenes");
  e_cameras    = root->FirstChildElement("library_cameras"      );
  e_lights     = root->FirstChildElement("library_lights"       );
  e_geometries = root->FirstChildElement("library_geometries"   );
  e_materials  = root->FirstChildElement("library_materials"    );
  e_effects    = root->FirstChildElement("library_effects"      );

  // load assets
  XMLElement* e_asset = root->FirstChildElement("asset");
  if ( e_asset ) {

    // NOTE (sky):
    // We probably should take care of different Y directions here if we want
    // to support exports from different packages.
    XMLElement* up_axis = e_asset->FirstChildElement("up_axis");
    stat("Y direction: "<< up_axis->GetText());
  }

  // load scenes -
  XMLElement* e_scene = root->FirstChildElement("scene");
  if ( e_scene ) {

    XMLElement* e_instance = e_scene->FirstChildElement("instance_visual_scene");

    // NOTE (sky):
    // COLLADA seems to support multiple scenes in one file
    // right now the parser only loads the first scene

    // load all scenes
    // while (e_instance) {
    //   // load a single scene
    //   e_instance = e_scene->NextSiblingElement("instance_visual_scene");
    // }

    // load first scene
    if (e_instance) {

      const char* instance_url = e_instance->Attribute("url");
      if ( instance_url ) {

        // look for scene in scene library
        string instance_id = instance_url + 1;
        XMLElement* e_instance = find_instance( e_scenes, instance_id );
        if ( e_instance ) {
          stat("Loading scene: " << instance_id);
          
          parseScene(e_instance, *scene);
        } else {
          stat("Error: undefined scene instance: " << instance_id);
          return -1;
        }

      } else {

        // Note (Sky):
        // not sure if there are non-indirection encodings but
        // if there is then it should be handled here
        return 0;

      }
    }
  }

  return 0;

}