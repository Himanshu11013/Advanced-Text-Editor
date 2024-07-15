#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>

#define MAX_TREE_HT 256
using namespace std;

// HuffmanCoding class
class HuffmanCoding {
public:
    map<char, string> codes;
    map<char, int> freq;

    class MinHeapNode {
    public:
        char data;
        int freq;
        MinHeapNode *left, *right;

        MinHeapNode(char data, int freq) {
            left = right = nullptr;
            this->data = data;
            this->freq = freq;
        }
    };

    struct compare {
        bool operator()(MinHeapNode* l, MinHeapNode* r) {
            return (l->freq > r->freq);
        }
    };

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    void calcFreq(const string& str) {
        for (char ch : str) {
            freq[ch]++;
        }
    }

    void storeCodes(MinHeapNode* root, string str) {
        if (root == nullptr)
            return;
        if (root->data != '$')
            codes[root->data] = str;
        storeCodes(root->left, str + "0");
        storeCodes(root->right, str + "1");
    }

    void buildHuffmanTree() {
        MinHeapNode *left, *right, *top;
        for (auto v = freq.begin(); v != freq.end(); v++)
            minHeap.push(new MinHeapNode(v->first, v->second));
        while (minHeap.size() != 1) {
            left = minHeap.top();
            minHeap.pop();
            right = minHeap.top();
            minHeap.pop();
            top = new MinHeapNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }
        storeCodes(minHeap.top(), "");
    }

    string decode(MinHeapNode* root, const string& s) {
        string ans = "";
        MinHeapNode* curr = root;
        for (char ch : s) {
            if (ch == '0')
                curr = curr->left;
            else if (ch == '1')
                curr = curr->right;
            if (curr->left == nullptr && curr->right == nullptr) {
                ans += curr->data;
                curr = root;
            }
        }
        return ans;
    }

    string encode(const string& str) {
        string encodedString;
        for (char ch : str) {
            encodedString += codes[ch];
        }
        return encodedString;
    }
};

