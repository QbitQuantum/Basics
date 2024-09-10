//------------------------------------------------------------------------------
// printMessage(): Recursive function to print all fields in this message
//---------------------------------------------------------------------------
void PrintSelected::printMessage(std::ostream& soutFields, std::ostream& soutVals, const google::protobuf::Message* const msg)
{
   std::streamsize oldWidth = soutFields.width();
   std::ostream::fmtflags oldFlags = soutFields.flags();

   const google::protobuf::Descriptor* descriptor = msg->GetDescriptor();
   const google::protobuf::Reflection* reflection = msg->GetReflection();

   const google::protobuf::Message& root = *msg;
   std::string msgName = descriptor->name();

   int fieldCount = descriptor->field_count();

   const google::protobuf::FieldDescriptor* fieldDescriptor = nullptr;

   std::string msgDivider = ";   ";
   std::string fieldDivider = ", ";

   bool lastField = false;

   if (fieldCount > 0) {
      for (int i = 0; i < fieldCount; i++) {
         if ((i+1) == fieldCount) lastField = true;

         // Get field descriptor (includes messages)
         fieldDescriptor = descriptor->field(i);

         // what type is this field?
         google::protobuf::FieldDescriptor::CppType cppType = fieldDescriptor->cpp_type();

         if (cppType == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {

            // do the same again for this message, etc.
            const google::protobuf::Message& sub_message = reflection->GetMessage(root, fieldDescriptor);
            printMessage(soutFields, soutVals, &sub_message);
         }
         else {
            // not a message: Print the field
            if (reflection->HasField(root, fieldDescriptor)) {
               soutFields <<  std::left << std::setw(12) << fieldDescriptor->name(); // Field name

               // get the value
               switch (cppType) {
                  case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                     soutVals <<  std::left << std::setw(12)<<  reflection->GetString(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_INT32: {
                     soutVals <<  std::left << std::setw(12)<<  reflection->GetInt32(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_INT64: {
                     soutVals <<  std::left << std::setw(12)<< reflection->GetInt64(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_UINT32: {
                     soutVals <<  std::left << std::setw(12)<< reflection->GetUInt32(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_UINT64: {
                     soutVals <<  std::left << std::setw(12)<< reflection->GetUInt64(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE: {
                     soutVals  <<  std::left << std::setw(12)<< reflection->GetDouble(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT: {
                     soutVals  <<  std::left << std::setw(12)<< reflection->GetFloat(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_BOOL: {
                     soutVals <<  std::left << std::setw(12)<< reflection->GetBool(root, fieldDescriptor);
                     break;
                  }
                  case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                     const google::protobuf::EnumValueDescriptor* enumVal = reflection->GetEnum(root, fieldDescriptor);
                     int enumIndex = enumVal->index();
                     soutVals <<  std::left << std::setw(12)<<  enumIndex;
                     break;
                  }
                  default: {
                     soutVals << "   \t";
                     break;
                  }
               }
            }  // end if has field
            else {
               // This field had no data. We should skip it
            }
            if (lastField) {
               // print message divider
               soutFields << msgDivider;
               soutVals << msgDivider;
            }
            else {
               // print field Divider
               soutFields << fieldDivider;
               soutVals << fieldDivider;
            }
         }
      }
   }

   soutFields.width( oldWidth );
   soutFields.setf( oldFlags );
}