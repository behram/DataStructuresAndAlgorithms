#include<iostream>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int key;
    int value;
};

struct Node{
    Element elem;
    Node * parent;
    Node * left;
    Node * right;
};

void removeNode(Node * node);

Node * createNode(Element elem, Node * PARENT=NULL){
    Node *newNode = new Node;
    newNode->elem.key=elem.key;
    newNode->elem.value=elem.value;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->parent=PARENT;

    return newNode;
}

struct BST{
    Node *root;
};

void init(BST & tree){
    tree.root=NULL;
}

bool insertElem(Node *node, Element elem){

    if (elem.key < node->elem.key){
        if(node->left)
            return insertElem(node->left,elem);

        node->left = createNode(elem, node);
        return true;
    }
    else{
        if (elem.key > node->elem.key)
        {
            if(node->right)
                return insertElem(node->right,elem);

            node->right = createNode(elem, node);
            return true;
        }
    }

    return false;
}

bool insertElem(BST & tree, Element elem){

    if (tree.root)
        return insertElem(tree.root, elem);

    tree.root = createNode(elem);
    return true;

}

void showInorder2(Node * NODE){
    if (NODE != NULL){
        showInorder2(NODE->left);
        cout << NODE->elem.key << "(" << NODE->elem.value << "),";
        showInorder2(NODE->right);
    }
}

void showInorder(BST & tree){
    showInorder2(tree.root);
    cout << endl;

}

void showPreorder2(Node * NODE){
    if (NODE != NULL){
        cout << NODE->elem.key << "(" << NODE->elem.value << "),";
        showPreorder2(NODE->left);
        showPreorder2(NODE->right);
    }
}

void showPreorder(BST & tree){
    showPreorder2(tree.root);
    cout << endl;
}

void showPostorder2(Node * NODE){
    if (NODE != NULL){
        showPostorder2(NODE->left);
        showPostorder2(NODE->right);
        cout << NODE->elem.key << "(" << NODE->elem.value << "),";
    }
}

void showPostorder(BST & tree){
    showPostorder2(tree.root);
    cout << endl;
}

void showNode (Node * NODE){
    cout << NODE->elem.key << "(" << NODE->elem.value << ")" << endl;
}

Node * treeSearch(Node * NODE, int key){
    if (NODE == NULL)
        return NODE;
    if (NODE->elem.key == key)
        return NODE;
    if (key < NODE->elem.key)
        return treeSearch(NODE->left, key);
    return treeSearch(NODE->right, key);
}

bool findKey(BST & tree,int key, Element &elem){

    Node *x = treeSearch(tree.root, key);
    if (x == NULL)
        return false;
    elem.key = x->elem.key;
    elem.value = x->elem.value;
    return true;

}

Node * treeMAX (Node * NODE){
    while (NODE->right != NULL)
        NODE = NODE->right;
    return NODE;
}

Node * treeMIN (Node * NODE){
    while (NODE->left != NULL)
        NODE = NODE->left;
    return NODE;
}



Node * treeSUCC (Node * NODE){
    if (NODE->right != NULL)
        return treeMIN(NODE->right);
    int key = NODE->elem.key;
    do{
        NODE = NODE->parent;
    }
    while (NODE->elem.key <key);

    return NODE;
}

bool removeKey(BST & tree, int key, Element &elem){

    Node * x = treeSearch(tree.root, key);

    if (x == NULL)
        return false;

    if(!x->left && !x->right){
        if(!x->parent){
            elem.key=x->elem.key;
            elem.value=x->elem.value;
            delete x;
            init(tree);
            return true;
        }

        if (x->parent->right == x)
            x->parent->right = NULL;
        else
            x->parent->left = NULL;

        elem.key=x->elem.key;
        elem.value=x->elem.value;
        delete x;
        return true;
    }

    if(x->left && x->right){

        elem.key=x->elem.key;
        elem.value=x->elem.value;

        Element sucessorEl;
        Node *sucessor = treeSUCC(x);

        removeKey(tree,sucessor->elem.key,sucessorEl);

        x->elem = sucessorEl;                    //Swap
        return true;
    }

    if(x->left || x->right)
    {
        if(!x->parent)
        {
            tree.root = (x->left ? x->left : x->right);
            tree.root->parent = NULL;
        }
        else
        if(x->parent->left == x)
        {
            x->parent->left = (x->left ? x->left : x->right);
            x->parent->left->parent = x->parent;
        }
        else
        {
            x->parent->right = (x->left ? x->left : x->right);
            x->parent->right->parent = x->parent;
        }

        elem.key=x->elem.key;
        elem.value=x->elem.value;
        delete x;
        return true;
    }

    return false;

}

void removeNode(Node * node){
    if(!node) return;

    removeNode(node->left);
    removeNode(node->right);
    delete node;
}

void clear(BST & tree){

    removeNode(tree.root);
    init(tree);

}

int numberOfNodes(Node* node){
    if(!node)
        return 0;

    int count = 0;

    count+=numberOfNodes(node->left);
    count++;
    count+=numberOfNodes(node->right);
    return count;
}

int numberOfNodes(BST & tree){
    return numberOfNodes(tree.root);
}

int height(Node *node)
{
    if(!node)
        return 0;

    int nodeOfHeight = 0;
    nodeOfHeight++;

    int left = height(node->left);
    int right = height(node->right);

    (left > right) ? nodeOfHeight+=left : nodeOfHeight+=right;
    return nodeOfHeight;
}

int height(BST & tree){
    return height(tree.root);
}

int countLeaves(Node *node)
{
    if(!node)
        return 0;
    if(!node->left && !node->right)
        return 1;
    else
        return countLeaves(node->left) + countLeaves(node->right);
}

int countLeaves(BST & tree){
    return countLeaves(tree.root);
}

int functionA(BST & tree){
    return -1;
}

int functionB(BST & tree, int key){
    return -1;
}

bool functionC(BST & tree, int key, Element &elem){
    return false;
}


void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    BST *tree;
    int currentT=0;
    int value;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        // zero-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }

        if(isCommand(command,"SI"))
        {
            showInorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SP"))
        {
            showPreorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"SQ"))
        {
            showPostorder(tree[currentT]);
            continue;
        }

        if(isCommand(command,"CL"))
        {
            clear(tree[currentT]);
            continue;
        }

        if(isCommand(command,"IN"))
        {
            init(tree[currentT]);
            continue;
        }

        if(isCommand(command,"NN"))
        {
            cout << numberOfNodes(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"HE"))
        {
            cout << height(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"LE"))
        {
            cout << countLeaves(tree[currentT]) << endl;
            continue;
        }

        if(isCommand(command,"FA"))
        {
            cout << functionA(tree[currentT]) << endl;
            continue;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"IE"))
        {
            int variable2;
            stream >> variable2;
            Element elem;
            elem.key=value;
            elem.value=variable2;
            showBool(insertElem(tree[currentT],elem));
            continue;
        }

        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }
        if(isCommand(command,"RK"))
        {
            Element elem;
            bool ret=removeKey(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }


        if(isCommand(command,"CH"))
        {
            currentT=value;
            continue;
        }

        if(isCommand(command,"GO"))
        {
            tree=new BST[value];
            continue;
        }

        if(isCommand(command,"FB"))
        {
            cout << functionB(tree[currentT],value) << endl;
            continue;
        }

        if(isCommand(command,"FC"))
        {
            Element elem;
            bool ret=functionC(tree[currentT], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
