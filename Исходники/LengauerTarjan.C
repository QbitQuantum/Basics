uint32_t LengauerTarjan::EVAL(uint32_t vertexV){
    if(ancestor[vertexV] == 0){
        return label[vertexV];
    }
    COMPRESS(vertexV);
    if(semi[label[ancestor[vertexV]]] >= semi[label[vertexV]]){
        return label[vertexV];
    }
    return label[ancestor[vertexV]];
}