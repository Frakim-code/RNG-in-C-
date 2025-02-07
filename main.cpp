#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits> // Include this header for input validation
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// Function prototypes
string generateIMEI();
string generateScratchCardNumber();
string generateVehicleNumberPlate();
string generateKRAPIN();
void displayMenu();
void generateNumbers(int choice, int quantity);
void saveToFile(const vector<string> &numbers, const string &type);

unordered_set<string> uniqueNumbers;

int main() {
  srand(time(0)); // Seed for random number generation
  int choice, quantity;

  displayMenu();
  while (true) {
    cout << "\033[1;34mChoice: \033[0m";
    if (!(cin >> choice) || choice < 1 || choice > 5) {
      cout << "\033[1;31mInvalid choice! Please enter a number between 1 and "
              "5.\033[0m\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (choice == 5)
      break;

    cout << "\033[1;34mEnter the quantity of numbers to generate: \033[0m";
    if (!(cin >> quantity) || quantity <= 0) {
      cout << "\033[1;31mInvalid quantity! Please enter a positive "
              "number.\033[0m\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    generateNumbers(choice, quantity);
    displayMenu();
  }

  return 0;
}

// Function to display menu with ASCII art and color coding
void displayMenu() {
  cout << "\033[1;34m"; // Set text color to blue
  cout << "\n=============================\n";
  cout << "       Number Generator       \n";
  cout << "=============================\n\033[0m"; // Reset text color
  cout << "\033[1;32m1. Generate Phone IMEIs\033[0m\n";
  cout << "\033[1;33m2. Generate Scratch Card Numbers\033[0m\n";
  cout << "\033[1;36m3. Generate Vehicle Number Plates\033[0m\n";
  cout << "\033[1;35m4. Generate KRA PINs\033[0m\n";
  cout << "\033[1;31m5. Exit\033[0m\n";
}

// Function to generate numbers based on user choice
void generateNumbers(int choice, int quantity) {
  string number;
  vector<string> generatedNumbers;

  for (int i = 0; i < quantity; ++i) {
    do {
      switch (choice) {
      case 1:
        number = generateIMEI();
        break;
      case 2:
        number = generateScratchCardNumber();
        break;
      case 3:
        number = generateVehicleNumberPlate();
        break;
      case 4:
        number = generateKRAPIN();
        break;
      default:
        return;
      }
    } while (uniqueNumbers.find(number) != uniqueNumbers.end());
    uniqueNumbers.insert(number);
    generatedNumbers.push_back(number);
  }

  // Display generated numbers with color coding
  for (const auto &num : generatedNumbers) {
    switch (choice) {
    case 1:
      cout << "\033[1;32m" << num << "\033[0m\n";
      break; // Green for IMEIs
    case 2:
      cout << "\033[1;33m" << num << "\033[0m\n";
      break; // Yellow for Scratch Cards
    case 3:
      cout << "\033[1;36m" << num << "\033[0m\n";
      break; // Cyan for Vehicle Plates
    case 4:
      cout << "\033[1;35m" << num << "\033[0m\n";
      break; // Magenta for KRA PINs
    }
  }

  // Save the generated numbers to a file
  string type;
  switch (choice) {
  case 1:
    type = "IMEIs";
    break;
  case 2:
    type = "ScratchCards";
    break;
  case 3:
    type = "VehiclePlates";
    break;
  case 4:
    type = "KRAPINs";
    break;
  }
  saveToFile(generatedNumbers, type);
}

// Function to save numbers to a file
void saveToFile(const vector<string> &numbers, const string &type) {
  ofstream outFile(type + ".txt", ios::app); // Append to the file
  if (!outFile) {
    cout << "\033[1;31mError opening file for writing!\033[0m\n";
    return;
  }
  for (const auto &num : numbers) {
    outFile << num << endl;
  }
  outFile.close();
  cout << "\033[1;34mNumbers saved to " << type << ".txt\033[0m\n";
}

// Function to generate IMEI
string generateIMEI() {
  string imei = "35";
  for (int i = 0; i < 12; ++i) {
    imei += to_string(rand() % 10);
  }
  // Add Luhn check digit (simplified)
  int sum = 0;
  for (int i = 0; i < 14; ++i) {
    int digit = imei[i] - '0';
    if (i % 2 == 1)
      digit *= 2;
    sum += digit / 10 + digit % 10;
  }
  imei += to_string((10 - sum % 10) % 10);
  return imei;
}

// Function to generate Scratch Card Number
string generateScratchCardNumber() {
  string scratchCard = "";
  for (int i = 0; i < 12; ++i) {
    scratchCard += to_string(rand() % 10);
  }
  return scratchCard;
}

// Function to generate Vehicle Number Plate
string generateVehicleNumberPlate() {
  string plate = "K";
  for (int i = 0; i < 2; ++i) {
    plate += (char)('A' + rand() % 26);
  }
  plate += " ";
  for (int i = 0; i < 3; ++i) {
    plate += to_string(rand() % 10);
  }
  return plate;
}

// Function to generate KRA PIN
string generateKRAPIN() {
  string kraPIN = "A";
  for (int i = 0; i < 9; ++i) {
    kraPIN += to_string(rand() % 10);
  }
  return kraPIN;
}
