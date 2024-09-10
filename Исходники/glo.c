/**
 * Group:
 *     C
 *
 * Function:
 *     Gua_Status Glo_FunctionWrapper(void *nspace, Gua_Short argc, Gua_Object *argv, Gua_Object *object, Gua_String error)
 *
 * Description:
 *     Function wrapper.
 *
 * Arguments:
 *     nspace,    a pointer to a structure Gua_Namespace. Must do a cast before use it;
 *     argc,      the number of arguments to pass to the function;
 *     argv,      an array containing the arguments to the function;
 *                argv[0] is the function name;
 *     object,    a structure containing the return object of the function;
 *     error,     a pointer to the error message.
 *
 * Results:
 *     The return object of the wrapped function.
 */
Gua_Status Glo_FunctionWrapper(void *nspace, Gua_Short argc, Gua_Object *argv, Gua_Object *object, Gua_String error)
{
    GLint arg2i;
    GLint arg3i;
    GLfloat arg3f;
    GLMmodel *model;
    GLuint model_list;
    Gua_Object o;
    FILE *fp;
    Gua_String errMessage;
    
    arg2i = 0;
    arg3f = 0.0;
    model = NULL;
    model_list = 0;
    
    if (argc == 0) {
        errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
        sprintf(errMessage, "%s\n", "no function specified");
        strcat(error, errMessage);
        Gua_Free(errMessage);

        return GUA_ERROR;
    }
    
    /**
     * Group:
     *     Scripting
     *
     * Function:
     *     gloLoadObj(file, modifiers, degree)
     *
     * Description:
     *      Load an OBJ file and returns an OpenGL list.
     *
     * Examples:
     *     output == annProcess(ann, input, dim_in_j, dim_out_j).
     */
    if (strcmp(Gua_ObjectToString(argv[0]), "gloLoadObj") == 0) {
        if (argc != 4) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "wrong number of arguments for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        if (Gua_ObjectType(argv[1]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 1 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (!((Gua_ObjectType(argv[2]) == OBJECT_TYPE_INTEGER) || (Gua_ObjectType(argv[2]) == OBJECT_TYPE_REAL))) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 2 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (!((Gua_ObjectType(argv[3]) == OBJECT_TYPE_INTEGER) || (Gua_ObjectType(argv[3]) == OBJECT_TYPE_REAL))) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 3 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        if (Gua_ObjectType(argv[2]) == OBJECT_TYPE_INTEGER) {
            arg2i = Gua_ObjectToInteger(argv[2]);
        } else if (Gua_ObjectType(argv[2]) == OBJECT_TYPE_REAL) {
            arg2i = roundl(Gua_ObjectToReal(argv[2]));            
        }
        if (Gua_ObjectType(argv[3]) == OBJECT_TYPE_INTEGER) {
            arg3f = Gua_ObjectToInteger(argv[3]);
        } else if (Gua_ObjectType(argv[3]) == OBJECT_TYPE_REAL) {
            arg3f = Gua_ObjectToReal(argv[3]);            
        }
        
        /*
         * Reads the model data, defines its vertices normals
         * and create an OpenGL list to reference the object.
         */
        model = glmReadOBJ(Gua_ObjectToString(argv[1]));
        glmUnitize(model);
        glmFacetNormals(model);
        glmVertexNormals(model, arg3f);
        model_list = glmList(model, arg2i);
        
        Gua_IntegerToPObject(object, model_list);
    /**
     * Group:
     *     Scripting
     *
     * Function:
     *     gloLoadPPM(file, "width", "height")
     *
     * Description:
     *      Load a PPM image file.
     *
     * Examples:
     *     texture = gloLoadPPM($texture_file, "texture_width", "texture_height").
     */
    } else if (strcmp(Gua_ObjectToString(argv[0]), "gloLoadPPM") == 0) {
        if (argc != 4) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "wrong number of arguments for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        if (Gua_ObjectType(argv[1]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 1 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (Gua_ObjectType(argv[2]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 1 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (Gua_ObjectType(argv[3]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 1 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        Gua_LinkByteArrayToPObject(object, (Gua_String)Glo_LoadPPM(Gua_ObjectToString(argv[1]), &arg2i, &arg3i), arg2i * arg3i * 3);
        
        Gua_IntegerToObject(o, arg2i);
        Gua_SetStoredObject(o);
        if (Gua_SetVariable((Gua_Namespace *)nspace, Gua_ObjectToString(argv[2]), &o, SCOPE_STACK) != GUA_OK) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "can't set variable", Gua_ObjectToString(argv[2]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
        }
        
        Gua_IntegerToObject(o, arg3i);
        Gua_SetStoredObject(o);
        if (Gua_SetVariable((Gua_Namespace *)nspace, Gua_ObjectToString(argv[3]), &o, SCOPE_STACK) != GUA_OK) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "can't set variable", Gua_ObjectToString(argv[3]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
        }
    /**
     * Group:
     *     Scripting
     *
     * Function:
     *     gloSavePPM(texture, file, width, height)
     *
     * Description:
     *      Save a PPM image file.
     *
     * Examples:
     *     gloSavePPM(texture, "/tmp/texture.ppm", $texture_width, $texture_height).
     */
    } else if (strcmp(Gua_ObjectToString(argv[0]), "gloSavePPM") == 0) {
        if (argc != 5) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "wrong number of arguments for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        if (Gua_ObjectType(argv[1]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 1 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (Gua_ObjectType(argv[2]) != OBJECT_TYPE_STRING) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 2 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (!((Gua_ObjectType(argv[3]) == OBJECT_TYPE_INTEGER) || (Gua_ObjectType(argv[3]) == OBJECT_TYPE_REAL))) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 3 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        if (!((Gua_ObjectType(argv[4]) == OBJECT_TYPE_INTEGER) || (Gua_ObjectType(argv[4]) == OBJECT_TYPE_REAL))) {
            errMessage = (Gua_String) Gua_Alloc(sizeof(char) * MAX_ERROR_MSG_SIZE + 1);
            sprintf(errMessage, "%s %-.20s...\n", "illegal argument 4 for function", Gua_ObjectToString(argv[0]));
            strcat(error, errMessage);
            Gua_Free(errMessage);
            
            return GUA_ERROR;
        }
        
        /*
         * Open the PPM image file.
         */
        fp = fopen(Gua_ObjectToString(argv[2]), "w+");
        
        if (fp != NULL) {
            /*
             * Writes the PPM file header.
             */
            fputs("P6\n", fp);
            fprintf(fp, "%ld %ld\n", Gua_ObjectToInteger(argv[3]), Gua_ObjectToInteger(argv[4]));
            fputs("255\n", fp);
            
            /*
             * Writes the raw image data.
             */
            fwrite(Gua_ObjectToString(argv[1]), sizeof(char), Gua_ObjectToInteger(argv[3]) * Gua_ObjectToInteger(argv[4]) * 3, fp);
            
            fclose(fp);
        }
    }
    
    return GUA_OK;
}