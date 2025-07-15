#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp" //Include
#include <algorithm>
#include <queue> 

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Inline helper function that recursively searches for files within range
 * 
 * @param node Pointer to the current node. 
 * @param min The min value of the file size search range.
 * @param max The max value of the file size search range.
 * @param vec The vector that will store the pointers to files within range.
 * @note Helper function performs an in-order traversal, adding files within specified range to the vector. 
 *     if the size of the current node is greater than or equal to the min, it will traverse to the left subtree
 *     if the size of the current node is less than or equal to the max, it will traverse to the right subtree
 */
inline void helper(Node* node, size_t min, size_t max, std::vector<File*>& vec) {
    if(node != nullptr) {
        if(node->size_ >= min) { 
            helper(node->left_, min, max, vec);
        }
        for(auto it = node->files_.begin(); it != node->files_.end(); ++it) { // Keeps in mind 
            File* file = *it;
            size_t fileSize = file->getSize();
            if(fileSize >= min && fileSize <= max) {
                vec.push_back(file);
            }
        }
        if(node->size_ <= max) { 
            helper(node->right_, min, max, vec);
        }
    }
}

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> vec;
    if(min >= max) { // If the query interval is in descending order (ie. the given parameters min >= max), 
        std::swap(min, max);
    }
    helper(root_, min, max, vec); // Calling helper function
    return vec;
}

/**
 * @brief Adds a file to FileTrie 
 * 
 * @param f A pointer to file that is to be added to FileTrie 
 * @note Function converts file names to lowercase as searches are case-insensitive 
 *      Creates nodes in trie for each character in filename 
 *      Adds file pointer to matching corresponding node to filename 
 */
void FileTrie::addFile(File* f) {
    if(f != nullptr) {
        std::string filename = f->getName();
        for(auto it = filename.begin(); it != filename.end(); ++it) {
            *it = std::tolower(*it);
        }

        FileTrieNode* current = head; // Head is the root node of FileTrie, set as starting node
        for(auto it = filename.begin(); it != filename.end(); ++it) {
            char c = *it;
            if(current->next.find(c) == current->next.end()) { 
                current->next[c] = new FileTrieNode(c);
            }
            current = current->next[c];
            current->matching.insert(f);
        }
        head->matching.insert(f); 
    }
}

/**
 * @brief Gets files in FileTrie where names begin with a given prefix
 * 
 * @param prefix The specified prefix designated for matching file names
 * @return Unordered set of pointers to files with given prefix
 * @note Function converts file names to lowercase as searches are case-insensitive (alphanumeric characters or period)
 *      Traverses FileTrie based on given prefix to find matching node
 *      Returns an empty set for invalid prefix characters or no matching prefix in file names
 */
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::string lower = prefix; // Prefix itself is const string so create a copy
    for(auto it = lower.begin(); it != lower.end(); ++it) {
        char &c = *it; 
        if(std::isalnum(c) || c == '.') {
            c = std::tolower(c);
        }
        else {
            return std::unordered_set<File*>(); // Invalid Prefix {}
        }
    }
    FileTrieNode* current = head; 
    for(auto it = lower.begin(); it != lower.end(); ++it) {
        char& c = *it;
        if(current->next.find(c) == current->next.end()) { 
            return std::unordered_set<File*>(); // Prefix Not Found {}
        }
        current = current->next[c];
    }
    return current->matching;
}

/*
FileTrie::~FileTrie() {
    // You must implement all methods of FileTrie except for the constructor, which is just a default constructor. 
        // You can find the FileTrie class in FileTrie.hpp, but you must implement the methods in solution.cpp.
    // 1) Add a compiler directive "USE_VECTOR" at the top of your submitted FileTrie.hpp file:
        // #ifndef USE_VECTOR
        // #define USE_VECTOR
        // #endif
        // 2) Implement your own destructor for the FileTrie class within solution.cpp
        // If USE_VECTOR is not defined, the destructor provided by us will be used. 
            // (which is the destructor for the map implementation)
}
*/
