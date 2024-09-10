xml_element* XMLRPC_to_xml_element_worker(XMLRPC_VALUE current_vector, XMLRPC_VALUE node, 
                                          XMLRPC_REQUEST_TYPE request_type, int depth) {
#define BUF_SIZE 512
   xml_element* root = NULL;
   if (node) {
      char buf[BUF_SIZE];
      XMLRPC_VALUE_TYPE type = XMLRPC_GetValueType(node);
      XMLRPC_VECTOR_TYPE vtype = XMLRPC_GetVectorType(node);
      xml_element* elem_val = xml_elem_new();

      /* special case for when root element is not an array */
      if (depth == 0 && 
          !(type == xmlrpc_vector && 
            vtype == xmlrpc_vector_array && 
            request_type == xmlrpc_request_call) ) {
         int bIsFault = (vtype == xmlrpc_vector_struct && XMLRPC_VectorGetValueWithID(node, ELEM_FAULTCODE));

         xml_element* next_el = XMLRPC_to_xml_element_worker(NULL, node, request_type, depth + 1);
         if (next_el) {
            Q_PushTail(&elem_val->children, next_el);
         }
         elem_val->name = strdup(bIsFault ? ELEM_FAULT : ELEM_PARAMS);
        }
        else {
         switch (type) {
            case xmlrpc_empty: //  treat null value as empty string in xmlrpc.
         case xmlrpc_string:
            elem_val->name = strdup(ELEM_STRING);
            simplestring_addn(&elem_val->text, XMLRPC_GetValueString(node), XMLRPC_GetValueStringLen(node));
            break;
         case xmlrpc_int:
            elem_val->name = strdup(ELEM_INT);
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueInt(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_boolean:
            elem_val->name = strdup(ELEM_BOOLEAN);
            snprintf(buf, BUF_SIZE, "%i", XMLRPC_GetValueBoolean(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_double:
            elem_val->name = strdup(ELEM_DOUBLE);
            snprintf(buf, BUF_SIZE, "%f", XMLRPC_GetValueDouble(node));
            simplestring_add(&elem_val->text, buf);
            break;
         case xmlrpc_datetime:
            elem_val->name = strdup(ELEM_DATETIME);
            simplestring_add(&elem_val->text, XMLRPC_GetValueDateTime_ISO8601(node));
            break;
         case xmlrpc_base64:
            {
               struct buffer_st buf;
               elem_val->name = strdup(ELEM_BASE64);
               base64_encode(&buf, XMLRPC_GetValueBase64(node), XMLRPC_GetValueStringLen(node));
               simplestring_addn(&elem_val->text, buf.data, buf.offset );
               buffer_delete(&buf);
            }
            break;
         case xmlrpc_vector:
            {
               XMLRPC_VECTOR_TYPE my_type = XMLRPC_GetVectorType(node);
               XMLRPC_VALUE xIter = XMLRPC_VectorRewind(node);
               xml_element* root_vector_elem = elem_val;

               switch (my_type) {
               case xmlrpc_vector_array:
                  {
                      if(depth == 0) {
                         elem_val->name = strdup(ELEM_PARAMS);
                      }
                      else {
                         /* Hi my name is Dave and I like to make things as confusing
                          * as possible, thus I will throw in this 'data' element
                          * where it absolutely does not belong just so that people
                          * cannot code arrays and structs in a similar and straight
                          * forward manner. Have a good day.
                          *
                          * GRRRRRRRRR!
                          */
                         xml_element* data = xml_elem_new();
                         data->name = strdup(ELEM_DATA);
    
                         elem_val->name = strdup(ELEM_ARRAY);
                         Q_PushTail(&elem_val->children, data);
                         root_vector_elem = data;
                      }
                  }
                  break;
               case xmlrpc_vector_mixed:       /* not officially supported */
               case xmlrpc_vector_struct:
                  elem_val->name = strdup(ELEM_STRUCT);
                  break;
               default:
                  break;
               }

               /* recurse through sub-elements */
               while ( xIter ) {
                  xml_element* next_el = XMLRPC_to_xml_element_worker(node, xIter, request_type, depth + 1);
                  if (next_el) {
                     Q_PushTail(&root_vector_elem->children, next_el);
                  }
                  xIter = XMLRPC_VectorNext(node);
               }
            }
            break;
         default:
            break;
         }
      }

      {
         XMLRPC_VECTOR_TYPE vtype = XMLRPC_GetVectorType(current_vector);

         if (depth == 1) {
            xml_element* value = xml_elem_new();
            value->name = strdup(ELEM_VALUE);

            /* yet another hack for the "fault" crap */
            if (XMLRPC_VectorGetValueWithID(node, ELEM_FAULTCODE)) {
               root = value;
                }
                else {
               xml_element* param = xml_elem_new();
               param->name = strdup(ELEM_PARAM);

               Q_PushTail(&param->children, value);

               root = param;
            }
            Q_PushTail(&value->children, elem_val);
            }
            else if (vtype == xmlrpc_vector_struct || vtype == xmlrpc_vector_mixed) {
            xml_element* member = xml_elem_new();
            xml_element* name = xml_elem_new();
            xml_element* value = xml_elem_new();

            member->name = strdup(ELEM_MEMBER);
            name->name = strdup(ELEM_NAME);
            value->name = strdup(ELEM_VALUE);

            simplestring_add(&name->text, XMLRPC_GetValueID(node));

            Q_PushTail(&member->children, name);
            Q_PushTail(&member->children, value);
            Q_PushTail(&value->children, elem_val);

            root = member;
            }
            else if (vtype == xmlrpc_vector_array) {
            xml_element* value = xml_elem_new();

            value->name = strdup(ELEM_VALUE);

            Q_PushTail(&value->children, elem_val);

            root = value;
            }
            else if (vtype == xmlrpc_vector_none) {
            /* no parent.  non-op */
            root = elem_val;
            }
            else {
            xml_element* value = xml_elem_new();

            value->name = strdup(ELEM_VALUE);

            Q_PushTail(&value->children, elem_val);

            root = value;
         }
      }
   }
   return root;
}