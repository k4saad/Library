#include<iostream>
#include<string>

// Linked list

template<class T>
class Node{
public:
    Node() :  next(nullptr){}
    Node(T v, Node<T>* n = nullptr) : val(v), next(n){ } 
    T val;
    Node<T> *next;
};

template<class T>
class LinkedList{
public:
    Node<T> *head, *tail;
    LinkedList():head(nullptr), tail(nullptr){}
    bool isEmpty(){
        return head == nullptr;
    }
    void addToHead(T&);
    void deleteNode(T&);
};



template<class T>
void LinkedList<T>::addToHead(T& el){
    head = new Node<T>(el, head);
    if(tail == nullptr){
        tail = head;
    }
}

template<class T>
void LinkedList<T>::deleteNode(T& el){
    if(head != nullptr){
        if(head == tail && head->val == el){
            delete head;
            head = tail = nullptr;
        }
        else if(head->val == el){
            Node<T> *temp = head;
            delete head;
            head = temp->next;
        }
        else{
            Node<T> *pred, *temp;
            for(pred = head, temp = head->next; temp != nullptr && !(temp->val == el); pred = pred->next, temp = temp->next);
            if(temp!= nullptr){
                pred->next = temp->next;
                if(temp == tail){
                    tail = pred;
                }
                delete temp;
            }
        }
    }
}

class Customer;

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
    friend void checkOutBook();
    friend void returnBook();
public: 
    Book(): customer(nullptr){}
    bool operator==(const Book& bk) const{
        return title.compare(bk.title) == 0;
    }
};

class Author{
    std::string name;
    LinkedList<Book> books;
    std::ostream& printAuthor(std::ostream&) const;
    friend std::ostream& operator<< (std::ostream& out, const Author& ar){
        return ar.printAuthor(out);
    }
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
    friend class CheckedOutBook;
    friend Customer;
public:
    Author(){}
    bool operator==(const Author& ar) const{
        return name.compare(ar.name) == 0;
    }
};

class CheckedOutBook{
    Node<Author> *author; 
    Node<Book> *book;
    friend void checkOutBook();
    friend void returnBook();
    friend Customer;
public:
    CheckedOutBook(Node<Author>* ar = nullptr, Node<Book>* bk = nullptr) : author(ar), book(bk){}
    bool operator==(const CheckedOutBook& bk) const {
        return author->val.name.compare(bk.author->val.name) == 0 && book->val.title.compare(bk.book->val.title) == 0;
    }
};

class Customer{
    std::string name;
    LinkedList<CheckedOutBook> books;
    std::ostream& printCustomer(std::ostream&)const;
    friend std::ostream& operator<<(std::ostream& out, const Customer& cs){
        return cs.printCustomer(out);
    }
    friend void checkOutBook();
    friend void returnBook();
    friend Book;
public:    
    Customer(){}
    bool operator==(const Customer& cs)const{
        return name.compare(cs.name) == 0;
    }
};

LinkedList<Author> catalog['Z'+1];
LinkedList<Customer> people['Z'+1];

std::ostream& Author::printAuthor(std::ostream& out) const {
    out <<"\t\t\t"<< name << std::endl;
    Node<Book>* ref = books.head;
    while (ref != nullptr){
        out<<ref->val;
        ref = ref->next;
    }
    return out;
}

std::ostream& Book::printBook(std::ostream& out) const {
    out << "\t\t\t   * " << title;
    if (customer != nullptr)
        out << " - checked out to " << customer->name; // overloaded <<
    out << std::endl;
    return out;
}

std::ostream& Customer::printCustomer(std::ostream& out) const {
    out << "\t\t\t" <<name;
    if (books.head != nullptr) {
        out << " has the following books:\n";
        Node<CheckedOutBook>* ref = books.head;
        while (ref != nullptr){
            out << "\t\t\t   * " << ref->val.author->val.name << " , " << ref->val.book->val.title << std::endl;
            ref = ref->next;
            
        }
    }
    else out << " has no books\n";
    return out;
}

