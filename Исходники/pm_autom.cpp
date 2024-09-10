/************************************************************************
 Метод вызывается классом Automaton для загрузки специфических для
 Продукционной Машины структур данных. В случае успешного распознавания
 возвращаем true, иначе - false.
*************************************************************************/
bool PM_Automat::ProcessLexem(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             )
{
 if( t.GetToken()==B_FUNCTION )
 {
  const TrFunction *fun = functions->Get().CompileDeclaration( *this, txtfile, procedure_declarations );
  return true;
 } 
 else if( t.string().eqi(L"static") )
 {
  // это должно быть объявление глобальной переменной:
  // static тип = значение;
  // Мы скомпилируем его как функцию, инициализирующую переменную в глобальном пространстве.
  functions->Get().CompileStatic( *this, txtfile, procedure_declarations );
  return true;
 }

 return false;
}