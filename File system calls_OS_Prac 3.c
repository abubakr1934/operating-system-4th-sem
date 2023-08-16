#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char data;
    char buf[100], pat[10], temp[1024];
    int chl, ch = 0, fd, i, n, charcount = 0;
    char fname[10];
    FILE *fp;
    char *newline;

    do {
        printf("Perform different Operations on Files\n");
        printf("1. Create\n2. Read\n3. Write\n4. Read in Reverse Order\n5. Search\n6. Delete\n");
        printf("Enter your choice: ");
        scanf("%d", &chl);

        switch (chl) {
            case 1:
                printf("Enter file name to create: ");
                scanf("%s", fname);
                fd = creat(fname, 0777); // Create file with read, write, and execute permissions
                printf("File Created\n");
                printf("Enter the contents to write: ");
                scanf("%s", buf);
                charcount = strlen(buf);
                write(fd, buf, charcount);
                close(fd);
                break;

            case 2:
                printf("Enter file name to open: ");
                scanf("%s", fname);
                fd = open(fname, O_RDONLY, 0777); // Open file for reading
                printf("File opened\n");
                printf("The contents are: ");
                n = lseek(fd, 0, 2);
                printf("\nSize is: %d\n", n);
                lseek(fd, 0, 0);
                for (i = 1; i <= n; i++) {
                    read(fd, &data, 1);
                    printf("%c", data);
                }
                close(fd);
                break;

            case 3:
                printf("Enter file name to open: ");
                scanf("%s", fname);
                fd = open(fname, O_WRONLY | O_APPEND, 0777); // Open file for writing (append mode)
                printf("File opened\n");
                printf("Enter the contents to write: ");
                scanf("%s", buf);
                charcount = strlen(buf);
                write(fd, buf, charcount);
                close(fd);
                break;

            case 4:
                printf("Enter file name to open: ");
                scanf("%s", fname);
                fd = open(fname, O_RDONLY, 0777); // Open file for reading
                printf("File opened\n");
                printf("The contents in reverse order are: ");
                n = lseek(fd, 0, 2);
                lseek(fd, -1, 2);
                while (n-- > 0) {
                    read(fd, &data, 1);
                    printf("%c", data);
                    lseek(fd, -2, 1);
                }
                close(fd);
                break;

            case 5:
                printf("Enter file name to open: ");
                scanf("%s", fname);
                printf("Enter the pattern to be searched: ");
                scanf("%s", pat);
                fp = fopen(fname, "r"); // Open file for reading
                printf("File opened\n");
                while (fgets(temp, 1000, fp) != NULL) {
                    if (newline = strstr(temp, "\n"))
                        *newline = '\0';
                    if (strstr(temp, pat) != NULL) {
                        printf("%s\n", temp);
                    }
                }
                fclose(fp);
                break;

            case 6:
                printf("Enter file name to delete: ");
                scanf("%s", fname);
                unlink(fname); // Delete the specified file
                printf("File deleted.\n");
                break;
        }

        printf("Do you want to continue? Enter 0 for NO or 1 for YES: ");
        scanf("%d", &ch);
    } while (ch == 1);

    return 0;
}
