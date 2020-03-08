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
void list_directory(Zziper* self, string dir_name);
void compress (Zziper* self);
void decompress (Zziper* self);
void repr(Zziper* self);

void Zziper__init(Zziper* self)
{
    self->files = (string*) malloc(sizeof(string));
    self->number_of_files = 0;
    self->file_name = NULL;
    self->path = NULL;
}

void list_directory(Zziper* self, string dir_name)
{
    string file_name;
    DIR *directory;
    struct dirent *dir_object;

    directory = opendir(dir_name);
    static int i = 0;
    int len = 0;
    if (directory)
    {
        while ((dir_object = readdir(directory)) != NULL)
        {
            if (dir_object->d_type == DT_DIR)
            {
                if (strcmp(dir_object->d_name, ".") == 0 || strcmp(dir_object->d_name, "..") == 0)
                    continue;
                printf("%s %s\n", "New level of recursion:", dir_object->d_name);
                list_directory(self, dir_object->d_name);
            }
            else
            {
                file_name = dir_object->d_name;
                printf("%s %s\n", "Simple file: ", file_name);
                len = strlen(file_name) + 1;
                self->files = (string*)realloc(self->files, sizeof(string) * (i + 2));
                self->files[i] = (string) malloc(len);

                snprintf(self->files[i], len, "%s", file_name);
                printf("%s %s\n", "Simple file: ", self->files[i]);
                i++;
                self->number_of_files ++;
            }
        }
        closedir(directory);
    }
}


void repr (Zziper* self)
{
    printf("\nThe list of scanned files\n");

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

    Zziper zip;
    Zziper__init(&zip);
    list_directory(&zip, ".");
    repr(&zip);
    free(zip.files);


}
