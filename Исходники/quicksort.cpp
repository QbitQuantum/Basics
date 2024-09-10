void quicksort( vector<int> &vec ) {

    if ( vec.size() < 2 ) {
        return;
    }

    size_t pivot = (vec.size()/2);

    vector<int> lefty;
    vector<int> righty;

    partition( vec, pivot, lefty, righty );

    quicksort( lefty );
    quicksort( righty );

    vector<int> sorted;

    sorted.insert( sorted.end(), lefty.begin(), lefty.end() );
    sorted.insert( sorted.end(), vec[pivot] );
    sorted.insert( sorted.end(), righty.begin(), righty.end() );

    vec.swap(sorted);
    return;
}