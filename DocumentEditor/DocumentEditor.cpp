#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

// Abstraction of document elements
class DocumentElement {
    public:
        virtual string render() = 0;
};

// Concrete implementation for text elements
class TextElement: public DocumentElement {
    private:
        string text;
    public:
        TextElement(string t) : text(t) {}
        string render() override {
            return text;
        }
};

// Concrete implementation for image elements
class ImageElement: public DocumentElement {
    private:
        string imagePath;
    public:
        ImageElement(string path) : imagePath(path) {}
        string render() override {
            return "<img src='" + imagePath + "'>";
        }
};

// Concrete implementation for new line elements
class NewLineElement : public DocumentElement {
    public:
        string render() override {
            return "\n";
        }
};

// Concrete implementation for tab space elements
class TabSpaceElement : public DocumentElement {
    public:
        string render() override {
            return "\t";
        }
};

// Document class representing a collection of document elements
class Document {
    private:
        vector<DocumentElement*> elements;
    public:
        void addElement(DocumentElement* element) {
            elements.push_back(element);
        }
        string render() {
            string result;
            for (auto element : elements) {
                result += element->render();
            }
            return result;
        }
};

// Persistence interface for saving document data
class Persistence {
    public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of Persistence interface
class FileStorage : public Persistence {
    public:
        void save(string data) override {
            ofstream outFile("document.txt");
            if (outFile.is_open()) {
                outFile << data;
                outFile.close();
            } else {
                cerr << "Unable to open file for writing." << endl;
            }
        }
};

// Placeholder for DBStorage implementation of Persistence interface
class DBStorage : public Persistence {
    public:
        void save(string data) override {
            // Simulate saving to a database
            cout << "Saving data to the database: " << data << endl;
        }
};


// DocumentEditor class responsible for managing client interactions
class DocumentEditor {
    private:
        Document* document;
        Persistence* storage;
        string renderedDocument;
    public:
        DocumentEditor(Document* doc, Persistence* store) {
            document = doc;
            storage = store;
        }
        
        void addText(string text) {
            document->addElement(new TextElement(text));
        }

        void addImage(string path) {
            document->addElement(new ImageElement(path));
        }
        
        void addNewLine() {
            document->addElement(new NewLineElement());
        }

        void addTabSpace() {
            document->addElement(new TabSpaceElement());
        }

        string renderDocument() {
            if(!renderedDocument.empty()){
                return renderedDocument;
            }
            renderedDocument = document->render();
            return renderedDocument;
        }

        void saveDocument() {
            renderedDocument = document->render();
            storage->save(renderedDocument);
        }
};


// Client Usage Example
int main() {
    Document* doc = new Document();
    Persistence* storage = new FileStorage();
    DocumentEditor editor(doc, storage);

    editor.addText("Hello, World!");
    editor.addNewLine();
    editor.addImage("image.png");
    editor.addTabSpace();

    cout << editor.renderDocument() << endl;
    editor.saveDocument();

}
