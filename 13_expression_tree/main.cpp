//
// Created by caiop on 12/10/2023.
//
#include <iostream>
#include <string>
#include "vector_tree.cpp"
#include "linked_tree.cpp"

void measureFunction(std::function<void()> function, std::string &results) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    results += std::to_string(duration.count());
}

void print_csv_string() {
    std::vector<std::string> cases = {
            "A*B", "A*B+C*D-E", "A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+X+Y*Z", "A+B*C+D-A/E+F",
            "A+B*C+D-A/E+F", "A*B+C", "A-B/C", "A/B/C/D/E*F", "A+B/C-D", "A+B/C-D/E*F"
    };
    std::string results = "type,buildTime,displayTime,breadthFirstSearchTime,preOrderTime,inlineOrderTime,posOrderTime,heightTime,height,size\n";

    for (auto expression: cases) {
        results += "Vector,";
        auto start = std::chrono::high_resolution_clock::now();
        ArithmeticExpressionVector arithmeticExpressionVector(expression);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        results += std::to_string(duration.count()) + ',';

        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.displayTree();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.breadthFirstSearchQueue();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.preOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.inlineOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.posOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionVector]() {
            arithmeticExpressionVector.height();
        }, results);
        results += ',';
        results += std::to_string(arithmeticExpressionVector.height());
        results += ',';
        results += std::to_string(arithmeticExpressionVector.size());
        results += '\n';
    }

    for (auto expression: cases) {
        results += "Linked,";
        auto start = std::chrono::high_resolution_clock::now();
        ArithmeticExpressionLinked arithmeticExpressionLinked(expression);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        results += std::to_string(duration.count()) + ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.displayTree();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.breadthFirstSearch();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.preOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.inlineOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.posOrder();
        }, results);
        results += ',';
        measureFunction([&arithmeticExpressionLinked]() {
            arithmeticExpressionLinked.height();
        }, results);
        results += ',';
        results += std::to_string(arithmeticExpressionLinked.height());
        results += ',';
        results += std::to_string(arithmeticExpressionLinked.size());
        results += '\n';
    }
    std::cout << '\n';
    std::cout << results;
}

int main() {
    print_csv_string();
//    std::string expression = "2*2-1";
//    std::cin >> expression;
//    ArithmeticExpressionVector arithmeticExpressionVector(expression);

//    std::cout << expression << '\n';
//    std::cout << "displayTree:\n";
//    arithmeticExpressionVector.displayTree();
//    std::cout << "breadthFirstSearchQueue: ";
//    arithmeticExpressionVector.breadthFirstSearchQueue();
//    std::cout << "preOrder: ";
//    arithmeticExpressionVector.preOrder();
//    std::cout << "inlineOrder: ";
//    arithmeticExpressionVector.inlineOrder();
//    std::cout << "posOrder: ";
//    arithmeticExpressionVector.posOrder();

//    ArithmeticExpressionLinked arithmeticExpressionLinked(expression);

//    std::cout << expression << '\n';
//    std::cout << "displayTree:\n";
//    arithmeticExpressionLinked.displayTree();
//    std::cout << "breadthFirstSearchQueue: ";
//    arithmeticExpressionLinked.breadthFirstSearchQueue();
//    std::cout << "preOrder: ";
//    arithmeticExpressionLinked.preOrder();
//    std::cout << "inlineOrder: ";
//    arithmeticExpressionLinked.inlineOrder();
//    std::cout << "posOrder: ";
//    arithmeticExpressionLinked.posOrder();

    return 0;
}

