#include <stdbool.h>
#include <stdio.h>

typedef struct range {
    int start;
    int stop;
    int step;
    int curr_value;
} range;

void print_help() {
    printf("""./range -       prints help\n"""
           """./range N -     prints [0, 1, ..., N - 1, N) sequence\n"""
           """./range M N -   prints [M, M + 1, ..., N - 1, N) sequence\n"""
           """./range M N S - prints [M, M + S, M + 2S, ..., N - 1] sequence\n""");
}

bool argparse(int argc, char *argv[], int *start, int *stop, int *step) {
    if (argc <= 1)
        return false;

    if (argc == 2) {
        sscanf(argv[1], "%d", stop);
        *start = 0;
        *step = 1;
    }
    if (argc == 3) {
        sscanf(argv[1], "%d", start);
        sscanf(argv[2], "%d", stop);
        *step = 1;
    }
    if (argc == 4) {
        sscanf(argv[1], "%d", start);
        sscanf(argv[2], "%d", stop);
        sscanf(argv[3], "%d", step);
    }

    return true;
}

void range_init(range *I) {
    I->curr_value = I->start;
}

bool range_run(range *I) {
    return I->curr_value < I->stop;
}

void range_next(range *I) {
    I->curr_value += I->step;
}

int range_get(range *I) {
    return I->curr_value;
}

int main(int argc, char *argv[]) {
    range I;
    if (!argparse(argc, argv, &I.start, &I.stop, &I.step))
        print_help();
    else {
        for(range_init(&I); range_run(&I); range_next(&I))
            printf("%d\n", range_get(&I));
    }
    return 0;
}