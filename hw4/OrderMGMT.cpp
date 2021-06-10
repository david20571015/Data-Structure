#include "OrderMGMT.h"

#pragma GCC optimize("O3")
#pragma G++ optimize("O3")

void OrderMGMT::inOrder(Node* root) const {
  if (root != NIL) {
    this->inOrder(root->left);
    printf("(%d-%d-%s %d %d) ", root->date, root->id, (root->color ? "b" : "r"),
           root->leftSize, root->rightSize);
    this->inOrder(root->right);
  }
}

void OrderMGMT::preOrder(Node* root) const {
  if (root != NIL) {
    printf("(%d-%d-%s %d %d) ", root->date, root->id, (root->color ? "b" : "r"),
           root->leftSize, root->rightSize);
    this->preOrder(root->left);
    this->preOrder(root->right);
  }
}

void OrderMGMT::postOrder(Node* root) const {
  if (root != NIL) {
    this->postOrder(root->left);
    this->postOrder(root->right);
    printf("(%d-%d-%s %d %d) ", root->date, root->id, (root->color ? "b" : "r"),
           root->leftSize, root->rightSize);
  }
}

void OrderMGMT::leftRotate(Node* x) {
  Node* y = x->right;

  x->rightSize = y->leftSize;
  y->leftSize = 1 + x->leftSize + x->rightSize;

  x->right = y->left;

  if (y->left != NIL) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == NIL) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

void OrderMGMT::rightRotate(Node* y) {
  Node* x = y->left;

  y->leftSize = x->rightSize;
  x->rightSize = 1 + y->leftSize + y->rightSize;

  y->left = x->right;

  if (x->right != NIL) {
    x->right->parent = y;
  }
  x->parent = y->parent;

  if (y->parent == NIL) {
    this->root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  x->right = y;
  y->parent = x;
}

Node* OrderMGMT::search(const unsigned& date) const {
  Node* current = this->root;
  Node* pre = NIL;
  while (current != NIL) {
    if (date == current->date) {
      return current;
    } else if (date < current->date) {
      current = current->left;
    } else {
      pre = current;
      current = current->right;
    }
  }
  return pre;
}

Node* OrderMGMT::maximum() const {
  if (this->root == NIL) return NIL;
  Node* current = this->root;
  while (current->right != NIL) {
    current = current->right;
  }
  return current;
}

Node* OrderMGMT::minimum() const {
  if (this->root == NIL) return NIL;

  Node* current = this->root;
  while (current->left != NIL) {
    current = current->left;
  }
  return current;
}

Node* OrderMGMT::predecessor(Node* current) const {
  if (current == minNode || current == NIL) return NIL;

  if (current->left != NIL) {
    current = current->left;
    while (current->right != NIL) {
      current = current->right;
    }
    return current;
  }

  Node* new_node = current->parent;
  while (new_node != NIL && current == new_node->left) {
    current = new_node;
    new_node = new_node->parent;
  }
  return new_node;
}

Node* OrderMGMT::successor(Node* current) const {
  if (current == maxNode || current == NIL) return NIL;

  if (current->right != NIL) {
    current = current->right;
    while (current->left != NIL) {
      current = current->left;
    }
    return current;
  }

  Node* new_node = current->parent;
  while (new_node != NIL && current == new_node->right) {
    current = new_node;
    new_node = new_node->parent;
  }
  return new_node;
}

void OrderMGMT::insert(const unsigned& date, const unsigned& id) {
  ++(this->size);
  Node* y = this->NIL;
  Node* x = this->root;

  while (x != NIL) {
    y = x;
    if (date < x->date) {
      ++(x->leftSize);
      x = x->left;
    } else {
      ++(x->rightSize);
      x = x->right;
    }
  }

  Node* insert_node = new Node(date, id, RED, NIL, NIL);
  insert_node->parent = y;

  if (y == NIL) {
    this->root = insert_node;
  } else if (date < y->date) {
    y->left = insert_node;
  } else {
    y->right = insert_node;
  }

  insertFixUp(insert_node);
}

void OrderMGMT::insertFixUp(Node* current) {
  while (current->parent->color == RED) {
    if (current->parent == current->parent->parent->left) {
      Node* uncle = current->parent->parent->right;
      if (uncle->color == RED) {
        current->parent->color = BLACK;
        uncle->color = BLACK;
        uncle->parent->color = RED;
        current = current->parent->parent;
      } else {
        if (current == current->parent->right) {
          current = current->parent;
          leftRotate(current);
        }
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        rightRotate(current->parent->parent);
      }
    } else {
      Node* uncle = current->parent->parent->left;

      if (uncle->color == RED) {
        current->parent->color = BLACK;
        uncle->color = BLACK;
        uncle->parent->color = RED;
        current = current->parent->parent;
      } else {
        if (current == current->parent->left) {
          current = current->parent;
          rightRotate(current);
        }
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        leftRotate(current->parent->parent);
      }
    }
  }
  this->root->color = BLACK;
}

Node* OrderMGMT::remove(const unsigned& date) {
  --(this->size);
  Node* delete_node = this->root;

  while (delete_node != NIL) {
    if (date == delete_node->date) {
      break;
    } else if (date < delete_node->date) {
      --(delete_node->leftSize);
      delete_node = delete_node->left;
    } else {
      --(delete_node->rightSize);
      delete_node = delete_node->right;
    }
  }

  Node *x = NULL, *y = delete_node;

  if (delete_node->left != NIL && delete_node->right != NIL) {
    --(y->rightSize);
    y = y->right;
    while (y->left != NIL) {
      --(y->leftSize);
      y = y->left;
    }
  }

  Node* succ = successor(delete_node);

  if (y->left != NIL) {
    x = y->left;
  } else {
    x = y->right;
  }

  x->parent = y->parent;

  if (y->parent == NIL) {
    this->root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  if (y != delete_node) {
    delete_node->date = y->date;
    delete_node->id = y->id;
    succ = delete_node;
  }

  if (y->color == BLACK) removeFixUp(x);
  delete y;
  return succ;
}

void OrderMGMT::removeFixUp(Node* current) {
  while (current != root && current->color == BLACK) {
    if (current == current->parent->left) {
      Node* sibling = current->parent->right;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        current->parent->color = RED;
        leftRotate(current->parent);
        sibling = current->parent->right;
      }
      if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        current = current->parent;
      } else {
        if (sibling->right->color == BLACK) {
          sibling->left->color = BLACK;
          sibling->color = RED;
          rightRotate(sibling);
          sibling = current->parent->right;
        }
        sibling->color = current->parent->color;
        current->parent->color = BLACK;
        sibling->right->color = BLACK;
        leftRotate(current->parent);
        current = root;
      }
    } else {
      Node* sibling = current->parent->left;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        current->parent->color = RED;
        rightRotate(current->parent);
        sibling = current->parent->left;
      }
      if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        current = current->parent;
      } else {
        if (sibling->left->color == BLACK) {
          sibling->right->color = BLACK;
          sibling->color = RED;
          leftRotate(sibling);
          sibling = current->parent->left;
        }
        sibling->color = current->parent->color;
        current->parent->color = BLACK;
        sibling->left->color = BLACK;
        rightRotate(current->parent);
        current = root;
      }
    }
  }
  current->color = BLACK;
  this->root->color = BLACK;
}

