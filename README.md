# PathFinder
**PathFinder based Delhi Metro Route**

## Project Description:
PathFinder is designed to aid city bus/metro rail commuters in finding the most efficient path between their current stop and a destination stop within the Delhi Metro network. Leveraging data provided by the Delhi Metro Rail Corporation (DMRC), PathFinder utilizes a set of MetroLine objects (each represented as a doubly linked list) to determine the optimal route, taking into consideration junctions and fare calculations.

## Key Features:

### 1. AVL Tree Construction:
- Identifies all metro stops and junctions.
- Stores metro stops in an AVL Tree for efficient search and retrieval.
- Handles insertion and balancing of nodes to maintain the AVL Tree properties.

### 2. Path Search and Exploration:
- Finds paths between origin and destination stops.
- Explores possible routes using a queue-based exploration mechanism.
- Utilizes Trip objects to track the exploration along metro lines.

### 3. Junction Handling:
- Detects junctions where multiple metro lines intersect.
- Instantiates multiple trip objects for exploration at junctions.

### 4. Fare Calculation:
- Computes fare based on the difference in fare values between stops.
- Supports multi-line trips with cumulative fare calculation.

### 5. Path Reporting:
- Returns the path as a Path object containing intermediate stations, metro lines, and total fare.
- Prints the sequence of stations and lines along with the total fare.

## Classes and Data Structures:
- **MetroLine**: Doubly linked list representing a metro line.
- **MetroStop**: Node in the MetroLine linked list, representing a metro stop.
- **AVLNode**: Node in the AVL Tree, storing metro stop names and pointers to corresponding MetroStop objects.
- **Trip**: Represents a search direction along a metro line.
- **Exploration**: Queue storing unexplored trips.
- **PathFinder**: Main class containing methods for AVL tree construction, path finding, and fare calculation.
- **Path**: Stores the result of the path search, including intermediate stations, lines, and fare.

## Usage Instructions:

### 1. Initialize MetroLine Objects:
- Load data from input files representing different metro lines.
- Create MetroLine objects for each line and populate with MetroStop nodes.

### 2. Construct AVL Tree:
- Instantiate the PathFinder class.
- Call the method to construct the AVL tree using the MetroLine objects.

### 3. Find Path:
- Use the `findPath("origin stop", "destination stop")` method to search for a path.
- Retrieve the Path object containing the route details and fare.

### Sample Input File Format:
Samaypur Badli0
Rohini Sector 18, 194
Haiderpur Badli Mor8
Jahangirpuri12

### Class Templates and Test Cases:
- Provided in the project repository.
- Ensure proper integration and validation of the implemented classes and methods.
