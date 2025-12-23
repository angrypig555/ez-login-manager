#include <stdio.h>
#include <string.h>

char userfile[100];
char passwordfile[100];
char username[100];
FILE *fptr;
int logged_in;


int searchUser(const char *target) {
  fptr = fopen(userfile, "r");
  if (!fptr) {
    printf("error: failed to open users file\n");
    return 1;
  }
  char openedUserFile[100];
  while (fgets(openedUserFile, 100, fptr)) {
    openedUserFile[strcspn(openedUserFile, "\r\n")] = '\0';
    if (strcmp(openedUserFile, target) == 0 ) {
      fclose(fptr);
      return 1;
    }
  }
  fclose(fptr);
  return 0;
  
}

int main(int argc, char *argv[]) {
  printf("ez login manager started\n");
  if (argc != 3) {
    printf("error: files not provided\n");
    printf("syntax: ez-login-manager <users.txt> <password.txt>\n");
    return 1;
  }
  strcpy(userfile, argv[1]);
  strcpy(passwordfile, argv[2]);
  logged_in = 0;
  while (logged_in == 0) {
    printf("please enter username:\n");
    scanf("%s", username);
    if (!searchUser(username)) {
      printf("invalid username\n");
    } else {
      printf("succes!\n");
      logged_in = 1;
    }
  }

}
