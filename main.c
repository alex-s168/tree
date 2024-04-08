#include <stdio.h>

#ifdef _WIN32
# define MINIRENT_IMPLEMENTATION
# include "minirent/minirent.h"
#else
# include <dirent.h>
#endif // _WIN32

static int printContents(const char *path, size_t indent) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0)
            continue;

        if (strcmp(entry->d_name, "..") == 0)
            continue;
        
        for (size_t i = 0; i < indent; i ++)
            fputc('|', stdout);

        fputs(entry->d_name, stdout);
        fputc('\n', stdout);

        // minirent does not give us a function to check if a file is a dir,
        // so we just try to list it's contents and see
        (void) printContents(entry->d_name, indent + 1);
    }
    
    return closedir(dir);
}

int main(const int argc, char **argv) {
    const char *path = argc >= 2 ? argv[1] : ".";
    return printContents(path, 0);
}
