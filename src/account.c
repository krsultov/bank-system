/* Accounts and deposit/withdraw operations - Krum. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account.h"

void accountlist_add(AccountList *accounts, Account a) {
    if (accounts->count >= accounts->capacity) {
        size_t newCapacity = accounts->capacity == 0 ? 4 : accounts->capacity * 2;
        Account *newItems = realloc(accounts->items, newCapacity * sizeof(Account));
        if (!newItems) {
            perror("Failed to allocate memory for accounts");
            exit(EXIT_FAILURE);
        }
        accounts->items = newItems;
        accounts->capacity = newCapacity;
    }
    accounts->items[accounts->count++] = a;
}

int accounts_find_by_number(const AccountList *accounts, const char *number) {
    for (size_t i = 0; i < accounts->count; i++) {
        if (strcmp(accounts->items[i].number, number) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int accounts_find_by_owner(const AccountList *accounts, int ownerId) {
    for (size_t i = 0; i < accounts->count; i++) {
        if (accounts->items[i].ownerId == ownerId) {
            return (int)i;
        }
    }
    return -1;
}

void generate_account_number(char *out, size_t size, const AccountList *accounts) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charsetLen = (int)(sizeof(charset) - 1);
    const int numberLen = 10;

    do {
        for (int i = 0; i < numberLen && (size_t)(i + 1) < size; i++) {
            out[i] = charset[rand() % charsetLen];
        }
        out[numberLen] = '\0';
    } while (accounts_find_by_number(accounts, out) != -1);
}

/* Builds a new account with a unique number; the caller adds it to the list. */
Account account_create(AccountList *accounts, int ownerId) {
    Account a;
    generate_account_number(a.number, sizeof(a.number), accounts);
    a.balance = 0.0;
    a.ownerId = ownerId;
    return a;
}

void accounts_save(const AccountList *accounts, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        return;
    }
    fwrite(&accounts->count, sizeof(size_t), 1, f);
    if (accounts->count > 0 && accounts->items) {
        fwrite(accounts->items, sizeof(Account), accounts->count, f);
    }
    fclose(f);
}

void accounts_load(AccountList *accounts, const char *path) {
    accounts->items = NULL;
    accounts->count = 0;
    accounts->capacity = 0;

    FILE *f = fopen(path, "rb");
    if (!f) {
        return;
    }

    size_t count = 0;
    if (fread(&count, sizeof(size_t), 1, f) != 1) {
        fclose(f);
        return;
    }
    for (size_t i = 0; i < count; i++) {
        Account a;
        if (fread(&a, sizeof(Account), 1, f) != 1) {
            break;
        }
        accountlist_add(accounts, a);
    }
    fclose(f);
}

void accountlist_free(AccountList *accounts) {
    free(accounts->items);
    accounts->items = NULL;
    accounts->count = 0;
    accounts->capacity = 0;
}

/* deposit/withdraw operations are added in the next commit */

int deposit(Account *acc, double amount) { (void)acc; (void)amount; return 0; }
int withdraw(Account *acc, double amount) { (void)acc; (void)amount; return 0; }

void menu_deposit(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Депозит] Заготовка.\n"); }
void menu_withdraw(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Теглене] Заготовка.\n"); }
