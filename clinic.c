#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"
#include "clinic.h"

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data); 
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient); 
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient); 
            suspend();
            break;
        }
    } while (selection);
}




// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, eglibleNum = 0;
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            eglibleNum = 1;
        }
    }
    if (eglibleNum == 0)
    {
        printf("* **No records found * **");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        printf("\n");
        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection != 0);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, available = 1;
    for (i = 0; (available == 1) && (i < max); i++)
    {
        if (patient[i].patientNumber == 0)
        {
            available = 0;
            patient[i].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[i]);
            printf("*** New patient record added ***\n");
        }
    }
    if (available == 1)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    printf("\n");
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int num, matchedIndex;
    printf("Enter the patient number: ");
    num = inputIntPositive();
    printf("\n");
    matchedIndex = findPatientIndexByPatientNum(num, patient, max);
    if (matchedIndex == -1)
    {
        printf("ERROR: Patient record not found!\n");
        printf("\n");
    }
    else
    {
        menuPatientEdit(&patient[matchedIndex]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int num, matchedIndex;
    char select;
    printf("Enter the patient number: ");
    num = inputIntPositive();
    printf("\n");

    matchedIndex = findPatientIndexByPatientNum(num, patient, max);
    if (matchedIndex == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[matchedIndex], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        select = inputCharOption("yn");
        if (select == 'y')
        {
            patient[matchedIndex].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    printf("\n");
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;
    displayScheduleTableHeader(&data->appointments->date, 1);
    sortByDate(data);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (noEmpty(&data->appointments[i]))
        {
            for (j = 0; j < data->maxPatient; j++)
            {
                if (data->patients[j].patientNumber == data->appointments[i].patNum)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }

    }
    printf("\n");
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j;
    struct Date usrDate = { 0 };
    usrDate = validD();
    printf("\n");
    displayScheduleTableHeader(&usrDate, 0);
    sortByDate(data);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (noEmpty(&data->appointments[i]))
        {
            if ((usrDate.year == data->appointments[i].date.year) && (usrDate.month == data->appointments[i].date.month) && (usrDate.day == data->appointments[i].date.day))
            {
                for (j = 0; j < data->maxPatient; j++)
                {
                    if (data->patients[j].patientNumber == data->appointments[i].patNum)
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients)
{
    int i, flag = 0, validExist, nextSlot;
    struct Appointment addPatient = { 0 };
    printf("Patient Number: ");
    addPatient.patNum = inputIntPositive();
    do
    {
        addPatient.date = validD();
        addPatient.time = validT();
        validExist = 0;
        nextSlot = 0;
        for (i = 0; i < maxAppointments; i++)
        {
            if (noEmpty(&appoints[i]))
            {
                if (addPatient.date.year == appoints[i].date.year && addPatient.date.month == appoints[i].date.month && addPatient.date.day == appoints[i].date.day && addPatient.time.hour == appoints[i].time.hour && addPatient.time.min == appoints[i].time.min)
                {
                    validExist = 1;
                }
                nextSlot++;
            }
        }
        printf("\n");
        if (validExist == 1)
        {
            printf("ERROR: Appointment timeslot is not available!\n\n");
        }
        else
        {
            flag = 0;
            appoints[nextSlot].patNum = addPatient.patNum;
            appoints[nextSlot].date = addPatient.date;
            appoints[nextSlot].time = addPatient.time;
            printf("*** Appointment scheduled! ***\n\n");
            flag = 1;
        }
    } while (flag == 0);
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients)
{
    int patientNum,patIndex, matchedIndex = 0,i, flag=0;
    char selection;
    struct Date usrDate = { 0 };
    printf("Patient Number: ");
    patientNum = inputIntPositive();
    patIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatients);
    if (patIndex == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        usrDate = validD();
        for (i = 0; i < maxAppointments && flag == 0; i++)
        {
            if ((usrDate.year == appoints[i].date.year) && (usrDate.month == appoints[i].date.month) && (usrDate.day == appoints[i].date.day))
            {
                if (appoints[i].patNum == patientNum)
                {
                    flag = 1;
                    matchedIndex = i;
                }
            }
        }
        printf("\n");
        displayPatientData(&patients[patIndex], FMT_FORM);
        printf("Are you sure you want to remove this appointment (y,n): ");
        selection = inputCharOption("yn");
        printf("\n");

        if (selection == 'y') {
            appoints[matchedIndex].patNum = 0;
            printf("Appointment record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }
}

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int num, matchedIndex;
    printf("Search by patient number: ");
    num = inputIntPositive();
    printf("\n");
    matchedIndex = findPatientIndexByPatientNum(num, patient, max);
    if (matchedIndex != -1)
    {
        displayPatientData(&patient[matchedIndex], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int matchedNum = 0, i;
    char userPhone[PHONE_LEN + 1] = { 0 };
    printf("Search by phone number: ");
    inputCString(userPhone, PHONE_LEN, PHONE_LEN);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, userPhone) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            matchedNum++;
        }
    }
    if (matchedNum == 0)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int nextPatNum, largestPatNum = patient[0].patientNumber, i;
    for (i = 0; i < max; i++)
    {
        if (largestPatNum < patient[i].patientNumber)
        {
            largestPatNum = patient[i].patientNumber;
        }
    }
    nextPatNum = largestPatNum + 1;
    return nextPatNum;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, result, noValid = 0;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            result = i;
            noValid = 1;
        }
    }
    if (noValid == 0)
    {
        result = -1;
    }
    return result;
}

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    printf("\n");
    if (selection == 4)
    {
        strcpy(phone->description, "TBD");
        phone->number[0] = '\0';
    }
    else
    {
        if (selection == 1)
        {
            strcpy(phone->description, "CELL");
        }
        if (selection == 2)
        {
            strcpy(phone->description, "HOME");
        }
        if (selection == 3)
        {
            strcpy(phone->description, "WORK");
        }
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputNumString(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }
}

//additional function
int noEmpty(const struct Appointment* appoints)
{
    int empty = 0;

    if (appoints->patNum != 0) {
        empty = 1;
    }

    return empty;
}

struct Date validD(void)
{
    int year, month, day;

    printf("Year        : ");
    year = inputIntRange(2024, 2027);

    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    if (month == 2)
    {
        if (year % 4 == 0)
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else 
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    else
    {
        printf("Day (1-30)  : ");
        day = inputIntRange(1, 30);
    }

    struct Date date = { year, month, day };

    return date;
}

struct Time validT(void)
{
    int hour, min, flag = 1;
    while (flag == 1)
    {
        printf("Hour (0-23)  : ");
        hour = inputIntRange(0, 23);

        printf("Minute (0-59): ");
        min = inputIntRange(0, 59);

        if (hour >= TimeStart && hour < TimeEnd && min % Interval == 0) 
        {
            flag = 0;
        }
        else if (hour == TimeEnd && min == 0) 
        {
            flag = 0;
        }
        else 
        {
            printf("ERROR: Time must be between %02d:00 and %02d:00 in %d minute intervals.\n\n", TimeStart, TimeEnd, Interval);
        }
    }
    struct Time time = { hour, min };

    return time;
}

void sortByDate(struct ClinicData* data)
{
    int i,j;
    struct Appointment crCl;
    for (i = data->maxAppointments - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            struct Date curD = data->appointments[j].date;
            struct Date nextD = data->appointments[j + 1].date;
            struct Time curT = data->appointments[j].time;
            struct Time nextT = data->appointments[j + 1].time;

            if (curD.year > nextD.year || (curD.year == nextD.year && curD.month > nextD.month) ||
                (curD.year == nextD.year && curD.month == nextD.month && curD.day > nextD.day) ||
                (curD.year == nextD.year && curD.month == nextD.month && curD.day == nextD.day && curT.hour > nextT.hour) ||
                (curD.year == nextD.year && curD.month == nextD.month && curD.day == nextD.day && curT.hour == nextT.hour && curT.min > nextT.min)) {

                crCl = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = crCl;
            }
        }
        data->appointments[i] = data->appointments[j];
    }
}


// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i;
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        i = 0;
        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }
    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i;
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        i = 0;
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patNum, &appoints[i].date.year, & appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)
        {
            i++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file\n");
    }
    return i;
}