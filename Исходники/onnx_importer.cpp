void ONNXImporter::populateNet(Net dstNet)
{
    CV_Assert(model_proto.has_graph());
    opencv_onnx::GraphProto graph_proto = model_proto.graph();
    std::map<std::string, Mat> constBlobs = getGraphTensors(graph_proto);
    // List of internal blobs shapes.
    std::map<std::string, MatShape> outShapes;
    // Add all the inputs shapes. It includes as constant blobs as network's inputs shapes.
    for (int i = 0; i < graph_proto.input_size(); ++i)
    {
        opencv_onnx::ValueInfoProto valueInfoProto = graph_proto.input(i);
        CV_Assert(valueInfoProto.has_type());
        opencv_onnx::TypeProto typeProto = valueInfoProto.type();
        CV_Assert(typeProto.has_tensor_type());
        opencv_onnx::TypeProto::Tensor tensor = typeProto.tensor_type();
        CV_Assert(tensor.has_shape());
        opencv_onnx::TensorShapeProto tensorShape = tensor.shape();

        MatShape inpShape(tensorShape.dim_size());
        for (int j = 0; j < inpShape.size(); ++j)
        {
            inpShape[j] = tensorShape.dim(j).dim_value();
        }
        outShapes[valueInfoProto.name()] = inpShape;
    }

    std::string framework_name;
    if (model_proto.has_producer_name()) {
        framework_name = model_proto.producer_name();
    }

    // create map with network inputs (without const blobs)
    std::map<std::string, LayerInfo> layer_id;
    std::map<std::string, LayerInfo>::iterator layerId;
    std::map<std::string, MatShape>::iterator shapeIt;
    // fill map: push layer name, layer id and output id
    std::vector<String> netInputs;
    for (int j = 0; j < graph_proto.input_size(); j++)
    {
        const std::string& name = graph_proto.input(j).name();
        if (constBlobs.find(name) == constBlobs.end()) {
            netInputs.push_back(name);
            layer_id.insert(std::make_pair(name, LayerInfo(0, netInputs.size() - 1)));
        }
    }
    dstNet.setInputsNames(netInputs);

    int layersSize = graph_proto.node_size();
    LayerParams layerParams;
    opencv_onnx::NodeProto node_proto;

    for(int li = 0; li < layersSize; li++)
    {
        node_proto = graph_proto.node(li);
        layerParams = getLayerParams(node_proto);
        CV_Assert(node_proto.output_size() >= 1);
        layerParams.name = node_proto.output(0);

        std::string layer_type = node_proto.op_type();
        layerParams.type = layer_type;


        if (layer_type == "MaxPool")
        {
            layerParams.type = "Pooling";
            layerParams.set("pool", "MAX");
            layerParams.set("ceil_mode", isCeilMode(layerParams));
        }
        else if (layer_type == "AveragePool")
        {
            layerParams.type = "Pooling";
            layerParams.set("pool", "AVE");
            layerParams.set("ceil_mode", isCeilMode(layerParams));
            layerParams.set("ave_pool_padded_area", framework_name == "pytorch");
        }
        else if (layer_type == "GlobalAveragePool")
        {
            layerParams.type = "Pooling";
            layerParams.set("pool", "AVE");
            layerParams.set("global_pooling", true);
        }
        else if (layer_type == "Add" || layer_type == "Sum")
        {
            if (layer_id.find(node_proto.input(1)) == layer_id.end())
            {
                Mat blob = getBlob(node_proto, constBlobs, 1);
                blob = blob.reshape(1, 1);
                if (blob.total() == 1) {
                    layerParams.type = "Power";
                    layerParams.set("shift", blob.at<float>(0));
                }
                else {
                    layerParams.type = "Scale";
                    layerParams.set("bias_term", true);
                    layerParams.blobs.push_back(blob);
                }
            }
            else {
                layerParams.type = "Eltwise";
            }
        }
        else if (layer_type == "Sub")
        {
            Mat blob = getBlob(node_proto, constBlobs, 1);
            if (blob.total() == 1) {
                layerParams.type = "Power";
                layerParams.set("shift", -blob.at<float>(0));
            }
            else {
                layerParams.type = "Scale";
                layerParams.set("has_bias", true);
                layerParams.blobs.push_back(-1.0f * blob.reshape(1, 1));
            }
        }
        else if (layer_type == "Div")
        {
            Mat blob = getBlob(node_proto, constBlobs, 1);
            CV_Assert_N(blob.type() == CV_32F, blob.total());
            if (blob.total() == 1)
            {
                layerParams.set("scale", 1.0f / blob.at<float>(0));
                layerParams.type = "Power";
            }
            else
            {
                layerParams.type = "Scale";
                divide(1.0, blob, blob);
                layerParams.blobs.push_back(blob);
                layerParams.set("bias_term", false);
            }
        }
        else if (layer_type == "Constant")
        {
            CV_Assert(node_proto.input_size() == 0);
            CV_Assert(layerParams.blobs.size() == 1);
            constBlobs.insert(std::make_pair(layerParams.name, layerParams.blobs[0]));
            continue;
        }
        else if (layer_type == "ImageScaler")
        {
            const float scale = layerParams.has("scale") ? layerParams.get<float>("scale") : 1.0f;
            layerParams.erase("scale");

            if (layerParams.has("bias"))
            {
                layerParams.type = "Scale";
                layerParams.blobs.push_back(
                    Mat(Size(1,  layerParams.get("bias").size()), CV_32FC1, scale));

                layerParams.set("bias_term", true);
                Mat bias(1, layerParams.get("bias").size(), CV_32FC1);
                for (int j = 0; j < bias.total(); j++) {
                    bias.at<float>(0, j) = layerParams.get("bias").getRealValue(j);
                }
                layerParams.blobs.push_back(bias);
                layerParams.erase("bias");
            }
            else {
                layerParams.set("scale", scale);
                layerParams.type = "Power";
            }
        }
        else if (layer_type == "LeakyRelu")
        {
            layerParams.type = "ReLU";
            replaceLayerParam(layerParams, "alpha", "negative_slope");
        }
        else if (layer_type == "LRN")
        {
            replaceLayerParam(layerParams, "size", "local_size");
        }
        else if (layer_type == "BatchNormalization")
        {
            if (node_proto.input_size() != 5)
                CV_Error(Error::StsNotImplemented,
                         "Expected input, scale, bias, mean and var");

            layerParams.type = "BatchNorm";
            replaceLayerParam(layerParams, "epsilon", "eps");
            replaceLayerParam(layerParams, "spatial", "use_global_stats");

            Mat meanData = getBlob(node_proto, constBlobs, 3);
            Mat stdData =  getBlob(node_proto, constBlobs, 4);

            layerParams.blobs.push_back(meanData);
            layerParams.blobs.push_back(stdData);

            if (!node_proto.input(1).empty()) {
                layerParams.set("has_weight", true);
                layerParams.blobs.push_back(getBlob(node_proto, constBlobs, 1));  // weightData
            } else {
                layerParams.set("has_weight", false);
            }

            if (!node_proto.input(2).empty()) {
                layerParams.set("has_bias", true);
                layerParams.blobs.push_back(getBlob(node_proto, constBlobs, 2)); // biasData
            } else {
                layerParams.set("has_bias", false);
            }
        }
        else if (layer_type == "Gemm")
        {
            CV_Assert(node_proto.input_size() >= 2);
            layerParams.type = "InnerProduct";
            Mat weights = getBlob(node_proto, constBlobs, 1);
            int ind_num_out = 0;
            if (layerParams.has("transB") && !layerParams.get<int>("transB")) {
                transpose(weights, weights);
                ind_num_out = 1;
            }
            layerParams.blobs.push_back(weights);

            if (node_proto.input_size() == 3) {
                Mat bias = getBlob(node_proto, constBlobs, 2);
                layerParams.blobs.push_back(bias);
            }

            layerParams.set("num_output", layerParams.blobs[0].size[ind_num_out]);
            layerParams.set("bias_term", node_proto.input_size() == 3);
        }
        else if (layer_type == "MatMul")
        {
            CV_Assert(node_proto.input_size() == 2);
            layerParams.type = "InnerProduct";
            Mat blob = getBlob(node_proto, constBlobs, 1);
            layerParams.blobs.push_back(blob.t());
            layerParams.set("bias_term", false);
            layerParams.set("num_output", layerParams.blobs[0].size[0]);
        }
        else if (layer_type == "Mul")
        {
            CV_Assert(node_proto.input_size() == 2);
            if (layer_id.find(node_proto.input(1)) == layer_id.end()) {
                Mat blob = getBlob(node_proto, constBlobs, 1);
                blob = blob.reshape(1, 1);
                if (blob.total() == 1) {
                    layerParams.set("scale", blob.at<float>(0));
                    layerParams.type = "Power";
                }
                else {
                    layerParams.blobs.push_back(blob);
                    layerParams.type = "Scale";
                }
            }
            else {
                layerParams.type = "Eltwise";
                layerParams.set("operation", "prod");
            }
        }
        else if (layer_type == "Conv")
        {
            CV_Assert(node_proto.input_size() >= 2);
            layerParams.type = "Convolution";
            for (int j = 1; j < node_proto.input_size(); j++) {
                layerParams.blobs.push_back(getBlob(node_proto, constBlobs, j));
            }
            layerParams.set("num_output", layerParams.blobs[0].size[0]);
            layerParams.set("bias_term", node_proto.input_size() == 3);
        }
        else if (layer_type == "ConvTranspose")
        {
            CV_Assert(node_proto.input_size() >= 2);
            layerParams.type = "Deconvolution";
            for (int j = 1; j < node_proto.input_size(); j++) {
                layerParams.blobs.push_back(getBlob(node_proto, constBlobs, j));
            }
            layerParams.set("num_output", layerParams.blobs[0].size[1]);
            layerParams.set("bias_term", node_proto.input_size() == 3);
        }
        else if (layer_type == "Transpose")
        {
            layerParams.type = "Permute";
            replaceLayerParam(layerParams, "perm", "order");
        }
        else if (layer_type == "Unsqueeze")
        {
            CV_Assert(node_proto.input_size() == 1);
            Mat input = getBlob(node_proto, constBlobs, 0);

            DictValue axes = layerParams.get("axes");
            std::vector<int> dims;
            for (int j = 0; j < input.dims; j++) {
                dims.push_back(input.size[j]);
            }
            CV_Assert(axes.getIntValue(axes.size()-1) <= dims.size());
            for (int j = 0; j < axes.size(); j++) {
                dims.insert(dims.begin() + axes.getIntValue(j), 1);
            }

            Mat out = input.reshape(0, dims);
            constBlobs.insert(std::make_pair(layerParams.name, out));
            continue;
        }
        else if (layer_type == "Reshape")
        {
            CV_Assert(node_proto.input_size() == 2 || layerParams.has("shape"));

            if (node_proto.input_size() == 2) {
                Mat blob = getBlob(node_proto, constBlobs, 1);
                CV_Assert(blob.type() == CV_32SC1);

                if (layer_id.find(node_proto.input(0)) == layer_id.end()) {
                    Mat input = getBlob(node_proto, constBlobs, 0);
                    Mat out = input.reshape(0, static_cast<std::vector<int> >(blob));
                    constBlobs.insert(std::make_pair(layerParams.name, out));
                    continue;
                }
                layerParams.set("dim", DictValue::arrayInt<int*>(
                            blob.ptr<int>(), blob.total() ));
            }
            else {
                DictValue shape = layerParams.get("shape");
                std::vector<int> dim;
                for (int j = 0; j < shape.size(); j++) {
                    dim.push_back(shape.getIntValue(j));
                }

                if (layer_id.find(node_proto.input(0)) == layer_id.end()) {
                    Mat input = getBlob(node_proto, constBlobs, 0);
                    Mat out = input.reshape(0, dim);
                    constBlobs.insert(std::make_pair(layerParams.name, out));
                    continue;
                }
                replaceLayerParam(layerParams, "shape", "dim");
            }
        }
        else if (layer_type == "Pad")
        {
            layerParams.type = "Padding";
        }
        else if (layer_type == "Shape")
        {
            CV_Assert(node_proto.input_size() == 1);
            shapeIt = outShapes.find(node_proto.input(0));
            CV_Assert(shapeIt != outShapes.end());
            MatShape inpShape = shapeIt->second;

            Mat shapeMat(inpShape.size(), 1, CV_32S);
            for (int j = 0; j < inpShape.size(); ++j)
                shapeMat.at<int>(j) = inpShape[j];
            shapeMat.dims = 1;

            constBlobs.insert(std::make_pair(layerParams.name, shapeMat));
            continue;
        }
        else if (layer_type == "Gather")
        {
            CV_Assert(node_proto.input_size() == 2);
            CV_Assert(layerParams.has("axis"));
            Mat input = getBlob(node_proto, constBlobs, 0);
            Mat indexMat = getBlob(node_proto, constBlobs, 1);
            CV_Assert_N(indexMat.type() == CV_32S, indexMat.total() == 1);
            int index = indexMat.at<int>(0);
            int axis = layerParams.get<int>("axis");

            std::vector<cv::Range> ranges(input.dims, Range::all());
            ranges[axis] = Range(index, index + 1);

            Mat out = input(ranges);
            constBlobs.insert(std::make_pair(layerParams.name, out));
            continue;
        }
        else if (layer_type == "Concat")
        {
            bool hasVariableInps = false;
            for (int i = 0; i < node_proto.input_size(); ++i)
            {
                if (layer_id.find(node_proto.input(i)) != layer_id.end())
                {
                    hasVariableInps = true;
                    break;
                }
            }

            if (!hasVariableInps)
            {
                std::vector<Mat> inputs(node_proto.input_size()), concatenated;
                for (size_t i = 0; i < inputs.size(); ++i)
                {
                    inputs[i] = getBlob(node_proto, constBlobs, i);
                }
                Ptr<Layer> concat = ConcatLayer::create(layerParams);
                runLayer(concat, inputs, concatenated);

                CV_Assert(concatenated.size() == 1);
                constBlobs.insert(std::make_pair(layerParams.name, concatenated[0]));
                continue;
            }
        }
        else
        {
            for (int j = 0; j < node_proto.input_size(); j++) {
                if (layer_id.find(node_proto.input(j)) == layer_id.end())
                    layerParams.blobs.push_back(getBlob(node_proto, constBlobs, j));
            }
         }

         int id = dstNet.addLayer(layerParams.name, layerParams.type, layerParams);
         layer_id.insert(std::make_pair(layerParams.name, LayerInfo(id, 0)));


         std::vector<MatShape> layerInpShapes, layerOutShapes, layerInternalShapes;
         for (int j = 0; j < node_proto.input_size(); j++) {
             layerId = layer_id.find(node_proto.input(j));
             if (layerId != layer_id.end()) {
                 dstNet.connect(layerId->second.layerId, layerId->second.outputId, id, j);
                 // Collect input shapes.
                 shapeIt = outShapes.find(node_proto.input(j));
                 CV_Assert(shapeIt != outShapes.end());
                 layerInpShapes.push_back(shapeIt->second);
             }
         }

         // Compute shape of output blob for this layer.
         Ptr<Layer> layer = dstNet.getLayer(id);
         layer->getMemoryShapes(layerInpShapes, 0, layerOutShapes, layerInternalShapes);
         CV_Assert(!layerOutShapes.empty());
         outShapes[layerParams.name] = layerOutShapes[0];
     }
 }