std::string ObjLoader::LoadObj(shapes_t& shapes, const char* filename, const char* mtl_basepath)
{
    shapes.reset();
    
    std::stringstream err;
    std::istringstream ifs(FileUtils::getInstance()->getStringFromFile(filename));
    std::map<vertex_index, ssize_t> vertexCache;
    //std::ifstream ifs(filename);
    
    if (!ifs)
    {
        err << "Cannot open file [" << filename << "]" << std::endl;
        return err.str();
    }
    
    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;
    std::vector<std::vector<vertex_index> > faceGroup;
    std::string name;
    
    // material
    std::map<std::string, material_t> material_map;
    material_t material;
    
    int maxchars = 8192;  // Alloc enough size.
    std::vector<char> buf(maxchars);  // Alloc enough size.
    while (ifs.peek() != -1)
    {
        ifs.getline(&buf[0], maxchars);
        
        std::string linebuf(&buf[0]);
        
        // Trim newline '\r\n' or '\r'
        if (linebuf.size() > 0)
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        if (linebuf.size() > 0)
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        
        // Skip if empty line.
        if (linebuf.empty())
        {
            continue;
        }
        
        // Skip leading space.
        const char* token = linebuf.c_str();
        token += strspn(token, " \t");
        
        assert(token);
        if (token[0] == '\0') continue; // empty line
        
        if (token[0] == '#') continue;  // comment line
        
        // vertex
        if (token[0] == 'v' && isSpace((token[1])))
        {
            token += 2;
            float x, y, z;
            parseFloat3(x, y, z, token);
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            continue;
        }
        
        // normal
        if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2])))
        {
            token += 3;
            float x, y, z;
            parseFloat3(x, y, z, token);
            vn.push_back(x);
            vn.push_back(y);
            vn.push_back(z);
            continue;
        }
        
        // texcoord
        if (token[0] == 'v' && token[1] == 't' && isSpace((token[2])))
        {
            token += 3;
            float x, y;
            parseFloat2(x, y, token);
            vt.push_back(x);
            vt.push_back(y);
            continue;
        }
        
        // face
        if (token[0] == 'f' && isSpace((token[1])))
        {
            token += 2;
            token += strspn(token, " \t");
            
            std::vector<vertex_index> face;
            while (!isNewLine(token[0])) {
                // fix warning, cast to int, i think int is enough
                vertex_index vi = parseTriple(token, (int)v.size() / 3, (int)vn.size() / 3, (int)vt.size() / 2);
                face.push_back(vi);
                auto n = strspn(token, " \t\r");
                token += n;
            }
            
            faceGroup.push_back(face);
            
            continue;
        }
        
        // use mtl
        if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6])))
        {
            
            char namebuf[4096];
            token += 7;
            sscanf(token, "%s", namebuf);
            
            if (material_map.find(namebuf) != material_map.end())
            {
                material = material_map[namebuf];
            }
            else
            {
                // { error!! material not found }
                InitMaterial(material);
            }
            continue;
            
        }
        
        // load mtl
        if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6])))
        {
            char namebuf[4096];
            token += 7;
            sscanf(token, "%s", namebuf);
            
            std::string err_mtl = LoadMtl(material_map, namebuf, mtl_basepath);
            if (!err_mtl.empty())
            {
                faceGroup.clear();  // for safety
                //return err_mtl;
            }
            continue;
        }
        
        // group name
        if (token[0] == 'g' && isSpace((token[1])))
        {
            // flush previous face group.
            shape_t shape;
            exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
            
            faceGroup.clear();
            
            std::vector<std::string> names;
            while (!isNewLine(token[0]))
            {
                std::string str = parseString(token);
                names.push_back(str);
                token += strspn(token, " \t\r"); // skip tag
            }
            
            assert(names.size() > 0);
            
            // names[0] must be 'g', so skipt 0th element.
            if (names.size() > 1)
            {
                name = names[1];
            }
            else
            {
                name = "";
            }
            
            continue;
        }
        
        // object name
        if (token[0] == 'o' && isSpace((token[1])))
        {
            // flush previous face group.
            shape_t shape;
            exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
            
            faceGroup.clear();
            
            // @todo { multiple object name? }
            char namebuf[4096];
            token += 2;
            sscanf(token, "%s", namebuf);
            name = std::string(namebuf);
            
            continue;
        }
        
        // Ignore unknown command.
    }
    
    shape_t shape;
    exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
    faceGroup.clear();  // for safety
    
    return err.str();
}