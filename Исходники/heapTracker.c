/* Callback for JVMTI_EVENT_CLASS_FILE_LOAD_HOOK */
static void JNICALL
cbClassFileLoadHook(jvmtiEnv *jvmti, JNIEnv* env,
                jclass class_being_redefined, jobject loader,
                const char* name, jobject protection_domain,
                jint class_data_len, const unsigned char* class_data,
                jint* new_class_data_len, unsigned char** new_class_data)
{
    enterCriticalSection(jvmti); {
        /* It's possible we get here right after VmDeath event, be careful */
        if ( !gdata->vmDead ) {

            const char * classname;

            /* Name can be NULL, make sure we avoid SEGV's */
            if ( name == NULL ) {
                classname = java_crw_demo_classname(class_data, class_data_len,
                                NULL);
                if ( classname == NULL ) {
                    fatal_error("ERROR: No classname in classfile\n");
                }
            } else {
                classname = strdup(name);
                if ( classname == NULL ) {
                    fatal_error("ERROR: Ran out of malloc() space\n");
                }
            }

            *new_class_data_len = 0;
            *new_class_data     = NULL;

            /* The tracker class itself? */
            if ( strcmp(classname, STRING(HEAP_TRACKER_class)) != 0 ) {
                jint           cnum;
                int            systemClass;
                unsigned char *newImage;
                long           newLength;

                /* Get number for every class file image loaded */
                cnum = gdata->ccount++;

                /* Is it a system class? If the class load is before VmStart
                 *   then we will consider it a system class that should
                 *   be treated carefully. (See java_crw_demo)
                 */
                systemClass = 0;
                if ( !gdata->vmStarted ) {
                    systemClass = 1;
                }

                newImage = NULL;
                newLength = 0;

                /* Call the class file reader/write demo code */
                java_crw_demo(cnum,
                    classname,
                    class_data,
                    class_data_len,
                    systemClass,
                    STRING(HEAP_TRACKER_class),
                    "L" STRING(HEAP_TRACKER_class) ";",
                    NULL, NULL,
                    NULL, NULL,
                    STRING(HEAP_TRACKER_newobj), "(Ljava/lang/Object;)V",
                    STRING(HEAP_TRACKER_newarr), "(Ljava/lang/Object;)V",
                    &newImage,
                    &newLength,
                    NULL,
                    NULL);

                /* If we got back a new class image, return it back as "the"
                 *   new class image. This must be JVMTI Allocate space.
                 */
                if ( newLength > 0 ) {
                    unsigned char *jvmti_space;

                    jvmti_space = (unsigned char *)allocate(jvmti, (jint)newLength);
                    (void)memcpy((void*)jvmti_space, (void*)newImage, (int)newLength);
                    *new_class_data_len = (jint)newLength;
                    *new_class_data     = jvmti_space; /* VM will deallocate */
                }

                /* Always free up the space we get from java_crw_demo() */
                if ( newImage != NULL ) {
                    (void)free((void*)newImage); /* Free malloc() space with free() */
                }
            }
        
            (void)free((void*)classname);
        }
    } exitCriticalSection(jvmti);
}