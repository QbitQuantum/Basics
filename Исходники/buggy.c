int main(){

  //count[x][y] stores the no. of times we observe the letter y after letter x.
  int count[26][26];

  //initialize the count 2D array to zeros.
  int i, j;
  for(i = 0; i < 26; i++){
    for(j = 0; j < 26; j++){
      count[i][j] = 0;
    }
  }

  // Do the counting.
  int x, y, c;
  x = getchar();
  while( (c = getchar()) != EOF){
    y = c;
    if ((isLower(x)) && (isLower(y))){
      count[x-'a'][y-'a']++;//xとyは読み取った文字のASCIIコードだから、-'a'をつけた後は入るべき配列の位置を表す。
      }
    x = y;
  }

  //print the non-zero counts.
  for(i = 0; i < 26; i++){
    for(j = 0; j < 26; j++){
      if (count[i][j] > 0){
	printf("count[%c][%c] = %d\n", (i + 'a'), (j + 'a'), count[i][j]);
      }
    }
  }
  return 0;
}