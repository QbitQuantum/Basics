string RomanAdder::add(){
    string result = "";
    char letterOrder[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I' };
    int size = 7;
    int i, j, index;
    bool done;
    
    normalizeAddend( _addend1, _addend1 );
    normalizeAddend( _addend2, _addend2 );
    // cout << _addend1 << " " << _addend2 << endl;
    memset( symbolCounter, 0, sizeof( int ) * LETTERS );
    countSymbols( _addend1 );
    countSymbols( _addend2 );
    simplify( symbolCounter );
    
    index = letterOrder[0] - 'A';
    for( j = 0; j < symbolCounter[index]; j++ ){
        result += letterOrder[0];
    }
    for( i = 1; i < size; i++ ){
        done = false;
        index = letterOrder[i] - 'A';
        if( i % 2 == 0 ){
            if( symbolCounter[index] == 4 ){
                result += letterOrder[i];
                result += letterOrder[i - 1];
                done = true;
            }
        }
        else if( symbolCounter[index] == 1 && symbolCounter[letterOrder[i + 1] - 'A'] == 4 ){
            result += letterOrder[i + 1];
            result += letterOrder[i - 1];
            done = true;
            i++;
        }
        if( !done ){
            for( j = 0; j < symbolCounter[index]; j++ ){
                result += letterOrder[i];
            }
        }
    }
    
    return result;
}