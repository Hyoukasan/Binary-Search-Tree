#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node node_t;

void   insert(binary_trees_t* self, int X);
void   delete(binary_trees_t* self, int X);
void   search(binary_trees_t* self, int X);
void   max(binary_trees_t* self);
void   min(binary_trees_t* self);
void   size(binary_trees_t* self);
void   height(binary_trees_t* self);
void   inorder(binary_trees_t* self);
void   preorder(binary_trees_t* self);
void   postorder(binary_trees_t* self);
void   clear(binary_trees_t* self);
void   kth_min(binary_trees_t* self, int K);
void   kth_max(binary_trees_t* self, int K);
void   count_range(binary_trees_t* self, int L, int R);
void   range_query(binary_trees_t* self, int L, int R);
void   lca(binary_trees_t* self, int X, int Y);
void   predecessor(binary_trees_t* self, int X);
void   successor(binary_trees_t* self, int X);
void   mirror(binary_trees_t* self);
void   copy(binary_trees_t* src, binary_trees_t* dest);
void   merge(binary_trees_t* src_1, binary_trees_t* src_2, binary_trees_t* dest);
void   intersect(binary_trees_t* src_1, binary_trees_t* src_2, binary_trees_t* dest);
void   is_subtree(binary_trees_t* tree_1, binary_trees_t* tree_2);
void   print_all(binary_trees_t* self);

typedef enum
{
    CMD_INSERT,
    CMD_DELETE,
    CMD_SEARCH,
    CMD_MAX,
    CMD_MIN,
    CMD_SIZE,
    CMD_HEIGHT,
    CMD_INORDER,
    CMD_PREORDER,
    CMD_POSTORDER,
    CMD_CLEAR,
    CMD_KTH_MIN,
    CMD_KTH_MAX,
    CMD_COUNT_RANGE,
    CMD_RANGE_QUERY,
    CMD_LCA,
    CMD_PREDECESSOR,
    CMD_SUCCESSOR,
    CMD_MIRROR,
    CMD_COPY,
    CMD_MERGE,
    CMD_INTERSPECT,
    CMD_IS_SUBTREE,
    CMD_PRINT_ALL,
    CMD_ERR
} CMD_TYPE;

typedef enum
{
    TREE_A,
    TREE_B,
    TREE_C
} TREES_LIST;

struct node
{
    int key;
    node_t *left, *right;
};

typedef struct binary_trees
{
    node_t *root;

    size_t size_tree;
    size_t height_tree;

    /*general commands*/

    void    (*insert)(binary_trees_t* self, int X);
    void    (*delete)(binary_trees_t* self, int X);
    void    (*search)(binary_trees_t* self, int X);
    void    (*max)(binary_trees_t* self);
    void    (*min)(binary_trees_t* self);
    void    (*size)(binary_trees_t* self);
    void    (*height)(binary_trees_t* self);
    void    (*inorder)(binary_trees_t* self);
    void    (*preorder)(binary_trees_t* self);
    void    (*postorder)(binary_trees_t* self);
    void    (*clear)(binary_trees_t* self);

    /*extension commands*/

    void    (*kth_min)(binary_trees_t* self, int K);
    void    (*kth_max)(binary_trees_t* self, int K);
    void    (*count_range)(binary_trees_t* self, int L, int R);
    void    (*range_query)(binary_trees_t* self, int L, int R);
    void    (*lca)(binary_trees_t* self, int X, int Y);
    void    (*predecessor)(binary_trees_t* self, int X);
    void    (*successor)(binary_trees_t* self, int X);
    void    (*mirror)(binary_trees_t* self);
    void    (*copy)(binary_trees_t* src, binary_trees_t* dest);
    void    (*merge)(binary_trees_t* src_1, binary_trees_t* src_2, binary_trees_t* dest);
    void    (*intersect)(binary_trees_t* src_1, binary_trees_t* src_2, binary_trees_t* dest);
    void    (*is_subtree)(binary_trees_t* tree_1, binary_trees_t* tree_2);
    void    (*print_all)(binary_trees_t* self);
} binary_trees_t;

struct map
{
    char* command;
    CMD_TYPE type;
};

static struct map cmd_dict[] = {
    {"insert", CMD_INSERT},
    {"delete", CMD_DELETE},
    {"search", CMD_SEARCH},
    {"min", CMD_MIN},
    {"max", CMD_MAX},
    {"size", CMD_SIZE},
    {"height", CMD_HEIGHT},
    {"inorder", CMD_INORDER},
    {"preorder", CMD_PREORDER},
    {"postorder", CMD_POSTORDER},
    {"clear", CMD_CLEAR},
    {"kth_min", CMD_KTH_MIN},
    {"kth_max", CMD_KTH_MAX},
    {"count_range", CMD_COUNT_RANGE},
    {"range_query", CMD_RANGE_QUERY},
    {"lca", CMD_LCA},
    {"predecessor", CMD_PREDECESSOR},
    {"successor", CMD_SUCCESSOR},
    {"mirror", CMD_MIRROR},
    {"copy", CMD_COPY},
    {"merge", CMD_MERGE},
    {"intersect", CMD_INTERSPECT},
    {"is_subtree", CMD_IS_SUBTREE},
    {"print_all", CMD_PRINT_ALL},
    {NULL, CMD_ERR}
};

static struct map trees_list[] = {
    {"TREE_A", TREE_A},
    {"TREE_B", TREE_B},
    {"TREE_C", TREE_C}
}

void tree_init(binary_trees_t* tree)
{   
    tree->root = malloc(sizeof(binary_trees_t));
    if(tree->root == NULL) {
        return;
    }

    tree->size_tree = 0;
    tree->height_tree = 0;

    tree->insert      = insert;
    tree->delete      = delete;
    tree->search      = search;
    tree->max         = max;
    tree->min         = min;
    tree->size        = size;
    tree->height      = height;
    tree->inorder     = inorder;
    tree->preorder    = preorder;
    tree->postorder   = postorder;
    tree->clear       = clear;
    tree->kth_min     = kth_min;
    tree->kth_max     = kth_max;
    tree->count_range = count_range;
    tree->range_query = range_query;
    tree->lca         = lca;
    tree->predecessor = predecessor;
    tree->successor   = successor;
    tree->mirror      = mirror;
    tree->copy        = copy;
    tree->merge       = merge;
    tree->intersect   = intersect;
    tree->is_subtree  = is_subtree;
    tree->print_all   = print_all;
}

int main(void)
{

    binary_trees_t woodland[3] = {0};

    uint32_t N;
    scanf("%d", &N);

    while(getchar() != '\n');

    char buffer[100];
    char* command;
    char* args[4] = {NULL, NULL, NULL, NULL};

    for(size_t i = 0; i < N; i++) {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return;
        }


    }
}