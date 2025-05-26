#ifndef CORE_H
#define CORE_H

#define MAXBUFFERSIZE 1000

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int, int);

char inputCharOption(const char[]);

void inputCString(char*, int, int);

void inputNumString(char*, int, int);

void displayFormattedPhone(const char*);

#endif