 AnchorInfo::AnchorInfo(Syntax::Expression& expr, int offset, int width, String str, bool ignore)
   :_expr(&expr)
   ,_pos(Position::Any)
   ,_offset(offset)
   ,_str(ignore ? new String(str.ToLower()) : new String(str))
   ,_width(width)
   ,_ignore(ignore) 
   {
   }