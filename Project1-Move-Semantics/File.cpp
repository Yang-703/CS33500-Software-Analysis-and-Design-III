
#include "File.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
}

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================

/* @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
      *    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
      *    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
      *    - Default value of "NewFile.txt" if none provided or if filename is empty 
    * @param contents A string representing the contents of the file. Default to empty string if none provided.
    * @param icon A pointer to an integer array with length ICON_DIM. Default to nullptr if none provided.
      * @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
      * @note You'll notice we provide a default value for the first possible argument (filename)
      *       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
*/
File::File(const std::string& filename, const std::string& contents, int* icon) 
{
    contents_ = contents; 
    icon_ = icon; 

    if(filename.empty()) {
        filename_ = "NewFile.txt";
    }
    else {
        int count = 0; 
        auto pos = filename.end();

        for(auto it = filename.begin(); it != filename.end(); ++it)
        {
            if(*it == '.') {
                count++;
                pos = it; 
            }
            else if(!std::isalnum(*it)) {
                throw InvalidFormatException(); 
            }
        }

        if(count == 0) {
            filename_ = filename + ".txt";
        }
        else if(count > 1) { 
            throw InvalidFormatException();
        }
        else if(pos == filename.end()-1) { 
            filename_ = filename + "txt";
        }
        else {
            filename_ = filename; 
        }
    }
}

size_t File::getSize() const {
    return contents_.size();
}

/* Copy Constructor */
File::File(const File& rhs) {
    filename_ = rhs.filename_;
    contents_ = rhs.contents_;
    if(rhs.icon_ != nullptr)
    {
        icon_ = new int[ICON_DIM];
        for(int i = 0; i < ICON_DIM; i++) 
        {
            icon_[i] = rhs.icon_[i];
        }
    }
    else {
        icon_ = nullptr;
    }
    //std::cout << "Copy Constructor : " << *this << std::endl; 
}

/* Copy Assignment Operator */
File& File::operator=(const File& rhs) {
    if(this != &rhs)
    {
        filename_ = rhs.filename_;
        contents_ = rhs.contents_;
        delete[] icon_;
        if(rhs.icon_ != nullptr)
        {
            icon_ = new int[ICON_DIM];
            for(int i = 0; i < ICON_DIM; i++) 
            {
                icon_[i] = rhs.icon_[i];
            }
        }
        else {
            icon_ = nullptr;
        }
    }
    //std::cout << "Copy Assignment Operator : " << *this << std::endl; 
    return *this;
}

/* Move Constructor */
File::File(File&& rhs) {
    filename_ = std::move(rhs.filename_);
    contents_ = std::move(rhs.contents_);
    icon_ = rhs.icon_; 
    rhs.icon_ = nullptr;
    //std::cout << "Move Constructor : " << *this << std::endl; 
}

/* Move Assignment Operator */
File& File::operator=(File&& rhs) { 
    if(this != &rhs)
    {
        filename_ = std::move(rhs.filename_);
        contents_ = std::move(rhs.contents_);
        delete[] icon_;
        icon_ = rhs.icon_; 
        rhs.icon_ = nullptr;
    }
    //std::cout << "Move Assignment Operator : " << *this << std::endl; 
    return *this;
}

/* Destructor */
File::~File() { 
    delete[] icon_;
    icon_ = nullptr;
}