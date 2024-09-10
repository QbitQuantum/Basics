int PNNRange(LSH* lsh, value query, int P,value* array) {

    int i=0;
    int hashSize=0;
    hashTable neighbors;
    double* distArr=NULL;

    for (i = 0; i < lsh->L; i++) {

        //gets bucket where the value is
        List bucketList = GetListHashTable(lsh->tables[i].tables,
                                           &query, lsh->tables[i].GConfiguration);
        hashSize+=SizeList(bucketList);
    }
    InitHashTable(&neighbors,hashSize,sizeof(value),NULL,
                  data.distance,hashFunc,NULL);

    for (i = 0; i < lsh->L; i++) {


        //gets bucket where the value is
        List bucketList = GetListHashTable(lsh->tables[i].tables,
                                           &query, lsh->tables[i].GConfiguration);
        value* lValue = GetFirst(bucketList);
        //get all neighbours in range an place them in a list
        while (lValue != NULL) {
            InsertHashTable(neighbors, lValue,NULL);
            lValue = GetNext(bucketList);
        }
    }
    value** hashArr=malloc( GetHashSize(neighbors) * sizeof(value*));
    // WARNING //
    HashToArr(neighbors,(void**)hashArr);
    distArr=malloc(GetHashSize(neighbors)*sizeof(double));


    for(i=0; i<GetHashSize(neighbors); i++) {
        distArr[i]=data.distance(hashArr[i],&query);
    }

    QuickSortValue(distArr, hashArr,  GetHashSize(neighbors));

    for(i=0; (i<P && i<GetHashSize(neighbors)-1 ); i++) {
        array[i]=*hashArr[i+1];
    }
    DestroyHashTable(&neighbors);
    free(hashArr);
    free(distArr);
    return i;
}