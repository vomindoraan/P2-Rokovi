#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    double x, y, z;
} Point;

typedef struct distInfo {
    unsigned p1, p2;
    double dist;
} DistInfo;

DistInfo findFarthest(Point *a, unsigned n)
{
    DistInfo di = { -1, -1, 0.0 };
    unsigned i, j;

    for (i = 0; i < n-1; ++i) {
        for (j = i+1; j < n; ++j) {
            double dx = a[i].x-a[j].x, dy = a[i].y-a[j].y, dz = a[i].z-a[j].z;
            double dist = sqrt(dx*dx + dy*dy + dz*dz);

            if (dist > di.dist) {
                di.p1 = i;
                di.p2 = j;
                di.dist = dist;
            }
        }
    }

    return di;
}

int main(void)
{
    unsigned n, i;
    Point *pts;
    DistInfo di;

    printf("Uneti broj tacaka (min 2): ");
    scanf("%u", &n);
    if (n < 2) {
        return 2;
    }

    pts = malloc(n * sizeof *pts);
    if (!pts) {
        fprintf(stderr, "Neuspesna alokacija\n");
        return 1;
    }
    
    printf("Uneti tacke (x y z):\n");
    for (i = 0; i < n; ++i) {
        scanf("%lf %lf %lf", &pts[i].x, &pts[i].y, &pts[i].z);
    }

    di = findFarthest(pts, n);
    printf("%u %u %lf", di.p1, di.p2, di.dist);

    free(pts);
    return 0;
}
