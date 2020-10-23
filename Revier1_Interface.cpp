#include<iostream>
#include<vector>
typedef std::vector<std::vector<int64_t>> squareMatrix;

const int64_t modulo = 1000000000 + 7;

// Function for multiplication two matrices
squareMatrix multiplication(const squareMatrix& matrixFirst, const squareMatrix& matrixSecond);

// Function for creating a identity matrix
squareMatrix identityMatrix(const int matrixSize);

// Function for binary exponentiation
squareMatrix binaryPower(const squareMatrix& matrix, const int power);

// Function for read one number
int readNumber(std::istream&);

squareMatrix readMatrix(std::istream&, const int matrixSize, const int numberOfEdges);

// Function to calculate the sum in the first line of matrix
int countSumAtFirstLine(const squareMatrix& matrix);

void printNumber(std::ostream&, const int number);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  const int numberOfRooms=readNumber(std::cin), numberOfEdges=readNumber(std::cin), power=readNumber(std::cin);
  const squareMatrix matrix= readMatrix(std::cin, numberOfRooms, numberOfEdges);
  const int sumAtFirstLine=countSumAtFirstLine(binaryPower(matrix, power));
  printNumber(std::cout, sumAtFirstLine);
  return 0;
}