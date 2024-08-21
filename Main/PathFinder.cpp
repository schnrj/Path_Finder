#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;


// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    int totalStops = 0;
    MetroStop* stop = node;
    while (stop != nullptr)
    {
        totalStops++;
        stop = stop->getNextStop();
    }

    return totalStops;
}

vector<string> tokenizer(string row)
{
    vector<string> tokens;

    for (int i = 0 ; i < row.size() ; i++)
    {
        string token = "";
        while (row[i] != ' ' && row[i] != ',')
        {
            token += row[i++];
        }
        tokens.push_back(token);
    }

    return tokens;
}


void MetroLine::populateLine(std::string filename)
{
    // Read the file and populate the line
    fstream fin;
    fin.open(filename, ios::in);
    string row;
    while (getline(fin ,  row))
    {
        if (row.empty())break;
        vector<string> tokens = tokenizer(row);
        string stopName = "";
        for (int i = 0 ; i < tokens.size() - 1 ; i++) stopName += (tokens[i] + " ");
        stopName.erase(stopName.end() - 1);
        int fare = stoi(tokens[tokens.size() - 1]);
        if (node == nullptr) this->node = new MetroStop(stopName , this , fare);
        else
        {
            MetroStop* stop = node;
            while (stop->getNextStop() != nullptr)
            {
                stop = stop->getNextStop();
            }

            MetroStop* newstop = new MetroStop(stopName , this , fare);

            stop->setNextStop(newstop);
            newstop->setPrevStop(stop);
        }

    }
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height = 1; // utility variable

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;
    int getHeight() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
    void setHeight(int height);

};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
void AVLNode::setHeight(int height)
{
    this->height = height;
}

int AVLNode::getHeight() const
{
    return height;
}
std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {

private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node , string stopName);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node)
{
    if (node == nullptr) return 0;
    //returning maximum height of that node from its ancestor leaf node
    return node->getHeight();
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node)
{
    // 1 if left skewed , -1 for right skewed  , 0 for balanced , other for unbalanced
    return (height(node->getLeft()) - height(node->getRight()));
}

void AVLTree::rotateLeft(AVLNode* node)
{
    AVLNode* par = node->getParent();
    AVLNode* r = node->getRight();
    AVLNode* rl = r->getLeft();
    bool isleft = 1;
    if (par != nullptr) isleft = (par->getLeft() == node);
    if (isleft)
    {
        if (par != nullptr) par->setLeft(r);
        r->setParent(par);
    }
    else
    {
        if (par != nullptr) par->setRight(r);
        r->setParent(par);
    }
    if (node != NULL && r != nullptr) node->setRight(rl);
    if (r != nullptr && r->getLeft() != NULL) r->getLeft()->setParent(node);
    if (r != nullptr)r->setLeft(node);
    if (node != nullptr)node->setParent(r);
    if (par == nullptr) this->setRoot(r);
    // change height accrodingly
    node->setHeight( 1 +  max( height(node->getLeft()) , height(node->getRight()) ) );
    r->setHeight(1 +  max( height(r->getLeft()) , height(r->getRight()) ) );
    return;
}

void AVLTree::rotateRight(AVLNode* node)
{
    AVLNode* par = node->getParent();
    AVLNode* l = node->getLeft();
    AVLNode* lr = l->getRight();
    bool isleft = 1;
    if (par != nullptr) isleft = (par->getLeft() == node);

    if (isleft)
    {
        if (par != nullptr) par->setLeft(l);
        l->setParent(par);
    }
    else
    {
        if (par != nullptr) par->setRight(l);
        l->setParent(par);
    }
    if (node != NULL && l != nullptr) node->setLeft(lr);
    if (l != nullptr && l->getRight() != NULL) l->getRight()->setParent(node);
    if (l != nullptr)l->setRight(node);
    if (node != nullptr)node->setParent(l);
    if (par == nullptr) this->setRoot(l);
    // change height accrodingly
    node->setHeight(1 +  max( height(node->getLeft()) , height(node->getRight()) ) );
    l->setHeight(1 +  max( height(l->getLeft()) , height(l->getRight()) ) );
    return;
}

