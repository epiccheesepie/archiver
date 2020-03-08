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
            if (strcmp(dir_object->d_name, ".") == 0 || strcmp(dir_object->d_name, "..") == 0)
                continue;

            if (dir_object->d_type == DT_DIR)
            {
                printf("%s %d\n", dir_object->d_name, dir_object->d_type);
            }

            if (dir_object->d_type == DT_DIR)
            {
                printf("%s\n", "New level of recursion");
            }
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
        printf("%s\n", self->files[i]);

}

void listdir(string dir_name)
{
    DIR* directory;
    struct dirent *dir_object;

    directory = opendir(dir_name);
    if (directory)
    {
        while ((dir_object = readdir(directory)) != NULL)
        {
            if (dir_object->d_type == DT_DIR)
            {
                if (strcmp(dir_object->d_name, ".") == 0 || strcmp(dir_object->d_name, "..") == 0)
                    continue;

               printf("%s %s\n", "New level of recursion:", dir_object->d_name);
               listdir(dir_object->d_name);

            }
            else printf("%s %s\n", "Simple file: ", dir_object->d_name);

        }
        closedir(directory);
    }
}
int main() {

//    Zziper zip;
//    Zziper__init(&zip);
//    get_info(&zip);
//    repr(&zip);
//    free(zip.files);

    listdir(".");




}

//void listdir(const char *dir_name, int indent)
//{
//    DIR *directory;
//    struct dirent *dir_object;
//
//    if (!(directory = opendir(dir_name)))
//        return;
//
//    while ((dir_object = readdir(directory)) != NULL) {
//        if (dir_object->d_type == DT_DIR)
//        {
//            char path[1024];
//            if (strcmp(dir_object->d_name, ".") == 0 || strcmp(dir_object->d_name, "..") == 0)
//                continue;
//            snprintf(path, sizeof(path), "%s/%s", dir_name, dir_object->d_name);
//            printf("%*s[%s]\n", indent, "", dir_object->d_name);
//            listdir(path, indent + 2);
//        } else
//            {
//            printf("%*s- %s\n", indent, "", dir_object->d_name);
//            }
//    }
//    closedir(directory);
//}