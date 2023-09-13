#include<iostream>

class Customer; // forward declaration





class Book{
    std::string title;
    Customer *customer;
    
    std::ostream& printBook(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream& out, const Book& bk){
        return bk.printBook(out);
    }
    friend class CheckedOutBook;
    friend Customer;
    friend void includeBook();
    friend void checkedOutBook();
    friend void returnBook();
public: 
    Book(): customer(nullptr){}
    bool operator==(const Book& bk) const{
        return title.compare(bk.title) == 0;
    }
};
std::ostream& Book::printBook(std::ostream& out) const{
        out<<" *" <<title;
        if(customer != nullptr) 
            out<<" - checked out to "<<customer->name;
        out<<std::endl;
        return out;

}
class Author{
    std::string name;

public:
    Author(){}
    bool operator==(const Author& ar) const{
        return name.compare(ar.name) == 0;
    }

}

int main(){
    return 0;
}