# PathFinder

You want to develop a software to be used by city bus/metro rail commuters. Consider the metro rail network of Delhi. You may have a look at the latest [Delhi metro route map 2023](https://www.delhimetrorail.com/network_map). The purpose of the software is to help a commuter to work out a path from his/her current stop (metro station) to a destination stop.

The Delhi Metro Rail Corporation (DMRC) is willing to provide you with all the data related to metro routes and stations on each route. However, what is made available to you from DMRC is a set of MetroLine objects (each such object is a doubly linked list), one for each metro line/track (an object of class `MetroLine`). The linked list object carries a field which gives the name of the line and carries pointers to the sentinel nodes. Each node (object of class `MetroStop`) in the doubly linked list carries the name of the metro station, and a pointer to its `MetroLine`, along with pointers to the next and the previous nodes. There is no information given to you regarding which node (stop) is a junction of more than one metro line/track.

Given this collection of linked lists, you need to create a class called PathFinder. This class will have methods for several tasks.

## Task 1: Create an AVL Tree of All the Stations

The first task is to find what all nodes are junctions. You instantiate an AVL tree object. You start traversing each linked list (the `MetroLine` object) and keep inserting the metro station (stop) names on that linked list into the AVL tree. The key to be inserted into the AVL tree is the name of the metro stop. The AVL tree nodes are objects of class `AVLNode`. The keys for the AVL tree nodes are the metro stop names, hence we use the lexicographic ordering of the stop name to order the keys. 

If a stop is a junction, its name will get inserted more than once into the AVL tree. When a junction name is inserted for the first time, a new `AVLNode` is instantiated and inserted into the tree. But when the name of the junction is inserted for the second time (or more times), the `AVLNode` object (with that key, i.e., junction name) will be already there in the AVL tree. A search leading to an existing `AVLNode` with that key would imply that the `AVLNode` is a junction. 

The `AVLNode` refers to a metro stop and needs to keep a list of pointers to the corresponding node (object of class `MetroStop`) in the linked list of `MetroLine`. In case an `AVLNode` is a junction, there will be multiple metro lines passing through it. So, the `AVLNode` will keep a list of pointers to the distinct nodes (objects of `MetroStop`) referring to the same stop (junction). The distinct nodes are from the linked lists (of class `MetroLine`) of the lines that pass through the junction.

**Note:**
- Even though a junction will be a common stop in multiple metro lines, each linked list object (of class `MetroLine`) will have distinct node objects (`MetroStops`) all bearing the name of the same metro stop which is a junction.
- So the AVL tree node, if it is a junction, needs to keep a list of pointers to the separate (line/track linked-list) node objects.

After the AVL tree has been constructed, it is possible to examine a node and identify if it is a junction, and if yes, which are the lines passing through the junction.

## Task 2: Search for the Path

The second task is to work out a path between a given origin stop to a destination stop. We make a simplifying assumption that the metro track does not have cycles, which means it is not possible to plan a trip which reaches back to the origin and visits every intervening stop exactly once.

### Mechanism of Search:

1. **Instantiate Trip Objects:** 
   - As we begin searching from an origin stop, we shall instantiate `Trip` objects. For a given line/track, there will be two `Trip` objects that can be instantiated, one for the forward direction towards the head station of the linked list (`MetroLine`) and one for the backward direction towards the tail station of the linked list (`MetroLine`). 
   - A `Trip` object marks the initiation of search along the line/track in a particular direction. A `Trip` object also carries a pointer to a previous `Trip` object that instantiated it.

2. **Exploration:** 
   - If the search finds the destination, we are done and we report the `Trip` objects involved in the search. If a search visits a node which is a junction (the AVL tree would tell us if it is a stop junction), then we shall instantiate two new `Trip` objects for each track/line that crosses the junction. 
   - As a new `Trip` object is instantiated, it is placed in an object called `Exploration`. The `Exploration` object is a queue which stores the unexplored trips. 

3. **Search Process:** 
   - Search along a `Trip` requires traversing the linked list (`MetroLine`) starting from the junction in the specified direction. If the search along a `Trip` reaches the destination stop, we back-traverse along the trips and print the sequence of intermediate stations and the line/track names. 
   - Your program should also print the total fare to be paid for the route. If a trip is unsuccessful in finding the destination, then the `PathFinder` will dequeue and explore the next `Trip` object in the `Exploration` queue. 
   - Make a check to avoid the same trip getting explored again and again. If the `Exploration` queue becomes empty, it means that the destination stop is not reachable from the origin stop.

### Return Search Result as a Path Object:

The `PathFinder` class will have a member function called `findPath("origin stop", "destination stop")` which returns a pointer to an object of class `Path` if a path is found, or returns `NULL` in case there is no path found. This object will have 3 data members:
- A vector of strings for the names of the intermediate stations
- Another vector of strings with the corresponding metro lines
- An integer field to store the total fare.

### Computing the Fare

The input file will give you the fare applicable for a single metro line. The fare against each station is the fare from the origin stop of the metro line to a given station. Fare for a segment (one intermediate stop A to another intermediate stop B, assuming that B comes after A) can be computed as the absolute value of the difference of the fare for stop B and stop A. If a trip involves multiple metro lines, you can assume the total fare is computed as the sum of the fare of the intermediate segments. You are free to design what data fields you would like to store in the classes to compute the fare.

### Caution

Note that this assignment requires you to use linked lists, queues, and an AVL tree. You must use these data structures the way they are supposed to be used. You can use the implementations of linked lists and queues that you might have done in previous exercises. However, the AVL tree needs to be implemented and it should involve restructuring steps to restore the height balance property after every insertion. The test cases will check the height balance property of your AVL tree, which is the primary focus of this lab exercise.

## Sample Input

There are going to be multiple input files, each corresponding to a different track. More such input files and class templates will be provided. The last integer in every line is the price of the ticket (from origin). Every character which precedes the last integer is the name of the stop.

**File Name: Yellow.txt**

```
Samaypur Badli 0,
Rohini Sector 18 19 4,
Haiderpur Badli Mor 8,
Jahangirpuri 12,
Adarsh Nagar 16,
Azadpur 20,
Model Town 24,
GTB Nagar 28,
Vishwa Vidyalaya 32,
Vidhan Sabha 36,
Civil Lines 40,
Kashmere Gate 44,
Chandni Chowk 48,
...
```
