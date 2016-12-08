#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

#define RED true
#define BLACK false

struct Node {
    int key;
    bool color;
    Node *parent, *left, *right;
    static Node * const nil;
    Node(int key, bool color=BLACK, Node *parent=nil, Node *left=nil, Node *right=nil) :
        key(key), color(color), parent(parent), left(left), right(right) {}
};

Node nil_o(INT_MIN, BLACK, &nil_o, &nil_o, &nil_o);
Node * const Node::nil = &nil_o;
Node * const nil = &nil_o;

void PrintNodeDetail(Node *x) {
    char *color;
    if (x->color == RED) color = (char *) "RED";
    else color = (char *) "BLACK";
    cout << "Node: key=" << x->key
        << " color=" << color
        << " parent=" << x->parent
        << " left=" << x->left
        << " right=" << x->right
        << endl;
}

void PrintNode(Node *x) { cout << "Node: key=" << x->key << endl; }

Node *Search(Node *x, int k) {
    while (x != nil && k != x->key) {
        if (k < x->key) x = x->left;
        else x = x->right;
    }
    return x;
}
Node *Minimum(Node *x) { while (x->left != nil) x = x->left; return x;}
Node *Maximum(Node *x) { while (x->right != nil) x = x->right; return x;}
//         b
//      x
//         a
Node *Successor(Node *x) {
    if (x->right != nil) return Minimum(x->right);
    while (x->parent != nil && x != x->parent->left) x = x->parent;
    return x->parent;
}
Node *Predecessor(Node *x) {
    if (x->left != nil) return Maximum(x->left);
    while (x->parent != nil && x != x->parent->right) x = x->parent;
    return x->parent;
}

// for test only
void SetL(Node *x, Node *left) { x->left = left; x->left->parent = x; }
void SetR(Node *x, Node *right) { x->right = right; x->right->parent = x; }

struct RBTree {
    Node *root;
    RBTree() : root(nil) {}
};

//   |                      |
//   x                      y
//          y    -->  x
//     y.l               y.l
void LeftRotate(RBTree *t, Node *x) {
    Node *y = x->right; // set y
    x->right = y->left; // y gives child to x
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent; // y goes up
    if (x->parent == nil) t->root = y;
    else if (x->parent->left == x) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; // y takes x as child
    x->parent = y;
}

//        |           |
//        x           y      
//   y          -->         x
//     y.r              y.r
void RightRotate(RBTree *t, Node *x) {
    Node *y = x->left; // set y
    x->left = y->right; // y gives child to x
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent; // y goes up
    if (x->parent == nil) t->root = y;
    else if (x->parent->right == x) x->parent->right = y;
    else x->parent->left = y;
    y->right = x; // y takes x as child
    x->parent = y;
}

// z is RED even though it is root
// loop while z and z's parent are RED
// if z or z's parent is root, break
// if z's parent is black, break

/*
Red condition: Red has 2 black child (No consecutive reds)
z: suspicious consecutive red at low level
y: z's unclue

(case 1)

             .                    .
             Cb              new zCr
           .   .                .   .
        Br      yDr           Bb     Db
      .                      .
   zAr                     Ar

(case 2)

         Cb                        Cb
       .    .                    .   .
     Ar      yDb               Br     yDb
       .                      .
        zBr             new zAr

(case 3)

          Cb                 Bb
        .   .              .   .
       Br    yDb        zAr     Cr
      .                          .
    zAr                           Db
*/

