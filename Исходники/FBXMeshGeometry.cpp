void ResolveVertexDataArray(std::vector<T>& data_out, const Scope& source, 
	const std::string& MappingInformationType,
	const std::string& ReferenceInformationType,
	const char* dataElementName,
	const char* indexDataElementName,
	size_t vertex_count,
	const std::vector<unsigned int>& mapping_counts,
	const std::vector<unsigned int>& mapping_offsets,
	const std::vector<unsigned int>& mappings)
{
	std::vector<T> tempUV;
	ParseVectorDataArray(tempUV,GetRequiredElement(source,dataElementName));

	// handle permutations of Mapping and Reference type - it would be nice to
	// deal with this more elegantly and with less redundancy, but right
	// now it seems unavoidable.
	if (MappingInformationType == "ByVertice" && ReferenceInformationType == "Direct") {	
		data_out.resize(vertex_count);
		for (size_t i = 0, e = tempUV.size(); i < e; ++i) {

			const unsigned int istart = mapping_offsets[i], iend = istart + mapping_counts[i];
			for (unsigned int j = istart; j < iend; ++j) {
				data_out[mappings[j]] = tempUV[i];
			}
		}
	}
	else if (MappingInformationType == "ByVertice" && ReferenceInformationType == "IndexToDirect") {	
		data_out.resize(vertex_count);

		std::vector<int> uvIndices;
		ParseVectorDataArray(uvIndices,GetRequiredElement(source,indexDataElementName));

		for (size_t i = 0, e = uvIndices.size(); i < e; ++i) {

			const unsigned int istart = mapping_offsets[i], iend = istart + mapping_counts[i];
			for (unsigned int j = istart; j < iend; ++j) {
				if(static_cast<size_t>(uvIndices[i]) >= tempUV.size()) {
					DOMError("index out of range",&GetRequiredElement(source,indexDataElementName));
				}
				data_out[mappings[j]] = tempUV[uvIndices[i]];
			}
		}
	}
	else if (MappingInformationType == "ByPolygonVertex" && ReferenceInformationType == "Direct") {	
		if (tempUV.size() != vertex_count) {
			FBXImporter::LogError(Formatter::format("length of input data unexpected for ByPolygon mapping: ") 
				<< tempUV.size() << ", expected " << vertex_count
			);
			return;
		}

		data_out.swap(tempUV);
	}
	else if (MappingInformationType == "ByPolygonVertex" && ReferenceInformationType == "IndexToDirect") {	
		data_out.resize(vertex_count);

		std::vector<int> uvIndices;
		ParseVectorDataArray(uvIndices,GetRequiredElement(source,indexDataElementName));

		if (uvIndices.size() != vertex_count) {
			FBXImporter::LogError("length of input data unexpected for ByPolygonVertex mapping");
			return;
		}

		unsigned int next = 0;
		BOOST_FOREACH(int i, uvIndices) {
			if(static_cast<size_t>(i) >= tempUV.size()) {
				DOMError("index out of range",&GetRequiredElement(source,indexDataElementName));
			}

			data_out[next++] = tempUV[i];
		}
	}