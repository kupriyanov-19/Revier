#include<iostream>
#include<vector>
using std::vector;
typedef std::vector<std::vector<int64_t>> squareMatrix;

const int64_t MODULO = 1000000000 + 7;

// Structure for representation edges
struct Edge
{
    int edgeStart, edgeEnd;
};

// Function for multiplication two matrices
squareMatrix multiplyMatrices(const squareMatrix& matrixFirst, const squareMatrix& matrixSecond);

// Function for creating a identity matrix
squareMatrix createIdentityMatrix(const int matrixSize);

// Function for binary exponentiation
squareMatrix getMatrixPower(const squareMatrix& matrix, const int power);

// Function for read one number
int readNumber(std::istream&);

std::vector<Edge> readEdges(std::istream&, const int numberOfEdges);

squareMatrix createAdjacencyMatrix(const std::vector<Edge>&, const int matrixSize);

// Function to calculate the sum in the first line of matrix
int countSumAtFirstLine(const squareMatrix& matrix);

void printNumber(std::ostream&, const int number);

int countNumberOfPaths(const std::vector<Edge>&, const int numberOfRooms, const int power);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const int numberOfRooms = readNumber(std::cin);
    const int numberOfEdges = readNumber(std::cin);
    const int power = readNumber(std::cin);
    const std::vector<Edge> allEdges = readEdges(std::cin, numberOfEdges);
    const int numberOfPaths = countNumberOfPaths(allEdges, numberOfRooms, power);
    printNumber(std::cout, numberOfPaths);
    return 0;
}
