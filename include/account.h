#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "models.h"

void accountlist_add(AccountList *accounts, Account a);
int accounts_find_by_number(const AccountList *accounts, const char *number);
int accounts_find_by_owner(const AccountList *accounts, int ownerId);

void generate_account_number(char *out, size_t size, const AccountList *accounts);
Account account_create(AccountList *accounts, int ownerId);

int deposit(Account *acc, double amount);
int withdraw(Account *acc, double amount);

void accounts_load(AccountList *accounts, const char *path);
void accounts_save(const AccountList *accounts, const char *path);
void accountlist_free(AccountList *accounts);

void menu_account_info(Bank *bank, const char *accountNumber);
void menu_deposit(Bank *bank, const char *accountNumber);
void menu_withdraw(Bank *bank, const char *accountNumber);

#endif
