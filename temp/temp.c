static ll_status_t ll_node_create(ll_node_t **out_node, int32_t value)
{
  ll_node_t *node;

  assert(out_node != NULL);

  node = (ll_node_t *)malloc(sizeof(*node));
  if (node == NULL)
    return LL_ERR_ALLOC;
  
  *node = (ll_node_t){
    .value = value,
    .next = NULL
  };
  *out_node = node;
  return LL_OK;
}