class AVLNode {
public:
    string word;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const string& w) : word(w), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insert(AVLNode* node, const string& word) {
    if (!node)
        return new AVLNode(word);

    if (word < node->word)
        node->left = insert(node->left, word);
    else if (word > node->word)
        node->right = insert(node->right, word);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && word < node->left->word)
        return rightRotate(node);

    if (balance < -1 && word > node->right->word)
        return leftRotate(node);

    if (balance > 1 && word > node->left->word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && word < node->right->word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

AVLNode* deleteNode(AVLNode* root, const string& word) {
    if (!root)
        return root;

    if (word < root->word)
        root->left = deleteNode(root->left, word);
    else if (word > root->word)
        root->right = deleteNode(root->right, word);
    else {
        if ((!root->left) || (!root->right)) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->word = temp->word;
            root->right = deleteNode(root->right, temp->word);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(AVLNode* root) {
    if (root != nullptr) {
        cout << root->word << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

class TextEditor {
    AVLNode* root;

public:
    TextEditor() : root(nullptr) {}

    void insert(const string& word) {
        root = ::insert(root, word);
        display();
    }

    void replace(const string& oldWord, const string& newWord) {
        root = ::deleteNode(root, oldWord);
        root = ::insert(root, newWord);
        display();
    }

    void deleteWord(const string& word) {
        root = ::deleteNode(root, word);
        display();
    }

    void display() {
        cout << ".........................................................................................................................." << endl;
        preOrder(root);
        cout << endl;
        cout << ".........................................................................................................................." << endl;
    }

    string getSentence() {
        string sentence;
        stack<AVLNode*> stack;
        AVLNode* current = root;
        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            if (!sentence.empty()) {
                sentence += " ";
            }
            sentence += current->word;
            current = current->right;
        }
        return sentence;
    }
};

class SpellChecker {
    class TreeNode {
    public:
        string word;
        int next[40];

        TreeNode(string x) : word(x) {
            fill(begin(next), end(next), 0);
        }
        TreeNode() {}
    };

    TreeNode rootNode;
    vector<TreeNode> tree;
    int nodePtr;

public:
    SpellChecker() : tree(10000), nodePtr(0) {}

    int editDistance(string& a, string& b) {
        int m = a.length(), n = b.length();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] != b[j - 1])
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
                else
                    dp[i][j] = dp[i - 1][j - 1];
            }
        }
        return dp[m][n];
    }

    void add(TreeNode& root, TreeNode& curr) {
        if (root.word == "") {
            root = curr;
            return;
        }
        int dist = editDistance(curr.word, root.word);
        if (tree[root.next[dist]].word == "") {
            nodePtr++;
            tree[nodePtr] = curr;
            root.next[dist] = nodePtr;
        } else {
            add(tree[root.next[dist]], curr);
        }
    }

    vector<string> getSimilarWords(TreeNode& root, const string& s, int TOL) {
        vector<string> ret;
        if (root.word == "") return ret;
        int dist = editDistance(const_cast<string&>(root.word), const_cast<string&>(s));
        if (dist <= TOL) ret.push_back(root.word);
        int start = max(1, dist - TOL);
        while (start <= dist + TOL) {
            vector<string> tmp = getSimilarWords(tree[root.next[start]], s, TOL);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
            start++;
        }
        return ret;
    }

    void loadDictionary(const vector<string>& dictionary) {
        nodePtr = 0;
        for (const auto& dictWord : dictionary) {
            TreeNode tmp = TreeNode(dictWord);
            add(rootNode, tmp);
        }
    }

    vector<string> spellCheck(const string& word, int TOL = 2) {
        return getSimilarWords(rootNode, word, TOL);
    }
};

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> dictionary;
    string word;
    while (infile >> word) {
        dictionary.push_back(word);
    }
    infile.close();

    SpellChecker spellChecker;
    spellChecker.loadDictionary(dictionary);

    TextEditor editor;
    HuffmanCoding huffman;

    string command, inputWord, oldWord, newWord;

    while (true) {
        cout << "Enter command (1.insert/2.replace/3.delete/4.exit): ";
        cin >> command;

        if (command == "1") {
            cout << "Enter word to insert: ";
            cin >> inputWord;
            editor.insert(inputWord);

            cout << "Do you want to perform a spell check? (yes/no): ";
            string choice;
            cin >> choice;

            if (choice == "yes") {
                vector<string> match = spellChecker.spellCheck(inputWord);
                cout << "Similar words to " << inputWord << ": ";
                for (const auto& x : match) {
                    cout << x << " ";
                }
                cout << endl;
            } else {
                editor.display();
            }

        } else if (command == "2") {
            cout << "Enter word to replace: ";
            cin >> oldWord;
            cout << "Enter new word: ";
            cin >> newWord;
            editor.replace(oldWord, newWord);

        } else if (command == "3") {
            cout << "Enter word to delete: ";
            cin >> inputWord;
            editor.deleteWord(inputWord);

        } else if (command == "4") {
            string sentence = editor.getSentence();
            cout << endl;
            cout << "Generated Sentence: " << sentence << endl;
            cout << endl;

            // Huffman Encoding
            string encodedString, decodedString;
            huffman.calcFreq(sentence);
            if (huffman.freq.empty()) {
                cerr << "Error: Frequency map is empty, no characters to encode!" << endl;
                return 1;
            }

            huffman.buildHuffmanTree();

            cout << "Character With their Frequencies:\n";
            for (auto v = huffman.codes.begin(); v != huffman.codes.end(); v++)
                cout << v->first << ' ' << v->second << endl;

            encodedString = huffman.encode(sentence);
            cout << "\nEncoded Huffman data:\n" << encodedString << endl;

            decodedString = huffman.decode(huffman.minHeap.top(), encodedString);
            cout << "\nDecoded Huffman Data:\n" << decodedString << endl;

            // Calculate and display compression ratio
            int originalSize = sentence.length() * 8; // size in bits
            int encodedSize = encodedString.length(); // size in bits
            double compressionRatio = static_cast<double>(encodedSize) / originalSize;

            cout << "\nOriginal Size (in bits): " << originalSize << endl;
            cout << "Encoded Size (in bits): " << encodedSize << endl;
            cout << "Compression Ratio: " << compressionRatio << endl;

            // Output encoded and decoded data to files
            ofstream encodedFile("encode.txt");
            if (!encodedFile) {
                cerr << "Error opening encoded file!" << endl;
                return 1;
            }
            encodedFile << encodedString;
            encodedFile.close();

            ofstream decodedFile("decode.txt");
            if (!decodedFile) {
                cerr << "Error opening decoded file!" << endl;
                return 1;
            }
            decodedFile << decodedString;
            decodedFile.close();

            break;

        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}