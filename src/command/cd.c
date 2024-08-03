#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(const char *path) {
    write(2, "minishell: cd: ", 15);
    write(2, path, strlen(path));
    write(2, ": No such file or directory\n", 28);
}

void cmd_cd(t_data *data) {
    t_token *node = data->token;
    char *path = NULL;
    char *home;

    // 'cd' komutundan sonraki token'ı kontrol et
    if (node && node->next) {
        path = node->next->value;
    }

    // Eğer path NULL veya boş ise HOME dizinine git
    if (path == NULL || ft_strcmp(path, "") == 0) {
        home = getenv("HOME");
        if (home == NULL) {
            write(2, "minishell: cd: HOME environment variable not set\n", 50);
            return;
        }
        path = home;
    }
    // '~' ile başlayan path için home dizinine git
    else if (path[0] == '~') {
        home = getenv("HOME");
        if (home == NULL) {
            write(2, "minishell: cd: HOME environment variable not set\n", 50);
            return;
        }
        char *new_path = malloc(strlen(home) + strlen(path));
        if (!new_path) {
            write(2, "minishell: cd: memory allocation failed\n", 41);
            return;
        }
        strcpy(new_path, home);
        strcat(new_path, path + 1);
        path = new_path;
    }

    // Debugging: path ve chdir sonuçlarını yazdır
    printf("Trying to change directory to: %s\n", path);

    // Dizin değiştirme işlemi
    if (chdir(path) != 0) {
        print_error(path);
    }

    // Bellek yönetimi
    if (path && path[0] == '~') {
        free(path);
    }
}
