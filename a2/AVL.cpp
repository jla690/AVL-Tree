#include "AVL.h"

//PRE: enough memory
//POST: new AVL
AVL::AVL() {
    root = nullptr;
}

//PRE: memory allocated to AVL
//POST: deallocate memory of AVL
AVL::~AVL() {
    delete root -> left;
    delete root -> right;
}

//PRE: valid AVL
//POST: return root of AVL
Node* AVL::getRoot() {
  return root;
}

//PRE: valid Node* N
//POST: returns copy of N with allocated memory
Node* AVL::copyhelper(const Node* N) {
    if (N == nullptr) {
      return nullptr;
    }
    Node* t = new Node;
    t->data = N->data;
    t->height = N->height;
    t->left = copyhelper(N->left);
    t->right = copyhelper(N->right);
    return t;
}

//PRE: valid Node* N
//POST: N is now cloned into root
AVL::AVL(const AVL &N) {
    root = copyhelper(N.root);
}

//PRE: valid N and N is not current AVL
//POST: deleted root and N copied to root
AVL & AVL::operator = (const AVL & N) {
    if (this != &N) {
      delete root->left;
      delete root->right;
      Node* temp = copyhelper(N.root);
      root = temp;
      return *this;
    }
}

//PRE: valid Node* N and data is in N
//POST: deleted node with data, and balanced tree if needed
Node * AVL::remove(int data, Node* N) {
    if (N == nullptr) {
      return nullptr;
    }
    //searching for data
    if (data < N->data) {
      N->left = remove(data,N->left);
    }
    else if (data > N->data) {
      N->right = remove(data,N->right);
    }
    else {
    if (N->left == nullptr || N->right == nullptr) { //1 or 0 children
      Node* t;
      if (N->left) {
        t = N->left;
      }
      else {
        t = N->right;
      }
      if (t == nullptr) { //0 children
        t = N;
        N = nullptr;
      }
      else {
        *N = *t;
      }
      delete t;
    }
    else { //2 children
      Node* t = findMin(N->right);
      N->data = t->data;
      N->right = remove(t->data,N->right);
    }
    }
    if (N == nullptr) { //1 node in tree
      return N;
    }
    N->height = 1+max(height(N->left),height(N->right)); //fixing height
    int bal = getBalance(N);
    if (bal > 1) { 
      if (getBalance(N->left) >= 0) { //LL
        return singleRightRotate(N);
      }
      else if (getBalance(N->left) < 0) { //LR
        N->left = doubleLeftRightRotate(N->left);
        return singleRightRotate(N);
      }
    }
    else if (bal < -1){ //RR
      if (getBalance(N->right) <= 0) {
        return singleLeftRotate(N);
      }
      else if (getBalance(N->right) > 0) { //RL
        N->right = doubleRightLeftRotate(N->right);
        return singleLeftRotate(N);
      }
    }
    return N;
  }

//PRE: valid N
//POST: return height of left subtree minus right
int AVL::getBalance(Node* N) {
    if (N == nullptr) {
      return 0;
    }
    int bal;
    int leftheight = height(N->left);
    int rightheight = height(N->right);
    bal = leftheight-rightheight;
    return bal;
  }

//PRE: valid N
//POST: if N is internal
bool AVL::isInternal(Node* N) {
    return (N->left || N->right);
  }
//PRE: valid N
//POST: if N is external
bool AVL::isExternal(Node* N) {
    return (N->left == nullptr && N->right == nullptr);
  }

//PRE: valid N
//POST: if data is found
bool AVL::search(Node* N, int data) {
    if (N == nullptr) {
      return false;
    }
    if (N->data == data) {
      return true;
    }
    if (data > N->data) {
      return search(N->right,data);
    }
    else {
      return search(N->left,data);
    }
  }

//PRE: valid N
//POST: height of N
int AVL::height(Node* N) {
  if (N == nullptr) {
    return 0;
  }
    return N->height;
  }

//PRE: valid N
//POST: print postorder of tree
void AVL::postOrder(Node* N) {
    if (N) {
    postOrder(N->left);
    postOrder(N->right);
    cout<<N->data<<" ";
    }
  }

//PRE: valid N
//POST: print inorder of tree
void AVL::inOrder(Node* N) {
    if (N) {
    inOrder(N->left);
    // cout<<N->data<<" ";
    inOrder(N->right);
    }
  }

//PRE: valid N
//POST: print preorder of tree
void AVL::preOrder(Node* N) {
    if (N) {
    cout<<N->data<<" ";
    preOrder(N->left);
    preOrder(N->right);
    }
  }

//PRE: valid N
//POST: return size of N
int AVL::size(Node* N) {
  if (N == nullptr) {
    return 0;
  }
    return 1+ size(N->left) + size(N->right);
  }

//PRE: valid N
//POST: check if tree is full
bool AVL::isFull(Node* N) {
    if (N == nullptr) {
      return true;
    }
    if (N->left == nullptr && N->left == nullptr) { //single node
      return true;
    }
    if (N->left && N->right) { //check if every node has 2 or 0 leaves
      return (isFull(N->left) && isFull(N->right));
    }
    else {
      return false;
    }
  }

