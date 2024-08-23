#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "miniz.h"

void unzip(const char* zipFilePath, const char* outputDir) {
    mz_zip_archive zipArchive;
    memset(&zipArchive, 0, sizeof(zipArchive));

    // Open the zip archive
    if (!mz_zip_reader_init_file(&zipArchive, zipFilePath, 0)) {
        std::cerr << "Failed to open zip file: " << zipFilePath << std::endl;
        return;
    }

    // Get the number of files in the zip
    int fileCount = (int)mz_zip_reader_get_num_files(&zipArchive);
    for (int i = 0; i < fileCount; ++i) {
        mz_zip_archive_file_stat fileStat;
        if (!mz_zip_reader_file_stat(&zipArchive, i, &fileStat)) {
            std::cerr << "Failed to get file stat for index: " << i << std::endl;
            continue;
        }

        // Print the filename to the console
        std::cout << "File: " << fileStat.m_filename << std::endl;

        // Prepare output file path
        std::string outputPath = std::string(outputDir) + "\\" + fileStat.m_filename;

        // Create directories if necessary
        if (fileStat.m_is_directory) {
            CreateDirectoryA(outputPath.c_str(), NULL);
        }
        else {
            // Extract the file
            if (!mz_zip_reader_extract_to_file(&zipArchive, i, outputPath.c_str(), 0)) {
                std::cerr << "Failed to extract file: " << fileStat.m_filename << std::endl;
            }
            else {
                // Check if the file is a .txt file
                if (outputPath.size() >= 4 && outputPath.substr(outputPath.size() - 4) == ".txt") {
                    // If the file is a .txt file, read and print its contents
                    std::ifstream inputFile(outputPath);
                    if (inputFile.is_open()) {
                        std::cout << "Contents of " << fileStat.m_filename << ":\n";
                        std::string line;
                        while (std::getline(inputFile, line)) {
                            std::cout << line << std::endl;
                        }
                        inputFile.close();
                    }
                    else {
                        std::cerr << "Failed to open file: " << outputPath << std::endl;
                    }
                }
            }
        }
    }

    // Close the zip archive
    mz_zip_reader_end(&zipArchive);
}

int main() {
    const char* zipFilePath = "../../assets/dave.zip";
    const char* outputDir = "../../assets/py";

    unzip(zipFilePath, outputDir);

    std::cout << "Press Enter to exit...";
    std::cin.get(); // Wait for user input before closing
    return 0;
}
