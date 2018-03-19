//Определить класс «Квадратная матрица» – Matrix. Класс должен 
//содержать несколько конструкторов, в том числе конструктор 
//копирования.Реализовать методы для сложения, вычитания, 
//умножения матриц; вычисления нормы матрицы.Перегрузить 
//операции сложения, вычитания, умножения и присваивания для 
//данного класса.Создать массив объектов класса Matrix и 
//передать его в функцию, которая изменяет i - ю матрицу 
//путем возведения ее в квадрат.В головной программе вывести 
//результат.

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class Matrix {
	float **f_p_matrix;
	int i_size;
public:
	//конструктор по умолчанию
	Matrix() {
		cout << "Введите размерность: ";
		cin >> i_size;
		f_p_matrix = new float *[i_size];
		for (int i = 0; i < i_size; i++) f_p_matrix[i] = new float[i_size];
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
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

	Matrix(int i_size); //конструктор основной
	Matrix(const Matrix&); //конструктор копирования
	Matrix& Sum(const Matrix& matrix); //сложение
	Matrix& Sub(const Matrix& matrix); //вычитание
	Matrix& Mul(const Matrix& matrix); //умножение
	Matrix& operator = (const Matrix& matrix); //оператор присваивания
	float InfNorm(); //бесконечная норма
	float FstNorm(); //первая норма
	float EucNorm(); //евклидова норма
	friend ostream& operator<<(ostream&, Matrix&); //оператор вывода
};

//конструктор копирования
Matrix::Matrix(const Matrix& matrix) {
	i_size = matrix.i_size;
	f_p_matrix = new float *[i_size];
	for (int i = 0; i < i_size; i++) f_p_matrix[i] = new float[i_size];
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++)
			f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
}

Matrix::Matrix(int i_size) : i_size(i_size) {
	f_p_matrix = new float *[i_size];
	for (int i = 0; i < i_size; i++) f_p_matrix[i] = new float[i_size];
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++)
			f_p_matrix[i][j] = rand() % 11;
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
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++) {
			result->f_p_matrix[i][j] = 0;
			for (int k = 0; k < i_size; k++)
				result->f_p_matrix[i][j] += (f_p_matrix[i][k] * matrix.f_p_matrix[k][j]);
		}
	return *result;
}

//оператор присваивания
Matrix& Matrix::operator = (const Matrix& matrix) {
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++)
			f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
	return *this;
}

//нахождение бесконечной нормы
float Matrix::InfNorm() {
	float f_norm = 0.0;
	for (int i = 0; i < i_size; i++) {
		float f_temp = 0.0;
		for (int j = 0; j < i_size; j++)
			f_temp += abs(f_p_matrix[i][j]);
		if (f_temp > f_norm) f_norm = f_temp;
	}
	return f_norm;
}

//нахождение первой нормы
float Matrix::FstNorm() {
	float f_norm = 0.0;
	for (int j = 0; j < i_size; j++) {
		float f_temp = 0.0;
		for (int i = 0; i < i_size; i++)
			f_temp += abs(f_p_matrix[i][j]);
		if (f_temp > f_norm) f_norm = f_temp;
	}
	return f_norm;
}

//нахождение евклидовой нормы
float Matrix::EucNorm() {
	float f_norm = 0.0;
	for (int i = 0; i < i_size; i++)
		for (int j = 0; j < i_size; j++)
			f_norm += abs(f_p_matrix[i][j]* f_p_matrix[i][j]);
	return sqrt(f_norm);
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

//вывод массива матриц
void PrintMas(int i_quan, Matrix *matrix) {
	cout << "\nMatrix *m_mas = new Matrix[i_quan]:\n";
	for (int i = 0; i < i_quan; i++)
	cout << "m_mas[" << i << "]" << matrix[i];
}

//возведение матрицы в квадрат по индексу
void Pow(int i_num, Matrix *matrix) {
	matrix[i_num] = matrix[i_num] * matrix[i_num];
}

void main() {
	setlocale(LC_ALL, "russian");
	srand(time(0));
	cout << "КВАДРАТНЫЕ МАТРИЦЫ\n";
	int i_size, i_quan, i_num;
	cout << "Введите размерность(i_size): ";
	cin >> i_size;
	Matrix m_1(i_size),
		m_2 = m_1,
		m_res = (i_size);
	cout << "\nЗаполнение случайными числами\n" << "Оригинальная матрица (Matrix m_1(i_size)):\n" << m_1;
	cout << "Бесконечная норма (m_1.InfNorm()) = " << m_1.InfNorm() << endl;
	cout << "Первая норма (m_1.FstNorm()) = " << m_1.FstNorm() << endl;
	cout << "Евклидова норма (m_1.EucNorm()) = " << m_1.EucNorm() << endl << endl;
	cout << "Использование конструктора копирования\n" << "Скопированная матрица (m_2 = m_1):\n" << m_2;
	m_res = m_1 + m_2;
	cout << "Перегрузка оператора сложения\n" << "(m_res = m_1 + m_2):\n" << m_res;
	m_res = m_1 - m_2;
	cout << "Перегрузка оператора вычитания\n" << "(m_res = m_1 - m_2):\n" << m_res;
	m_res = m_1 * m_2;
	cout << "Перегрузка оператора умножения\n" << "(m_res = m_1 * m_2):\n" << m_res;
	m_res = m_1;
	cout << "Перегрузка оператора присвоения\n" << "(m_res = m_1): \n" << m_res;
	cout << "Создание массива матриц\n" << "Введите число матриц в массиве (i_quan):";
	cin >> i_quan;
	Matrix *m_mas = new Matrix[i_quan];
	PrintMas(i_quan, m_mas);
	cout << "Передача массива матриц в функцию квадрата\n" << "Введите номер матрицы для возведения в квадрат:";
	cin >> i_num;
	Pow(i_num, m_mas);
	PrintMas(i_quan, m_mas);
	cout << endl << endl;
	delete m_mas;
	system("@pause");
}