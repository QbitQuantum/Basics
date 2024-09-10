 std::vector<uint8_t>
 JSZCluster::addArgument(v8::Local<v8::Value> value, const std::shared_ptr<ClusterCmdParamsBase> &cmdParam) {
     if (value->IsUint32()) {
         return cmdParam->getType().getRaw(value->ToUint32()->Value());
     }
     if (value->IsInt32()) {
         return cmdParam->getType().getRaw(value->ToInt32()->Value());
     }
     if (value->IsString()) {
         String::Utf8Value utf8Value(value);
         return cmdParam->getType().getRaw(*utf8Value);
     }
     if (value->IsArray()) {
         Local<Array> array = value.As<Array>();
         std::vector<std::string> strArray;
         for (uint32_t index = 0; index < array->Length(); index++) {
             String::Utf8Value utf8Value(array->Get(index));
             strArray.push_back(*utf8Value);
         }
         return cmdParam->getType().getRaw(strArray);
     }
     stringstream stream;
     stream << "To " << EXECUTE_CMD_BY_ID << " it is passed an invalid argument instead of type "
            << cmdParam->getZCLDataType();
     throw JSException(stream.str());
 }