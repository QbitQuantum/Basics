wstring 
TransferRule::category_name(const wstring& lemma, const wstring& tags) {
  wstring catname=L"";

  if (lemma.length()>0)//TODO: codificar bien el caracter extraño
    catname+=StringUtils::substitute(StringUtils::substitute(StringUtils::substitute(lemma,L"#",L"_"),L"\u2019",L"_"),L"'",L"QUOT")+L"_";

  catname+=StringUtils::substitute(StringUtils::substitute(StringUtils::substitute(StringUtils::substitute(tags,L".",L""),L"*",L"_"),L"+",L"plus"),L"@",L"arroba");

  return catname;
}