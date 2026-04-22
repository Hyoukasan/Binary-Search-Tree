#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct binary_trees binary_trees_t;
typedef struct node node_t;

void   insert(binary_trees_t* self, int X);
void   delete(binary_trees_t* self, int X);
void   search(binary_trees_t* self, int X);
int    max_value(binary_trees_t* self);
int    min_value(binary_trees_t* self);
void   size_tree(binary_trees_t* self);
void   height_tree(binary_trees_t* self);
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
    CMD_INTERSECT,
    CMD_IS_SUBTREE,
    CMD_PRINT_ALL,
    CMD_ERR
} CMD_TYPE;

typedef enum
{
    TREE_A,
    TREE_B,
    TREE_C,
    TREE_ERR
} TREES_LIST;

struct node
{
    int data;
    node_t *left, *right;
};

struct binary_trees
{
    node_t *root;

    size_t size, height;

    /*general commands*/

    void    (*insert)(binary_trees_t* self, int X);
    void    (*delete)(binary_trees_t* self, int X);
    void    (*search)(binary_trees_t* self, int X);
    int     (*max_value)(binary_trees_t* self);
    int     (*min_value)(binary_trees_t* self);
    void    (*size_tree)(binary_trees_t* self);
    void    (*height_tree)(binary_trees_t* self);
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
};

struct cmd_map
{
    char *command;
    CMD_TYPE type;
};

struct tree_map
{
    char *command;
    TREES_LIST type;
};
static struct cmd_map cmd_dict[] = {
    {"insert",      CMD_INSERT},
    {"delete",      CMD_DELETE},
    {"search",      CMD_SEARCH},
    {"min",         CMD_MIN},
    {"max",         CMD_MAX},
    {"size",        CMD_SIZE},
    {"height",      CMD_HEIGHT},
    {"inorder",     CMD_INORDER},
    {"preorder",    CMD_PREORDER},
    {"postorder",   CMD_POSTORDER},
    {"clear",       CMD_CLEAR},
    {"kth_min",     CMD_KTH_MIN},
    {"kth_max",     CMD_KTH_MAX},
    {"count_range", CMD_COUNT_RANGE},
    {"range_query", CMD_RANGE_QUERY},
    {"lca",         CMD_LCA},
    {"predecessor", CMD_PREDECESSOR},
    {"successor",   CMD_SUCCESSOR},
    {"mirror",      CMD_MIRROR},
    {"copy",        CMD_COPY},
    {"merge",       CMD_MERGE},
    {"intersect",   CMD_INTERSECT},
    {"is_subtree",  CMD_IS_SUBTREE},
    {"print_all",   CMD_PRINT_ALL},
    {NULL,          CMD_ERR}
};

static struct tree_map trees_list[] = {
    {"TREE_A", TREE_A},
    {"TREE_B", TREE_B},
    {"TREE_C", TREE_C},
    {NULL,     TREE_ERR}
};

void tree_init(binary_trees_t* tree)
{   
    tree->root = NULL;

    tree->insert      = insert;
    tree->delete      = delete;
    tree->search      = search;
    tree->max_value   = max_value;
    tree->min_value   = min_value;
    tree->size        = size_tree;
    tree->height      = height_tree;
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

node_t* create_node(int data)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node == NULL) {
        printf("error\n");
        return NULL;
    }

    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insert(binary_trees_t* self, int X)
{
    node_t** tmp_ptr = &self->root;

    while(*tmp_ptr != NULL) {
        if((*tmp_ptr)->data > X) {
            tmp_ptr = &(*tmp_ptr)->left;
        } else if((*tmp_ptr)->data < X) {
            tmp_ptr = &(*tmp_ptr)->right;
        } else return;
    }


    *tmp_ptr = create_node(X);
    if(*tmp_ptr == NULL) {
        printf("error\n");
    }
}

