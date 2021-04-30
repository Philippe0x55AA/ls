#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>


typedef struct FilesProps{
    struct dirent* file;
    struct stat fileStats;

}FilesProps;

int main(int argc, char **argv){
    int nbFiles = 0;
    int option;
    char curr[256];
    DIR *dir = NULL;

    FilesProps props;

    if(getcwd(curr,sizeof(curr)) == NULL)
        perror("Erreur: ");

    printf("current directory: %s\n",curr);

    dir = opendir(getcwd(curr,sizeof(curr)));

    if(dir == NULL)
        exit(1);

    props.file = readdir(dir);

    if (closedir(dir) == -1)
        exit(1);

    if (stat(argv[2], &props.fileStats) == -1) {
      perror("stat");
      exit(EXIT_SUCCESS);
}


    while((option = getopt(argc,argv,"ilgm")) != -1){

                switch(option){

                  case 'i':
                    while(((props.file) = readdir(dir)) != NULL){

                        printf("%lu\t %s\n ",props.file->d_ino,props.file->d_name);
                        nbFiles++;
                      }
                    printf("\nFiles: %d\n",nbFiles-1);
                    break;

                  case 'l':
                      while(((props.file) = readdir(dir)) != NULL){

                        stat(props.file->d_name,&props.fileStats);
                        printf("%o\t%d\t%d\t%s\t\n",props.fileStats.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO),props.fileStats.st_gid,props.fileStats.st_uid,props.file->d_name);
                        nbFiles++;
                  }
                    printf("\nFiles: %d\n",nbFiles-1);
                    break;

                  case 'g':
                    while(((props.file) = readdir(dir)) != NULL){

                      stat(props.file->d_name,&props.fileStats);
                      printf("%o\t%d\t%s\t\n",props.fileStats.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO),props.fileStats.st_gid,props.file->d_name);
                      nbFiles++;
                }
                  printf("\nFiles: %d\n",nbFiles-1);
                  break;

                  case 'm':
                    while(((props.file) = readdir(dir)) != NULL){

                      stat(props.file->d_name,&props.fileStats);
                      printf("%s,\t",props.file->d_name);
                      nbFiles++;
              }
                printf("\nFiles: %d\n",nbFiles-1);
                break;

            }
        }
    }
