#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;


class DocumentEditor {
    private:
        vector<string> document;
        string renderedDocument;

    public:
        // adds text as a plain string
        void addText(string text) {
            document.push_back(text);
        }

        // adds an image represented by its path 
        void addImage(string imagePath) {
            document.push_back( imagePath);
        }

        string renderDocument() {
            renderedDocument = "";
            for (const auto& element : document) {
                if(element.size()>4 && (element.substr(element.size()-4) == ".png" || element.substr(element.size()-4) == ".jpg")) {
                    renderedDocument += "<img src='" + element + "'>";
                } else {
                    renderedDocument += element;
                }
            }
            return renderedDocument;
        }

        void saveToFile() {
            ofstream outFile("document.txt");
            if(outFile.is_open()) {
                outFile << renderDocument();
                outFile.close();
            } else {
                cerr << "Failed to open file for writing." << endl;
            }
        }
};

int main() {
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("image.png");
    editor.addText("This is a test document.");
    cout<<editor.renderDocument()<<endl;
    editor.saveToFile();
    return 0;
}