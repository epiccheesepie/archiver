//
// Created by Professional on 08.03.2020.
//
#ifndef SIMPLEARCHIVER_ZZIPER_H
#define SIMPLEARCHIVER_ZZIPER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

typedef char* string;
typedef unsigned long int uint;
typedef  unsigned char* DumpFile;

typedef struct InfoFile
{
    uint number_of_bytes;
    string name;
    string address;

} InfoFile;

typedef struct Zziper
{
    int number_of_files;
    string *files;
    string path;
    string file_name;

} Zziper;

string get_string(const char *in);


void InfoFile_add(InfoFile *self, string name, uint number, string  address);

void File_write(InfoFile* self, FILE *outfile);

// Zziper methods
void Zziper__init (Zziper* self);
void list_directory(Zziper* self, string dir_name, FILE *outfile);
void compress (Zziper* self);
void decompress (Zziper* self);
void repr(Zziper* self);


#endif //SIMPLEARCHIVER_ZZIPER_H
