#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node {
    std::string data;
    int id;
    int leftChildId;
    int rightChildId;
};

std::vector<Node> nodes;
int nextNodeId = 1;

void loadTree() {
    std::ifstream file("tree.txt");
    if (file.is_open()) {
        int numNodes;
        file >> numNodes;
        nodes.resize(numNodes + 1); // Reserve space for 1-based indexing

        for (int i = 1; i <= numNodes; ++i) {
            file >> nodes[i].id >> nodes[i].leftChildId >> nodes[i].rightChildId;
            std::getline(file, nodes[i].data);
        }

        nextNodeId = numNodes + 1; // Set the next available node ID
        file.close();
    } else {
        // Create a basic decision tree if file doesn't exist
        Node root = {"Is it an animal?", 1, 0, 0};
        nodes.push_back(root);
    }
}

void saveTree() {
    std::ofstream file("tree.txt");
    if (file.is_open()) {
        file << nodes.size() - 1 << "\n"; // Write the number of nodes

        for (int i = 1; i < nodes.size(); ++i) {
            file << nodes[i].id << " " << nodes[i].leftChildId << " " << nodes[i].rightChildId << " " << nodes[i].data << "\n";
        }

        file.close();
    } else {
        std::cout << "Unable to open file for writing.\n";
    }
}

void updateTree(int nodeIndex) {
    std::string correctAnswer, newQuestion;
    std::cout << "What is the correct answer? ";
    std::getline(std::cin, correctAnswer);
    std::cout << "What is the question distinguishing it? ";
    std::getline(std::cin, newQuestion);

    Node newNode = {newQuestion, nextNodeId, 0, 0};
    Node correctAnswerNode = {correctAnswer, nextNodeId + 1, 0, 0};

    nodes.push_back(newNode);
    nodes.push_back(correctAnswerNode);

    nodes[nodeIndex].leftChildId = nextNodeId + 1;
    nodes[nodeIndex].rightChildId = nextNodeId;

    nextNodeId += 2;
    saveTree();
}

void playGame() {
    int currentNodeIndex = 1;
    char response;

    while (nodes[currentNodeIndex].leftChildId != 0 && nodes[currentNodeIndex].rightChildId != 0) {
        std::cout << nodes[currentNodeIndex].data << " (y/n): ";
        std::cin >> response;
        std::cin.ignore();

        if (toupper(response) == 'Y') {
            currentNodeIndex = nodes[currentNodeIndex].leftChildId;
        } else {
            currentNodeIndex = nodes[currentNodeIndex].rightChildId;
        }
    }

    std::cout << "My guess is: " << nodes[currentNodeIndex].data << "\n";
    std::cout << "Is my guess correct? (y/n): ";
    std::cin >> response;
    std::cin.ignore();

    if (toupper(response) == 'N') {
        updateTree(currentNodeIndex);
    }
}

int main() {
    loadTree();
    playGame();
    return 0;
}