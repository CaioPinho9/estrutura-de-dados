//
// Created by caiop on 12/10/2023.
//
#include <iostream>
#include <string>
#include "vector_tree.cpp"
#include "linked_tree.cpp"
#include <random>


void measureFunction(std::function<void()> function, std::string &results) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    results += std::to_string(duration.count());
}

void print_csv_string() {
    int now = 0;
    std::vector<std::string> cases = {
            "A*B",
            "A*B+C",
            "A-B/C",
            "A+B-C",
            "A+B/C-D",
            "A*B+C*D-E",
            "A*B-C/D+E",
            "A/B/C/D/E*F",
            "A+B/C-D/E*F",
            "A/B+C-D*E/F",
            "A-B+C*D/E-F",
            "A+B*C+D-A/E+F",
            "A+B*C+D-A/E+F",
            "A+B*C/D-E+F*G/H",
            "A+B*C/D-E+F*G/H-I",
            "A*B-C+D*E/F-G/H+I",
            "A/B/C*D*E+F-G*H+I",
            "A*B*C-D/E*F+G/H*I",
            "A+B-C*D/E+F*G-H/I",
            "A/B+C*D*E-F/G+H*I",
            "A*B/C/D+E-F*G/H*I/J",
            "A*B/C+D-E*F/G+H*I/J",
            "A+B*C-D*E/F+G-H*I/J*K",
            "A+B*C-D/E*F+G*H/I*J/K",
            "A*B*C/D*E+F-G/H*I/J*K/L",
            "A+B/C-D*E+F*G/H-I*J/K*L/M",
            "A*B/C+D-E*F/G-H*I/J*K*L/M*N",
            "A+B-C*D/E+F*G/H-I/J*K*L/M*N/O",
            "A*B*C/D-E*F+G/H-I*J/K*L/M*N/O*P",
            "A+B*C/D-E+F*G/H-I+J/K*L/M*N/O*P*Q",
            "A*B/C+D-E*F/G-H*I/J*K*L/M*N/O*P*Q*R",
            "A+B*C-D*E/F+G-H*I/J*K*L/M*N/O*P*Q*R*S",
            "A*B/C/D+E-F*G/H*I/J*K*L/M*N/O*P*Q*R*S*T",
            "A+B*C-D/E*F+G*H/I*J*K*L/M*N/O*P*Q*R*S*T*U",
            "A*B*C/D*E+F-G/H*I/J*K*L/M*N/O*P*Q*R*S*T*U*V",
            "A+B/C-D*E+F*G/H-I*J/K*L/M*N/O*P*Q*R*S*T*U*V*W",
            "A*B/C+D-E*F/G-H*I/J*K*L/M*N/O*P*Q*R*S*T*U*V*W*X",
            "A+B-C*D/E+F*G/H-I/J*K*L/M*N/O*P*Q*R*S*T*U*V*W*X*Y",
            "A*B*C/D-E*F+G/H-I*J/K*L/M*N/O*P*Q*R*S*T*U*V*W*X*Y*Z",
            "A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+X+Y*Z",
    };

    std::string results = "type,buildTime,displayTime,breadthFirstSearchTime,preOrderTime,inlineOrderTime,posOrderTime,heightTime,height,size\n";

    for (const auto &expression: cases) {
        std::cout << now << '/' << cases.size() * 2 << std::endl;
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
        now++;
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
        now++;
    }
    std::cout << '\n';
    std::cout << results;
}

int main() {
//    print_csv_string();

    std::string expression = "2*2-1";
    ArithmeticExpressionLinked arithmeticExpressionLinked(expression);

    std::cout << expression << '\n';
    std::cout << "displayTree:\n";
    arithmeticExpressionLinked.displayTree();
    std::cout << "breadthFirstSearchQueue: ";
    arithmeticExpressionLinked.breadthFirstSearch();
    std::cout << "preOrder: ";
    arithmeticExpressionLinked.preOrder();
    std::cout << "inlineOrder: ";
    arithmeticExpressionLinked.inlineOrder();
    std::cout << "posOrder: ";
    arithmeticExpressionLinked.posOrder();

    return 0;
}