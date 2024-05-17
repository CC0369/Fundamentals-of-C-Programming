#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DRIVER_SIZE 50
#define MAX_SEASON_SIZE 50
#define MAX_RACES 50
#define MAX_RACE_NUMBER_LENGTH 10
#define MAX_DIGITS 3
#define MAX_ENCODED_DIGIT_LENGTH 3
#define MAX_ENCODED_RACE_POSITION_LENGTH (MAX_ENCODED_DIGIT_LENGTH * MAX_DIGITS)
#define MAX_ENCODED_RACE_POSITIONS_LENGTH (MAX_ENCODED_RACE_POSITION_LENGTH * 3)


typedef struct driver{
    char firstName[10];
    char lastName[10]; 
    int points; 
    int number;
    char team[10];
    int year;
} driver_t; 

typedef struct {
    driver_t driverList[MAX_DRIVER_SIZE]; 
    int number_of_drivers; 
} driverList;

typedef struct race {
    char date[11];
    char location[30];
    char raceNumber[MAX_RACE_NUMBER_LENGTH];
    int numberOfLaps; 
    char P1[20];
    char P2[20];
    char P3[20]; 

} race_t;

typedef struct {
    race_t racesList[MAX_SEASON_SIZE]; 
    int number_of_races;
    int numResults; 
}   racesList;


void printMenu(racesList *races, driverList *drivers);
void displayAllResults(int number_of_races, race_t *races, driverList *drivers);
void addRaceResults(driverList *list);
void displayAllDrivers(driverList *drivers);
void calculateWorldChampion(int year); 
void encodeRaceData(const char *filename);
void displayAllTeams(driverList *drivers, int year);
void removeRaceResults(driverList *list);

int main(void){
    racesList races;
    driverList drivers;
    drivers.number_of_drivers = 0;
    races.number_of_races = 0;
    int year;

    int choice;
    do {
        printMenu(&races, &drivers);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayAllResults(races.number_of_races, races.racesList, &drivers);
                break;
            case 2:
                addRaceResults(&drivers);
                break;
            case 3:
                removeRaceResults(&drivers);
                break;
            case 4:
                encodeRaceData("race_results.bin");
                break;
            case 5:
                displayAllDrivers(&drivers);
                break;
            case 6:
                calculateWorldChampion(2024);
                break;
            case 7:
                printf("Year: ");
                scanf("%d", &year);
                displayAllTeams(&drivers, year);
                break;
            case 8:
                printf("choice 1");
                break;
            case 9:
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
                break;
        }
    } while (choice != 9);
    return 0;
}


/************
This function prints the user menu (Alexia)
inputs: none 
outputs: none
*************/ 

void printMenu(racesList *races, driverList *drivers) {
    printf("----------------------\n");
    printf("F1 Race Results Finder\n");
    printf("----------------------\n");
    printf("1. Display all race results\n");
    printf("2. Add race results\n");
    printf("3. Remove race results\n");
    printf("4. Save race results to database\n");
    printf("5. Display all drivers and their results\n");
    printf("6. Calculate World Champion\n");
    printf("7. Display all teams and their results\n");
    printf("8. Calculate Constructors' Champion\n");
    printf("9. Exit\n \n");
    printf("Please enter your choice (1-9): ");
}

/************
This function gets the total list of races (Ji Hyun)
inputs: from data  
outputs: list of all races over the period  
*************/ 

