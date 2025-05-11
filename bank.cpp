#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Banking::Banking() : loanAmount(0), interestRate(0.1f), isFraudDetected(false) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to take a loan
void Banking::takeLoan(int amount, float rate) {
    if (amount <= 0 || rate < 0.0f) {
        throw std::invalid_argument("Loan amount must be positive and interest rate must be non-negative.");
    }
    loanAmount += amount;
    interestRate = rate;
    std::cout << "Loan taken: " << amount << " gold at " << rate * 100 << "% interest.\n";
}

// Method to audit the bank
void Banking::auditBank() {
    int fraudChance = rand() % 100; // Random chance of detecting fraud (0-99)
    if (fraudChance < 20) { // 20% chance of fraud detection
        isFraudDetected = true;
        std::cout << "Fraud detected in the banking system!\n";
    }
    else {
        isFraudDetected = false;
        std::cout << "No fraud detected. Banking system is clean.\n";
    }
}

// Method to repay a loan
void Banking::repayLoan(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Repayment amount must be positive.");
    }
    if (amount > loanAmount) {
        std::cout << "Cannot repay more than the outstanding loan. Repaying full amount instead.\n";
        amount = loanAmount;
    }
    loanAmount -= amount;
    std::cout << "Repaid " << amount << " gold. Remaining loan: " << loanAmount << "\n";
}

// Update method (required by the System base class)
void Banking::update() {
    // Simulate random banking events
    int event = rand() % 3; // Random event: 0 = loan interest accrual, 1 = audit, 2 = repayment
    switch (event) {
    case 0:
        if (loanAmount > 0) {
            loanAmount += static_cast<int>(loanAmount * interestRate); // Accrue interest
            std::cout << "Loan interest accrued. New loan amount: " << loanAmount << "\n";
        }
        break;
    case 1:
        auditBank();
        break;
    case 2:
        try {
            repayLoan(rand() % 100 + 50); // Random repayment between 50 and 150
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        break;
    }
}

// Save banking state to a file
void Banking::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << loanAmount << " " << interestRate << " " << isFraudDetected;
        file.close();
        std::cout << "Banking state saved to " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to save banking state to file.\n";
    }
}

// Load banking state from a file
void Banking::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> loanAmount >> interestRate >> isFraudDetected;
        file.close();
        std::cout << "Banking state loaded from " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to load banking state from file.\n";
    }
}

// Get banking status as a string
std::string Banking::getStatus() const {
    return "Loan Amount: " + std::to_string(loanAmount) +
        ", Interest Rate: " + std::to_string(interestRate * 100) + "%" +
        ", Fraud Detected: " + (isFraudDetected ? "Yes" : "No");
}