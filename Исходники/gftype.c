boolean 
dochar ( void ) 
{
  /* 9998 9999 */ register boolean Result; eightbits o  ;
  integer p, q  ;
  boolean aok  ;
  aok = true ;
  while ( true ) {
      
    a = curloc ;
    o = getbyte () ;
    p = firstpar ( o ) ;
    if ( eof ( gffile ) ) 
    {
      fprintf ( stderr , "%s%s%c\n",  "Bad GF file: " , "the file ended prematurely" , '!'       ) ;
      uexit ( 1 ) ;
    } 
    if ( o <= 67 ) 
    {
      if ( wantsmnemonics ) 
      Fputs ( stdout ,  " paint " ) ;
      do {
	  if ( wantsmnemonics ) { 
	  if ( paintswitch == 0 ) 
	  fprintf ( stdout , "%c%ld%c",  '(' , (long)p , ')' ) ;
	  else
	  fprintf ( stdout , "%ld",  (long)p ) ;
	} 
	m = m + p ;
	if ( m > maxmobserved ) 
	maxmobserved = m - 1 ;
	if ( wantspixels ) {
	    
	  if ( paintswitch == 1 ) {
	      
	    if ( n <= maxrow ) 
	    {
	      l = m - p ;
	      r = m - 1 ;
	      if ( r > maxcol ) 
	      r = maxcol ;
	      m = l ;
	      while ( m <= r ) {
		  
		imagearray [m + ( maxcol + 1 ) * n ]= 1 ;
		m = m + 1 ;
	      } 
	      m = l + p ;
	    } 
	  } 
	} 
	paintswitch = 1 - paintswitch ;
	a = curloc ;
	o = getbyte () ;
	p = firstpar ( o ) ;
	if ( eof ( gffile ) ) 
	{
	  fprintf ( stderr , "%s%s%c\n",  "Bad GF file: " , "the file ended prematurely" ,           '!' ) ;
	  uexit ( 1 ) ;
	} 
      } while ( ! ( o > 67 ) ) ;
    } 
    switch ( o ) 
    {case 70 : 
    case 71 : 
    case 72 : 
    case 73 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%ld%c%ld",  (long)a , ": " , "skip" , (long)( o - 70 ) % 4 , ' ' , (long)p ) ;
	} 
	n = n + p + 1 ;
	m = 0 ;
	paintswitch = 0 ;
	if ( wantsmnemonics ) 
	fprintf ( stdout , "%s%ld%c",  " (n=" , (long)maxnstated - n , ')' ) ;
      } 
      break ;
    case 74 : 
    case 75 : 
    case 76 : 
    case 77 : 
    case 78 : 
    case 79 : 
    case 80 : 
    case 81 : 
    case 82 : 
    case 83 : 
    case 84 : 
    case 85 : 
    case 86 : 
    case 87 : 
    case 88 : 
    case 89 : 
    case 90 : 
    case 91 : 
    case 92 : 
    case 93 : 
    case 94 : 
    case 95 : 
    case 96 : 
    case 97 : 
    case 98 : 
    case 99 : 
    case 100 : 
    case 101 : 
    case 102 : 
    case 103 : 
    case 104 : 
    case 105 : 
    case 106 : 
    case 107 : 
    case 108 : 
    case 109 : 
    case 110 : 
    case 111 : 
    case 112 : 
    case 113 : 
    case 114 : 
    case 115 : 
    case 116 : 
    case 117 : 
    case 118 : 
    case 119 : 
    case 120 : 
    case 121 : 
    case 122 : 
    case 123 : 
    case 124 : 
    case 125 : 
    case 126 : 
    case 127 : 
    case 128 : 
    case 129 : 
    case 130 : 
    case 131 : 
    case 132 : 
    case 133 : 
    case 134 : 
    case 135 : 
    case 136 : 
    case 137 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%ld",  (long)a , ": " , "newrow " , (long)p ) ;
	} 
	n = n + 1 ;
	m = p ;
	paintswitch = 1 ;
	if ( wantsmnemonics ) 
	fprintf ( stdout , "%s%ld%c",  " (n=" , (long)maxnstated - n , ')' ) ;
      } 
      break ;
    case 138 : 
    case 139 : 
    case 140 : 
    case 141 : 
    case 142 : 
    case 143 : 
    case 144 : 
    case 145 : 
    case 146 : 
    case 147 : 
    case 148 : 
    case 149 : 
    case 150 : 
    case 151 : 
    case 152 : 
    case 153 : 
    case 154 : 
    case 155 : 
    case 156 : 
    case 157 : 
    case 158 : 
    case 159 : 
    case 160 : 
    case 161 : 
    case 162 : 
    case 163 : 
    case 164 : 
    case 165 : 
    case 166 : 
    case 167 : 
    case 168 : 
    case 169 : 
    case 170 : 
    case 171 : 
    case 172 : 
    case 173 : 
    case 174 : 
    case 175 : 
    case 176 : 
    case 177 : 
    case 178 : 
    case 179 : 
    case 180 : 
    case 181 : 
    case 182 : 
    case 183 : 
    case 184 : 
    case 185 : 
    case 186 : 
    case 187 : 
    case 188 : 
    case 189 : 
    case 190 : 
    case 191 : 
    case 192 : 
    case 193 : 
    case 194 : 
    case 195 : 
    case 196 : 
    case 197 : 
    case 198 : 
    case 199 : 
    case 200 : 
    case 201 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%ld",  (long)a , ": " , "newrow " , (long)p ) ;
	} 
	n = n + 1 ;
	m = p ;
	paintswitch = 1 ;
	if ( wantsmnemonics ) 
	fprintf ( stdout , "%s%ld%c",  " (n=" , (long)maxnstated - n , ')' ) ;
      } 
      break ;
    case 202 : 
    case 203 : 
    case 204 : 
    case 205 : 
    case 206 : 
    case 207 : 
    case 208 : 
    case 209 : 
    case 210 : 
    case 211 : 
    case 212 : 
    case 213 : 
    case 214 : 
    case 215 : 
    case 216 : 
    case 217 : 
    case 218 : 
    case 219 : 
    case 220 : 
    case 221 : 
    case 222 : 
    case 223 : 
    case 224 : 
    case 225 : 
    case 226 : 
    case 227 : 
    case 228 : 
    case 229 : 
    case 230 : 
    case 231 : 
    case 232 : 
    case 233 : 
    case 234 : 
    case 235 : 
    case 236 : 
    case 237 : 
    case 238 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%ld",  (long)a , ": " , "newrow " , (long)p ) ;
	} 
	n = n + 1 ;
	m = p ;
	paintswitch = 1 ;
	if ( wantsmnemonics ) 
	fprintf ( stdout , "%s%ld%c",  " (n=" , (long)maxnstated - n , ')' ) ;
      } 
      break ;
    case 244 : 
      if ( wantsmnemonics ) 
      {
	putc ('\n',  stdout );
	fprintf ( stdout , "%ld%s%s",  (long)a , ": " , "no op" ) ;
      } 
      break ;
    case 247 : 
      {
	{
	  fprintf ( stdout , "%ld%s%s%s",  (long)a , ": " , "! " ,           "preamble command within a character!" ) ;
	  putc ('\n',  stdout );
	} 
	goto lab9998 ;
      } 
      break ;
    case 248 : 
    case 249 : 
      {
	{
	  fprintf ( stdout , "%ld%s%s%s",  (long)a , ": " , "! " ,           "postamble command within a character!" ) ;
	  putc ('\n',  stdout );
	} 
	goto lab9998 ;
      } 
      break ;
    case 67 : 
    case 68 : 
      {
	{
	  fprintf ( stdout , "%ld%s%s%s",  (long)a , ": " , "! " , "boc occurred before eoc!" ) ;
	  putc ('\n',  stdout );
	} 
	goto lab9998 ;
      } 
      break ;
    case 69 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s",  (long)a , ": " , "eoc" ) ;
	} 
	putc ('\n',  stdout );
	goto lab9999 ;
      } 
      break ;
    case 239 : 
    case 240 : 
    case 241 : 
    case 242 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s",  (long)a , ": " , "xxx '" ) ;
	} 
	badchar = false ;
	b = 16 ;
	if ( p < 0 ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%s",  (long)a , ": " , "! " , "string of negative length!" ) ;
	  putc ('\n',  stdout );
	} 
	while ( p > 0 ) {
	    
	  q = getbyte () ;
	  if ( ( q < 32 ) || ( q > 126 ) ) 
	  badchar = true ;
	  if ( wantsmnemonics ) 
	  {
	    putc ( xchr [q ],  stdout );
	    if ( b < linelength ) 
	    b = b + 1 ;
	    else {
		
	      putc ('\n',  stdout );
	      b = 2 ;
	    } 
	  } 
	  p = p - 1 ;
	} 
	if ( wantsmnemonics ) 
	putc ( '\'' ,  stdout );
	if ( badchar ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%s",  (long)a , ": " , "! " ,           "non-ASCII character in xxx command!" ) ;
	  putc ('\n',  stdout );
	} 
      } 
      break ;
    case 243 : 
      {
	if ( wantsmnemonics ) 
	{
	  putc ('\n',  stdout );
	  fprintf ( stdout , "%ld%s%s%ld%s",  (long)a , ": " , "yyy " , (long)p , " (" ) ;
	} 
	if ( wantsmnemonics ) 
	{
	  printscaled ( p ) ;
	  putc ( ')' ,  stdout );
	} 
      } 
      break ;
      default: 
      {
	fprintf ( stdout , "%ld%s%s%s%ld%c",  (long)a , ": " , "! " , "undefined command " , (long)o , '!' ) ;
	putc ('\n',  stdout );
      } 
      break ;
    } 
  } 
  lab9998: { putc ( '!' ,  stdout );  putc ( '\n',  stdout ); }
  aok = false ;
  lab9999: Result = aok ;
  return Result ;
} 