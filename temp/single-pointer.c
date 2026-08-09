static ll_node_t *ll_node_create(int32_t value) {
    ll_node_t *node;

    node = (ll_node_t *)malloc(sizeof(*node));
    if (node == NULL) {
        // Return NULL if memory allocation fails
        return NULL; 
    }

    *node = (ll_node_t){
        .value = value,
        .next = NULL
    };

    return node;
}