//PRE: valid N
//POST: check if tree is AVL
bool AVL::isAVL(Node* N) {
    if (N == nullptr) {
      return true;
    }
    if (getBalance(N) >= -1 && getBalance(N) <= 1 && isAVL(N->left) && isAVL(N->left)) { //balance of all nodes -1,0,1
      return true;
    }
    return false;
  }

//PRE: valid N
//POST: insert data into tree and balance if needed
Node* AVL::insert(int data, Node* N) {
    if (N == nullptr) { //empty tree
      Node* t = new Node();
      t->data = data;
      t->height = 1;
      t->left = nullptr;
      t->right = nullptr;
      return t;
    }
    //searching
    if (data > N->data) {
      N->right = insert(data,N->right);
    }
    else if (data < N->data) {
      
      N->left = insert(data,N->left);
    }
    else { //duplicate
      return N;
    }
    N->height = 1+max(height(N->left),height(N->right));
    int bal = getBalance(N);
    
    if (bal > 1) { 
      if (data < N->left->data) {
        return singleRightRotate(N); //ll
      }
      if (data > N->left->data) { //lr
      
        return doubleLeftRightRotate(N);
      }
    }
    if (bal < -1) {
      if (data > N->right->data) { //rr
        return singleLeftRotate(N);
      }
      if (data < N->right->data) { //rl
        return doubleRightLeftRotate(N);
      }
    }
    return N;
  }

//PRE: valid N
//POST: balance RR case
Node * AVL::singleRightRotate(Node* &N) {
    Node* t = N->left;
    Node* t2 = t->right;
    t->right = N;
    N->left = t2;
    N->height = max(height(N->right),height(N->left))+1;
    t->height = max(height(t->right),height(t->left))+1;
    return t;
  }
  
//PRE: valid N
//POST: balance LL case
Node * AVL::singleLeftRotate(Node* &N) {
    Node* t = N->right;
    Node* t2 = t->left;
    t->left = N;
    N->right = t2;
    N->height = max(height(N->left),height(N->right))+1;
    t->height = max(height(t->left),height(t->right))+1;
    return t;
  }

//PRE: valid N
//POST: balance LR case
Node * AVL::doubleLeftRightRotate(Node* &N) {
    N->left = singleLeftRotate(N->left);
    return singleRightRotate(N);
  }

//PRE: valid N
//POST: balance RL case
  Node * AVL::doubleRightLeftRotate(Node* &N) {
    N->right = singleRightRotate(N->right);
    return singleLeftRotate(N);
  }
//PRE: valid N
//POST: find smallest data node in subtrees
  Node * AVL::findMin(Node* N) {
    if (N == nullptr) {
      return nullptr;
    }
    Node* t = N;
    while (t->left) {
      t = t->left;
    }
    return t;
  }

//PRE: valid N
//POST: find largest data node in subtrees
  Node * AVL::findMax(Node* N) {
    if (N == nullptr) {
      return nullptr;
    }
    Node* t = N;
    while (t->right) {
      t = t->right;
    }
    return t;
  }
//PRE: valid N
//POST: find parent of N
  Node * AVL::parent(Node* N) {
    return parenthelper(root,N);
  }

//PRE: valid root and child node
//POST: returns parent node
  Node* AVL::parenthelper(Node* avlroot, Node* avlchild) {
    if (avlroot == nullptr || isRoot(avlchild)) {
      return nullptr;
    }
    else {
      if (avlroot->left->data == avlchild->data || avlroot->right->data == avlchild->data) {
        return avlroot;
      }
      else {
        if (avlchild->data < avlroot->left->data) {
          return parenthelper(avlroot->right, avlchild);
        }
        else {
          return parenthelper(avlroot->left, avlchild);
        }
      }
    }
    return nullptr;
  }
//PRE: valid N
//POST: check if tree is complete
  bool AVL::isComplete(Node* N, int depth, int count) {
    if (N == nullptr) {
      return true;
    }
    if (depth >= count) {
      return false;
    }
    return (isComplete(N->left,2*depth+1,count) && isComplete(N->right,2*depth+2,count));
  }

//PRE: valid 2 integers
//POST: returns largest of 2 integers
  int max(int a, int b) {
    return a > b ? a : b;
  }

//PRE: valid N
//POST: count children
  int AVL::childCount(Node* N) {
    int c = 0;
    if (N->right) {
      c++;
    }
    if (N->left) {
      c++;
    }
    return c;
  }

//PRE: valid N
//POST: check if root is N
  bool AVL::isRoot(Node* N) {
    return (height(N) == height(root));
  }

//public version of size
  int AVL::size() {
    return size(root);
  }

//public version of inorder
  void AVL::inOrder() {
    inOrder(root);
  }

//public version of postorder
  void AVL::postOrder() {
    postOrder(root);
  }
  //public version of preorder
  void AVL::preOrder() {
    preOrder(root);
  }
  //public version of isfull
  bool AVL::isFull() {
    return isFull(root);
  }
  //public version of iscomplete
  bool AVL::isComplete() {
    return isComplete(root,0,size());
  }
  //public version of isAVL
  bool AVL::isAVL() {
    return isAVL(root);
  }
  //public version of insertion
  void AVL::insert(int n) {
    if (search(root,n)) {
      return;
    }
    root = insert(n,root);
  }
  //public version of removal
  void AVL::remove(int n) {
    if (!search(root,n)) {
      return;
    }
    root = remove(n,root);
  }