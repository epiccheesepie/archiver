
#include "cmake-build-debug/source/zziper.h"


int main() {

    Zziper zip;
    Zziper__init(&zip);

    repr(&zip);
    printf("%d %s\n", zip.number_of_files, " - number of files");

   FILE *outfile;
   outfile = fopen("outfile.txt", "a+");
   list_directory(&zip, ".");
   fclose(outfile);



}
