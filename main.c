#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


typedef char* string;

typedef struct  Directory
{
    string name;
    string* sub_dirs;

}Directory;

typedef struct InfoFile
{

} InfoFile;

typedef struct Zziper
{
    int number_of_files;
    string *files;
    string path;
    string file_name;

} Zziper;

string get_string(const char *in)
{
    string cmd;
    int len = strlen(in) + 1;
    cmd = malloc(len);
    snprintf(cmd, len,"%s", in);
    return cmd;
}


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
    directory = opendir(dir_name);
    struct dirent *dir_record;

    static int i = 0;
    int len = 0;
    printf("Dir_name: %s\n", dir_name);
    char path[256];
    // TODO: свести к string
    //string path;
    if (directory)
    {
        while ((dir_record = readdir(directory)) != NULL)
        {
            if (strcmp(dir_record->d_name, ".") != 0 && strcmp(dir_record->d_name, "..") != 0)
            {
                if (dir_record->d_type == DT_DIR)
                {
                    printf("%s %s \n", "New level of recursion:", dir_record->d_name);
                    strcpy(path, dir_name);
                    strcat(path, "/");
                    strcat(path, dir_record->d_name);
                    list_directory(self, path);
                }
                else
                {
                    file_name = dir_record->d_name;
                    len = strlen(file_name) + 1;
                    self->files = (string*)realloc(self->files, sizeof(string) * (i + 2));
                    self->files[i] = (string) malloc(len);

                    snprintf(self->files[i], len, "%s", file_name);
                    printf("%s %s\n", "Simple file: ", self->files[i]);
                    i++;
                    self->number_of_files ++;
                }

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


int main() {

    Zziper zip;
    Zziper__init(&zip);
    list_directory(&zip, ".");
    repr(&zip);
    printf("%d %s\n", zip.number_of_files, " - number of files");
    free(zip.files);
    //listFilesRecursively(".");

}