void AVLTree::balance(AVLNode* node  , string stopName)
{
    //given node is not balanced;
    int balance = balanceFactor(node);
    if ( (node->getLeft() != NULL) && balance > 1 && stringCompare(node->getLeft()->getStopName() , stopName) > 0 ) //only right rotation(LL CASE)
    {
        rotateRight(node);
    }

    else if ((node->getRight() != NULL) && balance < -1 && stringCompare(stopName , node->getRight()->getStopName()) > 0 ) // only left rotation(RR CASE)
    {
        rotateLeft(node);
    }

    else if ((node->getLeft() != NULL) && balance > 1 && stringCompare(stopName , node->getLeft()->getStopName()) > 0) //LR CASE
    {
        rotateLeft(node->getLeft());
        rotateRight(node);
    }

    else if ((node->getRight() != NULL) && balance < -1 && stringCompare(node->getRight()->getStopName() , stopName) > 0) //RL CASE
    {
        rotateRight(node->getRight());
        rotateLeft(node);
    }

}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop)
{
    AVLNode* curr = this->root;
    AVLNode* par = NULL;
    //normal bst traversal
    while (curr != nullptr)
    {
        if (stringCompare(curr->getStopName() , node->getStopName()) > 0)
        {
            par = curr;
            curr = curr->getLeft();
        }
        else if (stringCompare(node->getStopName() , curr->getStopName()) > 0)
        {
            par = curr;
            curr = curr->getRight();
        }
        else // Equal keys are junctions !!
        {
            //just adding its CrossLine MetroObjs
            curr->addMetroStop(metroStop);
            delete node;
            return; // bcz no insertion needed
        }
    }
    //now no given station is not junction as per now so add all its line obj to its list
    node->addMetroStop(metroStop);
    // now you have par where you have to add new created node
    if (par == nullptr)
    {
        this->setRoot(node);
        return; // does not need to balance
    }
    else if (stringCompare(par->getStopName() , node->getStopName()) > 0)
    {
        par->setLeft(node);
        node->setParent(par);
    }
    else
    {
        par->setRight(node);
        node->setParent(par);
    }

    //travse bottom to up to change height of all nodes and check tree is balanced or not
    AVLNode* prevpar = NULL;
    while (par != nullptr)
    {
        par->setHeight(1 +  max( height(par->getLeft()) , height(par->getRight()) ) );
        prevpar = par;
        par = par->getParent();
        //now cheking for balancing
        if ( abs(balanceFactor(prevpar)) >= 2)
        {
            balance(prevpar , metroStop->getStopName()); // perform rotation and balance this
        }
    }

}

