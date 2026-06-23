#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "account.h"
#include "util.h"

unsigned long hash_password(const char *password) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*password++)) {
        hash = hash * 33 + c;
    }
    return hash;
}

void userlist_add(UserList *users, User u) {
    if (users->count >= users->capacity) {
        size_t new_capacity = users->capacity == 0 ? 4 : users->capacity * 2;
        User *new_items = realloc(users->items, new_capacity * sizeof(User));
        if (!new_items) {
            perror("Failed to allocate memory for users");
            exit(EXIT_FAILURE);
        }
        users->items = new_items;
        users->capacity = new_capacity;
    }
    users->items[users->count++] = u;
}

int users_find_by_name(const UserList *users, const char *name) {
    if (!users || !users->items) return -1;
    for (size_t i = 0; i < users->count; i++) {
        if (strcmp(users->items[i].username, name) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int users_next_id(const UserList *users) {
    if (!users || users->count == 0) return 1;
    int max_id = 0;
    for (size_t i = 0; i < users->count; i++) {
        if (users->items[i].id > max_id) {
            max_id = users->items[i].id;
        }
    }
    return max_id + 1;
}

int register_user(Bank *bank, const char *name, const char *pass) {
    if (users_find_by_name(&bank->users, name) != -1) {
        return 0;
    }

    User u;
    u.id = users_next_id(&bank->users);
    strncpy(u.username, name, sizeof(u.username) - 1);
    u.username[sizeof(u.username) - 1] = '\0';
    u.passwordHash = hash_password(pass);

    userlist_add(&bank->users, u);

    Account a = account_create(&bank->accounts, u.id);
    accountlist_add(&bank->accounts, a);

    users_save(&bank->users, USERS_FILE);
    accounts_save(&bank->accounts, ACCOUNTS_FILE);

    return 1;
}

int login_user(const UserList *users, const char *name, const char *pass) {
    int idx = users_find_by_name(users, name);
    if (idx == -1) {
        return -1;
    }
    unsigned long hash = hash_password(pass);
    if (users->items[idx].passwordHash == hash) {
        return users->items[idx].id;
    }
    return -1;
}
void users_load(UserList *users, const char *path) {
    users->items = NULL;
    users->count = 0;
    users->capacity = 0;

    FILE *f = fopen(path, "rb");
    if (!f) {
        return;
    }

    size_t count = 0;
    if (fread(&count, sizeof(size_t), 1, f) != 1) {
        fclose(f);
        return;
    }

    if (count > 0) {
        users->items = malloc(count * sizeof(User));
        if (!users->items) {
            perror("Failed to allocate memory in users_load");
            fclose(f);
            exit(EXIT_FAILURE);
        }
        if (fread(users->items, sizeof(User), count, f) != count) {
            free(users->items);
            users->items = NULL;
            users->count = 0;
            users->capacity = 0;
            fclose(f);
            return;
        }
    }
    users->count = count;
    users->capacity = count;
    fclose(f);
}

void users_save(const UserList *users, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        return;
    }
    fwrite(&users->count, sizeof(size_t), 1, f);
    if (users->count > 0 && users->items) {
        fwrite(users->items, sizeof(User), users->count, f);
    }
    fclose(f);
}

void userlist_free(UserList *users) {
    free(users->items);
    users->items = NULL;
    users->count = 0;
    users->capacity = 0;
}

void menu_register(Bank *bank) {
    char name[64];
    char pass[64];

    printf("Потребителско име: ");
    read_line(name, sizeof(name));
    printf("Парола: ");
    read_line(pass, sizeof(pass));

    if (register_user(bank, name, pass)) {
        printf("Регистрацията е успешна!\n");
    } else {
        printf("Грешка: Потребител с това име вече съществува.\n");
    }
}

int menu_login(Bank *bank) {
    char name[64];
    char pass[64];

    printf("Потребителско име: ");
    read_line(name, sizeof(name));
    printf("Парола: ");
    read_line(pass, sizeof(pass));

    int id = login_user(&bank->users, name, pass);
    if (id >= 0) {
        printf("Влизането е успешно!\n");
    } else {
        printf("Грешна парола или потребителско име.\n");
    }
    return id;
}
