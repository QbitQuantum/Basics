      bool deserialize(JsonNode& root, Render2d& render)
      {
         
         render.shadow = root["shadow"].Cast<bool>();
         render.billboard = root["billboard"].Cast<bool>();
            
         for(auto& node : root["sprites"].Children())
         {
            auto& sprite = node.second;
            Texture* texture = m_resource_manager->get_texture(m_resource_manager->load_texture("data/" + sprite["texture"].Cast<std::string>()));

            Sprite& new_sprite = render.add_sprite(node.first,
                  Vec3f {deserialize_vec2f(sprite["position"]),
                  (float)sprite["depth"].Cast<int>() / 1000.0f},
                  deserialize_vec2f(sprite["size"]), texture->id());

            new_sprite.crop.position = deserialize_vec2i(sprite["crop"]["0"]);
            new_sprite.crop.size = deserialize_vec2i(sprite["crop"]["1"]);

            new_sprite.crop.position = new_sprite.crop.position / texture->sizef();
            new_sprite.crop.size = new_sprite.crop.size / texture->sizef();

            texture->set_wrap_mode(Texture::Repeat, Texture::Repeat);

            texture->bind();
            texture->setup();
            texture->release();

         }

         return true;
      }