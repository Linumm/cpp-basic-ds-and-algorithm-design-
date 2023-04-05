#include <iostream>

// Struct Node, the data type of this case: int
struct node {
    int data;
    node* left;
    node* right;
};

// Struct BST
struct bst {
    node* root = nullptr;
    
    public:
        node* find(int value) {
            return find_impl(root, value);
        }

        void insert(int value) {
            if (!root) // In case of no existing tree
                root = new node {value, NULL, NULL}; 
            else
                insert_impl(root ,value);
        }

        void inorder() { inorder_impl(root); }
        // Inorder traversal in BST : prints out by increasing order!

        node* successor(node* start) { //To find successor in deletion process
            auto current = start->right;
            while (current && current->left)
                current = current->left;
            return current;
        }

        void deleteValue(int value) { root = delete_impl(root, value); }

    private:
        node* find_impl(node* current, int value) { //Use Recursive
            if (!current) { //case of nullptr
                std::cout << std::endl;
                return NULL;
            }

            if (current->data == value) {
                std::cout << current->data << "founded" << std::endl;
                return current;
            }

            if (value < current->data) { // Left
                std::cout << "Moved to left from: " << current->data << " ";
                return find_impl(current->left, value); 
            }

            // Right
            std::cout << "Moved to right from: " << current->data << " ";
            return find_impl(current->right, value); 
        }
        // The process of searching element works recursively, make it private to prevent from outer call


        void insert_impl(node* current, int value) {
            if (value < current->data) { // Check whether to go down, left or right
                if (!current->left)
                    current->left = new node {value, NULL, NULL};
                else
                    insert_impl(current->left, value);
            }
            else {
                if (!current->right)
                    current->right = new node {value, NULL, NULL};
                else
                    insert_impl(current->right, value);
            }
        }


        void inorder_impl(node* start) { // To find smallest among Right subtree
            if (!start) return;

            inorder_impl(start->left);
            std::cout << start->data << " ";
            inorder_impl(start->right);
        }


        node* delete_impl(node* start, int value) { // Since we have to change parent's node ptr, return "needed pointed node" in here
            if (!start)
                return NULL;
            
            if (value < start->data)
                start->left = delete_impl(start->left, value);
            else if (value > start->data)
                start->right = delete_impl(start->right, value);
            else { // Now arrived to target
                if (!start->left) { // Case: No child node or only right child
                    auto tmp = start->right;
                    delete start;
                    return tmp;
                }

                if (!start->right) { // Case: only left child
                    auto tmp = start->left;
                    delete start;
                    return tmp;
                }

                // Case: both child
                auto succNode = successor(start);
                start->data = succNode->data;

                // Find successor in right subtree and delete
                start->right = delete_impl(start->right, succNode->data);
            }

            return start;
        }

};

int main()
{
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    std::cout << "Inorder traversal: ";
    tree.inorder();
    std::cout << std::endl;

    tree.deleteValue(12);
    std::cout << "After deletion 12: ";
    tree.inorder();
    std::cout << std::endl;

    if (tree.find(12))
        std::cout << "Element 12 is in tree" << std::endl;
    else
        std::cout << "12 is not in tree" << std::endl;

    return 1;
}