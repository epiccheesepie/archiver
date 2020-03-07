#include <stdio.h>
#define N 100

struct Zziper
{
    char files [N][N];
    char path [N];
    char archive_name [N];
};

void Zziper__init (struct Zziper* self, char files [N][N], char path);
void get_info(struct Zziper* self);
void compress (struct Zziper* self);
void decompress (struct Zziper* self);

int main() {
    printf("Hello, World!\n");
    return 0;
}