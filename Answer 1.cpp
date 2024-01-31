#include <iostream>
using namespace std;
template <typename T, size_t Rows, size_t Cols>
class mtrx {
private:
    T data[Rows][Cols];

public:
    mtrx() {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                data[i][j] = T();
            }
        }
    }
    
    template <size_t R, size_t C>
    auto operator+(const mtrx<T, R, C>& other) const {
        static_assert(Rows == R && Cols == C, "Matrix size mismatch for addition");
        mtrx<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = this->data[i][j] + other(i, j);
            }
        }
        return result;
    }
    
    template <size_t R, size_t C>
    auto operator-(const mtrx<T, R, C>& other) const {
        static_assert(Rows == R && Cols == C, "Matrix size mismatch for subtraction");
        mtrx<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = this->data[i][j] - other(i, j);
            }
        }
        return result;
    }
    
    template <size_t R, size_t C>
    auto operator*(const mtrx<T, R, C>& other) const {
        static_assert(Cols == R, "Matrix size mismatch for multiplication");
        mtrx<T, Rows, C> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < C; ++j) {
                for (size_t k = 0; k < Cols; ++k) {
                    result(i, j) += this->data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }
    auto operator*(const T& scalar) const {
        mtrx<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = this->data[i][j] * scalar;
            }
        }
        return result;
    }

    auto transpose() const {
        mtrx<T, Cols, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(j, i) = this->data[i][j];
            }
        }
        return result;
    }
    
    T& operator()(size_t row, size_t col) {
        if (row >= Rows || col >= Cols) {
            throw out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        if (row >= Rows || col >= Cols) {
            throw out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }
    
    friend ostream& operator<<(ostream& os, const mtrx<T, Rows, Cols>& mtrx) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                os << mtrx(i, j) << ' ';
            }
            os << '\n';
        }
        return os;
    }
};

template <typename T, size_t N>
class mtrx<T, N, 1> {
private:
    T data[N][1];

public:
    
    mtrx() {
        for (size_t i = 0; i < N; ++i) {
            data[i][0] = T();
        }
    }
    
    auto operator+(const mtrx<T, N, 1>& other) const {
        mtrx<T, N, 1> result;
        for (size_t i = 0; i < N; ++i) {
            result(i, 0) = this->data[i][0] + other(i, 0);
        }
        return result;
    }
    
    auto operator-(const mtrx<T, N, 1>& other) const {
        mtrx<T, N, 1> result;
        for (size_t i = 0; i < N; ++i) {
            result(i, 0) = this->data[i][0] - other(i, 0);
        }
        return result;
    }
    
    auto operator*(const T& scalar) const {
        mtrx<T, N, 1> result;
        for (size_t i = 0; i < N; ++i) {
            result(i, 0) = this->data[i][0] * scalar;
        }
        return result;
    }
    
    T& operator()(size_t row, size_t col) {
        if (row >= N || col >= 1) {
            throw out_of_range("mtrx indices out of range");
        }
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        if (row >= N || col >= 1) {
            throw out_of_range("mtrx indices out of range");
        }
        return data[row][col];
    }
};

int main() {
    mtrx<int, 2, 3> mat1;
    mtrx<int, 2, 3> mat2;

    cout << "Enter values for Matrix 1 (2x3):\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> mat1(i, j);
        }
    }

    cout << "Enter values for Matrix 2 (2x3):\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> mat2(i, j);
        }
    }
    
    mtrx<int, 2, 3> sum = mat1 + mat2;
    mtrx<int, 2, 3> diff = mat1 - mat2;
    mtrx<int, 2, 2> product = mat1 * mat2.transpose();
    cout << "mtrx 1:\n" << mat1 << "\n";
    cout << "mtrx 2:\n" << mat2 << "\n";
    cout << "mtrx 1 + mtrx 2:\n" << sum << "\n";
    cout << "mtrx 1 - mtrx 2:\n" << diff << "\n";
    cout << "mtrx 1 * (mtrx 2 transposed):\n" << product << "\n";
    return 0;
}
