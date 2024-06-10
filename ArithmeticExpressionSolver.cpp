#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to evaluate an expression
bool findExpression(const vector<int>& numbersSet, int targetNum, int currentIndex, const string& currentExpression, string& finalExpression) {
    // Base case: If the target is 0 and all numbers are used, a solution is found
    if (targetNum == 0 && currentIndex == numbersSet.size()) {
        finalExpression = currentExpression;
        return true;
    }

    // Base case: If no more numbers are left, but the target is not achieved
    if (currentIndex == numbersSet.size()) {
        return false;
    }

    // Try adding the current number
    string additionExpression = currentExpression + (currentExpression.empty() ? "" : "+") + to_string(numbersSet[currentIndex]);
    if (findExpression(numbersSet, targetNum - numbersSet[currentIndex], currentIndex + 1, additionExpression, finalExpression)) {
        return true;
    }

    // Try multiplying the current number
    if (targetNum % numbersSet[currentIndex] == 0) {
        string multiplyExpression = currentExpression + (currentExpression.empty() ? "" : "*") + to_string(numbersSet[currentIndex]);
        if (findExpression(numbersSet, targetNum / numbersSet[currentIndex], currentIndex + 1, multiplyExpression, finalExpression)) {
            return true;
        }
    }

    return false;
}

int main() {
    vector<int> numbersSet = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int targetNum;
    cout << "Enter the target number: ";
    cin >> targetNum;

    string finalExpression;
    if (findExpression(numbersSet, targetNum, 0, "", finalExpression)) {
        cout << "Solution: " << finalExpression << " = " << targetNum << endl;
    } else {
        cout << "No solution exists for the target number " << targetNum << "." << endl;
    }

    return 0;
}
