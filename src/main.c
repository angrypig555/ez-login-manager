#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

char userfile[100];
char passwordfile[100];
char username[100];
char password[100];
char password_hash[33];
FILE *fptr;
int usrnamelogged_in;
int psswdlogged_in;


void md5_string(const char *input, char *output) {
  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)input, strlen(input), digest);

  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    sprintf(&output[i * 2], "%02x", digest[i]);

  output[32] = '\0';
}

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

int checkPassowrd(const char *target, const char *target_hash) {
  fptr = fopen(passwordfile, "r");
  if (!fptr) {
    printf("error: failed to open password file\n");
    return 1;
  }
  char openedPasswordFile[100];

  while (fgets(openedPasswordFile, 100, fptr)) {
    openedPasswordFile[strcspn(openedPasswordFile, "\r\n")] = '\0';

    char *file_user = strtok(openedPasswordFile, ":");
    char *file_hash = strtok(NULL, ":");

    if (!target || !target_hash)
      continue;

    if (strcmp(file_user, target) == 0 && strcmp(file_hash, target_hash) == 0) {
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
  usrnamelogged_in = 0;
  psswdlogged_in = 0;
  while (usrnamelogged_in == 0) {
    printf("please enter username:\n");
    scanf("%s", username);
    if (!searchUser(username)) {
      printf("invalid username\n");
    } else {
      printf("succes!\n");
      usrnamelogged_in = 1;
    }
  }
  while (psswdlogged_in == 0) {
    printf("enter password for %s:\n", username);
    scanf("%s", password);
    md5_string(password, password_hash);

    if (!checkPassowrd(username, password_hash)) {
      printf("invalid password\n");
    } else {
      printf("succes!\n");
      psswdlogged_in = 1;
    }
  }

}
