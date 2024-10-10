#include <iostream>
#include <string>
using namespace std;

// Definition of a Node in BST
struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;

    Node(string k, string m) : key(k), meaning(m), left(NULL), right(NULL) {}
};

// Class for Binary Search Tree
class Dictionary {
private:
    Node* root;

    // Helper function to insert a new node into the BST
    Node* insert(Node* node, string key, string meaning) {
        if (node == NULL) {
            node = new Node(key, meaning);
        } else if (key < node->key) {
            node->left = insert(node->left, key, meaning);
        } else if (key > node->key) {
            node->right = insert(node->right, key, meaning);
        }
        return node;
    }

    // Helper function to search for a key in the BST
    Node* search(Node* node, string key) {
        if (node == NULL || node->key == key) {
            return node;
        } else if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Helper function to delete a node from the BST
    Node* deleteNode(Node* node, string key) {
        if (node == NULL) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            // Node to be deleted found

            // Case 1: Node has no children or only one child
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 2: Node has two children
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->meaning = temp->meaning;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    // Helper function to find the node with minimum key value in BST
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    // Helper function to print the BST inorder
    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->key << ": " << node->meaning << endl;
            inorder(node->right);
        }
    }

public:
    Dictionary() : root(NULL) {}

    // Function to insert a key-value pair into the dictionary
    void insert(string key, string meaning) {
        root = insert(root, key, meaning);
    }

    // Function to search for a key in the dictionary
    string search(string key) {
        Node* result = search(root, key);
        if (result != NULL) {
            return result->meaning;
        } else {
            return "Key not found";
        }
    }

    // Function to delete a word from the dictionary
    void deleteWord(string key) {
        root = deleteNode(root, key);
    }

    // Function to update the meaning of a word in the dictionary
    void updateMeaning(string key, string newMeaning) {
        Node* node = search(root, key);
        if (node != NULL) {
            node->meaning = newMeaning;
            cout << "Meaning updated successfully!\n";
        } else {
            cout << "Word not found. Cannot update meaning.\n";
        }
    }

    // Function to print all keys and meanings in the dictionary
    void printDictionary() {
        inorder(root);
    }
};

// Main function for testing the Dictionary class
int main() {
    Dictionary dict;

    // Inserting initial key-value pairs
    dict.insert("apple", "A fruit that grows on trees.");
    dict.insert("banana", "A long curved fruit that grows in clusters.");
    dict.insert("cat", "A small domesticated carnivorous mammal with soft fur.");

    // Menu for user interaction
    cout << "Dictionary Application\n";
    cout << "----------------------\n";
    cout << "1. Add a new word\n";
    cout << "2. Search for a word\n";
    cout << "3. Update meaning of a word\n";
    cout << "4. Delete a word\n";
    cout << "5. Print all words and meanings\n";
    cout << "6. Exit\n";

    int choice;
    string key, meaning, newMeaning;

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter word to add: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore(); // to ignore newline character left in the stream
                getline(cin, meaning);
                dict.insert(key, meaning);
                cout << "Word '" << key << "' added successfully!\n";
                break;
            case 2:
                cout << "\nEnter word to search: ";
                cin >> key;
                cout << "Meaning of '" << key << "': " << dict.search(key) << endl;
                break;
            case 3:
                cout << "\nEnter word to update meaning: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore(); // to ignore newline character left in the stream
                getline(cin, newMeaning);
                dict.updateMeaning(key, newMeaning);
                break;
            case 4:
                cout << "\nEnter word to delete: ";
                cin >> key;
                dict.deleteWord(key);
                cout << "Word '" << key << "' deleted successfully!\n";
                break;
            case 5:
                cout << "\nDictionary contents:\n";
                dict.printDictionary();
                break;
            case 6:
                cout << "\nExiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}
