#ifndef ORDERMGMT_H
#define ORDERMGMT_H

#include <list>

using namespace std;

enum Color { RED, BLACK };

// Data structure consisting of Order ID and date.
struct Node {
  unsigned date;
  unsigned id;
  unsigned leftSize, rightSize;
  Color color;
  Node *left, *right, *parent;

  Node(unsigned date, unsigned id, Color color, Node *left = NULL,
       Node *right = NULL)
      : id(id),
        date(date),
        color(color),
        left(left),
        right(right),
        leftSize(0),
        rightSize(0),
        parent(NULL) {}
};

// Order Management System consolidating key operational processes.
class OrderMGMT {
 private:
  Node *root;
  Node *NIL;

  Node *maxNode;
  Node *minNode;

  unsigned size;

  void inOrder(Node *root) const;
  void preOrder(Node *root) const;
  void postOrder(Node *root) const;

  inline void leftRotate(Node *root);
  inline void rightRotate(Node *root);

  inline Node *search(const unsigned &date) const;
  inline Node *maximum() const;
  inline Node *minimum() const;
  inline Node *predecessor(Node *current) const;
  inline Node *successor(Node *current) const;

  void insert(const unsigned &date, const unsigned &id);
  void insertFixUp(Node *current);
  Node *remove(const unsigned &date);
  void removeFixUp(Node *current);

 public:
  OrderMGMT() {
    this->NIL = new Node(-1, -1, BLACK);
    this->root = this->NIL;
    this->root->parent = this->NIL;
    this->size = 0;
  }

  void inOrder() {
    cout << "inOrder\n";
    this->inOrder(this->root);
    cout << "\n";
  }
  void preOrder() {
    cout << "preOrder\n";
    this->preOrder(this->root);
    cout << "\n";
  }
  void postOrder() {
    cout << "postOrder\n";
    this->postOrder(this->root);
    cout << "\n";
  }

  void addOrder(unsigned date, unsigned id);
  void deleteOrders(unsigned start, unsigned end);
  list<unsigned> searchByDate(unsigned start, unsigned end);
  list<unsigned> searchByDateRank(unsigned a_th, unsigned b_th);
};

#endif
