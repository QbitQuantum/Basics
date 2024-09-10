void CodeViewWidget::OnRenameSymbol()
{
  const u32 addr = GetContextAddress();

  Common::Symbol* symbol = g_symbolDB.GetSymbolFromAddr(addr);

  if (!symbol)
    return;

  bool good;
  QString name =
      QInputDialog::getText(this, tr("Rename symbol"), tr("Symbol name:"), QLineEdit::Normal,
                            QString::fromStdString(symbol->name), &good);

  if (good && !name.isEmpty())
  {
    symbol->Rename(name.toStdString());
    emit SymbolsChanged();
    Update();
  }
}