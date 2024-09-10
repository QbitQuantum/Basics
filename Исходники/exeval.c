void eval_lerp(Expr *expr)
{
	expr->l->l->fn(expr->l->l);
	expr->l->r->fn(expr->l->r);
	expr->r->fn(expr->r);
	expr->v.x = LERP(expr->l->l->v.x, expr->l->r->v.x, expr->r->v.x);
}