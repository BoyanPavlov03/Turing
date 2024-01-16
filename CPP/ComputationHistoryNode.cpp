#include "../HPP/ComputationHistoryNode.hpp"
#include <queue>

ComputationHistoryNode::ComputationHistoryNode(Tape *tape) {
    this->tape = tape;
}

void ComputationHistoryNode::writeToFileAllLeafs(const std::string& fileName) {
    std::ofstream file(fileName);
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(this);
    while (!nodes.empty()) {
        ComputationHistoryNode *node = nodes.front();
        nodes.pop();
        if (node->children.empty()) {
            node->tape->removeAllLastEmptySymbol();
            file << node->tape->toString() << " ";
        } else {
            for (auto &child: node->children) {
                nodes.push(child);
            }
        }
    }
    file.close();
}

void ComputationHistoryNode::graphVizPrint() {
    std::ofstream out("/Users/boyan/Downloads/Turing/Resources/graph.txt");
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(this);
    out << "digraph G {\n";
    while (!nodes.empty()) {
        ComputationHistoryNode *node = nodes.front();
        nodes.pop();
        if (node->children.empty()) {
            out << "\"" << node->tape->toString() << "\" [shape=doublecircle];\n";
        } else {
            for (auto &child: node->children) {
                out << "\"" << node->tape->toString() << "\" -> \"" << child->tape->toString() << "\";\n";
                nodes.push(child);
            }
        }
    }
    out << "}";
    out.close();
}