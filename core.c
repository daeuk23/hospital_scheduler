#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "core.h"

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//get a valid integer from the keyboard (No need to modify this part)
int inputInt(void)
{
    int num;
    char newLane = 'X';
    do
    {
        scanf("%d%c", &num, &newLane);
        if (newLane != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLane != '\n');
    return num;
}


//get a valid positive integer from the keyboard
int inputIntPositive(void)
{
    int num, validNum = 0;
    do
    {
        num = inputInt();
        if (num > 0)
        {
            validNum = 1;
        }
        else if (num < 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (validNum == 0);
    return num;
}

// gets integer value in range from the keyboard
int inputIntRange(int minRange, int maxRange)
{
    int num, validNum = 0;
    do
    {
        num = inputInt();
        if (num >= minRange && num <= maxRange)
        {
            validNum = 1;
        }
        else if (num < minRange || num > maxRange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", minRange, maxRange);
        }
    } while (validNum == 0);
    return num;
}

//gets valid single character from user keyboard
char inputCharOption(const char validChar[])
{
    char userChar[100] = { 0 }, usrChr;
    int hasValid = 0, charNum,i;
    do
    {
        scanf("%[^\n]", userChar);
        clearInputBuffer();
        charNum = strlen(userChar);
        if (charNum == 1)
        {
            for (i = 0; hasValid == 0 && validChar[i] != '\0'; i++)
            {
                if (validChar[i] == userChar[0])
                {
                    hasValid = 1;
                    usrChr = validChar[0];
                }
            }
        }
        if(hasValid==0)
        {
            printf("ERROR: Character must be one of [%s]: ", validChar);
        }
    } while (hasValid == 0);
    return usrChr;
}

//The purpose of this function is to obtain user input for a C string value with a length
void inputCString(char* stringC, int minNum, int maxNum)
{
    int length, flag = 0, i;
    char chString[MAXBUFFERSIZE + 1] = { 0 }, ch;
    do
    {
        i = 0;
        while ((ch = getchar()) != '\n')
        {
            chString[i] = ch;
            i++;
        }
        chString[i] = '\0';
        length = strlen(chString);
        if (length<minNum || length>maxNum)
        {
            if (minNum == maxNum)
            {
                printf("ERROR: String length must be exactly %d chars: ", minNum);
            }
            else if (length < minNum)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minNum, maxNum);
            }
            else if (length > maxNum)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxNum);
            }
        }
        else
        {
            flag = 1;
            strcpy(stringC, chString);
        }
    } while (flag == 0);
}


//The purpose of this function is to obtain user input for a C string value with a length
void inputNumString(char* stringC, int minNum, int maxNum)
{
    int length, flag = 0, i;
    char chString[MAXBUFFERSIZE + 1] = { 0 }, ch;
    do
    {
        i = 0;
        while ((ch = getchar()) != '\n')
        {
            chString[i] = ch;
            i++;
        }
        chString[i] = '\0';
        length = strlen(chString);
        if (length<minNum || length>maxNum)
        {
            if (minNum == maxNum)
            {
                printf("Invalid %d-digit number! Number: ", minNum);
            }
            else if (length < minNum)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minNum, maxNum);
            }
            else if (length > maxNum)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxNum);
            }
        }
        else
        {
            flag = 1;
            strcpy(stringC, chString);
        }
    } while (flag == 0);
}


//The purpose of this function is to display an array of 10 - character digits as a formatted phone number
void displayFormattedPhone(const char* numArray)
{
    int i, length = 0;
    char visualArray[MAXBUFFERSIZE + 1];

    for (i = 0; (numArray != NULL) && isdigit(numArray[i]); i++)
    {
        length++;
    }

    if (length == 10)
    {
        printf("(");
        strncpy(visualArray, numArray, 3);
        visualArray[3] = '\0';
        printf("%s", visualArray);
        printf(")");
        strncpy(visualArray, numArray + 3, 3);
        visualArray[3] = '\0';
        printf("%s", visualArray);
        printf("-");
        strncpy(visualArray, numArray + 6, 4);
        visualArray[4] = '\0';
        printf("%s", visualArray);
    }
    else
    {
        printf("(___)___-____");
    }
}