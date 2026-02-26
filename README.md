# CS-300-Data-Structures-and-Algorithms
SNHU CS-300 portfolio repository containing runtime analysis of data structures (vector, hash table, BST) and a C++ advising assistance application demonstrating sorting and searching using a binary search tree.
This repository contains portfolio artifacts from CS-300, demonstrating my understanding of:

Data structures (Vector, Hash Table, Binary Search Tree)

Runtime and memory analysis (Big-O complexity)

Algorithm design and evaluation

File parsing and input validation

Software architecture and maintainability

C++ application development

This course focused on selecting appropriate data structures, analyzing performance tradeoffs, and implementing scalable solutions.

## Project One – Data Structures Analysis
- Summary of runtime and memory analysis
- Document link

## Project Two - working code
- What it does
- Instructions to compile & run

- The ABCU Advising Program is designed to manage course information and allow users to:
Option 2: Print all courses in alphanumeric order
Option 3: Print a single course, including its title and prerequisites
Input is provided via a CSV file formatted as: courseNumber, courseTitle, prerequisite1, prerequisite2, ... prerequisiteN
Each course is represented as: Course = {
    courseNumber,
    courseTitle,
    prerequisites[]
}

All data structures must support:
Loading and validating course data
Printing a sorted list of courses
Searching for a specific course

Load and Validation Logic (Common to All Structures)
Pseudocode: Read each line from CSV
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
1. Vector (courseList)
Load
loadVector(file):
    courseList = parsedCourses
    validatePrereqs()
   Option 2 (Print All Courses)
   sort(courseList by courseNumber)

Runtime (Worst Case)
print each course
Option 3 (Search Course)
linear scan through courseList
if match found → print course
| Operation               | Complexity |
| ----------------------- | ---------- |
| Load                    | O(n)       |
| Option 3 (Search)       | O(n)       |
| Option 2 (Sort + Print) | O(n log n) |

Evaluation
Advantages:
Simple implementation
Minimal overhead
Disadvantages:
Linear search time
Must sort every time Option 2 is selected

2. Hash Table (Chaining)
Load
loadHash(file):
    validatePrereqs()
    for each Course:
        insert into bucket hash(courseNumber)

Option 2 (Print All Courses)
Collect all bucket elements into vector
Sort vector
Print
Option 3 (Search Course)
Hash courseNumber
Traverse bucket chain
If found → print

Runtime (Worst Case)
Operation	Complexity
Load	O(n²) worst-case (all collisions)
Option 3 (Search)	O(n) worst-case
Option 2 (Sort + Print)	O(n log n)
Evaluation
Advantages:
Average search: O(1)
Efficient for direct lookups
Disadvantages:
Worst-case O(n) due to collisions
Unordered structure
Requires sorting for Option 2

3. Binary Search Tree (Ordered by courseNumber)
Load
loadBST(file):
    validatePrereqs()
    bstInsert each Course

Option 2 (Print All Courses)
inOrder(root)
In-order traversal prints in ascending order naturally.)
Option 3 (Search Course)
bstSearch(root, courseNumber)
If found → print
Runtime (Worst Case)
Operation	Complexity
Load	O(n²) worst-case (unbalanced tree)
Option 3 (Search)	O(n) worst-case
Option 2 (Print All)	O(n)
Average Case (Balanced Tree)
Operation	Complexity
Load	O(n log n)
Option 3	O(log n)
Option 2	O(n)
Evaluation
Advantages:
Naturally maintains sorted order
Efficient average-case lookup
No additional sorting required
Disadvantages:
Can degrade to O(n) if unbalanced
More complex than vector

Menu Logic (All Structures)
loop:
    print menu
    input choice

    if 1 → load selected structure
    if 2 → if loaded, print all courses
    if 3 → if loaded, search and print course
    if 9 → exit

   Final Runtime Comparison (Worst Case)
Structure	Load	Option 3	Option 2
Vector	O(n)	O(n)	O(n log n)
Hash Table	O(n²)	O(n)	O(n log n)
BST	O(n²)	O(n)	O(n)
Recommendation
While each structure has strengths, the Binary Search Tree (BST) is the best choice for this project.
Reasoning:
Option 2 requires sorted output.
BST supports sorted order natively through in-order traversal.
No additional sorting step is required.
Average search time is O(log n), which is more efficient than a vector.
Although the BST can degrade to O(n) in the worst case if unbalanced, it provides the best balance of performance and functionality for the requirements of the ABCU Advising Program. 
