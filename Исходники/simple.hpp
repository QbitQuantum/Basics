 void operator() ( Buffer< SampleType > &_buffer ) {
   if ( is_end ) {
     fillZero ( _buffer );
     return;
   }
   double time = instrument.getGlobalTime();
   while ( !release_stack.empty() && time - release_stack.top().first >= -0.00001f ) {
     instrument.noteOff ( release_stack.top().second );
     release_stack.pop();
   }
   while ( time - current_score->pos >= -0.00001f ) {
     if ( current_score->length == 0.0f ) {
       is_end = true;
       fillZero ( _buffer );
       return;
     }
     else {
       std::pair< double, int > temp;
       temp.first = current_score->pos + current_score->length;
       temp.second = instrument.noteOn ( current_score->note, exp2f ( ( current_score->touch - 1.0f ) * 10.0f ) );
       release_stack.push ( temp );
     }
     current_score++;
   }
   instrument ( _buffer );
 }