# 一个C++实现的二叉树可视化程序

本程序旨在不改变用户代码中定义的Tree结点结构的情况下，以较为直观的方式在终端输出二叉树结构图

## 文件结构

* `treeprinter.h`为核心文件
* `example1.cpp`为打印一棵简单二叉树的示例文件
* `example2.cpp`为打印一棵简单红黑树的示例文件
* `example3.cpp`为打印一棵用户自定义树结构的示例文件

## 使用方法

1. 包含`treeprinter.h`头文件

   ```c++
   #include "treeprinter.h"
   ```

2. 定义结点适配器（可选）

   默认提供了两种Tree结点的适配器，`SimpleTreeNodeAdapter`以及`SimpleRbTreeNodeAdapter`，分别针对简单Tree结点和简单RBTree结点进行适配，如果它们不能满足用户需求，用户可以自行定义适配器

3. 创建`TreePrinter`对象

   ```c++
   tp::TreePrinter<TreeNode> printer(root); // root是树的根结点
   ```

   以上代码将使用TreePrinter中默认的`SimpleTreeNodeAdapter`对Tree结点进行适配，如果此适配器不满足用户需求，用户可以自行指定需要的适配器，方法如下：

   ```c++
   tp::TreePrinter<MyTreeNode, MyTreeNodeAdapter> printer(root); // root是树的根结点
   ```

4. 打印树结构

   ```c++
   printer.print();
   ```

## Tree结点适配器

### 提供了两种简单的Tree结点适配器

`treeprinter.h`文件中默认提供了两种Tree结点的适配器，`SimpleTreeNodeAdapter`以及`SimpleRbTreeNodeAdapter`，均在名称空间`tp`中

* `SimpleTreeNodeAdapter`针对如下Tree结点进行适配：

  ```c++
  struct TreeNode {
      int val;
      TreeNode * left;
      TreeNode * right;
  };
  ```

* `SimpleRbTreeNodeAdapter`针对如下Tree结点类型进行适配：

  ```c++
  struct RbTreeNode {
      int val;
      int color;          // 0代表黑色，1代表红色
      RbTreeNode * left;
      RbTreeNode * right;
  };
  ```

### 用户自定义Tree结点适配器

用户可自行定义Tree结点适配器，以满足特定的需求，具体定义和使用方式可参考`example3.cpp`文件

Tree结点适配器必须能够提供如下内容：

* 类型成员`origin_type`：需要适配的Tree结点类型

* 类型成员`node_type`：适配器类型

* 构造函数：有且仅有一个`origin_type`*参数

* 析构函数：可选

* 函数成员`content()`：返回Tree结点内容的字符串表示

  ```c++
  string content();
  ```

* 函数成员`left()`：返回左孩子结点的适配器指针

  ```c++
  node_type * left();
  ```

* 函数成员`right()`：返回右孩子结点的适配器指针

  ```c++
  node_type * right();
  ```

提供一个参考示例：

```c++
// 用户自定义的tree结点结构
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

// 用户自定义该tree结点结构的适配器
// 该适配器用于将任意的tree结点结构转换成TreePrinter能够处理的tree结点的结构
class MyTreeNodeAdapter {
public:
    using origin_type = MyTreeNode;      // 原始结点类型
    using node_type = MyTreeNodeAdapter; // 结点适配器类型

    // 适配器的构造函数，必须有且仅有一个指向原始结点的指针参数
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
    
    // 返回结点内容的字符串表示
    string content() {
        return root_->val;
    }

    // 返回左结点的适配器指针
    node_type * left() {
        return left_;
    }

    // 返回右结点的适配器指针
    node_type * right() {
        return right_;
    }

private:
    origin_type * root_;
    node_type * left_;
    node_type * right_;
};
```

使用该适配器的方法如下：

```c++
// 使用TreePrinter时，模板参数传入原始类型和适配器类型，构造函数的参数是tree的根结点
tp::TreePrinter<MyTreeNode, MyTreeNodeAdapter> printer(root);
// 打印树结构
printer.print();
```