void status() {
    int i;
    std::cout << "\n\n\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\t\t\tLibrary has the following books:\n\n";
    for (i = 'A'; i <= 'Z'; i++)
        if (catalog[i].head != nullptr)
            std::cout <<catalog[i].head->val;
    std::cout << "\n\t\t\tThe following people are using the library:\n\n";
    for (i = 'A'; i <= 'Z'; i++)
        if (people[i].head != nullptr)       
            std::cout << people[i].head->val;
	std::cout<<"\n\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}

void includeBook() {
    int b=0;
    int i;
    Author newAuthor;
    Book newBook;
    std::cout<<"\t\t\tEnter author's name: ";
    std::cin>>newAuthor.name;
    std::cout<<"\t\t\tEnter the title of the book: ";
    std::cin>>newBook.title;

    for ( i = 'A'; i <= 'Z'; i++){
        if(catalog[i].head != nullptr){
            if (catalog[i].head->val == newAuthor){
                b=1;
                break;
            }
        }
    }
    if (b == 1){
        catalog[i].head->val.books.addToHead(newBook);
    }
    else{
        newAuthor.books.addToHead(newBook);
        char fL = newAuthor.name.at(0);
        
        catalog[fL].addToHead(newAuthor);
    }    
} 

void checkOutBook() {
    int a = 0, b = 0;
    Customer customer;
    Author author;
    Book book;
    Node<Author> *authorRef;
    Node<Book> *bookRef;
    std::cout<<"\t\t\tEnter Customer's name : ";
    std::cin>> customer.name;
    while (true) {
        std::cout<<"\t\t\tEnter author's name : ";
        std::cin>> author.name;
        char fL = author.name[0];
        if(catalog[fL].head != nullptr){
            if (catalog[fL].head->val == author){
                authorRef = catalog[fL].head;
                a=1;
            }
        }
        if (a == 0){
            std::cout << "\t\t\tMisspelled author's name\n";
        }
        else break;
    }
    while (true) {    
        std::cout<<"\t\t\tEnter the title of the book : ";
        std::cin>> book.title;
        Node<Book>* b_temp = authorRef->val.books.head;
        while(b_temp != nullptr){
            if(b_temp->val == book){
                bookRef = b_temp;
                b = 1;
                break;
            }
            else b_temp = b_temp->next;
        }
        if(b == 0){
            std::cout<<"\t\t\tMisspelled title\n";
        }
        else break;

    }
    int i,c = 0;
	Node<Customer> *customerRef;
    for ( i = 'A'; i <= 'Z'; i++){
        if(people[i].head != nullptr){
            if (people[i].head->val == customer){
            	customerRef = people[i].head;
                c=1;
                break;
            }
        }
    }
    CheckedOutBook checkedOutBook(authorRef,bookRef);
    char firstLetter = customer.name.at(0);
    if (c == 0) { // a new customer
        customer.books.addToHead(checkedOutBook); // in the library;
        people[firstLetter].addToHead(customer);
        bookRef->val.customer = &people[firstLetter].head->val;
    }
    else {
        customerRef->val.books.addToHead(checkedOutBook);
        bookRef->val.customer = &people[firstLetter].head->val;
    }
}

void returnBook() {
    Customer customer;
    Book book;
    Author author;
    Node<Customer> *customerRef;
    Node<Book> *bookRef;
    Node<Author> *authorRef;
    int i,c=0;
    while (true) {
        std::cout<<"\t\t\tEnter customer's name : ";
        std::cin>>customer.name;
        char fL = customer.name[0];
        if(people[fL].head != nullptr){
            if (people[fL].head->val == customer){
                customerRef = people[fL].head;
                c=1;
            }
        }
        if(c == 0){
            std::cout << "\t\t\tCustomer's name misspelled\n";
        }   
        else break;
    }
    int a = 0;
    while (true) {
        std::cout<<"\t\t\tEnter author's name : ";
        std::cin>>author.name;
        char fL = author.name[0];
        if(catalog[fL].head != nullptr){
            if (catalog[fL].head->val == author){
                authorRef = catalog[fL].head;
                a=1;
            }
        }
        if (a == 0){
            std::cout << "\t\t\tMisspelled author's name\n";
        }
        else break;
    }
    int b = 0;
    while (true) {
        std::cout<<"\t\t\tEnter the title of the book : ";
        std::cin>>book.title;

        Node<Book>* b_temp = authorRef->val.books.head;
        while(b_temp != nullptr){
            if(b_temp->val == book){
                bookRef = b_temp;
                b = 1;
                break;
            }
            else b_temp = b_temp->next;
        }
        if(b == 0){
            std::cout<<"\t\t\tMisspelled title\n";
        }
        else break;
    }
    CheckedOutBook checkedOutBook(authorRef,bookRef);
    bookRef->val.customer = nullptr;
    customerRef->val.books.deleteNode(checkedOutBook);
}

int menu() {
    int option;

    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                 Library Management System                  \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Include a book in the catalog                         \n";
    std::cout << "\t\t\t  2)  Check out a book                                      \n";
    std::cout << "\t\t\t  3)  Return a book                                         \n";
    std::cout << "\t\t\t  4)  Status of library                                     \n";
    std::cout << "\t\t\t  5)  Exit                                                  \n\n";
	std::cout<<"\t\t\t Enter Choice : ";
    std::cin >> option;
    return option;
}

int main(){
    while (true){
        switch (menu()) {
            case 1: includeBook(); break;
            case 2: checkOutBook(); break;
            case 3: returnBook(); break;
            case 4: status(); break;
            case 5: return 0;
            default: std::cout << "\t\t\tWrong option, try again: ";
        }
    }
}

