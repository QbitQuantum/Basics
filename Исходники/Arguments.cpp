double Arguments::asDouble(int index) const {
    return atof(argList[index].c_str());
}