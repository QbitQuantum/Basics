//==================================================================
//
//  Parses a string strting from linestart
//  and continues to read till a null terminator is found
//
//  Takes regards to the provided linetype_t type, and interprets
//  the contents accordingly
//
//  (ex: If a line contains v, parse a vertex)
//
//  Parameters:
//          char* linestart: Start pointer of string
//          linetype_t: Type of line (eg vertex, normal, face, etc)
//          int* out: currently not used.
//
//  Returns 0 upon success, -1 upon fail. If fail, see FileParser::GetError()
//
//==================================================================
int OBJFileParser::ParseData(char* linestart, linetype_t type, int* out)
{
    bool useOut = false;
    if(out != nullptr)
        useOut = true;
    
    char buff[255];
    strcpy(buff, linestart);
    
    switch (type) {
        case LT_VERTEX:
        {
            //vertex layout: v x y z
            char* content = ParseFindNext(buff);
            if(!content)
            {
                this->error = FP_ERROR_SYNTAX;
                return -1;
            }
            
            char* end = nullptr;
            
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec3D.x = tempVal;
            
            content = ParseFindNext(content);
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec3D.y = tempVal;
            
            content = ParseFindNext(content);
            tempVal = strtof(content, &end);
            
            tempVec3D.z = tempVal;
            
            temp_vertices.push_back(tempVec3D);
            
            break;
        }
            
            
        case LT_TEXTURECOORD:
        {
            //tc layout: vt u v
            char* content = ParseFindNext(buff);
            if(!content)
            {
                this->error = FP_ERROR_SYNTAX;
                return -1;
            }
            
            char* end = nullptr;
            
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec2D.x = tempVal;
            
            content = ParseFindNext(content);
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec2D.y = tempVal;
            
            temp_texcoords.push_back(tempVec2D);
            
            break;
        }
            
        case LT_NORMAL:
        {
            char* content = ParseFindNext(buff);
            if(!content)
            {
                this->error = FP_ERROR_SYNTAX;
                return -1;
            }
            
            char* end = nullptr;
            
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec3D.x = tempVal;
            
            content = ParseFindNext(content);
            tempVal = strtof(content, &end);
            content = end;
            
            tempVec3D.y = tempVal;
            
            content = ParseFindNext(content);
            tempVal = strtof(content, &end);
            
            tempVec3D.z = tempVal;
            
            temp_normals.push_back(tempVec3D);
            break;
        }
            
        case LT_FACE:
        {
            face_t face;
            for(char* ptr = buff; *ptr != '\0'; ptr++)
            {
                indice_group_t group;
                char* end;
                
                char* val = ParseFindNext(ptr);
                if(!val)
                    break;
                
                group.vertex = (int)strtof(val, &end);
                val = end;
                
                if(*val == '/' && *(val + 1) != '/')
                {
                    group.textureCoord = (int)strtof((val + 1), &end);
                } else
                {
                    group.textureCoord = -1;
                }
                
                val = end;
                
                if(*val == '/')
                {
                    group.normal = (int)strtof((val + 1), &end);
                } else
                {
                    group.normal = -1;
                }
                val = end;
                
                ptr = val;
                
                face.indiceGroups.push_back(group);
                
            }
            
            temp_faces.push_back(face);
            break;
        }
            
        default:
            break;
    }
    
    return 0;
}