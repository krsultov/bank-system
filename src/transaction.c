/* Transaction queue, transfer and processing - Krum. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transaction.h"
#include "account.h"
#include "util.h"

void txqueue_init(TxQueue *q) { q->head = NULL; q->tail = NULL; }

void txqueue_enqueue(TxQueue *q, Transaction tx) {
    TxNode *node = malloc(sizeof(TxNode));
    if (!node) {
        perror("Failed to allocate memory for transaction");
        exit(EXIT_FAILURE);
    }
    node->tx = tx;
    node->next = NULL;
    if (q->tail == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
}

int txqueue_dequeue(TxQueue *q, Transaction *out) {
    if (q->head == NULL) {
        return 0;
    }
    TxNode *node = q->head;
    *out = node->tx;
    q->head = node->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(node);
    return 1;
}

int txqueue_is_empty(const TxQueue *q) { return q->head == NULL; }

void txqueue_free(TxQueue *q) {
    TxNode *node = q->head;
    while (node != NULL) {
        TxNode *next = node->next;
        free(node);
        node = next;
    }
    q->head = NULL;
    q->tail = NULL;
}

void transactions_save(const TxQueue *q, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        return;
    }
    size_t count = 0;
    for (TxNode *n = q->head; n != NULL; n = n->next) {
        count++;
    }
    fwrite(&count, sizeof(size_t), 1, f);
    for (TxNode *n = q->head; n != NULL; n = n->next) {
        fwrite(&n->tx, sizeof(Transaction), 1, f);
    }
    fclose(f);
}

void transactions_load(TxQueue *q, const char *path) {
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
        Transaction tx;
        if (fread(&tx, sizeof(Transaction), 1, f) != 1) {
            break;
        }
        txqueue_enqueue(q, tx);
    }
    fclose(f);
}

void menu_transfer(Bank *bank, const char *accountNumber) {
    printf("Номер на получаваща сметка: ");
    char target[16];
    read_line(target, sizeof(target));

    if (accounts_find_by_number(&bank->accounts, target) < 0) {
        printf("Грешка: сметката не съществува.\n");
        return;
    }
    if (strcmp(target, accountNumber) == 0) {
        printf("Грешка: не може да превеждате към собствената си сметка.\n");
        return;
    }

    printf("Сума за трансфер: ");
    double amount;
    if (!read_amount(&amount)) {
        printf("Грешка: невалидна сума.\n");
        return;
    }

    Transaction tx;
    strcpy(tx.opCode, "TRANSFER");
    tx.amount = amount;
    strncpy(tx.fromAccount, accountNumber, sizeof(tx.fromAccount) - 1);
    tx.fromAccount[sizeof(tx.fromAccount) - 1] = '\0';
    strncpy(tx.toAccount, target, sizeof(tx.toAccount) - 1);
    tx.toAccount[sizeof(tx.toAccount) - 1] = '\0';

    txqueue_enqueue(&bank->queue, tx);
    transactions_save(&bank->queue, TRANSACTIONS_FILE);
    printf("Трансферът е добавен в опашката за обработка.\n");
}
void process_transactions(Bank *bank) { (void)bank; printf("[Обработка] Заготовка.\n"); }
