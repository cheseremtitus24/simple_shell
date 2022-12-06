#include "main.h"

int is_regular_file(const char* path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return (S_ISREG(path_stat.st_mode));
}

int isDirectory(const char* path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
    {
        return (0);
    }
    return (S_ISDIR(statbuf.st_mode));

}

bool file_exists(char *filepath) {
    struct stat sb;

    if (lstat(filepath, &sb) == -1) {
//        perror(filepath);
        return false;
    } else {
        return true;
    }

}

