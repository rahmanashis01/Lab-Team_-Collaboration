#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 3

// Structure to store bus details
struct Bus {
    char busNumber[10];
    int totalSeats;
    int availableSeats;
};

// Function to display bus details
void displayBuses(struct Bus buses[], int count) {
    printf("\n=== Bus Seat Availability ===\n");
    printf("Bus No.\tTotal Seats\tAvailable Seats\n");
    printf("------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t\t%d\n", buses[i].busNumber, buses[i].totalSeats, buses[i].availableSeats);
    }
}

// Function to check seat availability
void checkSeatAvailability(struct Bus buses[], int count) {
    char busNum[10];
    int found = 0;

    printf("\nEnter Bus Number to check availability: ");
    scanf("%s", busNum);

    for (int i = 0; i < count; i++) {
        if (strcmp(buses[i].busNumber, busNum) == 0) {
            found = 1;
            printf("Bus %s has %d available seats.\n", buses[i].busNumber, buses[i].availableSeats);
            return;
        }
    }

    if (!found) {
        printf("Bus not found!\n");
    }
}

// Function to book a seat
void bookSeat(struct Bus buses[], int count) {
    char busNum[10];
    int found = 0;

    printf("\nEnter Bus Number to book a seat: ");
    scanf("%s", busNum);

    for (int i = 0; i < count; i++) {
        if (strcmp(buses[i].busNumber, busNum) == 0) {
            found = 1;
            if (buses[i].availableSeats > 0) {
                buses[i].availableSeats--;
                printf("Seat booked successfully in Bus %s!\n", buses[i].busNumber);
            } else {
                printf("No available seats in Bus %s!\n", buses[i].busNumber);
            }
            return;
        }
    }

    if (!found) {
        printf("Bus not found!\n");
    }
}

// Function to save bus details to file
void saveBusData(struct Bus buses[], int count) {
    FILE *file = fopen("buses.txt", "w");
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %d\n", buses[i].busNumber, buses[i].totalSeats, buses[i].availableSeats);
    }

    fclose(file);
    printf("Bus data saved successfully!\n");
}

// Function to load bus details from file
int loadBusData(struct Bus buses[]) {
    FILE *file = fopen("buses.txt", "r");
    if (file == NULL) {
        printf("No previous bus records found.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %d %d", buses[count].busNumber, &buses[count].totalSeats, &buses[count].availableSeats) != EOF) {
        count++;
    }

    fclose(file);
    printf("Bus data loaded successfully!\n");
    return count;
}

int main() {
    struct Bus buses[MAX_BUSES];
    int count, choice;

    // Load previous bus data if available
    count = loadBusData(buses);

    // If no data exists, initialize some buses
    if (count == 0) {
        strcpy(buses[0].busNumber, "DIU101");
        buses[0].totalSeats = 40;
        buses[0].availableSeats = 10;

        strcpy(buses[1].busNumber, "DIU102");
        buses[1].totalSeats = 35;
        buses[1].availableSeats = 5;

        strcpy(buses[2].busNumber, "DIU103");
        buses[2].totalSeats = 50;
        buses[2].availableSeats = 20;

        count = 3;
    }

    while (1) {
        printf("\n=== DIU Transport Seat Checker ===\n");
        printf("1. Display Bus Seat Availability\n");
        printf("2. Check Seat Availability\n");
        printf("3. Book a Seat\n");
        printf("4. Save Data\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBuses(buses, count);
                break;
            case 2:
                checkSeatAvailability(buses, count);
                break;
            case 3:
                bookSeat(buses, count);
                break;
            case 4:
                saveBusData(buses, count);
                break;
            case 5:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
