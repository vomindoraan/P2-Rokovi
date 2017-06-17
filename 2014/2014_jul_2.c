#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 30

#define ALLOC_CHECK(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)
#define FILE_CHECK(f)  if (!(f)) perror(NULL), exit(2)

// Za platforme koje nemaju ugradjene min i max
#define min(a, b) (((x) < (y)) ? (x) : (y))
#define max(a, b) (((x) > (y)) ? (x) : (y))

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
	Node *head = NULL, *tail;
	word_t word;
	char c, i = 0;

	while ((c = fgetc(fp)) != EOF) {
		if (isalpha(c)) {
			word[i++] = tolower(c); // Pamti kao sva mala slova
			continue;
		} else if (i == 0)
			continue; // Preskace uzastopne razmake/interpunkciju

		word[i] = '\0';
		i = 0;

		Node *node = find_word(head, word);
		if (node) {
			node->n++;
			continue;
		}

		ALLOC_CHECK(node = malloc(sizeof *node));
		strcpy(node->word, word);
		node->n = 1;
		node->next = NULL;

		if (head) tail->next = node;
		else      head = node;
		tail = node;
	}

	return head;
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
		n1  += max(dn,  0);
		n2  += max(-dn, 0);
		n12 += min(p1->n, p2->n);

		p2->n = 0; // Sprecava ponovno dodavanje u drugoj petlji
	}

	for (Node *p2 = list2; p2; p2 = p2->next)
		n2 += p2->n;

	printf("isto - %d\noriginal - %d\nkopija - %d\n", n12, n1, n2);
}

int main(void)
{
	FILE *f_orig = fopen("original.txt", "r"),
	     *f_copy = fopen("kopija.txt",   "r");
	FILE_CHECK(f_orig && f_copy);

	Node *list_orig = read_wordlist(f_orig),
	     *list_copy = read_wordlist(f_copy);

	compare(list_orig, list_copy);

	fclose(f_orig), fclose(f_copy);
	free(list_orig), free(list_copy);
}
