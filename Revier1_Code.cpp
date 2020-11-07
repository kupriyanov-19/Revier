#include<iostream>
#include<vector>
typedef std::vector<std::vector<int64_t>> squareMatrix;

const int64_t MODULO = 1000000000 + 7;
const int INDEXATION_SHIFT = - 1;

// Structure for representation edges
struct Edge
{
    int edgeStart, edgeEnd;
};

// Function for multiplication two matrices
squareMatrix multiplyMatrices(
    const squareMatrix& matrixFirst,
    const squareMatrix& matrixSecond)
{
    const int heightOfFirstMatrix = matrixFirst.size();
    if (heightOfFirstMatrix < 1) {
        throw std::logic_error("matrix must have non-zero size");
    }
    const int widhtOfFirstMatrix = matrixFirst[0].size();
    const int heightOfSecondMatrix = matrixSecond.size();
    if (heightOfSecondMatrix < 1) {
        throw std::logic_error("matrix must have non-zero size");
    }
    const int widhtOfSecondmatrix = matrixSecond[0].size();
    if (widhtOfFirstMatrix != heightOfSecondMatrix) {
        throw std::logic_error("matrices cannot be multiplied");
    }

    squareMatrix matrixProduct;
    matrixProduct.assign(heightOfFirstMatrix, {});
    for (int i = 0; i < heightOfFirstMatrix; ++i) {
        matrixProduct[i].assign(widhtOfSecondmatrix, 0);
    }
    for (int row = 0; row < heightOfFirstMatrix; ++row) {
        for (int column = 0; column < widhtOfSecondmatrix; ++column) {
            for (int i = 0; i < widhtOfFirstMatrix; ++i) {
                matrixProduct[row][column] +=
                    (matrixFirst[row][i] * matrixSecond[i][column]) % MODULO;
            }
            matrixProduct[row][column] %= MODULO;
        }
    }
    return matrixProduct;
}

// Function for creating a identity matrix
squareMatrix createIdentityMatrix(const int matrixSize) {
    squareMatrix identityMatrix;
    identityMatrix.assign(matrixSize, {});
    for (int i = 0; i < matrixSize; ++i) {
        identityMatrix[i].assign(matrixSize, 0);
        identityMatrix[i][i] = 1;
    }
    return identityMatrix;
}

// Function for binary exponentiation
squareMatrix getMatrixPower(const squareMatrix& matrix, const int power) {
    if (power == 0) {
        return createIdentityMatrix(matrix.size());
    }
    if (power % 2 == 1) {
        const squareMatrix matrixInPowerMinusOneDegree =
            getMatrixPower(matrix, power - 1);
        return multiplyMatrices(matrix, matrixInPowerMinusOneDegree);
    } else {
        const squareMatrix matrixInPowerHalvedDegree =
            getMatrixPower(matrix, power / 2);
        return multiplyMatrices(matrixInPowerHalvedDegree,
            matrixInPowerHalvedDegree);
    }
}

// Function for read one number
int readNumber(std::istream& input) {
    int number;
    input >> number;
    return number;
}

std::vector<Edge> transformInput(
    const std::vector<Edge>& edgesInInputIndexing)
{
    std::vector<Edge> edgesInRequiredIndexing(edgesInInputIndexing.size());
    for (int i = 0; i < edgesInInputIndexing.size(); ++i) {
        edgesInRequiredIndexing[i].edgeStart =
            edgesInInputIndexing[i].edgeStart + INDEXATION_SHIFT;
        edgesInRequiredIndexing[i].edgeEnd =
            edgesInInputIndexing[i].edgeEnd + INDEXATION_SHIFT;
    }
    return edgesInRequiredIndexing;
}

std::vector<Edge> readEdges(
    std::istream& input,
    const int numberOfEdges)
{
    std::vector<Edge> edgesInInputIndexing(numberOfEdges);
    for (int i = 0; i < numberOfEdges; ++i) {
        int startOfEdge, endOfEdge;
        input >> startOfEdge >> endOfEdge;
        edgesInInputIndexing[i].edgeStart = startOfEdge;
        edgesInInputIndexing[i].edgeEnd = endOfEdge;
    }
    const std::vector<Edge> edgesInRequiredIndexing =
        transformInput(edgesInInputIndexing);
    return edgesInRequiredIndexing;
}

squareMatrix createAdjacencyMatrix(
    const std::vector<Edge>& allEdges,
    const int matrixSize)
{
    squareMatrix adjacencyMatrix;
    adjacencyMatrix.assign(matrixSize, {});
    for (int i = 0; i < matrixSize; ++i) {
        adjacencyMatrix[i].assign(matrixSize, 0);
    }
    for (int i = 0; i < allEdges.size(); ++i) {
        if (allEdges[i].edgeStart < 0 || allEdges[i].edgeStart >= matrixSize ||
            allEdges[i].edgeEnd < 0 || allEdges[i].edgeEnd >= matrixSize)
            throw std::range_error("vertex must exist in graph");
        adjacencyMatrix[allEdges[i].edgeStart][allEdges[i].edgeEnd]++;
    }
    return adjacencyMatrix;
}

// Function to calculate the sum in the first line of matrix
int countSumAtFirstLine(const squareMatrix& matrix) {
    int64_t sumAtFirstLine = 0;
    if (matrix.size() < 1) {
        throw std::logic_error("matrix must have non-zero size");
    }
    for (int i = 0; i < matrix[0].size(); ++i) {
        sumAtFirstLine += matrix[0][i];
    }
    return sumAtFirstLine % MODULO;
}

void printNumber(std::ostream& output, const int number) {
    output << number;
}

int countNumberOfPaths(
    const std::vector<Edge>& allEdges,
    const int numberOfRooms, const int power)
{
    const squareMatrix matrix = createAdjacencyMatrix(allEdges, numberOfRooms);
    const squareMatrix transformedMatrix = getMatrixPower(matrix, power);
    const int sumAtFirstLine = countSumAtFirstLine(transformedMatrix);
    return sumAtFirstLine;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const int numberOfRooms = readNumber(std::cin);
    const int numberOfEdges = readNumber(std::cin);
    const int power = readNumber(std::cin);
    const std::vector<Edge> allEdges = readEdges(std::cin, numberOfEdges);
    const int numberOfPaths =
        countNumberOfPaths(allEdges, numberOfRooms, power);
    printNumber(std::cout, numberOfPaths);
    return 0;
}
