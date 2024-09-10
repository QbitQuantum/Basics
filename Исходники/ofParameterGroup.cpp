ofAbstractParameter & ofParameterGroup::get(string name) const {
    map<string,int>::const_iterator it = obj->parametersIndex.find(escape(name));
    int index = it->second;
    return get(index);
}