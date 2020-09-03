#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

/*
  Library Catalog
    1. Create a Book class which has the ff elements:
      -Title
      -Page Count
      -ISBN
      -Whether or not it is checked out
    2. Add an 'Add Book' function
    3. Add a 'Display All Books' function

*/
using namespace std;

void writeFile(string title, string author, int pageCount, string isbn);


//define class
class Book{
  public:
    //Book Properties
    string Title;
    string Author;
    int PageCount;
    string Isbn;
  public:
    //Constructor
    Book(){
    }
    //functions to set properties
    void setTitle(string title) {Title = title;};
    void setAuthor(string author) {Author = author;};
    void setPageCount(int pageCount) {PageCount = pageCount;};
    void setIsbn(string isbn) {Isbn = isbn;};
    //function to display book info
    void bookInfo();

};

//Book Objects array
Book books[256];
//Counter of books in array
int counter = 0;


//Replaces instaces of spaces to dash
string replaceToDash(string entry){
  replace(entry.begin(), entry.end(), ' ', '-');
  return entry;
}

//Replaces instances of dash to space
string replaceToSpace(string entry){
  replace(entry.begin(), entry.end(), '-', ' ');
  return entry;
}

//Displaces info about books
void Book::bookInfo(){
  cout << "Title: " << replaceToSpace(Title) << endl;
  cout << "Author: " << replaceToSpace(Author) << endl;
  cout << "Page Count: " << PageCount << endl;
  cout << "ISBN: " << replaceToSpace(Isbn) << "\n\n";
}

//Counts number of lines in selected text file
int lineCounter(){
  string line;
  int count = 0;
  ifstream file("books.txt");
  if(file.is_open()){
    while(!file.eof()){
      getline(file, line);
      count ++;
    }
    file.close();
  }
  return count;
}


//Display info function
void displayInfo(){
  //Defining variables
  string title;
  string author;
  int pageCount;
  string isbn;
  int lineCount = lineCounter();

  //Opening and accessing file
  fstream file;
  file.open("books.txt", ios::in);

  if(!file){
    cout << "Error: Book file not found" << endl;
    system("pause");
    exit(EXIT_FAILURE);
  }


  //Iterating through file and saving each file input as an object inside the books array
  for(int i = counter; i<lineCount; i++){
    if(file >> title >> author >> pageCount >> isbn){
      books[i].setTitle(title);
      books[i].setAuthor(author);
      books[i].setPageCount(pageCount);
      books[i].setIsbn(isbn);

      //Displaying info
      books[i].bookInfo();
    }
  }
  
}

void createBook(){
  //Declaring variables
  string title;
  string author;
  int pageCount;
  string isbn;

  //Taking input about book from user
  cout << "Book Title: ";
  cin.ignore();
  getline(cin, title);
  cout << "Author: ";
  getline(cin, author);
  cout << "Page Count: ";
  cin >> pageCount;
  cout << "ISBN: ";
  cin.ignore();
  getline(cin, isbn);

  //Writing user's input into file
  writeFile(title, author, pageCount, isbn);

  //Writing user's input to object in books array
  books[counter].setTitle(title);
  books[counter].setAuthor(author);
  books[counter].setPageCount(pageCount);
  books[counter].setIsbn(isbn);
  counter++;

  cout << "Book added!" << endl;
}

void writeFile(string title, string author, int pageCount, string isbn){
  //Writing input to file
  ofstream file;
  file.open("books.txt", ios::app);
  file << replaceToDash(title) << " " << " " << replaceToDash(author) << " " << pageCount << " "<< replaceToDash(isbn) << " " << "\n" ;
  file.close();

  cout << "\n Addition Success!" << endl;
}

//Displays start menu and takes in user's choice of input
int startMenu(){
  int option;
  cout << "What would you like to do?" << endl;
  cout << "1. Add a Book" << endl;
  cout << "2. Display All Books" << endl;
  cout << "3. Exit" << endl;

  cin >> option;

  return option;
}

void defineChoice(int option){
    //Switch for corresponding function
    switch(option){
    case 1:
      //Creates a book
      createBook();
      break;
    case 2:
      displayInfo();
      break;
    case 3:
      break;
    default:
      cout << "You have entered an invalid option! \n\n" << endl;
      break;
  }
}


int main(){
  int option;

  //While the returned data is not the exit value, run loop
  while (option != 3){
    option = startMenu();
    defineChoice(option);
  }
  return 0;
}