#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define NAME_MAX 100

int main(int argc, char *argv[]) {
    char buf[NAME_MAX], fn[100];
    int f;
    char cwd[1024];
    int choice;

    DIR *p; // Declare p here
    struct dirent *d; // Declare d here
    
    do {
        // Displaying menu options
        printf("Enter\n1. To create a directory.\n2. To list files in a directory.\n3. To change directory.\n4. To remove a directory.\n5. To Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Name of directory: ");
                scanf("%s", fn);
                // Creating a directory with read, write, and execute permissions for all users
                f = mkdir(fn, 0777);
                if (f == -1) {
                    printf("\nCannot create a directory\n");
                    exit(-1);
                } else {
                    printf("\nDirectory with name [%s] created\n", fn);
                }
                break;

            case 2:
                // Getting the current working directory
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                    fprintf(stdout, "Current Working dir : %s\n", cwd);
                else {
                    perror("getcwd() error");
                    exit(-1);
                }

                // Opening the current directory
                p = opendir(cwd);
                if (p == NULL) {
                    perror("Cannot find directory\n");
                    exit(-1);
                }

                // Listing files in the directory
                while ((d = readdir(p)) != NULL)
                    printf("%s\t", d->d_name);
                closedir(p);
                break;

            case 3:
                printf("Enter Name of directory: ");
                scanf("%s", cwd);
                // Changing the current working directory
                if (chdir(cwd) == -1) {
                    fprintf(stderr, "Error: could not change to dir %s\n", cwd);
                    exit(1);
                } else {
                    getcwd(buf, NAME_MAX);
                    printf("CWD is %s\n", buf);
                }
                break;

            case 4:
                printf("Enter Name of directory: ");
                scanf("%s", fn);
                // Removing an empty directory
                f = rmdir(fn);
                if (f == -1) {
                    printf("\nCannot remove directory\n");
                    exit(-1);
                } else
                    printf("Directory deleted.\n");
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Wrong number entered.\n");
        }
    } while (choice != 5);

    return 0;
}
