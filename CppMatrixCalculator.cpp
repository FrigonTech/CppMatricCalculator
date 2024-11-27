#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

// Utility class for Matrix operations
class MatrixCalculator {
private:
    // Helper function to split string by delimiter
    static std::vector<std::string> split(const std::string& str, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            result.push_back(token);
        }
        return result;
    }

    // Helper function to draw matrix
    static void drawMatrix(const std::string& order, const std::map<std::string, int>& elements) {
        auto dims = split(order, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if(j==1){
                    std::cout<<"[";
                }
                else{
                    std::cout<<"][";
                }
                std::string key = std::to_string(i) + std::to_string(j);
                std::cout << elements.at(key) << "\t";
            }
            std::cout << "]" << std::endl;
        }
    }

    // Helper function to create matrix
    static std::pair<std::string, std::map<std::string, int>> createMatrix() {
        std::string order;
        std::cout << "Enter the order of matrix in 'mxn': ";
        std::cin >> order;
        
        auto dims = split(order, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        
        std::map<std::string, int> elements;
        for (int i = 1; i <= rows; i++) {//iterating over rows (top-bottom)
            for (int j = 1; j <= cols; j++) {//iterating over columns (left-right)
                std::cout << "Enter element " << i << j << ": ";//promppting value at ixj in matrix
                int value;
                std::cin >> value;
                elements[std::to_string(i) + std::to_string(j)] = value;//setting value of ixj at ixj in matrix
            }
        }
        return {order, elements};//returning orders and elements of matrix after creating it for ease
    }

public:
    // Addition of matrices
    static void addition() {
        std::cout << "For addition of matrices, we need two of them at a time\n";
        //we'll ask for two matrices for performing operations on them.
        auto [order1, matrix1] = createMatrix();
        auto [order2, matrix2] = createMatrix();
        //enforcing the rule of the mathematics in performing operations.
        if (order1 != order2) {
            std::cout << "Orders are not the same\n";
            return;
        }
        
        std::map<std::string, int> result;
        auto dims = split(order1, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        //adding elements in the correct manner.
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                std::string key = std::to_string(i) + std::to_string(j);
                result[key] = matrix1[key] + matrix2[key];
            }
        }
        //finally drawing result matrix.
        drawMatrix(order1, result);
    }
    //the rest of the operations follow the same function structure so commenting every-step in every function explicitely won't be necessary.

    // Subtraction of matrices
    static void subtraction() {
        std::cout << "For subtraction of matrices, we need two of them at a time\n";
        
        auto [order1, matrix1] = createMatrix();
        auto [order2, matrix2] = createMatrix();
        
        if (order1 != order2) {
            std::cout << "Orders are not the same\n";
            return;
        }
        
        std::map<std::string, int> result;
        auto dims = split(order1, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                std::string key = std::to_string(i) + std::to_string(j);
                result[key] = matrix1[key] - matrix2[key];
            }
        }
        
        drawMatrix(order1, result);
    }

    // Matrix multiplication
    static void multiplication() {
        std::cout << "For multiplication of matrices, we need two of them at a time\n";
        
        auto [order1, matrix1] = createMatrix();
        auto [order2, matrix2] = createMatrix();
        
        auto dims1 = split(order1, 'x');
        auto dims2 = split(order2, 'x');
        
        if (dims1[1] != dims2[0]) {
            std::cout << "The column of the first matrix and the row of the second matrix should match\n";
            return;
        }
        
        int rows1 = std::stoi(dims1[0]);
        int cols1 = std::stoi(dims1[1]);
        int cols2 = std::stoi(dims2[1]);
        
        std::map<std::string, int> result;
        std::string newOrder = dims1[0] + "x" + dims2[1];
        
        for (int i = 1; i <= rows1; i++) {
            for (int j = 1; j <= cols2; j++) {
                int sum = 0;
                for (int k = 1; k <= cols1; k++) {
                    std::string key1 = std::to_string(i) + std::to_string(k);
                    std::string key2 = std::to_string(k) + std::to_string(j);
                    sum += matrix1[key1] * matrix2[key2];
                }
                result[std::to_string(i) + std::to_string(j)] = sum;
            }
        }
        
        drawMatrix(newOrder, result);
    }

    // Scalar multiplication
    static void scalarMultiplication() {
        std::cout << "For scalar multiplication of matrix, we need a scalar quantity\n";
        
        auto [order, matrix] = createMatrix();
        
        std::cout << "Enter a scalar value to multiply: ";
        int scalar;
        std::cin >> scalar;
        
        std::map<std::string, int> result;
        auto dims = split(order, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                std::string key = std::to_string(i) + std::to_string(j);
                result[key] = matrix[key] * scalar;
            }
        }
        
        drawMatrix(order, result);
    }

    // Transpose of matrix
    static void transpose() {
        auto [order, matrix] = createMatrix();
        
        auto dims = split(order, 'x');
        int rows = std::stoi(dims[0]);
        int cols = std::stoi(dims[1]);
        
        std::map<std::string, int> result;
        std::string newOrder = dims[1] + "x" + dims[0];
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                std::string key = std::to_string(i) + std::to_string(j);
                std::string newKey = std::to_string(j) + std::to_string(i);
                result[newKey] = matrix[key];
            }
        }
        
        drawMatrix(newOrder, result);
    }
};

int main() {
    while (true) {
        std::cout << "What action to perform\n";
        std::cout << "Addition(1)\n"
                  << "Subtraction(2)\n"
                  << "Multiplication(3)\n"
                  << "Scalar Multiplication(4)\n"
                  << "Transpose(5)\n"
                  << "Exit(6)\n";
                  
        int choice;
        std::cout << "Enter the choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: MatrixCalculator::addition(); break;
            case 2: MatrixCalculator::subtraction(); break;
            case 3: MatrixCalculator::multiplication(); break;
            case 4: MatrixCalculator::scalarMultiplication(); break;
            case 5: MatrixCalculator::transpose(); break;
            case 6: return 0;
            default: std::cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}