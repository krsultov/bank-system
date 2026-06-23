#ifndef MODELS_H
#define MODELS_H

#include <stddef.h>

#define USERS_FILE        "users.dat"
#define ACCOUNTS_FILE     "accounts.dat"
#define TRANSACTIONS_FILE "transactions.dat"

typedef struct {
    int id;
    char username[32];
    unsigned long passwordHash;
} User;

typedef struct {
    char number[16];
    double balance;
    int ownerId;
} Account;

typedef struct {
    char opCode[16];
    double amount;
    char fromAccount[16];
    char toAccount[16];
} Transaction;

typedef struct {
    User *items;
    size_t count;
    size_t capacity;
} UserList;

typedef struct {
    Account *items;
    size_t count;
    size_t capacity;
} AccountList;

/* FIFO queue of pending transactions */
typedef struct TxNode {
    Transaction tx;
    struct TxNode *next;
} TxNode;

typedef struct {
    TxNode *head;
    TxNode *tail;
} TxQueue;

typedef struct {
    UserList users;
    AccountList accounts;
    TxQueue queue;
} Bank;

#endif
