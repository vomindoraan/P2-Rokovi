#include <stdio.h>
#include <stdlib.h>

#define MAX_SCHOOLS 400
#define NAME_LEN    30
#define UNASSIGNED  "NEUPISAN"

#define STR_(n)       #n
#define STR(n)        STR_(n)
#define FILE_CHECK(f) if (!(f)) perror(NULL), exit(1)

typedef struct {
    int  id;
    char name[NAME_LEN+1];
    int  free_places;
} School;

typedef School SchoolArray[MAX_SCHOOLS];

typedef struct {
    int   id;
    char  name[NAME_LEN+1];
    float gpa;
    int   wish;
} Student;

typedef struct node {
    Student st;
    struct node *next;
} StudentNode;

int read_schools(SchoolArray schools, FILE* fin)
{
    int n = 0;

    while (fscanf(fin, "%d %"STR(NAME_LEN)"[^\n]",
        &schools[n].free_places, schools[n].name) == 2)
    // STR(NAME_LEN) pretvara 30 u "30", pa se dobija format "%30[^\n]", sto
    // znaci "citaj string od najvise 30 znakova dok ne dodjes do kraja reda"
    {
        schools[n].id = n++;
    }

    return n;
}

void insert_node(StudentNode **phead, StudentNode *node)
{
    StudentNode *p = *phead, *prev = NULL;
    Student st = node->st;
    
    while ((st.wish > p->st.wish
        || st.wish == p->st.wish && st.gpa  < p->st.gpa
        || st.wish == p->st.wish && st.gpa == p->st.gpa && st.id > p->st.id)
        && p)
    {
        prev = p;
        p = p->next;
    }

    if (!prev) {
        *phead = node;
    } else {
        prev->next = node;
    }
    node->next = p;
}

StudentNode *read_students(FILE* fin)
{
    StudentNode *head = NULL;
    Student st;
    
    while (fread(&st, sizeof st, 1, fin)) {
        StudentNode *node = malloc(sizeof *node);
        if (!node) {
            fputs("Neuspesna alokacija", stderr);
            exit(2);
        }
        
        node->st = st;
        node->next = NULL;

        insert_node(&head, node);
    }

    return head;
}

void free_students(StudentNode *head)
{
    while (head) {
        StudentNode *node = head;
        head = head->next;
        free(node);
    }
}

void sorting_hat(StudentNode *students, SchoolArray schools, int n, FILE* fout)
{
    for (StudentNode *p = students; p; p = p->next) {
        fprintf(fout, "%d %s %.2f ", p->st.id, p->st.name, p->st.gpa);
        
        int i = p->st.wish;
        if (i >= 0 && i < n && schools[i].free_places > 0) {
            fprintf(fout, "%s\n", schools[i].name);
            schools[i].free_places--;
        } else {
            fprintf(fout, UNASSIGNED"\n");
        }
    }
}

int main(void)
{
    FILE *f_schools, *f_wishes, *f_admissions;
    FILE_CHECK(f_schools    = fopen("skole.txt", "r"));
    FILE_CHECK(f_wishes     = fopen("zelje.pod", "rb"));
    FILE_CHECK(f_admissions = fopen("upisi.txt", "w"));

    SchoolArray schools;
    int n = read_schools(schools, f_schools);

    StudentNode *students = read_students(f_wishes);

    sorting_hat(students, schools, n, f_admissions);

    free_students(students);
    fclose(f_schools);
    fclose(f_wishes);
    fclose(f_admissions);
}
