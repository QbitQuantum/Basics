// prime_server stuff
worker_t::result_t Paparazzi::work (const std::list<zmq::message_t>& job, void* request_info){
    //false means this is going back to the client, there is no next stage of the pipeline
    worker_t::result_t result{false};

    //this type differs per protocol hence the void* fun
    auto& info = *static_cast<http_request_t::info_t*>(request_info);

    // Try to generate a response 
    http_response_t response;
    try {
        // double start_call = getTime();

        //TODO: 
        //   - actually use/validate the request parameters
        auto request = http_request_t::from_string(static_cast<const char*>(job.front().data()), job.front().size());

        if (request.path == "/check") {
            // ELB check
            response = http_response_t(200, "OK", "OK", headers_t{CORS, TXT_MIME});
        } else {
            //  SCENE
            //  ---------------------
            auto scene_itr = request.query.find("scene");
            if (scene_itr == request.query.cend() || scene_itr->second.size() == 0) {
                // If there is NO SCENE QUERY value 
                if (request.body.empty()) 
                    // if there is not POST body content return error...
                    throw std::runtime_error("scene is required punk");

                // ... other whise load content
                setSceneContent(request.body);
                // The size of the custom scene is unique enough
                result.heart_beat = std::to_string(request.body.size());
            }
            else {
                // If there IS a SCENE QUERRY value load it
                setScene(scene_itr->second.front());
                result.heart_beat = scene_itr->second.front();
            }

            bool size_and_pos = true;
            float pixel_density = 1.0f;

            //  SIZE
            //  ---------------------
            auto width_itr = request.query.find("width");
            if (width_itr == request.query.cend() || width_itr->second.size() == 0)
                size_and_pos = false;
            auto height_itr = request.query.find("height");
            if (height_itr == request.query.cend() || height_itr->second.size() == 0)
                size_and_pos = false;
            auto density_itr = request.query.find("density");
            if (density_itr != request.query.cend() && density_itr->second.size() > 0)
                pixel_density = fmax(1.,std::stof(density_itr->second.front()));
            //  POSITION
            //  ---------------------
            auto lat_itr = request.query.find("lat");
            if (lat_itr == request.query.cend() || lat_itr->second.size() == 0)
                size_and_pos = false;
            auto lon_itr = request.query.find("lon");
            if (lon_itr == request.query.cend() || lon_itr->second.size() == 0)
                size_and_pos = false;
            auto zoom_itr = request.query.find("zoom");
            if (zoom_itr == request.query.cend() || zoom_itr->second.size() == 0)
                size_and_pos = false;
            

            if (size_and_pos) {
                // Set Map and OpenGL context size
                setSize(std::stoi(width_itr->second.front()), std::stoi(height_itr->second.front()), pixel_density);
                setPosition(std::stod(lon_itr->second.front()), std::stod(lat_itr->second.front()));
                setZoom(std::stof(zoom_itr->second.front()));
            } else {
                const std::regex re("\\/(\\d*)\\/(\\d*)\\/(\\d*)\\.png");
                std::smatch match;

                if (std::regex_search(request.path, match, re) && match.size() == 4) {
                    setSize(256,256, pixel_density);

                    int tile_coord[3] = {0,0,0};
                    for (int i = 0; i < 3; i++) {
                        std::istringstream cur(match.str(i+1));
                        cur >> tile_coord[i];
                    }
                    futile_coord_s tile;
                    tile.z = tile_coord[0];
                    setZoom(tile.z);

                    tile.x = tile_coord[1];
                    tile.y = tile_coord[2];
                    futile_bounds_s bounds;
                    futile_coord_to_bounds(&tile, &bounds);

                    setPosition(bounds.minx + (bounds.maxx-bounds.minx)*0.5,bounds.miny + (bounds.maxy-bounds.miny)*0.5);
                }
                else {
                    throw std::runtime_error("not enought data to construct image");
                }
            }

            //  OPTIONAL tilt and rotation
            //  ---------------------
            auto tilt_itr = request.query.find("tilt");
            if (tilt_itr != request.query.cend() && tilt_itr->second.size() != 0) {
                // If TILT QUERRY is provided assigned ...
                setTilt(std::stof(tilt_itr->second.front()));
            }
            else {
                // othewise use default (0.)
                setTilt(0.0f);
            }

            auto rotation_itr = request.query.find("rotation");
            if (rotation_itr != request.query.cend() && rotation_itr->second.size() != 0) {
                // If ROTATION QUERRY is provided assigned ...
                setRotation(std::stof(rotation_itr->second.front()));
            }
            else {
                // othewise use default (0.)
                setRotation(0.0f);
            }

            // Time to render
            //  ---------------------
            std::string image;
            if (m_map) {
                update();

                // Render Tangram Scene
                m_aab->bind();
                m_map->render();
                m_aab->unbind();
   
                // Once the main FBO is draw take a picture
                m_aab->getPixelsAsString(image);
                // double total_time = getTime()-start_call;
                // LOG("TOTAL CALL: %f", total_time);
                // LOG("TOTAL speed: %f millisec per pixel", (total_time/((m_width * m_height)/1000.0)));
            }

            response = http_response_t(200, "OK", image, headers_t{CORS, PNG_MIME});
        }