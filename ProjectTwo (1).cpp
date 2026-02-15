//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Michael Lovett
// Course      : SNHU CS-300
// Description : ABCU Advising Assistance Program (BST-based course planner)
//               Single-file solution (no external CSV parser headers).
//============================================================================

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --------------------------- Helpers ---------------------------
static inline string ltrim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start])))
        ++start;
    return s.substr(start);
}

static inline string rtrim(const string& s) {
    if (s.empty()) return s;
    size_t end = s.size();
    while (end > 0 && isspace(static_cast<unsigned char>(s[end - 1])))
        --end;
    return s.substr(0, end);
}

static inline string trim(const string& s) {
    return rtrim(ltrim(s));
}

static inline string toUpper(string s) {
    for (char& ch : s)
        ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
    return s;
}

// CSV splitter that respects double quotes
static vector<string> splitCSVRespectQuotes(const string& line) {
    vector<string> tokens;
    string cur;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                cur.push_back('"');
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes) {
            tokens.push_back(trim(cur));
            cur.clear();
        }
        else {
            cur.push_back(c);
        }
    }

    tokens.push_back(trim(cur));
    return tokens;
}

// --------------------------- Data Model ---------------------------
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// --------------------------- BST Implementation ---------------------------
class BinarySearchTree {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;
        Node(const Course& c) : course(c), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    static void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    static Node* insert(Node* node, const Course& c) {
        if (!node)
            return new Node(c);

        if (c.courseNumber < node->course.courseNumber)
            node->left = insert(node->left, c);
        else if (c.courseNumber > node->course.courseNumber)
            node->right = insert(node->right, c);
        else
            node->course = c; // duplicate update

        return node;
    }

    static const Course* search(Node* node, const string& key) {
        while (node) {
            if (key == node->course.courseNumber)
                return &node->course;
            node = (key < node->course.courseNumber) ? node->left : node->right;
        }
        return nullptr;
    }

    static void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", "
             << node->course.courseTitle << endl;
        inOrder(node->right);
    }

public:
    ~BinarySearchTree() { destroy(root); }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    void insertCourse(const Course& c) {
        root = insert(root, c);
    }

    const Course* getCourse(const string& courseNumber) const {
        return search(root, courseNumber);
    }

    void printCourseList() const {
        inOrder(root);
    }
};

// --------------------------- Loading Logic ---------------------------
static bool loadCoursesFromFile(const string& fileName,
                                BinarySearchTree& bst) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return false;
    }

    vector<Course> tempCourses;
    vector<string> courseNums;
    string line;

    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        vector<string> tokens = splitCSVRespectQuotes(line);
        if (tokens.size() < 2) continue;

        string courseNum = toUpper(trim(tokens[0]));
        string title = trim(tokens[1]);

        Course c;
        c.courseNumber = courseNum;
        c.courseTitle = title;

        for (size_t i = 2; i < tokens.size(); ++i) {
            string prereq = toUpper(trim(tokens[i]));
            if (!prereq.empty())
                c.prerequisites.push_back(prereq);
        }

        tempCourses.push_back(c);
        courseNums.push_back(courseNum);
    }

    file.close();

    bst.clear();

    for (const Course& c : tempCourses) {
        bst.insertCourse(c);
    }

    return true;
}

// --------------------------- Course Info ---------------------------
static void printCourseInfo(const BinarySearchTree& bst,
                            const string& input) {
    string key = toUpper(trim(input));
    const Course* c = bst.getCourse(key);

    if (!c) {
        cout << "Course not found." << endl;
        return;
    }

    cout << c->courseNumber << ", " << c->courseTitle << endl;

    if (c->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";
    for (size_t i = 0; i < c->prerequisites.size(); ++i) {
        cout << c->prerequisites[i];
        if (i + 1 < c->prerequisites.size())
            cout << ", ";
    }
    cout << endl;
}

// --------------------------- Menu ---------------------------
static void printMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

// --------------------------- Main ---------------------------
int main() {
    cout << "Welcome to the course planner." << endl;

    BinarySearchTree bst;
    bool loaded = false;
    int choice = 0;

    while (choice != 9) {
        printMenu();
        cout << "What would you like to do? ";

        string input;
        getline(cin, input);

        try {
            choice = stoi(input);
        }
        catch (...) {
            cout << input << " is not a valid option." << endl;
            continue;
        }

        switch (choice) {

        case 1: {
            cout << "Enter file name: ";
            string fileName;
            getline(cin, fileName);

            loaded = loadCoursesFromFile(trim(fileName), bst);

            if (loaded) {
                cout << "Courses loaded successfully." << endl;
            }

            break;
        }

        case 2:
            if (!loaded) {
                cout << "Please load data first (Option 1)." << endl;
                break;
            }
            cout << "Here is a sample schedule:" << endl;
            bst.printCourseList();
            break;

        case 3:
            if (!loaded) {
                cout << "Please load data first (Option 1)." << endl;
                break;
            }
            cout << "What course do you want to know about? ";
            {
                string courseNum;
                getline(cin, courseNum);
                printCourseInfo(bst, courseNum);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}