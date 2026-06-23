#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "models.h"
#include "util.h"
#include "user.h"
#include "account.h"
#include "transaction.h"

static void print_main_menu(void) {
    printf("\n===== БАНКОВ СОФТУЕР =====\n");
    printf("1. Логин\n");
    printf("2. Регистрация\n");
    printf("3. Изход\n");
    printf("Изберете опция: ");
}

static void print_session_menu(const char *username) {
    printf("\n----- Здравейте, %s -----\n", username);
    printf("1. Депозит\n");
    printf("2. Теглене\n");
    printf("3. Трансфер\n");
    printf("4. Обработка на транзакции\n");
    printf("5. Логаут\n");
    printf("Изберете опция: ");
}

static void session_loop(Bank *bank, int userId) {
    int ai = accounts_find_by_owner(&bank->accounts, userId);
    if (ai < 0) {
        printf("Грешка: за този потребител няма намерена сметка.\n");
        return;
    }

    char accountNumber[16];
    strcpy(accountNumber, bank->accounts.items[ai].number);

    char username[32] = "";
    for (size_t i = 0; i < bank->users.count; i++) {
        if (bank->users.items[i].id == userId) {
            strcpy(username, bank->users.items[i].username);
            break;
        }
    }

    int running = 1;
    while (running) {
        print_session_menu(username);
        char choice[16];
        read_line(choice, sizeof(choice));

        if (strcmp(choice, "1") == 0) {
            menu_deposit(bank, accountNumber);
        } else if (strcmp(choice, "2") == 0) {
            menu_withdraw(bank, accountNumber);
        } else if (strcmp(choice, "3") == 0) {
            menu_transfer(bank, accountNumber);
        } else if (strcmp(choice, "4") == 0) {
            process_transactions(bank);
        } else if (strcmp(choice, "5") == 0) {
            printf("Излизане от профила...\n");
            running = 0;
        } else {
            printf("Невалидна опция.\n");
        }
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    Bank bank;
    bank.users.items = NULL;
    bank.users.count = 0;
    bank.users.capacity = 0;
    bank.accounts.items = NULL;
    bank.accounts.count = 0;
    bank.accounts.capacity = 0;
    txqueue_init(&bank.queue);

    users_load(&bank.users, USERS_FILE);
    accounts_load(&bank.accounts, ACCOUNTS_FILE);
    transactions_load(&bank.queue, TRANSACTIONS_FILE);

    int running = 1;
    while (running) {
        print_main_menu();
        char choice[16];
        read_line(choice, sizeof(choice));

        if (strcmp(choice, "1") == 0) {
            int id = menu_login(&bank);
            if (id >= 0) {
                session_loop(&bank, id);
            }
        } else if (strcmp(choice, "2") == 0) {
            menu_register(&bank);
        } else if (strcmp(choice, "3") == 0) {
            printf("Довиждане!\n");
            running = 0;
        } else {
            printf("Невалидна опция.\n");
        }
    }

    userlist_free(&bank.users);
    accountlist_free(&bank.accounts);
    txqueue_free(&bank.queue);
    return 0;
}
