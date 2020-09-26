//
// Created by Ruolin Liu on 9/25/20.
//

#ifndef CLASSIC__GRAPH_H_
#define CLASSIC__GRAPH_H_
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <stack>
#include <string>


class Graph {

  struct Node {
    int id;
    std::vector<int> parents;
    std::vector<int> children;
    Node() = default;
    Node(int i): id(i) {}
  };

 public:
  static Graph CreateSimpleGraph() {
    Graph g(8);
    g.AddEdge(2, 6);
    g.AddEdge(2, 5);
    g.AddEdge(0, 7);
    g.AddEdge(3, 5);
    g.AddEdge(3, 1);
    g.AddEdge(5, 1);
    g.AddEdge(5, 4);
    g.AddEdge(7, 6);
    return g;
  }

  int nodesize() const {
    return nodes_.size();
  }

  void AddEdge(int from, int to) {
    assert(from < nodesize() && to < nodesize());
    auto key = std::make_pair(from, to);
    if (std::find(edges_.begin(), edges_.end(), key) == edges_.end()) {
      edges_.push_back(key);
      nodes_[from].children.push_back(to);
      nodes_[to].parents.push_back(from);
    }
  }

  void TopologySort() {
    /*
     * The DFS method solves this problem in a recursive fashion. However, I am not using
     * a recursive call.
     * The node is added to the result as long as all of the nodes from its subtree has been "visited", i.e.,
     * added to the result. The non-recursive DFS uses a stack to record the display order. In contrast to DFS, we no longer
     * display the node when it is added to the stack. Instead, we display a node when it is either 1) a leaf node, or
     * 2) all of its children have been displayed. Finally, the topology order is the reverse of the display order.
     */

    std::stack<int> display;
    std::string res;
    std::vector<int> visit(nodesize(), 0);
    for (auto node : nodes_) {
      if (node.parents.size() == 0) {
        display.push(node.id);
      }
    }
    while (!display.empty()) {
      int curnid = display.top();
      bool no_child = true;
      for( auto chlid : nodes_[curnid].children) {
        if (visit[chlid] == 0) {
          no_child = false;
          display.push(curnid);
        }
      }
      if (no_child) {
        visit[curnid] = 1;
        display.pop();
        res += std::to_string(curnid);
      }
    }
    std::reverse(res.begin(), res.end());
    std::cerr << res << std::endl;
  }

  void DFS(int start = 0) {
    std::string res;
    std::cerr << nodesize() << std::endl;
    std::cerr << nodes_.size() << std::endl;
    std::vector<int> visit(nodesize(), 0);
    assert(nodesize() > 0);
    std::stack<int> display;
    display.push(start);
    visit[start] = 1;
    while (!display.empty()) {
      int curnid = display.top();
      res += std::to_string(curnid);
      res += "->";
      display.pop();
      for( auto chlid : nodes_[curnid].children) {
        if (visit[chlid] == 0) {
          display.push(chlid);
          visit[chlid] = 1;
        }
      }
    }
    std::cerr << res << std::endl;
  }

protected:
  Graph(int nnode) {
    for (unsigned i = 0; i < nnode; ++i) {
      nodes_.emplace_back(i);
    }
  }

  Graph() = default;

  std::vector<Node> nodes_;
  std::vector<std::pair<int, int>> edges_;

};

#endif //CLASSIC__GRAPH_H_
