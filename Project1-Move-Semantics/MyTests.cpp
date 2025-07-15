#include <iostream>
#include <string> 
#include "File.hpp"
#include "Folder.hpp"

int main() {
    
    //Testing File Constructor
    try { 
        File empty_file; 
        std::cout << empty_file << std::endl; 
        std:: cout << "File Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std:: cout << "File Constructor - Failed" << std::endl; 
    }
    
    try { 
        File correct_file("CorrectFile.txt");
        std::cout << correct_file << std::endl;
        std:: cout << "File Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std:: cout << "File Constructor - Failed" << std::endl; 
    }
    
    try { 
        File no_period("CorrectFiletxt");
        std::cout << no_period << std::endl;
        std:: cout << "File Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std:: cout << "File Constructor - Failed" << std::endl; 
    }
    
    try { 
        File period_end("CorrectFiletxt.");
        std::cout << period_end << std::endl;
        std:: cout << "File Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std:: cout << "File Constructor - Failed" << std::endl; 
    }
    
    try { 
        File wrong_file("Correct.File.txt");
        std::cout << wrong_file << std::endl;
        std:: cout << "File Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std:: cout << "File Constructor - Failed" << std::endl; 
    }
    
    //Testing File Copy Constructor
    try { 
        File original_file("TestFile.txt", "Copy Constructor");
        File copy_file(original_file);  
        std::cout << "Original File: " << original_file << std::endl;
        std::cout << "Copied File: " << copy_file << std::endl;
        std::cout << "File Copy Constructor - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std::cout << "File Copy Constructor - Failed" << std::endl; 
    }
    
    //Testing File Move Constructor 
    try {
        File temp_file("MoveFile.txt", "Move Constructor");
        File move_file(std::move(temp_file));  // Moving the file
    } catch (InvalidFormatException) {
        std::cout << "File Move Constructor - Failed" << std::endl; 
    }
    
    //Testing File Copy Assignment Operator
    try {
        File file1("CopyAssign.txt", "Copy Assignment Operator File 1");
        File file2 = file1;  // Copy assignment
        std::cout << std::endl << "File 1 - " << file1 << std::endl;
        std::cout << "File 2 - " << file2 << std::endl;
        std::cout << "File Copy Assignment - Passed" << std::endl << std::endl; 
    } catch (InvalidFormatException) {
        std::cout << "File Copy Assignment - Failed" << std::endl; 
    }
    
    //Testing File Move Assignment Operator 
    try {
        File file3("MoveAssign.txt", "This is file 3.");
        File file4 = std::move(file3);  // Move assignment
    } catch (InvalidFormatException) {
        std::cout << "File Move Assignment - Failed" << std::endl; 
    }
    
    //Testing Folder Functions 
    
    //Testing AddFile & RemoveFile
    Folder folder1("Folder1");
    File file5("FileToAdd.txt", "Adding to folder.");
    bool addition = folder1.addFile(file5);
    folder1.display();
    std::cout << "AddFile: " << (addition ? "Passed" : "Failed") << std::endl;
    std::cout << std::endl; 
    
    bool removal = folder1.removeFile("FileToAdd.txt");
    folder1.display();
    std::cout << "RemoveFile: " << (removal ? "Passed" : "Failed") << std::endl;
    std::cout << std::endl; 
    
    //Testing MoveFileTo
    Folder folder2("Folder2");
    File file6("FileToMove.txt", "Moving file content.");
    folder1.addFile(file6);
    bool move = folder1.moveFileTo("FileToMove.txt", folder2);
    folder1.display();
    folder2.display();
    std::cout << "MoveFileTo : " << (move ? "Passed" : "Failed") << std::endl;
    std::cout << std::endl; 
    
    //Testing CopyFileTo
    File file7("FileToCopy.txt", "Copying file content.");
    folder1.addFile(file7);
    bool copy = folder1.copyFileTo("FileToCopy.txt", folder2);
    folder1.display();
    folder2.display();
    std::cout << "CopyFile: " << (copy ? "Passed" : "Failed") << std::endl;
    std::cout << std::endl; 

    return 0;
}