#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class Matrix {
	float **f_p_matrix;
	int i_size, i_length;
public:
	Matrix(int i_size = 5): i_size(i_size), i_length(i_size*i_size){
		int i, j;
		srand(time(0));
		f_p_matrix = new float *[i_size];
		for (i = 0; i < i_size; i++) f_p_matrix[i] = new float[i_size];
		for (i = 0; i < i_size; i++)
			for (j = 0; j < i_size; j++)
				f_p_matrix[i][j] = rand() % 20 + 1;
	}

	Matrix(const Matrix &matrix) {
		i_size = matrix.i_size;
		Matrix *temp = new Matrix[i_size];
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
				temp->f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
	}
	
	float Get(int i, int j) {
		return f_p_matrix[i][j];
	}

	void Put(int i, int j, float f_value) {
		f_p_matrix[i][j] = f_value;
	}

	void Show() {
		int i, j;
		cout << "\nРазмер матрицы - " << i_size << "x" << i_size << ", количество элементов - " << i_length;
		for (i = 0; i < i_size; i++) {
			cout << endl << endl;
			for (j = 0; j < i_size; j++)
				cout << setw(2) << f_p_matrix[i][j] << " ";
		}
		cout << endl << endl;
	}

	Matrix operator+(Matrix &matrix)
	{
		Matrix *result = new Matrix(i_size);
		for (int i = 0; i < i_size; ++i)
			for (int j = 0; j < i_size; ++j)
				result->f_p_matrix[i][j] = this->f_p_matrix[i][j] + matrix.f_p_matrix[i][j];
		result->Show();
		return *result;
	}

};

void main() {
	setlocale(LC_ALL, "russian");
	cout << "КВАДРАТНЫЕ МАТРИЦЫ 1.0\n";
	int i;
	cout << "Введите размер матрицы: ";
	cin >> i;
	Matrix *m_1 = new Matrix(i), *m_2 = m_1, *m_3 = new Matrix();
	cout << "\nПервая матрица.";
	m_1->Show();
	cout << "Вторая матрица.";
	m_2->Show();
	m_3->Show();
	*m_3 = *m_1 + *m_2;
	m_3->Show();

	cout << endl << endl;
	system("@pause");
}