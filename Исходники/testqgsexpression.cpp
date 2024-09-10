    void evaluation_data()
    {
      QTest::addColumn<QString>( "string" );
      QTest::addColumn<bool>( "evalError" );
      QTest::addColumn<QVariant>( "result" );

      // literal evaluation
      QTest::newRow( "literal null" ) << "NULL" << false << QVariant();
      QTest::newRow( "literal int" ) << "123" << false << QVariant( 123 );
      QTest::newRow( "literal double" ) << "1.2" << false << QVariant( 1.2 );
      QTest::newRow( "literal text" ) << "'hello'" << false << QVariant( "hello" );
      QTest::newRow( "literal double" ) << ".000001" << false << QVariant( 0.000001 );
      QTest::newRow( "literal double" ) << "1.0e-6" << false << QVariant( 0.000001 );
      QTest::newRow( "literal double" ) << "1e-6" << false << QVariant( 0.000001 );

      // unary minus
      QTest::newRow( "unary minus double" ) << "-1.3" << false << QVariant( -1.3 );
      QTest::newRow( "unary minus int" ) << "-1" << false << QVariant( -1 );
      QTest::newRow( "unary minus text" ) << "-'hello'" << true << QVariant();
      QTest::newRow( "unary minus null" ) << "-null" << true << QVariant();

      // arithmetics
      QTest::newRow( "plus int" ) << "1+3" << false << QVariant( 4 );
      QTest::newRow( "plus double" ) << "1+1.3" << false << QVariant( 2.3 );
      QTest::newRow( "plus with null" ) << "null+3" << false << QVariant();
      QTest::newRow( "plus invalid" ) << "1+'foo'" << true << QVariant();
      QTest::newRow( "minus int" ) << "1-3" << false << QVariant( -2 );
      QTest::newRow( "mul int" ) << "8*7" << false << QVariant( 56 );
      QTest::newRow( "div int" ) << "20/6" << false << QVariant( 3 );
      QTest::newRow( "mod int" ) << "20%6" << false << QVariant( 2 );
      QTest::newRow( "minus double" ) << "5.2-3.1" << false << QVariant( 2.1 );
      QTest::newRow( "mul double" ) << "2.1*5" << false << QVariant( 10.5 );
      QTest::newRow( "div double" ) << "11.0/2" << false << QVariant( 5.5 );
      QTest::newRow( "mod double" ) << "6.1 % 2.5" << false << QVariant( 1.1 );
      QTest::newRow( "pow" ) << "2^8" << false << QVariant( 256. );
      QTest::newRow( "division by zero" ) << "1/0" << false << QVariant();
      QTest::newRow( "division by zero" ) << "1.0/0.0" << false << QVariant();

      // comparison
      QTest::newRow( "eq int" ) << "1+1 = 2" << false << QVariant( 1 );
      QTest::newRow( "eq double" ) << "3.2 = 2.2+1" << false << QVariant( 1 );
      QTest::newRow( "eq string" ) << "'a' = 'b'" << false << QVariant( 0 );
      QTest::newRow( "eq null" ) << "2 = null" << false << QVariant();
      QTest::newRow( "eq mixed" ) << "'a' = 1" << false << QVariant( 0 );
      QTest::newRow( "ne int 1" ) << "3 != 4" << false << QVariant( 1 );
      QTest::newRow( "ne int 2" ) << "3 != 3" << false << QVariant( 0 );
      QTest::newRow( "lt int 1" ) << "3 < 4" << false << QVariant( 1 );
      QTest::newRow( "lt int 2" ) << "3 < 3" << false << QVariant( 0 );
      QTest::newRow( "gt int 1" ) << "3 > 4" << false << QVariant( 0 );
      QTest::newRow( "gt int 2" ) << "3 > 3" << false << QVariant( 0 );
      QTest::newRow( "le int 1" ) << "3 <= 4" << false << QVariant( 1 );
      QTest::newRow( "le int 2" ) << "3 <= 3" << false << QVariant( 1 );
      QTest::newRow( "ge int 1" ) << "3 >= 4" << false << QVariant( 0 );
      QTest::newRow( "ge int 2" ) << "3 >= 3" << false << QVariant( 1 );
      QTest::newRow( "lt text 1" ) << "'bar' < 'foo'" << false << QVariant( 1 );
      QTest::newRow( "lt text 2" ) << "'foo' < 'bar'" << false << QVariant( 0 );

      // is, is not
      QTest::newRow( "is null,null" ) << "null is null" << false << QVariant( 1 );
      QTest::newRow( "is not null,null" ) << "null is not null" << false << QVariant( 0 );
      QTest::newRow( "is null" ) << "1 is null" << false << QVariant( 0 );
      QTest::newRow( "is not null" ) << "1 is not null" << false << QVariant( 1 );
      QTest::newRow( "is int" ) << "1 is 1" << false << QVariant( 1 );
      QTest::newRow( "is not int" ) << "1 is not 1" << false << QVariant( 0 );
      QTest::newRow( "is text" ) << "'x' is 'y'" << false << QVariant( 0 );
      QTest::newRow( "is not text" ) << "'x' is not 'y'" << false << QVariant( 1 );

      //  logical
      QTest::newRow( "T or F" ) << "1=1 or 2=3" << false << QVariant( 1 );
      QTest::newRow( "F or F" ) << "1=2 or 2=3" << false << QVariant( 0 );
      QTest::newRow( "T and F" ) << "1=1 and 2=3" << false << QVariant( 0 );
      QTest::newRow( "T and T" ) << "1=1 and 2=2" << false << QVariant( 1 );
      QTest::newRow( "not T" ) << "not 1=1" << false << QVariant( 0 );
      QTest::newRow( "not F" ) << "not 2=3" << false << QVariant( 1 );
      QTest::newRow( "null" ) << "null=1" << false << QVariant();
      QTest::newRow( "U or F" ) << "null=1 or 2=3" << false << QVariant();
      QTest::newRow( "U and F" ) << "null=1 and 2=3" << false << QVariant( 0 );
      QTest::newRow( "invalid and" ) << "'foo' and 2=3" << true << QVariant();
      QTest::newRow( "invalid or" ) << "'foo' or 2=3" << true << QVariant();
      QTest::newRow( "invalid not" ) << "not 'foo'" << true << QVariant();

      // in, not in
      QTest::newRow( "in 1" ) << "1 in (1,2,3)" << false << QVariant( 1 );
      QTest::newRow( "in 2" ) << "1 in (1,null,3)" << false << QVariant( 1 );
      QTest::newRow( "in 3" ) << "1 in (null,2,3)" << false << QVariant();
      QTest::newRow( "in 4" ) << "null in (1,2,3)" << false << QVariant();
      QTest::newRow( "not in 1" ) << "1 not in (1,2,3)" << false << QVariant( 0 );
      QTest::newRow( "not in 2" ) << "1 not in (1,null,3)" << false << QVariant( 0 );
      QTest::newRow( "not in 3" ) << "1 not in (null,2,3)" << false << QVariant();
      QTest::newRow( "not in 4" ) << "null not in (1,2,3)" << false << QVariant();

      // regexp, like
      QTest::newRow( "like 1" ) << "'hello' like '%ll_'" << false << QVariant( 1 );
      QTest::newRow( "like 2" ) << "'hello' like 'lo'" << false << QVariant( 0 );
      QTest::newRow( "like 3" ) << "'hello' like '%LO'" << false << QVariant( 0 );
      QTest::newRow( "ilike" ) << "'hello' ilike '%LO'" << false << QVariant( 1 );
      QTest::newRow( "regexp 1" ) << "'hello' ~ 'll'" << false << QVariant( 1 );
      QTest::newRow( "regexp 2" ) << "'hello' ~ '^ll'" << false << QVariant( 0 );
      QTest::newRow( "regexp 3" ) << "'hello' ~ 'llo$'" << false << QVariant( 1 );

      // concatenation
      QTest::newRow( "concat with plus" ) << "'a' + 'b'" << false << QVariant( "ab" );
      QTest::newRow( "concat" ) << "'a' || 'b'" << false << QVariant( "ab" );
      QTest::newRow( "concat with int" ) << "'a' || 1" << false << QVariant( "a1" );
      QTest::newRow( "concat with int" ) << "2 || 'b'" << false << QVariant( "2b" );
      QTest::newRow( "concat with null" ) << "'a' || null" << false << QVariant();
      QTest::newRow( "concat numbers" ) << "1 || 2" << false << QVariant( "12" );

      // math functions
      QTest::newRow( "sqrt" ) << "sqrt(16)" << false << QVariant( 4. );
      QTest::newRow( "abs(0.1)" ) << "abs(0.1)" << false << QVariant( 0.1 );
      QTest::newRow( "abs(0)" ) << "abs(0)" << false << QVariant( 0. );
      QTest::newRow( "abs(-0.1)" ) << "abs(-0.1)" << false << QVariant( 0.1 );
      QTest::newRow( "invalid sqrt value" ) << "sqrt('a')" << true << QVariant();
      QTest::newRow( "sin 0" ) << "sin(0)" << false << QVariant( 0. );
      QTest::newRow( "cos 0" ) << "cos(0)" << false << QVariant( 1. );
      QTest::newRow( "tan 0" ) << "tan(0)" << false << QVariant( 0. );
      QTest::newRow( "asin 0" ) << "asin(0)" << false << QVariant( 0. );
      QTest::newRow( "acos 1" ) << "acos(1)" << false << QVariant( 0. );
      QTest::newRow( "atan 0" ) << "atan(0)" << false << QVariant( 0. );
      QTest::newRow( "atan2(0,1)" ) << "atan2(0,1)" << false << QVariant( 0. );
      QTest::newRow( "atan2(1,0)" ) << "atan2(1,0)" << false << QVariant( M_PI / 2 );
      QTest::newRow( "exp(0)" ) << "exp(0)" << false << QVariant( 1. );
      QTest::newRow( "exp(1)" ) << "exp(1)" << false << QVariant( exp( 1. ) );
      QTest::newRow( "ln(0)" ) << "ln(0)" << false << QVariant();
      QTest::newRow( "log10(-1)" ) << "log10(-1)" << false << QVariant();
      QTest::newRow( "ln(1)" ) << "ln(1)" << false << QVariant( log( 1. ) );
      QTest::newRow( "log10(100)" ) << "log10(100)" << false << QVariant( 2. );
      QTest::newRow( "log(2,32)" ) << "log(2,32)" << false << QVariant( 5. );
      QTest::newRow( "log(10,1000)" ) << "log(10,1000)" << false << QVariant( 3. );
      QTest::newRow( "log(-2,32)" ) << "log(-2,32)" << false << QVariant();
      QTest::newRow( "log(2,-32)" ) << "log(2,-32)" << false << QVariant();
      QTest::newRow( "log(0.5,32)" ) << "log(0.5,32)" << false << QVariant( -5. );
      QTest::newRow( "round(1234.557,2) - round up" ) << "round(1234.557,2)" << false << QVariant( 1234.56 );
      QTest::newRow( "round(1234.554,2) - round down" ) << "round(1234.554,2)" << false << QVariant( 1234.55 );
      QTest::newRow( "round(1234.6) - round up to int" ) << "round(1234.6)" << false << QVariant( 1235 );
      QTest::newRow( "round(1234.6) - round down to int" ) << "round(1234.4)" << false << QVariant( 1234 );
      QTest::newRow( "max(1)" ) << "max(1)" << false << QVariant( 1. );
      QTest::newRow( "max(1,3.5,-2.1)" ) << "max(1,3.5,-2.1)" << false << QVariant( 3.5 );
      QTest::newRow( "min(-1.5)" ) << "min(-1.5)" << false << QVariant( -1.5 );
      QTest::newRow( "min(-16.6,3.5,-2.1)" ) << "min(-16.6,3.5,-2.1)" << false << QVariant( -16.6 );
      QTest::newRow( "clamp(-2,1,5)" ) << "clamp(-2,1,5)" << false << QVariant( 1.0 );
      QTest::newRow( "clamp(-2,-10,5)" ) << "clamp(-2,-10,5)" << false << QVariant( -2.0 );
      QTest::newRow( "clamp(-2,100,5)" ) << "clamp(-2,100,5)" << false << QVariant( 5.0 );
      QTest::newRow( "floor(4.9)" ) << "floor(4.9)" << false << QVariant( 4. );
      QTest::newRow( "floor(-4.9)" ) << "floor(-4.9)" << false << QVariant( -5. );
      QTest::newRow( "ceil(4.9)" ) << "ceil(4.9)" << false << QVariant( 5. );
      QTest::newRow( "ceil(-4.9)" ) << "ceil(-4.9)" << false << QVariant( -4. );
      QTest::newRow( "scale_linear(0.5,0,1,0,1)" ) << "scale_linear(0.5,0,1,0,1)" << false << QVariant( 0.5 );
      QTest::newRow( "scale_linear(0,0,10,100,200)" ) << "scale_linear(0,0,10,100,200)" << false << QVariant( 100. );
      QTest::newRow( "scale_linear(5,0,10,100,200)" ) << "scale_linear(5,0,10,100,200)" << false << QVariant( 150. );
      QTest::newRow( "scale_linear(10,0,10,100,200)" ) << "scale_linear(10,0,10,100,200)" << false << QVariant( 200. );
      QTest::newRow( "scale_linear(-1,0,10,100,200)" ) << "scale_linear(-1,0,10,100,200)" << false << QVariant( 100. );
      QTest::newRow( "scale_linear(11,0,10,100,200)" ) << "scale_linear(11,0,10,100,200)" << false << QVariant( 200. );

      QTest::newRow( "scale_exp(0.5,0,1,0,1,2)" ) << "scale_exp(0.5,0,1,0,1,2)" << false << QVariant( 0.25 );
      QTest::newRow( "scale_exp(0,0,10,100,200,2)" ) << "scale_exp(0,0,10,100,200,2)" << false << QVariant( 100. );
      QTest::newRow( "scale_exp(5,0,10,100,200,2)" ) << "scale_exp(5,0,10,100,200,2)" << false << QVariant( 125. );
      QTest::newRow( "scale_exp(10,0,10,100,200,0.5)" ) << "scale_exp(10,0,10,100,200,0.5)" << false << QVariant( 200. );
      QTest::newRow( "scale_exp(-1,0,10,100,200,0.5)" ) << "scale_exp(-1,0,10,100,200,0.5)" << false << QVariant( 100. );
      QTest::newRow( "scale_exp(4,0,9,0,90,0.5)" ) << "scale_exp(4,0,9,0,90,0.5)" << false << QVariant( 60. );

      // cast functions
      QTest::newRow( "double to int" ) << "toint(3.2)" << false << QVariant( 3 );
      QTest::newRow( "text to int" ) << "toint('53')" << false << QVariant( 53 );
      QTest::newRow( "null to int" ) << "toint(null)" << false << QVariant();
      QTest::newRow( "int to double" ) << "toreal(3)" << false << QVariant( 3. );
      QTest::newRow( "text to double" ) << "toreal('53.1')" << false << QVariant( 53.1 );
      QTest::newRow( "null to double" ) << "toreal(null)" << false << QVariant();
      QTest::newRow( "int to text" ) << "tostring(6)" << false << QVariant( "6" );
      QTest::newRow( "double to text" ) << "tostring(1.23)" << false << QVariant( "1.23" );
      QTest::newRow( "null to text" ) << "tostring(null)" << false << QVariant();

      // string functions
      QTest::newRow( "lower" ) << "lower('HeLLo')" << false << QVariant( "hello" );
      QTest::newRow( "upper" ) << "upper('HeLLo')" << false << QVariant( "HELLO" );
      QTest::newRow( "length" ) << "length('HeLLo')" << false << QVariant( 5 );
      QTest::newRow( "replace" ) << "replace('HeLLo', 'LL', 'xx')" << false << QVariant( "Hexxo" );
      QTest::newRow( "regexp_replace" ) << "regexp_replace('HeLLo','[eL]+', '-')" << false << QVariant( "H-o" );
      QTest::newRow( "regexp_replace invalid" ) << "regexp_replace('HeLLo','[[[', '-')" << true << QVariant();
      QTest::newRow( "substr" ) << "substr('HeLLo', 3,2)" << false << QVariant( "LL" );
      QTest::newRow( "substr outside" ) << "substr('HeLLo', -5,2)" << false << QVariant( "" );
      QTest::newRow( "regexp_substr" ) << "regexp_substr('abc123','(\\\\d+)')" << false << QVariant( "123" );
      QTest::newRow( "regexp_substr invalid" ) << "regexp_substr('abc123','([[[')" << true << QVariant();
      QTest::newRow( "strpos" ) << "strpos('Hello World','World')" << false << QVariant( 6 );
      QTest::newRow( "strpos outside" ) << "strpos('Hello World','blah')" << false << QVariant( -1 );
      QTest::newRow( "left" ) << "left('Hello World',5)" << false << QVariant( "Hello" );
      QTest::newRow( "right" ) << "right('Hello World', 5)" << false << QVariant( "World" );
      QTest::newRow( "rpad" ) << "rpad('Hello', 10, 'x')" << false << QVariant( "Helloxxxxx" );
      QTest::newRow( "rpad truncate" ) << "rpad('Hello', 4, 'x')" << false << QVariant( "Hell" );
      QTest::newRow( "lpad" ) << "lpad('Hello', 10, 'x')" << false << QVariant( "xxxxxHello" );
      QTest::newRow( "lpad truncate" ) << "rpad('Hello', 4, 'x')" << false << QVariant( "Hell" );
      QTest::newRow( "title" ) << "title(' HeLlO   WORLD ')" << false << QVariant( " Hello   World " );
      QTest::newRow( "trim" ) << "trim('   Test String ')" << false << QVariant( "Test String" );
      QTest::newRow( "trim empty string" ) << "trim('')" << false << QVariant( "" );
      QTest::newRow( "wordwrap" ) << "wordwrap('university of qgis',13)" << false << QVariant( "university of\nqgis" );
      QTest::newRow( "wordwrap" ) << "wordwrap('university of qgis',13,' ')" << false << QVariant( "university of\nqgis" );
      QTest::newRow( "wordwrap" ) << "wordwrap('university of qgis',-3)" << false << QVariant( "university\nof qgis" );
      QTest::newRow( "wordwrap" ) << "wordwrap('university of qgis',-3,' ')" << false << QVariant( "university\nof qgis" );
      QTest::newRow( "wordwrap" ) << "wordwrap('university of qgis\nsupports many multiline',-5,' ')" << false << QVariant( "university\nof qgis\nsupports\nmany multiline" );
      QTest::newRow( "format" ) << "format('%1 %2 %3 %1', 'One', 'Two', 'Three')" << false << QVariant( "One Two Three One" );

      // implicit conversions
      QTest::newRow( "implicit int->text" ) << "length(123)" << false << QVariant( 3 );
      QTest::newRow( "implicit double->text" ) << "length(1.23)" << false << QVariant( 4 );
      QTest::newRow( "implicit int->bool" ) << "1 or 0" << false << QVariant( 1 );
      QTest::newRow( "implicit double->bool" ) << "0.1 or 0" << false << QVariant( 1 );
      QTest::newRow( "implicit text->int" ) << "'5'+2" << false << QVariant( 7 );
      QTest::newRow( "implicit text->double" ) << "'5.1'+2" << false << QVariant( 7.1 );
      QTest::newRow( "implicit text->bool" ) << "'0.1' or 0" << false << QVariant( 1 );

      // conditions (without base expression, i.e. CASE WHEN ... THEN ... END)
      QTest::newRow( "condition when" ) << "case when 2>1 then 'good' end" << false << QVariant( "good" );
      QTest::newRow( "condition else" ) << "case when 1=0 then 'bad' else 678 end" << false << QVariant( 678 );
      QTest::newRow( "condition null" ) << "case when length(123)=0 then 111 end" << false << QVariant();
      QTest::newRow( "condition 2 when" ) << "case when 2>3 then 23 when 3>2 then 32 else 0 end" << false << QVariant( 32 );
      QTest::newRow( "coalesce null" ) << "coalesce(NULL)" << false << QVariant();
      QTest::newRow( "coalesce mid-null" ) << "coalesce(1, NULL, 3)" << false << QVariant( 1 );
      QTest::newRow( "coalesce exp" ) << "coalesce(NULL, 1+1)" << false << QVariant( 2 );
      QTest::newRow( "regexp match" ) << "regexp_match('abc','.b.')" << false << QVariant( 1 );
      QTest::newRow( "regexp match invalid" ) << "regexp_match('abc DEF','[[[')" << true << QVariant();
      QTest::newRow( "regexp match escaped" ) << "regexp_match('abc DEF','\\\\s[A-Z]+')" << false << QVariant( 1 );
      QTest::newRow( "regexp match false" ) << "regexp_match('abc DEF','\\\\s[a-z]+')" << false << QVariant( 0 );

      // Datetime functions
      QTest::newRow( "to date" ) << "todate('2012-06-28')" << false << QVariant( QDate( 2012, 6, 28 ) );
      QTest::newRow( "to interval" ) << "tointerval('1 Year 1 Month 1 Week 1 Hour 1 Minute')" << false << QVariant::fromValue( QgsExpression::Interval( 34758060 ) );
      QTest::newRow( "day with date" ) << "day('2012-06-28')" << false << QVariant( 28 );
      QTest::newRow( "day with interval" ) << "day(tointerval('28 days'))" << false << QVariant( 28.0 );
      QTest::newRow( "month with date" ) << "month('2012-06-28')" << false << QVariant( 6 );
      QTest::newRow( "month with interval" ) << "month(tointerval('2 months'))" << false << QVariant( 2.0 );
      QTest::newRow( "year with date" ) << "year('2012-06-28')" << false << QVariant( 2012 );
      QTest::newRow( "year with interval" ) << "year(tointerval('2 years'))" << false << QVariant( 2.0 );
      QTest::newRow( "age" ) << "age('2012-06-30','2012-06-28')" << false << QVariant::fromValue( QgsExpression::Interval( 172800 ) );
      QTest::newRow( "negative age" ) << "age('2012-06-28','2012-06-30')" << false << QVariant::fromValue( QgsExpression::Interval( -172800 ) );

      // Color functions
      QTest::newRow( "ramp color" ) << "ramp_color('Spectral',0.3)" << false << QVariant( "253,190,115,255" );
      QTest::newRow( "color rgb" ) << "color_rgb(255,127,0)" << false << QVariant( "255,127,0" );
      QTest::newRow( "color rgba" ) << "color_rgba(255,127,0,200)" << false << QVariant( "255,127,0,200" );
      QTest::newRow( "color hsl" ) << "color_hsl(100,50,70)" << false << QVariant( "166,217,140" );
      QTest::newRow( "color hsla" ) << "color_hsla(100,50,70,200)" << false << QVariant( "166,217,140,200" );
      QTest::newRow( "color hsv" ) << "color_hsv(40,100,100)" << false << QVariant( "255,170,0" );
      QTest::newRow( "color hsva" ) << "color_hsva(40,100,100,200)" << false << QVariant( "255,170,0,200" );
      QTest::newRow( "color cmyk" ) << "color_cmyk(100,50,33,10)" << false << QVariant( "0,115,154" );
      QTest::newRow( "color cmyka" ) << "color_cmyka(50,25,90,60,200)" << false << QVariant( "51,76,10,200" );
    }