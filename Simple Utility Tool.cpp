#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void compressFiles() {
    std::cout << "Compressing files...\n";
    std::string directoryPath = "."; // Replace with the directory path you want to compress
    // Implementation for compressing files
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // Compress each file in the directory (Example: using a .zip archive)
        fs::path file = entry.path();
        std::string command = "zip " + file.stem().string() + ".zip " + file.filename().string();
        system(command.c_str());
        std::cout << "Compressed: " << file.filename() << "\n";
    }
    std::cout << "Files compressed.\n";
}

void decompressFiles() {
    std::cout << "Decompressing files...\n";
    std::string directoryPath = "."; // Replace with the directory path containing compressed files
    // Implementation for decompressing files
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // Decompress each file in the directory (Example: unzip .zip archives)
        fs::path file = entry.path();
        if (file.extension() == ".zip") {
            std::string command = "unzip " + file.filename().string();
            system(command.c_str());
            std::cout << "Decompressed: " << file.filename() << "\n";
        }
    }
    std::cout << "Files decompressed.\n";
}

void encryptText() {
    // Example: Encrypt text
    std::cout << "Encrypting text...\n";
    std::string originalText;
    std::cout << "Enter the text to encrypt: ";
    std::cin.ignore(); // Ignore newline from previous input
    std::getline(std::cin, originalText); // Read text input
    std::string encryptedText = "Encrypted: ";
    // Simple encryption logic: shift each character by 1 in ASCII
    for (char c : originalText) {
        encryptedText += static_cast<char>(c + 1);
    }
    std::cout << "Text encrypted: " << encryptedText << "\n";
}

void decryptText() {
    // Example: Decrypt text
    std::cout << "Decrypting text...\n";
    std::string encryptedText;
    std::cout << "Enter the text to decrypt: ";
    std::cin.ignore(); // Ignore newline from previous input
    std::getline(std::cin, encryptedText); // Read text input
    std::string decryptedText = "Decrypted: ";
    // Simple decryption logic: shift each character back by 1 in ASCII
    for (char c : encryptedText.substr(11)) {
        decryptedText += static_cast<char>(c - 1);
    }
    std::cout << decryptedText << "\n";
}

// Additions:

void renameFiles() {
    std::cout << "Renaming files...\n";
    std::string directoryPath = "."; // Replace with the directory path you want to rename files in
    int counter = 1;
    // Implementation for renaming files
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        fs::path file = entry.path();
        fs::path newFileName = file.parent_path() / ("renamed_file_" + std::to_string(counter++) + file.extension().string());
        fs::rename(file, newFileName);
        std::cout << "Renamed: " << file.filename() << " to " << newFileName.filename() << "\n";
    }
    std::cout << "Files renamed.\n";
}

void listFilesInDirectory() {
    std::cout << "Listing files in directory...\n";
    std::string directoryPath = "."; // Replace with the directory path you want to list
    std::vector<std::string> files;
    // Implementation for listing files in the directory
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        files.push_back(entry.path().filename().string());
    }
    std::cout << "Files in " << directoryPath << ":\n";
    for (const auto &file : files) {
        std::cout << file << "\n";
    }
}

void analyzeFile() {
    std::cout << "Analyzing file...\n";
    std::string filePath;
    std::cout << "Enter the file path to analyze: ";
    std::cin >> filePath;
    fs::path file(filePath);
    if (fs::exists(file)) {
        std::cout << "File Size: " << std::fixed << std::setprecision(2) << fs::file_size(file) / 1024.0 << " KB\n";
        std::cout << "File Type: " << file.extension().string() << "\n";
        auto lastModifiedTime = fs::last_write_time(file);
        std::time_t modifiedTime = std::chrono::system_clock::to_time_t(lastModifiedTime);
        std::cout << "Last Modified Time: " << std::asctime(std::localtime(&modifiedTime));
    } else {
        std::cout << "File does not exist.\n";
    }
}

void displayMenu() {
    std::cout << "Enhanced Utility Tool\n";
    std::cout << "1. Compress Files\n";
    std::cout << "2. Decompress Files\n";
    std::cout << "3. Encrypt Text\n";
    std::cout << "4. Decrypt Text\n";
    std::cout << "5. Rename Files\n";
    std::cout << "6. List Files in Directory\n";
    std::cout << "7. Analyze a File\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                compressFiles();
                break;
            case 2:
                decompressFiles();
                break;
            case 3:
                encryptText();
                break;
            case 4:
                decryptText();
                break;
            case 5:
                renameFiles();
                break;
            case 6:
                listFilesInDirectory();
                break;
            case 7:
                analyzeFile();
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
