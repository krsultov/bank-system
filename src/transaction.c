/* Transaction queue, transfer and processing - Krum. */
#include <stdio.h>
#include <stdlib.h>

#include "transaction.h"

void txqueue_init(TxQueue *q) { q->head = NULL; q->tail = NULL; }
void txqueue_enqueue(TxQueue *q, Transaction tx) { (void)q; (void)tx; }
int txqueue_dequeue(TxQueue *q, Transaction *out) { (void)q; (void)out; return 0; }
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

void transactions_load(TxQueue *q, const char *path) { (void)q; (void)path; }
void transactions_save(const TxQueue *q, const char *path) { (void)q; (void)path; }

void menu_transfer(Bank *bank, const char *accountNumber) { (void)bank; (void)accountNumber; printf("[Трансфер] Заготовка.\n"); }
void process_transactions(Bank *bank) { (void)bank; printf("[Обработка] Заготовка.\n"); }
