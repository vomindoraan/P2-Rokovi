#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_USERS "korisnici.txt"
#define FILE_LOG   "log.txt"
#define NAME_LEN   21
#define EMAIL_LEN  41
#define ACT_LOGON  'p'
#define ACT_LOGOFF 'o'

#define MAX(a, b)      ((a) > (b) ? (a) : (b))
#define ALLOC_CHECK(p) if (!(p)) fputs("Neuspesna alokacija", stderr), exit(1)
#define FILE_CHECK(p)  if (!(p)) perror(NULL), exit(2)

typedef struct elem {
	char name[NAME_LEN];
	char email[EMAIL_LEN];
	int  logon;
	int  total;
	struct elem* next;
} Elem;

Elem *read_list(FILE *fp) {
	Elem *head = NULL, *tail;
	char name[NAME_LEN], email[EMAIL_LEN];

	while (fscanf(fp, "%s%s", name, email) == 2) { // fscanf vraca broj uspesno procitanih arg
		Elem *p;
		ALLOC_CHECK(p = malloc(sizeof *p));

		strcpy(p->name, name);
		strcpy(p->email, email);
		p->logon = p->total = 0;
		p->next = NULL;

		if (!head) head = p;
		else       tail->next = p;
		tail = p;
	}

	return head;
}

void free_list(Elem **plist) {
	Elem *list = *plist;
	while (list) {
		Elem *p = list;
		list = list->next;
		free(p);
	}
	*plist = NULL;
}

void update_list(Elem *list, FILE *fp) {
	char email[EMAIL_LEN], action;
	int time;

	while (fscanf(fp, "%s%*c%c%d", email, &action, &time) == 3) { // %* odbacuje procitan unos
		Elem *p = list;
		while (strcmp(p->email, email)) p = p->next;
		if (!p) continue; // Korisnik ne postoji u listi

		// Korisnik nadjen
		/**/ if (action == ACT_LOGON)
			p->logon = time;
		else if (action == ACT_LOGOFF)
			p->total += time - p->logon;
			// p->max = max(p->max, time-p->logon) - ako bi se trazio maks
	}
}

int main(void)
{
	FILE *fp_users, *fp_log;
	FILE_CHECK(fp_users = fopen(FILE_USERS, "r"));
	FILE_CHECK(fp_log   = fopen(FILE_LOG,   "r"));

	Elem *list = read_list(fp_users);
	update_list(list, fp_log);

	int max_time = 0;
	for (Elem *p = list; p; p = p->next) // Nalazi maks vreme
		max_time = MAX(max_time, p->total);

	for (Elem *p = list; p; p = p->next)
		if (p->total == max_time) {
			p->name[0] = toupper(p->name[0]);
			puts(p->name);
			break;
		}

	free_list(&list);
	fclose(fp_users);
	fclose(fp_log);
}