void InsertFixup(RBTree *t, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right; // uncle
            if (y->color == RED) {
                // case (1)
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED; // next z RED
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // case (2)
                    z = z->parent;
                    LeftRotate(t, z);
                }
                // case (3)
                z->parent->color = BLACK; // z parent BLACK will break loop
                z->parent->parent->color = RED;
                RightRotate(t, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left; // uncle
            if (y->color == RED) {
                // case (1)
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED; // next z RED
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // case (2)
                    z = z->parent;
                    RightRotate(t, z);
                }
                // case (3)
                z->parent->color = BLACK; // z parent BLACK will break loop
                z->parent->parent->color = RED;
                LeftRotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = BLACK; // First insert or case (1) might change root RED
}

void Insert(RBTree *t, Node *z) {
    Node *y = nil;
    Node *x = t->root;
    while (x != nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == nil) t->root = z; // Tree was empty
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = z->right = nil; // Just for sure
    z->color = RED; // Strategic
    InsertFixup(t, z);
}

// Move v as u’s position in tree
// q (parent of u, can be nil if u is root)
// u (!=nil)
// v (can be nil)
// @note u’s attributes not modified throughout this function
void Transplant(RBTree *t, Node *u, Node *v) {
    if (u->parent == nil) t->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

/*

!!! Always preserve BH to subtrees !!!

(case 1) make x's sibling BLACK (2 color change and left rotate)

          Bb!                   Db
       .    .                 .     .
    xAb      wDr!          Br       Eb
            .   .        .   .
          Cb     Eb    xAb   wCb

(case 2) 1-color change and go up

          B?                  xB?
        .   .               .     .
     xAb     wDb!         Ab      Dr
            .   .                .  .
          Cb     Eb            Cb    Eb

(case 3) transform to case 4 (right rotate)

          B?                     B?
       .    .                  .   .
    xAb      wDb!          xAb     wCb
          .     .                    .
          Cr!    Eb                   Dr
                                       .
                                         Eb

(case 4) Terminal case x to root (after inherit color, left rotate)

          B?!                          D?
       .      .                      .    .
    xAb        wDb!                Bb      Eb
             .     .             .   .
           C??      Er!       Ab      C??        x = root

*/

void DeleteFixup(RBTree *t, Node *x) {
    while (x != t->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                // case 1 -> case 2, 3, or 4
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // case 2 -> go up
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // case 3 -> case 4
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(t, w);
                    w = x->parent->right;
                }
                // case 4 (Terminal)
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(t, x->parent);
                x = t->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = BLACK;
}

void Delete(RBTree *t, Node *z) {
    Node *y = z;
    bool y_original_color = y->color;
    Node *x = nil;
    if (z->left == nil) {
        x = z->right;
        Transplant(t, z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        Transplant(t, z, z->left);
    } else {
        y = Minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y == z->right) {
            x->parent = y;
        } else {
            Transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK) {
        DeleteFixup(t, x);
    }
}

int main() {
    PrintNodeDetail(nil);
    //       3
    //   1       6
    // 0   2   5   7
    //        4 
    Node *n0 = new Node(0);
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3); // root
    Node *n4 = new Node(4);
    Node *n5 = new Node(5);
    Node *n6 = new Node(6);
    Node *n7 = new Node(7);
    SetL(n3, n1);
    SetR(n3, n6);
    SetL(n1, n0);
    SetR(n1, n2);
    SetL(n6, n5);
    SetR(n6, n7);
    SetL(n5, n4);
    PrintNode(Minimum(n3)); // 0
    PrintNode(Maximum(n3)); // 7
    PrintNode(Successor(n3)); // 4
    PrintNode(Successor(n2)); // 3
    // RedBlack Tree
    // all case covered when insert [4]
    //            B11
    //      R2           B14
    //  B1     B7           R15
    //       R5 yR8
    //    z[R4]
    // --- case (1)
    //            B11
    //      R2          yB14
    //  B1    zR7           R15
    //       B5  B8
    //     [R4]
    // --- case (2)
    //            B11
    //       R7         yB14
    //   zR2    B8          R15
    //  B1 B5
    //    [R4]
    // --- case (3)
    //            B7
    //      zR2        R11
    //    B1   B5     B8 B14
    //        [R4]         R15
    //
    RBTree *t = new RBTree();
    Node *i11 = new Node(11, BLACK);
    Node *i2 = new Node(2, RED);
    Node *i14 = new Node(14, BLACK);
    Node *i1 = new Node(1, BLACK);
    Node *i7 = new Node(7, BLACK);
    Node *i15 = new Node(15, RED);
    Node *i5 = new Node(5, RED);
    Node *i8 = new Node(8, RED);
    Node *i4 = new Node(4);
    t->root = i11;
    SetL(i11, i2);
    SetR(i11, i14);
    SetL(i2, i1);
    SetR(i2, i7);
    SetR(i14, i15);
    SetL(i7, i5);
    SetR(i7, i8);  // ... insert test setup.
    Insert(t, i4); // insert test
    PrintNode(i7->left); // 2
    PrintNode(i7->right); // 11
    PrintNode(i2->left); // 1
    PrintNode(i2->right); // 5
    PrintNode(i11->left); // 8
    PrintNode(i11->right); // 14
    PrintNode(i5->left); // 4
    PrintNode(i5->right); // INT_MIN
    PrintNode(i14->right); // 15 ... check insert test
    // DeleteFixup
    //
    //    case 1           case 2 
    //
    //     2b                4b            4b
    //    .   .            .    .        .    .
    // x1b   w4r          2r    5b     x2r     5b
    //       .  .        .  .         .   .
    //      3b  5b    x1b   w3b      1b   3r
    //                    nil nil       nil nil
    RBTree *td = new RBTree();
    Node *d2 = new Node(2, BLACK);
    Node *d1 = new Node(1, BLACK);
    Node *d4 = new Node(4, RED);
    Node *d3 = new Node(3, BLACK);
    Node *d5 = new Node(5, BLACK);
    td->root = d2;
    SetL(d2, d1);
    SetR(d2, d4);
    SetL(d4, d3);
    SetR(d4, d5);
    DeleteFixup(td, d1);
    cout << endl;
    assert(td->root->key == 4);
    assert(d4->left->key == 2);
    assert(d4->right->key == 5);
    assert(d2->left->key == 1);
    assert(d2->right->key == 3);
    return 0;
}
