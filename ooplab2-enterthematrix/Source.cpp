#include <iostream>
#include <iomanip>

using namespace std;

class Matrix {
	float **f_p_matrix;
	int i_columns, i_rows;
public:
	Matrix(int i_columns = 5, int i_rows = 5): i_columns(i_columns), i_rows(i_rows) {
		int i, j;
		f_p_matrix = new float *[i_columns];
		for (i = 0; i < i_rows; i++) f_p_matrix[i] = new float[i_columns];
		for (i = 0; i < i_rows; i++)
			for (j = 0; j < i_columns; j++)
				f_p_matrix[i][j] = rand() % 20 + 1;
	}
	
	float Get(int i, int j) {
		return f_p_matrix[i][j];
	}

	void Show() {
		int i, j;
		cout << i_rows << " строк, " << i_columns << " столбцов.";
		for (i = 0; i < i_rows; i++) {
			cout << endl << endl;
			for (j = 0; j < i_columns; j++)
				cout << setw(2) << Get(i, j) << " ";
		}
	}

};

void main() {
	setlocale(LC_ALL, "russian");
	cout << "КВАДРАТНЫЕ МАТРИЦЫ 1.0\n";
	Matrix *m_1 = new Matrix();
	m_1->Show();

	cout << endl << endl;
	system("@pause");
}