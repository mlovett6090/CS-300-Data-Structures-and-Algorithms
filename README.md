CS-300 – Data Structures and Algorithms
Michael Lovett
Southern New Hampshire University
SNHU CS-300 portfolio repository containing runtime analysis of data structures (Vector, Hash Table, BST) and a C++ advising assistance application demonstrating sorting and searching using a Binary Search Tree.
📌 Repository Overview
This repository contains portfolio artifacts from CS-300, demonstrating my understanding of:
Data Structures (Vector, Hash Table, Binary Search Tree)
Runtime and memory analysis (Big-O complexity)
Algorithm design and evaluation
File parsing and input validation
Software architecture and maintainability
C++ application development
This course focused on selecting appropriate data structures, analyzing performance tradeoffs, and implementing scalable solutions.
📊 Project One – Data Structures Analysis
Problem Statement
The ABCU Advising Program is designed to manage course information and allow users to:
Option 2: Print all courses in alphanumeric order
Option 3: Print a single course, including its title and prerequisites
Input is provided via a CSV file formatted as: courseNumber, courseTitle, prerequisite1, prerequisite2, ... prerequisiteN
Each course is represented as:
Course = {
    courseNumber,
    courseTitle,
    prerequisites[]
}
All data structures must support:
Loading and validating course data
Printing a sorted list of courses
Searching for a specific course
Load and Validation Logic (Common to All Structures)
Pseudocode:
Read each line from CSV
If line has fewer than 2 fields → format error
Create Course object
Store courseNumber in a collection

After reading all lines:
Validate each prerequisite against the set of courseNumbers
Insert validated Course into chosen data structure
Assumption:
Let n = number of courses.
Per-line parsing is considered O(1) relative to n.
Data Structure Implementations
1️⃣ Vector (courseList)
Load
loadVector(file):
    courseList = parsedCourses
    validatePrereqs()
Option 2 – Print All Courses
sort(courseList by courseNumber)
print each course
Option 3 – Search Course
linear scan through courseList
if match found → print course
Runtime (Worst Case)
Operation	Complexity
Load	O(n)
Option 3 (Search)	O(n)
Option 2 (Sort + Print)	O(n log n)
Evaluation
Advantages
Simple implementation
Minimal overhead
Disadvantages
Linear search time
Must sort each time Option 2 is selected
2️⃣ Hash Table (Chaining)
Load
loadHash(file):
    validatePrereqs()
    for each Course:
        insert into bucket hash(courseNumber)
Option 2 – Print All Courses   
Collect all bucket elements into vector
Sort vector
Print
Option 3 – Search Course
Hash courseNumber
Traverse bucket chain
If found → print
Runtime (Worst Case)
Operation	Complexity
Load	O(n²) (all collisions)
Option 3 (Search)	O(n)
Option 2 (Sort + Print)	O(n log n)
Evaluation
Advantages
Average search O(1)
Efficient for direct lookups
Disadvantages
Worst-case O(n) due to collisions
Unordered structure
Requires sorting for Option 2
3️⃣ Binary Search Tree (Ordered by courseNumber)
Load
loadBST(file):
    validatePrereqs()
    bstInsert each Course
Option 2 – Print All Courses
inOrder(root)
(In-order traversal prints courses in ascending order naturally.)
Option 3 – Search Course
bstSearch(root, courseNumber)
If found → print

Runtime (Worst Case)
Operation	Complexity
Load	O(n²) (unbalanced tree)
Option 3 (Search)	O(n)
Option 2 (Print All)	O(n)
Average Case (Balanced Tree)
Operation	Complexity
Load	O(n log n)
Option 3	O(log n)
Option 2	O(n)
Evaluation
Advantages
Naturally maintains sorted order
Efficient average-case lookup
No additional sorting required
Disadvantages
Can degrade to O(n) if unbalanced
More complex than a vector
📈 Final Runtime Comparison (Worst Case)
Structure	Load	Option 3	Option 2
Vector	O(n)	O(n)	O(n log n)
Hash Table	O(n²)	O(n)	O(n log n)
BST	O(n²)	O(n)	O(n)
✅ Recommendation
While each structure has strengths, the Binary Search Tree (BST) is the best choice for this project.
Reasoning:
Option 2 requires sorted output.
BST supports sorted order natively via in-order traversal.
No additional sorting step is required.
Average search time is O(log n), more efficient than a vector.
Although the BST can degrade to O(n) if unbalanced, it provides the best balance of performance and functionality for the requirements of the ABCU Advising Program.
💻 Project Two – C++ Advising Assistance Application
Overview
This project implements a working course planner using a custom Binary Search Tree.
Features
Load course data from CSV file
Print all courses in alphanumeric order
Display a single course with prerequisites
Input validation and error handling
Proper memory management via destructor
Menu Logic
loop:
    print menu
    input choice

    if 1 → load selected structure
    if 2 → if loaded, print all courses
    if 3 → if loaded, search and print course
    if 9 → exit

🧠 Reflection
What was the problem you were solving?
The primary problem was determining the most efficient way to store, organize, and retrieve course information for an academic advising system. The program needed to read structured data, maintain course relationships, support sorted output, and allow quick searches.
How did you approach the problem?
I evaluated multiple data structures — vector, hash table, and binary search tree — before implementing a solution. Instead of focusing only on functionality, I analyzed runtime tradeoffs and scalability. Understanding data structures is critical because performance depends directly on how data is stored and accessed. This analysis led me to select the BST as the best fit for the project requirements.
How did you overcome roadblocks?
Challenges included parsing CSV input correctly, validating prerequisites, and ensuring proper BST insertion and search logic. I addressed these issues by breaking the program into modular components and testing each function independently. This structured debugging approach improved both reliability and development efficiency.
How has this project expanded your software design approach?
This project reinforced the importance of planning before coding. I now consider system requirements, data scale, and algorithm efficiency before choosing a data structure. It strengthened my understanding of Big-O analysis as a practical design tool rather than just a theoretical concept.
How has this evolved your coding practices?
I focused on modular design, meaningful naming conventions, and separating data structure logic from user interface logic. I also ensured proper memory management and clear code organization. As a result, my programs are more readable, maintainable, and adaptable to future enhancements.
🚀 Conclusion
This repository demonstrates my ability to:
Analyze and compare data structures
Apply Big-O runtime evaluation
Design scalable solutions
Implement custom data structures in C++
Write maintainable, structured code
These projects strengthened both my theoretical understanding and practical implementation skills in data structures and algorithm design.    
