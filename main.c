#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


typedef char* string;

string get_string(const char *in)
{
    string cmd;
    int len = strlen(in) + 1;
    cmd = malloc(len);
    snprintf(cmd, len,"%s", in);
    return cmd;
}

typedef struct Zziper
{
    int number_of_files;
    string *files;
    string path;
    string file_name;
} Zziper;

void Zziper__init (Zziper* self);
void get_info(Zziper* self);
void compress (Zziper* self);
void decompress (Zziper* self);
void repr(Zziper* self);

void Zziper__init(Zziper* self)
{
    self->number_of_files=0;
    self->file_name = NULL;
    self->files = NULL;
    self->path = NULL;
}

void get_info(Zziper* self)
{
    string name;
    self->files = (string*) malloc(sizeof(string));

    DIR *directory;
    struct dirent *dir_object;

    directory = opendir(".");
    int i = 0;
    int len = 0;
    if (directory)
    {
        while ((dir_object = readdir(directory)) != NULL)
        {
            name = dir_object->d_name;
            len = strlen(name) + 1;
            self->files = (string*)realloc(self->files, sizeof(string) * (i + 2));
            self->files[i] = (string) malloc(len);
            snprintf(self->files[i], len,"%s", name);
            i++;
            self->number_of_files ++;

        }

        closedir(directory);

    }
}

void repr (Zziper* self)
{
    printf("The list of scanned files", "%s\n");

    for (int i=0; i < self->number_of_files; i++)
    {
        printf("%s\n", self->files[i]);
    }

}
int main() {

    Zziper zip;
    Zziper__init(&zip);
    get_info(&zip);
    repr(&zip);
    free(zip.files);


}