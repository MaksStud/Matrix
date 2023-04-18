#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include <vector>
#include "doctest.h"

using namespace std;

template<typename T>
class SparseMatrix {
public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols), sparse_matrix(rows) {}

    void check_index(int row, int col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Invalid index");
        }
    }

    void add_element(int row, int col, T value) {
        check_index(row, col);
        sparse_matrix[row].emplace_back(col, value);
    }

    void remove_element(int row, int col) {
        check_index(row, col);
        auto& row_data = sparse_matrix[row];
        for (auto it = row_data.begin(); it != row_data.end(); ++it) {
            if (it->first == col) {
                row_data.erase(it);
                return;
            }
        }
        throw std::runtime_error("Element not found");
    }
    
    T get_element(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Invalid index");
        }

        for (const auto& item : sparse_matrix[row]) {
            if (item.first == col) {
                return item.second;
            }
        }

        return T{};
    }


    void print() {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                std::cout << get_element(row, col) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int rows;
    int cols;
    std::vector<std::vector<std::pair<int, T>>> sparse_matrix;
};

TEST_CASE("Add test type int") {
    SparseMatrix<int> matrix1(3, 3);
    matrix1.add_element(0, 0, 1);
    matrix1.add_element(1, 1, 2);
    matrix1.add_element(2, 2, 3);
    CHECK(matrix1.get_element(0, 0) == 1);
    CHECK(matrix1.get_element(1, 1) == 2);
    CHECK(matrix1.get_element(2, 2) == 3);
}

TEST_CASE("Add test type char") {
    SparseMatrix<char> matrix2(2, 2);
    matrix2.add_element(0, 0, 'a');
    matrix2.add_element(0, 1, 'b');
    matrix2.add_element(1, 0, 'c');
    CHECK(matrix2.get_element(0, 0) == 'a');
    CHECK(matrix2.get_element(0, 1) == 'b');
    CHECK(matrix2.get_element(1, 0) == 'c');
}

TEST_CASE("Add test type string") {
    SparseMatrix<string> matrix2(2, 2);
    matrix2.add_element(0, 0, "ab");
    matrix2.add_element(0, 1, "cg");
    matrix2.add_element(1, 0, "khg");
    CHECK(matrix2.get_element(0, 0) == "ab");
    CHECK(matrix2.get_element(0, 1) == "cg");
    CHECK(matrix2.get_element(1, 0) == "khg");
}


/*
int main() {
    SparseMatrix<int> matrix1(3, 3);
    matrix1.add_element(0, 0, 1);
    matrix1.add_element(1, 1, 2);
    matrix1.add_element(2, 2, 3);
    matrix1.print();

    cout << endl;

    SparseMatrix<char> matrix2(2, 2);
    matrix2.add_element(0, 0, 'a');
    matrix2.add_element(0, 1, 'b');
    matrix2.add_element(1, 0, 'c');
    matrix2.add_element(1, 1, 'd');
    matrix2.print();

    return 0;
} */


