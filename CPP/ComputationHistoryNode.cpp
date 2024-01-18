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
    std::ofstream out("../Resources/graph.txt");
    std::queue<ComputationHistoryNode*> nodes;
    nodes.push(this);
    out << "digraph G {\n";
    unsigned index = 0;
    while (!nodes.empty()) {
        ComputationHistoryNode *node = nodes.front();
        nodes.pop();
        std::string nodeTapeString = node->tape->toString();
        if (node->children.empty()) {
            out << "\"" << nodeTapeString << "\" [shape=doublecircle];\n";
        } else {
            for (auto &child: node->children) {
                out << "\"" << nodeTapeString << "\" -> \"" << child->tape->toString() << "\" [xlabel = \"" << commandToString(child->command) << "\"];\n";
                nodes.push(child);
            }
        }
    }
    out << "}";
    out.close();
}