// Function to insert a new order.
// date: Date of a order.
// id: Order ID.
void OrderMGMT::addOrder(unsigned date, unsigned id) {
  Node* target = search(date);
  if (target->date == date && target != NIL) return;
  insert(date, id);
  maxNode = maximum();
  minNode = minimum();
}

// Function to delete orders from a given range.
// start: Begin date.
// end: End date.
void OrderMGMT::deleteOrders(unsigned start, unsigned end) {
  if (start > end || this->root == NIL) return;

  start = start < minNode->date ? minNode->date : start;
  end = end > maxNode->date ? maxNode->date : end;

  Node *curr = search(start), *nextNode;
  if (curr != NIL && curr->date != start) curr = successor(curr);

  while (curr != NIL && curr->date <= end) {
    curr = remove(curr->date);
  }

  maxNode = maximum();
  minNode = minimum();
}

// Function to return a STL list of order IDs from a given range of dates.
// start: Begin date.
// end: End date.
list<unsigned> OrderMGMT::searchByDate(unsigned start, unsigned end) {
  list<unsigned> result;
  if (start > end || this->root == NIL) return result;

  start = start < minNode->date ? minNode->date : start;
  end = end > maxNode->date ? maxNode->date : end;

  Node* curr = search(start);
  if (curr != NIL && curr->date != start) curr = successor(curr);

  while (curr != NIL && curr->date <= end) {
    result.push_back(curr->id);
    curr = successor(curr);
  }
  return result;
}

// Function to return a STL list of order IDs starting from the a_th rank of
// date to the b_th rank of date. a_th: Begin rank. b_th: End rank.
list<unsigned> OrderMGMT::searchByDateRank(unsigned a_th, unsigned b_th) {
  list<unsigned> result;
  if (a_th == 0 && b_th == 0) return result;
  a_th = (a_th == 0) ? 1 : a_th;
  b_th = b_th > this->size ? this->size : b_th;
  if (a_th > b_th || a_th > this->size) return result;

  Node* curr = this->root;
  unsigned currRank = curr->leftSize + 1;

  while (currRank != a_th) {
    if (currRank < a_th) {
      curr = curr->right;
      currRank += curr->leftSize + 1;
    }
    if (currRank > a_th) {
      curr = curr->left;
      currRank -= curr->rightSize + 1;
    }
  }

  for (unsigned i = a_th; i <= b_th && curr != NIL; i++) {
    result.push_back(curr->id);
    curr = successor(curr);
  }
  return result;
}