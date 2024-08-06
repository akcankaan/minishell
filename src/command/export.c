#include <stdio.h>
#include "../../includes/minishell.h"

// Anahtar ve değer ayıklama işlemi
void extract_key_value(const char *arg, char **key, char **value) {
    int len = 0;
    char *equals_sign = ft_strchr(arg, '=');
    if (equals_sign) {
        len = equals_sign - arg;
        *key = ft_substr(arg, 0, len);
        *value = ft_strdup(equals_sign + 1);
        add_garbage_c(*value);
    } else {
        *key = ft_strdup(arg);
        *value = NULL;
    }
    add_garbage_c(*key);
}

// Ortam değişkenlerini yazdırma
void print_env_var(const t_env *env) {
    while (env && env->key) {
        printf("declare -x %s=", env->key);
        if (env->value) {
            printf("\"%s\"\n", env->value);
        } else {
            printf("\n");
        }
        env = env->next;
    }
}

// Ortam değişkenlerini güncelleme veya ekleme
void update_or_add_env_var(char *key, char *value, t_data *data) {
    t_env *env = get_env(data, key);
    if (env) {
        if (value) {
            garbage_collecter(env->value);
            env->value = ft_strdup(value);
            add_garbage_c(env->value);
        }
    } else {
        env = gc_malloc(sizeof(t_env));
        env->key = ft_strdup(key);
        env->value = value ? ft_strdup(value) : NULL;
        if (env->value) add_garbage_c(env->value);
        env->next = data->env;
        data->env = env;
        add_garbage_c(env->key);
    }
}

// Anahtar doğrulama
int is_valid_key(const char *key) {
    if (!key || !ft_isalpha(key[0])) return 0;
    for (int i = 1; key[i]; i++) {
        if (!ft_isalnum(key[i])) return 0;
    }
    return 1;
}

// Export komutu işleme
void cmd_export(t_data *data) {
    char *key;
    char *value;

    if (data->token && data->token->value) {
        t_token *current = data->token;
        while (current) {
            extract_key_value(current->value, &key, &value);
            if (!is_valid_key(key)) {
                print_error(current, ": not a valid identifier\n", 1);
                return;
            }
            update_or_add_env_var(key, value, data);
            current = current->next;
        }
    } else {
        print_env_var(data->env);
    }
}
