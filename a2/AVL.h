#include <iostream>

using namespace std;


struct Node {
  int data;
  Node * left;
  Node * right;
  int height;
};

class AVL {
  
  Node * remove(int data, Node * N);
  int getBalance(Node * N);
  bool isInternal(Node * N);
  bool isExternal(Node * N);
  bool search(Node * N, int data);
  int height(Node * N);
  void postOrder(Node * N);
  void inOrder(Node * N);
  void preOrder(Node * N);
  int size(Node * N);
  bool isFull(Node * N);
  bool isAVL(Node * N);
  Node * insert(int data, Node * N);
  Node * singleRightRotate(Node * & N);
  Node * singleLeftRotate(Node * & N);
  Node * doubleLeftRightRotate(Node * & N);
  Node * doubleRightLeftRotate(Node * & N);
  Node * findMin(Node *N);
  Node * findMax(Node *N);
  
  bool isComplete(Node * N, int depth, int count);
  int childCount(Node * N);
  bool isRoot(Node * N);
  Node* copyhelper(const Node* N);
  Node* parenthelper(Node* avlroot, Node* avlchild);

  public:
  Node * root;
  Node * parent(Node *N);
  Node * getRoot();
  AVL();
  ~AVL();
  AVL(const AVL &N);
  AVL & operator = (const AVL & N);
  int size();
  void inOrder();
  void postOrder();
  void preOrder();
  bool isFull();
  bool isComplete();
  bool isAVL();
  void insert(int n);
  void remove(int n);
};