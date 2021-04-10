#include <vector>
#include "treeprinter.h"

using namespace std;

struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;

    TreeNode(int val = 0, TreeNode * left = nullptr, TreeNode * right = nullptr)
        : val(val)
        , left(left)
        , right(right) {}
};

int main(int argc, char * argv[]) {
    int n = 15;
    vector<TreeNode *> nodes(n);
    
    for(int i = n - 1; i >= 0; --i) {
        TreeNode * node = new TreeNode(i + 1);
        int leftId = i * 2 + 1;
        int rightId = leftId + 1;
        node->left = leftId < n ? nodes[leftId] : nullptr;
        node->right = rightId < n ? nodes[rightId] : nullptr;
        nodes[i] = node;
    }

    cout << "TreePrinter Version: " << tp::version << endl;

    tp::TreePrinter<TreeNode> printer(nodes[0]);
    printer.print();

    for(int i = 0; i < n; ++i) {
        delete nodes[i];
        nodes[i] = nullptr;
    }

    return 0;
}