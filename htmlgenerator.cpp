#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function prototypes
void createTable();
void createForm();
void createNavbar();
void createArticle();
void generateHTML(const vector<string>& htmlElements);

int main() {
    vector<string> htmlElements;
    int choice;
    bool quit = false;

    while (!quit) {
        cout << "Select an option:\n";
        cout << "1. Create Table\n";
        cout << "2. Create Form\n";
        cout << "3. Create Navigation Bar\n";
        cout << "4. Create Article\n";
        cout << "5. Generate HTML File\n";
        cout << "6. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createTable();
                htmlElements.push_back("<table>...</table>");
                break;
            case 2:
                createForm();
                htmlElements.push_back("<form>...</form>");
                break;
            case 3:
                createNavbar();
                htmlElements.push_back("<nav>...</nav>");
                break;
            case 4:
                createArticle();
                htmlElements.push_back("<article>...</article>");
                break;
            case 5:
                generateHTML(htmlElements);
                break;
            case 6:
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Function definitions
void createTable() {
    // Code to get table details from the user and generate the table HTML
}

void createForm() {
    // Code to get form details from the user and generate the form HTML
}

void createNavbar() {
    // Code to get navigation bar details from the user and generate the navigation bar HTML
}

void createArticle() {
    // Code to get article details from the user and generate the article HTML
}

void generateHTML(const vector<string>& htmlElements) {
    ofstream htmlFile("output.html");

    if (htmlFile.is_open()) {
        htmlFile << "<!DOCTYPE html>\n";
        htmlFile << "<html>\n";
        htmlFile << "<head>\n";
        htmlFile << "<title>Generated HTML Page</title>\n";
        htmlFile << "</head>\n";
        htmlFile << "<body>\n";

        for (const string& element : htmlElements) {
            htmlFile << element << "\n";
        }

        htmlFile << "</body>\n";
        htmlFile << "</html>\n";

        cout << "HTML file generated successfully (output.html).\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }

    htmlFile.close();
}