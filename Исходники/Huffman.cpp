int main() {
    string command;
    ibstream infile;
    obstream outfile;
    Encoding huffman;
    while(true){
        infile.clear();
        outfile.clear();
        getLine("compress(c) or decompress(d)", command);
        if(command == "c"){
            huffman.compress(infile, outfile);
        }else if(command == "d"){
            huffman.decompress(infile, outfile);
        }else if(command == "exit")
            break;
        else{
            cout << "invalid command" << endl;
        }
    }
    return 0;
}