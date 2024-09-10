//rest just returns a pointer to the tail of 
//the list without the head
sequence* sequence::rest(){
 
// makes a new pointer called s which points to a new 
// sequence called mySQ
    sequence* s = new Sequence(mySQ[0]);
    concatenate(s);
    
    sequence* s2 = new Sequence(mySQ[0]);
    s2->concatenate(s);

    sequence* s3 = new Sequence;	//use this in homework
    s3->mySQ[0] = mySQ[0];		//something like this
    
 
    
}