#include <stdio.h>
#include <stdlib.h>
#define ORDEM 3

struct node
{
    int n;                 // Chaves do nó
    int keys[ORDEM - 1];   // Array de chaves
    struct node *p[ORDEM]; // Filhos da árvore
} *root = NULL;

enum KeyStatus
{
    Duplicate,
    SearchFailure,
    Success,
    InsertIt,
    LessKeys
};

void insert(int key);
void display(struct node *root, int);
enum KeyStatus ins(struct node *r, int x, int *y, struct node **u);
int searchPos(int x, int *key_arr, int n);

int main()
{
    int key, choice;

    printf("Criação de árvore B para ordem = %d\n", ORDEM);
    while (1)
    {
        printf("\n");
        printf("1 -> Inserir\n");
        printf("2 -> Imprimir árvore\n");
        printf("3 -> Sair\n");
        printf("\n");
        printf("Informe sua escolha: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Informe a chave: ");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("A ávore é:\n");
            display(root, 0);
            break;
        case 3:
            exit(1);
        default:
            printf("Escolha uma opção válida.\n");
            break;
        }
    }
    return 0;
}

void insert(int key)
{
    struct node *newnode;
    int upKey;
    enum KeyStatus value;
    value = ins(root, key, &upKey, &newnode);
    if (value == Duplicate)
        printf("Key already available\n");
    if (value == InsertIt)
    {
        struct node *uproot = root;
        root = malloc(sizeof(struct node));
        root->n = 1;
        root->keys[0] = upKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
    }
}

enum KeyStatus ins(struct node *ptr, int key, int *upKey, struct node **newnode)
{
    struct node *newPtr, *lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    enum KeyStatus value;
    if (ptr == NULL)
    {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;

    if (n < ORDEM - 1)
    {
        pos = searchPos(newKey, ptr->keys, n);
        for (i = n; i > pos; i--)
        {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        // Chave é inserida na posição correta
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n; // Incrementando o número de chaves do nó
        return Success;
    }
    // Se a chave do nó for a máxima e a posição for a ultima
    if (pos == ORDEM - 1)
    {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else // Se a chave do nó for a máxima e a posição não for a ultima
    {
        lastKey = ptr->keys[ORDEM - 2];
        lastPtr = ptr->p[ORDEM - 1];
        for (i = ORDEM - 2; i > pos; i--)
        {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
    }
    splitPos = (ORDEM - 1) / 2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode) = malloc(sizeof(struct node)); // Nó direito depois da partição*/
    ptr->n = splitPos;                        // Número de chaves do nó particionado à esquerda
    (*newnode)->n = ORDEM - 1 - splitPos;     // Número de chaves do nó particionado à direita
    for (i = 0; i < (*newnode)->n; i++)
    {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];

        if (i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}

void display(struct node *ptr, int blanks)
{
    if (ptr)
    {
        int i;
        for (i = 1; i <= blanks; i++)
            printf(" ");
        for (i = 0; i < ptr->n; i++)
            printf("%d ", ptr->keys[i]);
        printf("\n");
        for (i = 0; i <= ptr->n; i++)
            display(ptr->p[i], blanks + 10);
    }
}

int searchPos(int key, int *key_arr, int n)
{
    int pos = 0;

    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}
