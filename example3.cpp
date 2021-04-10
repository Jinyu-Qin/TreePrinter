#include <vector>
#include "treeprinter.h"

using namespace std;

// 用户自定义的tree节点结构
struct MyTreeNode {
    int key;
    string val;
    MyTreeNode * left;
    MyTreeNode * right;

    MyTreeNode(int key = 0, string val = "", MyTreeNode * left = nullptr, MyTreeNode * right = nullptr)
        : key(key)
        , val(val)
        , left(left)
        , right(right) {}
};

// 用户自定义该tree节点结构的适配器
// 该适配器用于将任意的tree节点结构转换成TreePrinter能够处理的tree节点的结构
class MyTreeNodeAdapter {
public:
    using origin_type = MyTreeNode;      // 原始节点类型
    using node_type = MyTreeNodeAdapter; // 节点适配器类型

    // 适配器的构造函数，必须有且仅有一个指向原始节点的指针参数
    MyTreeNodeAdapter(origin_type * root)
        : root_(root)
        , left_(root->left == nullptr ? nullptr : new MyTreeNodeAdapter(root->left))
        , right_(root->right == nullptr ? nullptr : new MyTreeNodeAdapter(root->right)) {}
    
    // 析构函数
    ~MyTreeNodeAdapter() {
        if(left_ != nullptr) {
            delete left_;
            left_ = nullptr;
        }

        if(right_ != nullptr) {
            delete right_;
            right_ = nullptr;
        }
    }
    
    // 返回节点内容的字符串表示
    string content() {
        return root_->val;
    }

    // 返回左节点的适配器指针
    node_type * left() {
        return left_;
    }

    // 返回右节点的适配器指针
    node_type * right() {
        return right_;
    }

private:
    origin_type * root_;
    node_type * left_;
    node_type * right_;
};

int main(int argc, char * argv[]) {
    vector<string> names {"Bob", "Mark", "Bill", "James", "Henry", "Jack", "Gary", "Karl", "Lee", "Dean", "Ann", "John"};
    vector<MyTreeNode *> nodes(names.size());
    
    for(int i = nodes.size() - 1; i >= 0; --i) {
        MyTreeNode * node = new MyTreeNode(i + 1, names[i]);
        int leftId = i * 2 + 1;
        int rightId = leftId + 1;
        node->left = leftId < nodes.size() ? nodes[leftId] : nullptr;
        node->right = rightId < nodes.size() ? nodes[rightId] : nullptr;
        nodes[i] = node;
    }

    cout << "TreePrinter Version: " << tp::version << endl;

    // 使用TreePrinter时，模板参数传入原始类型和适配器类型，构造函数的参数是tree的根节点
    tp::TreePrinter<MyTreeNode, MyTreeNodeAdapter> printer(nodes[0]);
    // 打印树结构
    printer.print();

    for(int i = 0; i < nodes.size(); ++i) {
        delete nodes[i];
        nodes[i] = nullptr;
    }

    return 0;
}
