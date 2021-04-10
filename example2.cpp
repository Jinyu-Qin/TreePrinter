#include <iostream>
#include "treeprinter.h"

using namespace std;

struct RbTreeNode {
    int val;
    int color;
    RbTreeNode * left;
    RbTreeNode * right;

    RbTreeNode(int val = 0, int color = 1, RbTreeNode * left = nullptr, RbTreeNode * right = nullptr)
        : val(val)
        , color(color)
        , left(left)
        , right(right) {}
};

int main(int argc, char * argv[]) {
    // 0 - black, 1 - red
    vector<int> colors {0, 1, 0, 0, 0, 1, 1, 1, 1};
    vector<RbTreeNode *> nodes(colors.size());

    for(int i = 0; i < nodes.size(); ++i) {
        nodes[i] = new RbTreeNode(i + 1, colors[i]);
    }
    nodes[0]->left = nodes[1];
    nodes[0]->right = nodes[2];
    nodes[1]->left = nodes[3];
    nodes[1]->right = nodes[4];
    nodes[2]->left = nodes[5];
    nodes[2]->right = nodes[6];
    nodes[4]->left = nodes[7];
    nodes[4]->right = nodes[8];

    cout << "TreePrinter Version: " << tp::version << endl;
    
    tp::TreePrinter<RbTreeNode, tp::SimpleRbTreeNodeAdapter<RbTreeNode>> printer(nodes[0]);
    printer.print();

    return 0;
}