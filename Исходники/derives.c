void
free_derives()
{
  FREE(derives[ntokens]);
  FREE(derives + ntokens);
}