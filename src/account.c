/* Accounts and deposit/withdraw operations - Krum. */
#include <stdio.h>
#include <stdlib.h>

#include "account.h"

void accountlist_add(AccountList *accounts, Account a) { (void)accounts; (void)a; }
int accounts_find_by_number(const AccountList *accounts, const char *number) { (void)accounts; (void)number; return -1; }
int accounts_find_by_owner(const AccountList *accounts, int ownerId) { (void)accounts; (void)ownerId; return -1; }
void generate_account_number(char *out, size_t size, const AccountList *accounts) { (void)accounts; if (size > 0) out[0] = '\0'; }

Account account_create(AccountList *accounts, int ownerId) {
    (void)accounts;
    Account a;
    a.number[0] = '\0';
    a.balance = 0.0;
    a.ownerId = ownerId;
    return a;
}

int deposit(Account *acc, double amount) { (void)acc; (void)amount; return 0; }
int withdraw(Account *acc, double amount) { (void)acc; (void)amount; return 0; }
void accounts_load(AccountList *accounts, const char *path) { (void)accounts; (void)path; }
void accounts_save(const AccountList *accounts, const char *path) { (void)accounts; (void)path; }

void accountlist_free(AccountList *accounts) {
    free(accounts->items);
    accounts->items = NULL;
    accounts->count = 0;
    accounts->capacity = 0;
}

void menu_deposit(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Депозит] Заготовка.\n"); }
void menu_withdraw(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Теглене] Заготовка.\n"); }