void AVLTree::populateTree(MetroLine* metroLine)
{
    MetroStop* curr = metroLine->getNode();

    while (curr != nullptr)
    {
        AVLNode *avlnode = new AVLNode(curr->getStopName());
        //now inserting this node to AVLtree
        this->insert(avlnode  , curr);
        curr = curr->getNextStop();
    }


}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName)
{

    AVLNode* curr = this->root;

    //normal bst traversal
    while (curr != nullptr)
    {
        if (stringCompare(curr->getStopName() , stopName) > 0)
        {
            curr = curr->getLeft();
        }
        else if (stringCompare(stopName , curr->getStopName()) > 0)
        {
            curr = curr->getRight();
        }
        else // Equal keys are junctions !!
        {
            return curr;
        }
    }

    return curr;

}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();

    if ( trip != nullptr) cout << "Dequeued: " << trip->getNode()->getStopName() << endl;

    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const
{
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    tree->setRoot(nullptr);
    for (auto line : lines)
    {
        tree->populateTree(line);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination)
{
    Exploration *exp = new Exploration();
    AVLNode* start = tree->searchStop(origin);
    if (start == nullptr)return NULL;

    AVLNode* end = tree->searchStop(destination);
    if (end == nullptr)return NULL;

    unordered_map<MetroLine* , bool> visited;


    vector<MetroStop*> ms = start->getStops();
    for (auto i : ms)
    {
        //there are two trips , forw and backw
        Trip *cforw = new Trip(i , nullptr);
        Trip *cback = new Trip(i , nullptr);
        exp->enqueue(cforw);
        exp->enqueue(cback);
    }
    vector<Path*> paths;
    MetroLine* nvis = NULL;
    while (!(exp->isEmpty()))
    {
        Trip* forw = exp->dequeue();
        Trip* back = exp->dequeue();
        MetroLine* line = NULL;
        if (forw != NULL)line = forw->getNode()->getLine();
        if (back != NULL)line = back->getNode()->getLine();
     
        while (forw != NULL && forw->getNode() != nullptr)
        {
            if (forw->getPrev() != NULL && forw->getNode()->getStopName() == origin )break;
            if (forw->getNode()->getStopName() == destination)
            {
                Path *cpath = new Path();
                if (nvis != NULL) nvis = forw->getNode()->getLine();
                Trip *curr = forw;
                Trip *par = curr;
                MetroLine *pline = curr->getNode()->getLine();
                int refFare = curr->getNode()->getFare();
                int fare = 0;
                while (curr != NULL)
                {
                    MetroStop* cms = curr->getNode();
                    cpath->addStop(cms);
                    int cfare = cms->getFare();
                    MetroLine *cline = cms->getLine();
                    if (cline != pline)
                    {
                        if (par->getNode()->getPrevStop() != nullptr && par->getNode()->getPrevStop()->getStopName() == cms->getStopName())
                        {
                            fare += abs(par->getNode()->getPrevStop()->getFare()  - refFare);
                            refFare = cms->getFare();

                        }
                        else
                        {
                            fare += abs(par->getNode()->getNextStop()->getFare()  - refFare);
                            refFare = cms->getFare();
                        }

                        pline = cline;
                    }
                    else
                    {
                        fare += abs(cfare - refFare) ;

                    }
                    refFare = cfare;

                    par = curr;
                    curr = curr->getPrev();
                }

                cpath->setTotalFare(fare);

                paths.push_back(cpath);
                break;
            }
            AVLNode* nnode = tree->searchStop(forw->getNode()->getStopName());
            vector<MetroStop*> msps = nnode->getStops();
            MetroLine* cl =  forw->getNode()->getLine();
            //if jun then it will embeeded all the stops
            for (auto i : msps)
            {
                //there are two trips , forw and backw
                if (visited[i->getLine()] == 0 && cl != i->getLine())
                {
                    Trip *cforw = NULL;
                    Trip *cback = NULL;
                    if (i->getNextStop() != nullptr) cforw = new Trip( i->getNextStop() , forw);
                    if (i->getPrevStop() != nullptr) cback = new Trip( i->getPrevStop() , forw);
                    exp->enqueue(cforw);
                    exp->enqueue(cback);
                }
            }

            MetroStop* next = forw->getNode()->getNextStop();
            Trip* ncurr = new Trip(next , forw);


            forw = ncurr;
        }

        while (back != NULL && back->getNode() != nullptr)
        {
            if (back->getPrev() != NULL && back->getNode()->getStopName() == origin)break;
            if (back->getNode()->getStopName() == destination)
            {
                if (nvis != NULL) nvis = back->getNode()->getLine();
                Path *cpath = new Path();
                Trip *curr = back;
                Trip *ppar = curr;
                MetroLine *pline = curr->getNode()->getLine();
                int refFare = curr->getNode()->getFare();
                int totFare = 0;
                while (curr != NULL)
                {
                    MetroStop* cms = curr->getNode();
                    cpath->addStop(cms);
                    int cfare = cms->getFare();
                    MetroLine *cline = cms->getLine();
                    if (cline != pline)
                    {
                        if (ppar->getNode()->getPrevStop() != nullptr && ppar->getNode()->getPrevStop()->getStopName() == cms->getStopName())
                        {
                            totFare += abs(ppar->getNode()->getPrevStop()->getFare()  - refFare);
                            refFare = cms->getFare();

                        }
                        else
                        {
                            totFare += abs(ppar->getNode()->getNextStop()->getFare()  - refFare);
                            refFare = cms->getFare();
                        }

                        pline = cline;
                    }
                    else
                    {
                        totFare += abs(cfare - refFare) ;

                    }
                    refFare = cfare;

                    ppar = curr;
                    curr = curr->getPrev();
                }

                cpath->setTotalFare(totFare);

                paths.push_back(cpath);
                break;
            }
            AVLNode* pnode = tree->searchStop(back->getNode()->getStopName());
            vector<MetroStop*> msps = pnode->getStops();
            MetroLine* cl =  back->getNode()->getLine();
            //if jun then it will embeeded all the stops
            for (auto i : msps)
            {
                //there are two trips , forw and backw
                if (visited[i->getLine()] == 0 && cl != i->getLine())
                {
                    Trip *cforw = nullptr;
                    Trip *cback = nullptr;
                    if (i->getNextStop() != nullptr) cforw = new Trip( i->getNextStop() , back);
                    if (i->getPrevStop() != nullptr) cback = new Trip( i->getPrevStop() , back);

                    exp->enqueue(cforw);
                    exp->enqueue(cback);
                }
            }

            MetroStop* prev = back->getNode()->getPrevStop();
            Trip* pcurr = new Trip(prev , back);

            back = pcurr;
        }

        if (nvis == NULL || line != nvis) visited[line] = 1;

    }


    //return shortest path
    if (paths.size() == 0) return NULL;
    Path *spath = paths[0];
    int min = paths[0]->getStops().size();
    for (int i = 1 ; i < paths.size() ; i++)
    {
        if (paths[i]->getStops().size() < min)
        {
            spath = paths[i];
            min = paths[i]->getStops().size();
        }
    }
    return spath;
}
vector<MetroLine*> lines;

