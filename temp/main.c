#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 1. Structure Definition
typedef struct ll_node {
    int32_t value;
    struct ll_node *next;
} ll_node_t;

// 2. Node Creation Function (Single Pointer)
static ll_node_t *ll_node_create(int32_t value) {
    ll_node_t *node = (ll_node_t *)malloc(sizeof(*node));
    if (node == NULL) {
        return NULL; 
    }

    *node = (ll_node_t){
        .value = value,
        .next = NULL
    };

    return node;
}

// 3. Helper function to print the list
static void ll_print(ll_node_t *head) {
    ll_node_t *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// 4. Helper function to free the entire list memory
static void ll_free(ll_node_t *head) {
    ll_node_t *current = head;
    while (current != NULL) {
        ll_node_t *next_node = current->next;
        free(current);
        current = next_node;
    }
}

static ll_node_t *ll_insert_end(ll_node_t *head, int32_t value) {
    // 1. Create the new node using our single pointer creation function
    ll_node_t *new_node = ll_node_create(value);
    if (new_node == NULL) {
        return head; // Return unchanged list if allocation fails
    }

    // 2. Edge Case: If the list is empty, the new node is the new head
    if (head == NULL) {
        return new_node;
    }

    // 3. Traverse to the last node of the list
    ll_node_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // 4. Link the last node to our new node
    current->next = new_node;

    // 5. Return the head (which hasn't changed in this case)
    return head;
}


// 5. Calling Code (Main)
int main(void) {
    printf("Creating a linked list...\n");

    // Create the first node (Head)
    ll_node_t *head = ll_node_create(10);
    if (head == NULL) {
        fprintf(stderr, "Failed to allocate memory for head node.\n");
        return 1;
    }

    // Create and link the second node
    head->next = ll_node_create(20);
    if (head->next == NULL) {
        fprintf(stderr, "Failed to allocate memory for second node.\n");
        ll_free(head);
        return 1;
    }

    // Create and link the third node
    head->next->next = ll_node_create(30);
    if (head->next->next == NULL) {
        fprintf(stderr, "Failed to allocate memory for third node.\n");
        ll_free(head);
        return 1;
    }

    // Print the list: should output 10 -> 20 -> 30 -> NULL
    printf("Linked List Content: ");
    ll_print(head);

    // Clean up memory
    ll_free(head);
    printf("Memory freed successfully.\n");

    // FIX: Reassign the existing variable instead of redefining it
    head = NULL; 

    // Test the insert end function
    head = ll_insert_end(head, 10); 
    head = ll_insert_end(head, 20); 
    head = ll_insert_end(head, 30);

    // Print and free the new list before exiting
    printf("New Linked List Content: ");
    ll_print(head);
    ll_free(head);

    return 0;
}
