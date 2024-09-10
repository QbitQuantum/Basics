void SmiSmpsIO::writeTimeFile(const char* filename, const char* extension, const bool strictFormat) {
    std::string fnWithExt = filename;
    fnWithExt.append(".").append(extension);
    CoinFileOutput* output = CoinFileOutput::create(fnWithExt, CoinFileOutput::COMPRESS_NONE);

    std::stringstream line;
    line.fill(' ');
    line << "TIME          " << this->getModProblemName() << "\nPERIODS\n";
    
    for (int stg = 0; stg < core->getNumStages(); stg++) {
        line << "    ";
        if (core->getColStart(stg) == core->getNumCols())
            line << std::setw(10) << std::left << "RHS"; // if this stage has no columns, it may have some RHS values
        else if (strictFormat)
            line << std::setw(10) << std::left << this->columnName(core->getColStart(stg));
        else
            line << this->columnName(core->getColStart(stg)) << " ";
        line << std::setw(25) << std::left << this->rowName(core->getRowStart(stg));
        line << "STAGE_" << stg << "\n";
    }
    line << "ENDATA\n";
    output->puts(line.str());        
    delete output;
}