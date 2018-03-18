#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class Matrix {
	float **f_p_matrix;
	int i_size;
public:
	//конструктор по умолчанию + основной
	Matrix(int i_size = 5): i_size(i_size) {
		int i, j;
		srand(time(0));
		f_p_matrix = new float *[i_size];
		for (i = 0; i < i_size; i++) f_p_matrix[i] = new float[i_size];
		for (i = 0; i < i_size; i++)
			for (j = 0; j < i_size; j++)
				f_p_matrix[i][j] = rand() % 11;
	}

	//оператор сложения
	Matrix& operator + (const Matrix& matrix) {
		return Sum(matrix);
	}

	//оператор вычитания
	Matrix& operator - (const Matrix& matrix) {
		return Sub(matrix);
	}

	//оператор умножения
	Matrix& operator * (const Matrix& matrix) {
		return Mul(matrix);
	}

	Matrix(const Matrix&); //конструктор копирования
	Matrix& Sum(const Matrix& matrix); //метод сложения
	Matrix& Sub(const Matrix& matrix); //метод вычитания
	Matrix& Mul(const Matrix& matrix); //метод умножения
	friend ostream& operator<<(ostream&, Matrix&); //оператор вывода
};

//конструктор копирования
Matrix::Matrix(const Matrix& matrix) {
	i_size = matrix.i_size;
	Matrix *temp = new Matrix[i_size];
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++)
			temp->f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
}

//метод сложения
Matrix& Matrix::Sum(const Matrix& matrix) {
	Matrix *result = new Matrix(i_size);
	for (int i = 0; i < i_size; ++i)
		for (int j = 0; j < i_size; ++j)
			result->f_p_matrix[i][j] = f_p_matrix[i][j] + matrix.f_p_matrix[i][j];
	return *result;
}

//метод вычитания
Matrix& Matrix::Sub(const Matrix& matrix) {
	Matrix *result = new Matrix(i_size);
	for (int i = 0; i < i_size; ++i)
		for (int j = 0; j < i_size; ++j)
			result->f_p_matrix[i][j] = f_p_matrix[i][j] - matrix.f_p_matrix[i][j];
	return *result;
}

//метод умножения
Matrix& Matrix::Mul(const Matrix& matrix) {
	Matrix *result = new Matrix(i_size);
	int i, j, k;

	for (i = 0; i < i_size; i++)
		for (j = 0; j < i_size; j++)
		{
			result->f_p_matrix[i][j] = 0;
			for (k = 0; k < i_size; k++)
				result->f_p_matrix[i][j] += (f_p_matrix[i][k] * matrix.f_p_matrix[k][j]);
		}
	return *result;
}

//оператор вывода
ostream& operator <<(ostream& out, Matrix& matrix) {
	int i, j;
	for (i = 0; i < matrix.i_size; i++) {
		out << endl;
		for (j = 0; j < matrix.i_size; j++)
			out << setw(3) << matrix.f_p_matrix[i][j] << " ";
	}
	out << endl << endl << endl;
	return out;
}

void main() {
	setlocale(LC_ALL, "russian");
	cout << "КВАДРАТНЫЕ МАТРИЦЫ 1.0\n";
	int i_size;
	cout << "Введите размерность: ";
	cin >> i_size;
	Matrix *m_1 = new Matrix(i_size),
		*m_2 = m_1,
		*m_res = new Matrix(i_size);
	cout << "\nОригинальная матрица:\n" << *m_1;
	cout << "Скопированная матрица:\n" << *m_2;
	*m_res = *m_1 + *m_2;
	cout << "Матрица1 + Матрица2:\n" << *m_res;
	*m_res = *m_1 - *m_2;
	cout << "Матрица1 - Матрица2:\n" << *m_res;
	*m_res = *m_1 * *m_2;
	cout << "Матрица1 * Матрица2:\n" << *m_res;
	cout << endl << endl;
	system("@pause");
}