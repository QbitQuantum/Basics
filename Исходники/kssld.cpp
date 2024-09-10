QStringList KSSLD::caList() {
QStringList x;
KConfig cfg("ksslcalist", true, false);

	x = cfg.groupList();
	x.remove("<default>");

return x;
}