node_t* find_min_node(node_t* node)
{
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void delete(binary_trees_t* self, int X)
{
    if(self->root == NULL) {
        printf("error\n");
        return;
    }

    node_t* tmp_ptr = self->root;

    while(tmp_ptr != NULL) {
        if(tmp_ptr->data > X) {
            tmp_ptr = tmp_ptr->left;
        } else if(tmp_ptr->data < X) {
            tmp_ptr = tmp_ptr->right;
        } else {
            break;
        }
    }

}

void search(binary_trees_t* self, int X)
{
    node_t* tmp_ptr = self->root;

    while(tmp_ptr != NULL) {
        if(tmp_ptr->data > X) {
            tmp_ptr = tmp_ptr->left;
        } else if(tmp_ptr->data < X) {
            tmp_ptr = tmp_ptr->right;
        } else {
            printf("found\n");
            return;
        }
    }

    printf("not found\n");
}

int max_value(binary_trees_t* self)
{
    if(self->root == NULL) {
        return INT_MAX;
    }

    node_t* tmp_ptr = self->root;

    while(tmp_ptr->right != NULL) {
        tmp_ptr = tmp_ptr->right;
    }

    return tmp_ptr->data;
}

int min_value(binary_trees_t* self)
{
    if(self->root == NULL) {
        return INT_MAX;
    }

    node_t* tmp_ptr = self->root;

    while(tmp_ptr->left != NULL) {
        tmp_ptr = tmp_ptr->left;
    }

    return tmp_ptr->data;
}

void inorder_node(node_t* root)
{
    if(root == NULL) {
        return;
    }

    inorder_node(root->left);
    printf("%d ", root->data);
    inorder_node(root->right);
}

void inorder(binary_trees_t* self)
{
    if(self->root == NULL) {
        printf("error\n");
        return;
    }

    inorder_node(self->root);
    printf("\n");
}

void preorder_node(node_t* root)
{
    if(root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder_node(root->left);
    preorder_node(root->right);
}

void preorder(binary_trees_t* self)
{
    if(self->root == NULL) {
        printf("error\n");
        return;
    }

    preorder_node(self->root);
    printf("\n");
}

void postorder_node(node_t* root)
{
    if(root == NULL) {
        return;
    }

    postorder_node(root->left);
    postorder_node(root->right);
    printf("%d ", root->data);
}

void postorder(binary_trees_t* self)
{
    if(self->root == NULL) {
        printf("error\n");
        return;
    }

    postorder_node(self->root);
    printf("\n");
}

CMD_TYPE search_cmd_table(char* arg)
{   
    for(size_t i = 0; cmd_dict[i].command != NULL; i++) {
        if(strcmp(cmd_dict[i].command, arg) == 0) {
            return cmd_dict[i].type;
        }
    }

    return CMD_ERR;
}

TREES_LIST search_tree_table(char* arg)
{   
    for(size_t i = 0; trees_list[i].command != NULL; i++) {
        if(strcmp(trees_list[i].command, arg) == 0) {
            return trees_list[i].type;
        }
    }

    return TREE_ERR;
}

int main(void)
{

    binary_trees_t woodland[3] = {0};

    tree_init(&woodland[TREE_A]);
    tree_init(&woodland[TREE_B]);
    tree_init(&woodland[TREE_C]);

    uint32_t N;
    scanf("%u", &N);

    while(getchar() != '\n');

    char buffer[100];
    char* args[5] = {NULL, NULL, NULL, NULL, NULL};
    CMD_TYPE command_type;
    TREES_LIST tree_type;
    TREES_LIST src_type;
    TREES_LIST dst_type;

    int value, K, L, R, result;

    for(size_t i = 0; i < N; i++) {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 1;
        }

        buffer[strcspn(buffer, "\n\r")] = '\0';

        args[0] = strtok(buffer, " ");
        command_type = search_cmd_table(args[0]);
        if(command_type == CMD_ERR) {
            printf("error\n");
            continue;
        }

        args[1] = strtok(NULL, " ");
        tree_type = search_tree_table(args[1]);
        if(tree_type == TREE_ERR) {
            printf("error\n");
            continue;
        }

        args[2] = strtok(NULL, " ");
        args[3] = strtok(NULL, " ");
        args[4] = strtok(NULL, " ");

        switch (command_type)
        {
        case CMD_INSERT:
            if(args[2] == NULL) {
                printf("error\n");
                break;
            }

            value = atoi(args[2]);
            woodland[tree_type].insert(&woodland[tree_type], value);
            break;
        
        case CMD_DELETE:
            if(args[2] == NULL) {
                printf("error\n");
                break;
            }

            value = atoi(args[2]);
            woodland[tree_type].delete(&woodland[tree_type], value);
            break;
        
        case CMD_SEARCH:
            if(args[2] == NULL) {
                printf("error\n");
                break;
            }

            value = atoi(args[2]);
            woodland[tree_type].search(&woodland[tree_type], value);
            break;

        case CMD_MIN:
            result = woodland[tree_type].min_value(&woodland[tree_type]);
            if(result == INT_MAX) {
                printf("error\n");
                break;
            }

            printf("%d\n", result);
            break;
        
        case CMD_MAX:
            result = woodland[tree_type].max_value(&woodland[tree_type]);
            if(result == INT_MAX) {
                printf("error\n");
                break;
            }

            printf("%d\n", result);
            break;
        
        case CMD_SIZE:
            break;

        case CMD_HEIGHT:
            break;

        case CMD_INORDER:
            break;

        case CMD_PREORDER:
            break;

        case CMD_POSTORDER:
            break;

        case CMD_CLEAR:
            break;
        
        case CMD_KTH_MIN:
            break;

        case CMD_KTH_MAX:
            break;
        
        case CMD_COUNT_RANGE:
            break;

        case CMD_RANGE_QUERY:
            break;
        
        case CMD_LCA:
            break;
        
        case CMD_PREDECESSOR:
            break;

        case CMD_SUCCESSOR:
            break;

        case CMD_MIRROR:
            break;

        case CMD_COPY:
            break;
        
        case CMD_MERGE:
            break;

        case CMD_INTERSECT:
            break;

        case CMD_IS_SUBTREE:
            break;
        
        case CMD_PRINT_ALL:
            break;

        default:
            printf("error\n");
            break;
        }

    }

    return 0;
}