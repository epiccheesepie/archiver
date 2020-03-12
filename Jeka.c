#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define _NAME_FILE 50
#define _PATH 50

typedef char* string;

typedef struct Zziper
{
    int number_of_files;
    string *files;
    string path;
    string file_name;

} Zziper;

void Zziper__init (Zziper* self);

typedef struct fFile //структура файла в метаданные
{
    char name[_NAME_FILE];
    char path[_PATH];
    int size;
} fFile;

void Zziper__init(Zziper* self)
{
    self->files = (string*) malloc(sizeof(string));
    self->number_of_files = 0;
    self->file_name = NULL;
    self->path = NULL;
}

string concatName(string s1, string s2) {
    string buf = calloc(strlen(s1) + strlen(s2) + 2, 1);
    strcat(buf,s1);
    strcat(buf,"/");
    strcat(buf,s2);
    return buf;
}

string concatPath(string s1, string s2) {
    string buf = calloc(strlen(s1) + strlen(s2) + 2, 1);
    strcat(buf,s1);
    strcat(buf,s2);
    strcat(buf,"/");
    return buf;
}

void newDir(char* path) {
    char *token, *last;
    char work[_PATH];
    string full = "";
    strcpy(work,path);
    token = strtok_r(work,"/",&last);
    while(token != NULL) {
        full = concatPath(full,token);
        //printf("%s\n", full);
        mkdir(full,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        token = strtok_r(NULL, "/", &last);
    }
}

void zip_archiver(Zziper* self, string dir_name)
{
    string file_name; //переменные для директории
    string name_for_open;
    DIR *directory;
    struct dirent *dir_record;

    int in, out; //переменные для работы с инфофайлом и архивом
    int info;
    long int size = 0;
    fFile item;

    directory = opendir(dir_name);
    static int i = 0;
    int len = 0;
    //printf("Dir_name: %s\n", dir_name);
    char path[_PATH];
    char buf;

    if (directory)
    {
        while ((dir_record = readdir(directory)) != NULL)
        {
            if (strcmp(dir_record->d_name, ".") != 0 && strcmp(dir_record->d_name, "..") != 0)
            {
                if (dir_record->d_type == DT_DIR)
                {
                    //printf("%s %s \n", "New level of recursion:", dir_record->d_name);
                    strcpy(path, dir_name);
                    strcat(path, "/");
                    strcat(path, dir_record->d_name);
                    zip_archiver(self, path);
                }
                else
                {
                    file_name = dir_record->d_name;
                    len = strlen(file_name) + 1;
                    self->files = (string*)realloc(self->files, sizeof(string) * (i + 2));
                    self->files[i] = (string) malloc(len);

                    snprintf(self->files[i], len, "%s", file_name);
                    //printf("%s %s\n", "Simple file: ", self->files[i]);
                    i++;
                    self->number_of_files ++;

                    out = open("archive.bin",  O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                    name_for_open = concatName(dir_name,file_name);
                    in = open(name_for_open, O_RDONLY);
                    lseek(out,0,SEEK_END);
                    lseek(in,0,SEEK_SET);   

                    while(read(in, &buf, 1) == 1) {
                        write(out, &buf, 1);
                        size++;
                    }

                    strcpy(&item.name[0], file_name);
                    strcpy(&item.path[0], dir_name);
                    item.size = size;
                    printf("%s %s\n", "Path of file: ", item.path);
                    printf("%s %s\n", "Name of file: ", item.name);
                    printf("%s %d\n", "Size of file: ", item.size);
                    printf("\n");
                    size = 0;
                    info = open("info.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                    lseek(info,0,SEEK_END);
                    write(info,&item,sizeof(fFile));

                    close(info);
                    close(in);
                    close(out);
                }

            }


        }
        closedir(directory);
    }
} 

void unzip_archiver(int out, int info) {

    fFile item; //объект структуры (файл)
    int in;
    int buf;
    string full_name;
    long int cnt = 0; //размер

    while(read(info,&item,sizeof(fFile)) == sizeof(fFile)) {
        newDir(item.path);
        full_name = concatName(item.path,item.name);
        printf("%s %s\n", "Path of file: ", item.path);
        printf("%s %s\n", "Name of file: ", item.name);
        printf("%s %d\n", "Size of file: ", item.size);
        printf("\n");
        in = open(full_name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
        lseek(in,0,SEEK_SET);
        while((read(out, &buf, 1) == 1) && cnt != item.size) {
            write(in, &buf, 1);
            cnt++;
        }
        cnt = 0;
        close(in);
    }
}

int main() {

    Zziper zip;
    Zziper__init(&zip);
    zip_archiver(&zip, ".");
    printf("%d %s\n", zip.number_of_files, " - number of files");
    free(zip.files);

    /*int out, info;
    out = open("archive.bin", O_RDONLY);
    info = open("info.out", O_RDONLY);
    unzip_archiver(out, info);
    close(out);
    close(info);*/
}