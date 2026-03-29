#include <stdio.h>

int balance = 0;  // global variable (bad practice)

// deposit function
void deposit() {
    int amount;
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Deposited: %d\n", amount);
    } else {
        printf("Invalid amount\n");
    }
}

// withdraw function
void withdraw() {
    int amount;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    if (amount <= balance && amount > 0) {
        balance -= amount;
        printf("Withdrawn: %d\n", amount);
    } else {
        printf("Invalid transaction\n");
    }
}

// show balance
void showBalance() {
    printf("Current balance: %d\n", balance);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Deposit\n2. Withdraw\n3. Balance\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) deposit();
        else if (choice == 2) withdraw();
        else if (choice == 3) showBalance();
        else if (choice == 4) break;
        else printf("Invalid choice\n");
    }

    return 0;
}
