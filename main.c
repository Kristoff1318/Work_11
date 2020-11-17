#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int genrand() {
    int rand;
    int opener = open("/dev/random", O_RDONLY);

    if (opener == -1) printf("error message %s\n\n", strerror(errno));

    int randomizer = read(opener, &rand, sizeof(rand));

    if (randomizer == -1) printf("error message %s\n\n", strerror(errno));

    close(opener);
    return rand;
}

int main() {
    int random[10];
    int i;
    printf("Generating random numbers:\n");
    for(i = 0; i < 10; i++) {
        random[i] = genrand();
        printf("\trandom %d: %d\n", i, random[i]);
    }

    int output = open("output.txt", O_CREAT | O_WRONLY, 0664);

    if (output == -1) printf("error message: %s\n", strerror(errno));

    printf("\nWriting numbers to file...\n\n");

    int final = write(output, random, sizeof(random));

    int new_array[10];

    printf("Reading numbers from file...\n\n");

    int a = open("output.txt", O_RDONLY);
    if (a == -1) printf("error message: %s\n", strerror(errno));
    int reading_file = read(a, new_array, sizeof(new_array));

    printf("Verification that written values were the same:\n");
    for(i = 0; i < 10; i++) {
        printf("\trandom %d: %d\n", i, new_array[i]);
    }

    close(output);
    close(a);
    return 0;
}
