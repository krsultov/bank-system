/* Registration and login - Eva. Placeholder until implemented. */
#include <stdio.h>
#include <stdlib.h>

#include "user.h"

unsigned long hash_password(const char *password) { (void)password; return 0; }
void userlist_add(UserList *users, User u) { (void)users; (void)u; }
int users_find_by_name(const UserList *users, const char *name) { (void)users; (void)name; return -1; }
int users_next_id(const UserList *users) { (void)users; return 1; }
int register_user(Bank *bank, const char *name, const char *pass) { (void)bank; (void)name; (void)pass; return 0; }
int login_user(const UserList *users, const char *name, const char *pass) { (void)users; (void)name; (void)pass; return -1; }
void users_load(UserList *users, const char *path) { (void)users; (void)path; }
void users_save(const UserList *users, const char *path) { (void)users; (void)path; }

void userlist_free(UserList *users) {
    free(users->items);
    users->items = NULL;
    users->count = 0;
    users->capacity = 0;
}

void menu_register(Bank *bank) {
    (void)bank;
    printf("[Регистрация] Все още не е имплементирано (Eva).\n");
}

int menu_login(Bank *bank) {
    (void)bank;
    printf("[Логин] Все още не е имплементирано (Eva).\n");
    return -1;
}
