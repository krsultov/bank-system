/* Transaction queue, transfer and processing - Krum. */
#include <stdio.h>
#include <stdlib.h>

#include "transaction.h"

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

void menu_transfer(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Трансфер] Заготовка.\n"); }
void process_transactions(Bank *bank) { (void)bank; printf("[Обработка] Заготовка.\n"); }
