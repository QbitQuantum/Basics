 void getValue(float *value)
 {
     ptr<SceneNode> scene = manager->loadResource("scene").cast<SceneNode>();
     ptr<Module> o = find(scene, path).cast<Module>();
     if (o == NULL) {
         return;
     }
     assert(!o->getUsers().empty());
     ptr<Uniform> u = (*(o->getUsers().begin()))->getUniform(name);
     if (u != NULL) {
         vec2f v2;
         vec3f v3;
         vec4f v4;
         switch (dim) {
         case 1:
             value[0] = u.cast<Uniform1f>()->get();
             break;
         case 2:
             v2 = u.cast<Uniform2f>()->get();
             value[0] = v2.x;
             value[1] = v2.y;
             break;
         case 3:
             v3 = u.cast<Uniform3f>()->get();
             value[0] = v3.x;
             value[1] = v3.y;
             value[2] = v3.z;
             break;
         case 4:
             v4 = u.cast<Uniform4f>()->get();
             value[0] = v4.x;
             value[1] = v4.y;
             value[2] = v4.z;
             value[3] = v4.w;
             break;
         }
     }
 }