#ifndef USER_H
#define USER_H

#include "models.h"

unsigned long hash_password(const char *password);

void userlist_add(UserList *users, User u);
int users_find_by_name(const UserList *users, const char *name);
int users_next_id(const UserList *users);

int register_user(Bank *bank, const char *name, const char *pass);
int login_user(const UserList *users, const char *name, const char *pass);

void users_load(UserList *users, const char *path);
void users_save(const UserList *users, const char *path);
void userlist_free(UserList *users);

void menu_register(Bank *bank);
int menu_login(Bank *bank);

#endif
