#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Simple function to trim whitespace
std::string trim(const std::string& str) {
    const size_t first = str.find_first_not_of(' ');
    const size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check if username already exists
bool userExists(const std::string& username) {
    std::string filename = "users/" + username + ".txt";
    return fs::exists(filename);
}

// Register new user
void registerUser() {
    std::string username, password;

    std::cout << "\n--- Registration ---\n";
    std::cout << "Enter a username: ";
    std::cin >> username;

    if (userExists(username)) {
        std::cout << "⚠️ Username already taken. Try another.\n";
        return;
    }

    std::cout << "Enter a password: ";
    std::cin >> password;

    fs::create_directory("users"); // create directory if it doesn't exist
    std::ofstream file("users/" + username + ".txt");

    if (file.is_open()) {
        file << username << '\n' << password;
        file.close();
        std::cout << "✅ Registration successful!\n";
    } else {
        std::cout << "❌ Error creating user file.\n";
    }
}

// Login existing user
void loginUser() {
    std::string username, password, storedUser, storedPass;

    std::cout << "\n--- Login ---\n";
    std::cout << "Enter username: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "❌ No such user found.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    std::ifstream file("users/" + username + ".txt");
    if (file.is_open()) {
        std::getline(file, storedUser);
        std::getline(file, storedPass);
        file.close();

        if (trim(username) == trim(storedUser) && trim(password) == trim(storedPass)) {
            std::cout << "✅ Login successful. Welcome, " << username << "!\n";
        } else {
            std::cout << "❌ Incorrect password.\n";
        }
    } else {
        std::cout << "❌ Error reading user file.\n";
    }
}

int main() {
    int choice;

    do {
        std::cout << "\n==== User System Menu ====\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 0: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
