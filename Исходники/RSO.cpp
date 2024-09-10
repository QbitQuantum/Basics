void RSOView::Apply(PPCSymbolDB* symbol_db) const
{
  for (const RSOExport& rso_export : GetExports())
  {
    u32 address = GetExportAddress(rso_export);
    if (address != 0)
    {
      Symbol* symbol = symbol_db->AddFunction(address);
      if (!symbol)
        symbol = symbol_db->GetSymbolFromAddr(address);

      const std::string export_name = GetExportName(rso_export);
      if (symbol)
      {
        // Function symbol
        symbol->Rename(export_name);
      }
      else
      {
        // Data symbol
        symbol_db->AddKnownSymbol(address, 0, export_name, Symbol::Type::Data);
      }
    }
  }
  DEBUG_LOG(SYMBOLS, "RSO(%s): %zu symbols applied", GetName().c_str(), GetExportsCount());
}