void displayAllResults(int number_of_races, race_t *races, driverList *drivers) {
    FILE *file = fopen("f1driver.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    drivers->number_of_drivers = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token == NULL) continue;

        strcpy(drivers->driverList[drivers->number_of_drivers].firstName, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(drivers->driverList[drivers->number_of_drivers].lastName, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        drivers->driverList[drivers->number_of_drivers].points = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        drivers->driverList[drivers->number_of_drivers].number = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(drivers->driverList[drivers->number_of_drivers].team, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        drivers->driverList[drivers->number_of_drivers].year = atoi(token);

        drivers->number_of_drivers++;
    }
    fclose(file);
    printf("\nAll Results\n");
    printf("-------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-10s %-10s %-20s\n", "Firstname", "Lastname", "Points", "Number", "Team");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < drivers->number_of_drivers; i++) {
        printf("%-20s %-20s %-10d %-10d %-20s\n", drivers->driverList[i].firstName, drivers->driverList[i].lastName, drivers->driverList[i].points, drivers->driverList[i].number, drivers->driverList[i].team);
    }
}

/************
This function adds to the total list of races (Darren)
inputs: race structs from user   
outputs: none   
*************/ 

void addRaceResults(driverList *list) {
    if (list->number_of_drivers >= MAX_DRIVER_SIZE) {
        printf("Error: Maximum number of drivers reached.\n");
        return;
    }

    driver_t newDriver;

    printf("Enter first name: ");
    scanf("%9s", newDriver.firstName);
    printf("Enter last name: ");
    scanf("%9s", newDriver.lastName);
    printf("Enter points: ");
    scanf("%d", &newDriver.points);
    printf("Enter driver number: ");
    scanf("%d", &newDriver.number);
    printf("Enter team: ");
    scanf("%9s", newDriver.team);
    printf("Enter year: ");
    scanf("%d", &newDriver.year);

    FILE *file = fopen("f1driver.txt", "a");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(file, "%s,%s,%d,%d,%s,%d\n", newDriver.firstName, newDriver.lastName, newDriver.points, newDriver.number, newDriver.team, newDriver.year);

    fclose(file);

    list->driverList[list->number_of_drivers] = newDriver;
    list->number_of_drivers++;

    printf("Race result added successfully.\n");
}

/************
This function removes the last race from total list of races (Aiden)
inputs: race structs from user   
outputs: none   
*************/ 

void removeRaceResults(driverList *list) {
    if (list->number_of_drivers > 0) {
        list->number_of_drivers--;
        printf("Last race results removed successfully.\n");
    } else {
        printf("No races to remove.\n");
    }
}


/************
This function saves the race results to the database (Alexia)
inputs: race list from user   
outputs: none   
*************/ 

int encodeDigit(int digit) {
    if (digit < 10) {
        return 0x80 | (digit << 4);
    } else {
        return 0xC0 | ((digit / 10) << 4);
    }
}

void saveRaceResultstoDatabase(race_t *races, int numRaces, const char *filename) {
    int numEncodedBytes = numRaces * (sizeof(races->date) + sizeof(races->location) + sizeof(races->raceNumber) + sizeof(races->numberOfLaps) + MAX_ENCODED_RACE_POSITIONS_LENGTH * 3);

    char *encodedRaces = malloc(numEncodedBytes);

    int offset = 0;
    for (int i = 0; i < numRaces; i++) {
        race_t race = races[i];

        memcpy(encodedRaces + offset, race.date, sizeof(race.date));
        offset += sizeof(race.date);

        memcpy(encodedRaces + offset, race.location, sizeof(race.location));
        offset += sizeof(race.location);

        memcpy(encodedRaces + offset, race.raceNumber, sizeof(race.raceNumber));
        offset += sizeof(race.raceNumber);

        int numLapsEncoded = encodeDigit(race.numberOfLaps / 100) << 4;
        numLapsEncoded |= encodeDigit(race.numberOfLaps % 100 / 10) << 2;
        numLapsEncoded |= encodeDigit(race.numberOfLaps % 10);
        memcpy(encodedRaces + offset, &numLapsEncoded, sizeof(numLapsEncoded));
        offset += sizeof(numLapsEncoded);

        memcpy(encodedRaces + offset, race.P1, sizeof(race.P1));
        offset += sizeof(race.P1);

        memcpy(encodedRaces + offset, race.P2, sizeof(race.P2));
        offset += sizeof(race.P2);

        memcpy(encodedRaces + offset, race.P3, sizeof(race.P3));
        offset += sizeof(race.P3);

    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(encodedRaces, 1, numEncodedBytes, file);
        fclose(file);
    }

    free(encodedRaces);
}
}

void encodeRaceData(const char *filename){
    race_t race; 

    printf("Enter the race date(yyyy-mm-dd): ");
    scanf("%10s", race.date);

    printf("Enter the race location: ");
    scanf("%29s", race.location);

    printf("Enter the race number: ");
    scanf("%9s", race.raceNumber);

    printf("Enter the number of laps: ");
    scanf("%d", &race.numberOfLaps);

    printf("Enter the Driver in First Position: ");
    scanf("%20s", race.P1);

    printf("Enter the Driver in Second Position: ");
    scanf("%20s", race.P2);

    printf("\nEnter the Driver in Third Position: ");
    scanf("%20s", race.P3);

    race_t races[1];
    races[0] = race;
    saveRaceResultstoDatabase(races, 1, filename);

}



/************
This function prints all of the drivers, and their results from each race in the selected year (Ji Hyun)
inputs: year  
outputs: list of all drivers, with their podium stats and points. 
*************/ 

void displayAllDrivers(driverList *drivers) {
    printf("\nAll Drivers\n");
    FILE *file = fopen("f1driver.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    drivers->number_of_drivers = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token == NULL) continue;

        char firstName[20];
        char lastName[20];
        strcpy(firstName, token);

        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(lastName, token);

        int points;
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        points = atoi(token);

        int number;
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        number = atoi(token);

        char team[20];
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strcpy(team, token);

        int i;
        int found = 0;
        for (i = 0; i < drivers->number_of_drivers; i++) {
            if (strcmp(drivers->driverList[i].firstName, firstName) == 0 &&
                strcmp(drivers->driverList[i].lastName, lastName) == 0) {
                drivers->driverList[i].points += points;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(drivers->driverList[drivers->number_of_drivers].firstName, firstName);
            strcpy(drivers->driverList[drivers->number_of_drivers].lastName, lastName);
            drivers->driverList[drivers->number_of_drivers].points = points;
            drivers->driverList[drivers->number_of_drivers].number = number;
            strcpy(drivers->driverList[drivers->number_of_drivers].team, team);
            drivers->number_of_drivers++;
        }
    }
    fclose(file);
    printf("-------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-10s %-10s %-20s\n", "Firstname", "Lastname", "Points", "Number", "Team");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < drivers->number_of_drivers; i++) {
        printf("%-20s %-20s %-10d %-10d %-20s\n", drivers->driverList[i].firstName,
               drivers->driverList[i].lastName, drivers->driverList[i].points,
               drivers->driverList[i].number, drivers->driverList[i].team);
    }
}

/************
This function displays the driver with the most points (Darren)
inputs: year  
outputs: the world champion driver
*************/ 

void calculateWorldChampion(int year) {
    FILE *file = fopen("f1driver.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    // Initialize variables to store the champion's name and points
    char championFirstName[20];
    char championLastName[20];
    int maxPoints = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char firstName[20], lastName[20], team[20];
        int points, number;

        // Parse the line to extract driver information
        if (sscanf(line, "%19[^,],%19[^,],%d,%d,%19[^,\n]", firstName, lastName, &points, &number, team) == 5) {
            // Check if the current driver has more points than the current maxPoints
            if (points > maxPoints) {
                maxPoints = points;
                strcpy(championFirstName, firstName);
                strcpy(championLastName, lastName);
            }
        }
    }

    fclose(file);

    // Print the world champion
    if (maxPoints > 0) {
        printf("The World Champion for %d is %s %s with %d points.\n",
               year, championFirstName, championLastName, maxPoints);
    } else {
        printf("No drivers found.\n");
    }
}



/************
This function prints all teams, and their results in the selected year. (Aiden)
inputs: year 
outputs: list of the teams of that particular year, with their constructors points. 
*************/ 

void displayAllTeams(driverList *drivers, int year){
    printf("ALL Team Results in year %d\n", year);
    for(int i = 0; i < drivers->number_of_drivers; i++){
        if(drivers->driverList[i].year == year){
            printf("%s: %d\n", drivers->driverList[i].team, drivers->driverList[i].points);
        }
    }
}

