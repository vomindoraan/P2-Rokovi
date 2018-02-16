#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 30

#define CHECK_ALLOC(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)
#define CHECK_FILE(f)  if (!(f)) perror(NULL), exit(2)

// Za platforme koje nemaju ugrađene min i max
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef char word_t[WORD_LEN+1];

typedef struct node {
    word_t word;
    int    n;
    struct node *next;
} Node;

Node *find_word(Node *list, word_t word)
{
    for (Node *p = list; p; p = p->next)
        if (strcmp(p->word, word) == 0)
            return p;
    return NULL;
}

Node *read_wordlist(FILE *fp)
{
    Node *list = NULL;
    word_t word;
    char c, i = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha(c)) {
            word[i++] = tolower(c);  // Pamti kao sva mala slova
            continue;
        } else if (i == 0)
            continue;  // Preskače uzastopne razmake/interpunkciju

        word[i] = '\0';
        i = 0;

        Node *node = find_word(list, word);
        if (node) {
            node->n++;
            continue;
        }

        CHECK_ALLOC(node = malloc(sizeof *node));
        strcpy(node->word, word);
        node->n = 1;
        node->next = list;
        list = node;
    }

    return list;
}

void compare(Node *list1, Node *list2)
{
    int n1 = 0, n2 = 0, n12 = 0;

    for (Node *p1 = list1; p1; p1 = p1->next) {
        Node *p2 = find_word(list2, p1->word);
        if (!p2) {
            n1 += p1->n;
            continue;
        }

        int dn = p1->n - p2->n;
        n1  += MAX(dn,  0);
        n2  += MAX(-dn, 0);
        n12 += MIN(p1->n, p2->n);

        p2->n = 0;  // Sprečava ponovno dodavanje u drugoj petlji
    }

    for (Node *p2 = list2; p2; p2 = p2->next)
        n2 += p2->n;

    printf("isto - %d\noriginal - %d\nkopija - %d\n", n12, n1, n2);
}

int main(void)
{
    FILE *f_orig = fopen("original.txt", "r"),
         *f_copy = fopen("kopija.txt",   "r");
    CHECK_FILE(f_orig && f_copy);

    Node *list_orig = read_wordlist(f_orig),
         *list_copy = read_wordlist(f_copy);

    compare(list_orig, list_copy);

    fclose(f_orig), fclose(f_copy);
    free(list_orig), free(list_copy);
}
