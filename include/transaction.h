#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "models.h"

void txqueue_init(TxQueue *q);
void txqueue_enqueue(TxQueue *q, Transaction tx);
int txqueue_dequeue(TxQueue *q, Transaction *out);
int txqueue_is_empty(const TxQueue *q);
void txqueue_free(TxQueue *q);

void transactions_load(TxQueue *q, const char *path);
void transactions_save(const TxQueue *q, const char *path);

void menu_transfer(Bank *bank, const char *accountNumber);
void process_transactions(Bank *bank);

#endif
