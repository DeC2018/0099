#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstddef>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  void recoverTree(TreeNode* root) {
    inorder(root);
    swap(x, y);
  }

 private:
  TreeNode* pred = nullptr;
  TreeNode* x = nullptr;  // 1st wrong node
  TreeNode* y = nullptr;  // 2nd wrong node

  void inorder(TreeNode* root) {
    if (root == nullptr)
      return;

    inorder(root->left);

    if (pred && root->val < pred->val) {
      y = root;
      if (x == nullptr)
        x = pred;
      else
        return;
    }
    pred = root;

    inorder(root->right);
  }

  void swap(TreeNode* x, TreeNode* y) {
    const int temp = x->val;
    x->val = y->val;
    y->val = temp;
  }
};

// Helper function to build a tree from a vector (level-order, using 'null' as nullptr)
TreeNode* buildTree(const std::vector<std::string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(std::stoi(nodes[0]));
    std::queue<TreeNode*> q;
    q.push(root);
    int idx = 1;
    while (!q.empty() && idx < nodes.size()) {
        TreeNode* curr = q.front(); q.pop();
        if (idx < nodes.size() && nodes[idx] != "null") {
            curr->left = new TreeNode(std::stoi(nodes[idx]));
            q.push(curr->left);
        }
        idx++;
        if (idx < nodes.size() && nodes[idx] != "null") {
            curr->right = new TreeNode(std::stoi(nodes[idx]));
            q.push(curr->right);
        }
        idx++;
    }
    return root;
}

// Helper function to print a tree in level-order (as per the example output)
void printTree(TreeNode* root) {
    std::queue<TreeNode*> q;
    q.push(root);
    std::vector<std::string> res;
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (node) {
            res.push_back(std::to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        } else {
            res.push_back("null");
        }
    }
    // Remove trailing "null"s
    while (!res.empty() && res.back() == "null") res.pop_back();
    std::cout << "[";
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) std::cout << ",";
        std::cout << res[i];
    }
    std::cout << "]" << std::endl;
}

// Helper to parse input string like "[1,3,null,null,2]"
std::vector<std::string> parseInput(const std::string& s) {
    std::vector<std::string> res;
    std::string t = s;
    t.erase(std::remove(t.begin(), t.end(), '['), t.end());
    t.erase(std::remove(t.begin(), t.end(), ']'), t.end());
    std::stringstream ss(t);
    std::string item;
    while (getline(ss, item, ',')) {
        // Remove whitespace
        item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
        res.push_back(item);
    }
    return res;
}

int main() {
    std::vector<std::string> inputs = {
        "[1,3,null,null,2]",
        "[3,1,4,null,null,2]"
    };

    for (const auto& input : inputs) {
        std::cout << "Input: root = " << input << std::endl;
        auto nodeList = parseInput(input);
        TreeNode* root = buildTree(nodeList);

        Solution sol;
        sol.recoverTree(root);

        std::cout << "Output: ";
        printTree(root);
    }
    return 0;
}
