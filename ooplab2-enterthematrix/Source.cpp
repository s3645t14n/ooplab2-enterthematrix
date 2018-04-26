//Определить класс «Квадратная матрица» – Matrix. Класс должен 
//содержать несколько конструкторов, в том числе конструктор 
//копирования. Реализовать методы для сложения, вычитания, 
//умножения матриц; вычисления нормы матрицы. Перегрузить 
//операции сложения, вычитания, умножения и присваивания для 
//данного класса. Создать массив объектов класса Matrix и 
//передать его в функцию, которая изменяет i - ю матрицу 
//путем возведения ее в квадрат. В головной программе вывести 
//результат.

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

double random(double min = 0.0, double max = 10.0) {
	return (double)(rand()) / RAND_MAX*(max - min) + min;
}

template <class t_Type> class Matrix {
	t_Type **f_p_matrix;
	int i_size;
public:
	//конструктор по умолчанию
	Matrix() {
		srand(clock()*time(0)*rand());
		cout << "Введите размерность: ";
		cin >> i_size;
		f_p_matrix = new t_Type*[i_size];
		for (int i = 0; i < i_size; i++)
			f_p_matrix[i] = new t_Type[i_size];
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
				f_p_matrix[i][j] = random();
	};

	//деструктор
	~Matrix() {
		for (int i = 0; i < i_size; i++)
			delete[] f_p_matrix[i];
		delete[] f_p_matrix;
		cout << "Матрица удалена" << endl;
	};

	//основной конструктор
	Matrix(int i_size) : i_size(i_size) {
		srand(clock()*time(0)*rand());
		f_p_matrix = new t_Type *[i_size];
		for (int i = 0; i < i_size; i++)
			f_p_matrix[i] = new t_Type[i_size];
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
				f_p_matrix[i][j] = random();
	};

	//конструктор копирования
	Matrix(const Matrix& matrix) {
		i_size = matrix.i_size;
		f_p_matrix = new t_Type *[i_size];
		for (int i = 0; i < i_size; i++) f_p_matrix[i] = new t_Type[i_size];
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
				f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
	};

	//возврат размера
	int GetSize() {
		return i_size;
	}

	//возврат элемента
	t_Type GetVal(int i, int j) {
		return f_p_matrix[i][j];
	}

	//сложение
	Matrix Sum(const Matrix& matrix) {
		Matrix *result = new Matrix(i_size);
		for (int i = 0; i < i_size; ++i)
			for (int j = 0; j < i_size; ++j)
				result->f_p_matrix[i][j] = f_p_matrix[i][j] + matrix.f_p_matrix[i][j];
		return *result;
	};

	//вычитание
	Matrix Sub(const Matrix& matrix) {
		Matrix *result = new Matrix(i_size);
		for (int i = 0; i < i_size; ++i)
			for (int j = 0; j < i_size; ++j)
				result->f_p_matrix[i][j] = f_p_matrix[i][j] - matrix.f_p_matrix[i][j];
		return *result;
	};

	//умножение
	Matrix Mul(const Matrix& matrix) {
		Matrix *result = new Matrix(i_size);
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++) {
				result->f_p_matrix[i][j] = 0;
				for (int k = 0; k < i_size; k++)
					result->f_p_matrix[i][j] += (f_p_matrix[i][k] * matrix.f_p_matrix[k][j]);
			}
		return *result;
	};

	//оператор сложения
	Matrix operator+ (const Matrix& matrix) {
		return Sum(matrix);
	};

	//оператор вычитания
	Matrix operator- (const Matrix& matrix) {
		return Sub(matrix);
	};

	//оператор умножения
	Matrix operator* (const Matrix& matrix) {
		return Mul(matrix);
	};

	//оператор присваивания
	Matrix& operator= (const Matrix& matrix) {
		if (&matrix != this) {
			delete[] f_p_matrix;
			f_p_matrix = new t_Type *[i_size];
			for (int i = 0; i < i_size; i++)
				f_p_matrix[i] = new t_Type[i_size];
			for (int i = 0; i < i_size; i++)
				for (int j = 0; j < i_size; j++)
					f_p_matrix[i][j] = matrix.f_p_matrix[i][j];
		}
		return *this;
	};

	//бесконечная норма
	t_Type InfNorm() {
		t_Type f_norm = 0.0;
		for (int i = 0; i < i_size; i++) {
			t_Type f_temp = 0.0;
			for (int j = 0; j < i_size; j++)
				f_temp += abs(f_p_matrix[i][j]);
			if (f_temp > f_norm) f_norm = f_temp;
		}
		return f_norm;
	};

	//первая норма
	t_Type FstNorm() {
		t_Type f_norm = 0.0;
		for (int j = 0; j < i_size; j++) {
			t_Type f_temp = 0.0;
			for (int i = 0; i < i_size; i++)
				f_temp += abs(f_p_matrix[i][j]);
			if (f_temp > f_norm) f_norm = f_temp;
		}
		return f_norm;
	};

	//евклидова норма
	t_Type EucNorm() {
		t_Type f_norm = 0.0;
		for (int i = 0; i < i_size; i++)
			for (int j = 0; j < i_size; j++)
				f_norm += abs(f_p_matrix[i][j] * f_p_matrix[i][j]);
		return sqrt(f_norm);
	};
};

//оператор вывода
template <typename o_Type> ostream& operator<< (ostream& out, Matrix<o_Type>& matrix) {
	int i, j;
	cout << "шаблонированный вывод через template <typename t_Type> ostream& operator<<\n";
	for (i = 0; i < matrix.GetSize(); i++) {
		out << endl;
		for (j = 0; j < matrix.GetSize(); j++)
			out << setw(5) << setprecision(3) << matrix.GetVal(i, j) << " ";
	}
	out << endl << endl << endl;
	return out;
}

//оператор вывода char
ostream& operator<< (ostream& out, Matrix<char>& matrix) {
	int i, j;
	cout << "простой вывод через ostream& operator<< (ostream& out, Matrix<char>& matrix)\n";
	for (i = 0; i < matrix.GetSize(); i++) {
		out << endl;
		for (j = 0; j < matrix.GetSize(); j++) {
			switch ((int)matrix.GetVal(i, j)) {
			case 0:
				out << setw(7) << "ноль" << " ";
				break;
			case 1:
				out << setw(7) << "один" << " ";
				break;
			case 2:
				out << setw(7) << "два" << " ";
				break;
			case 3:
				out << setw(7) << "три" << " ";
				break;
			case 4:
				out << setw(7) << "четыре" << " ";
				break;
			case 5:
				out << setw(7) << "пять" << " ";
				break;
			case 6:
				out << setw(7) << "шесть" << " ";
				break;
			case 7:
				out << setw(7) << "семь" << " ";
				break;
			case 8:
				out << setw(7) << "восемь" << " ";
				break;
			case 9:
				out << setw(7) << "девять" << " ";
				break;
			}
			
		}
	}
	out << endl << endl << endl;
	return out;
}

//вывод массива матриц
template <typename f_Type> void PrintMas(int i_quan, Matrix<f_Type>* matrix) {
	cout << "\nMatrix *m_p_mas = new Matrix[i_quan]:\n";
	for (int i = 0; i < i_quan; i++)
		cout << "m_p_mas[" << i << "]" << matrix[i];
}

//возведение матрицы в квадрат по ее индексу
template <typename f_Type> void Pow(int i_num, Matrix<f_Type>* matrix) {
	matrix[i_num] = matrix[i_num] * matrix[i_num];
}

void main() {
	setlocale(LC_ALL, "russian");
	cout << "КВАДРАТНЫЕ МАТРИЦЫ\n";
	int i_size, i_quan, i_num;

	//создание матриц
	cout << "Введите размерность(i_size): ";
	cin >> i_size;
	Matrix<float> m_1(i_size),
		m_res = (i_size);
	Matrix<int> mi_1(i_size);
	Matrix<char> mc_1(i_size);
	cout << "\nЗаполнение случайными числами...\n"
		<< "Оригинальная матрица float (Matrix m_1(i_size)):\n" << m_1
		<< "СЛучайная матрица int (Matrix mi_1(i_size)):\n" << mi_1
		<< "Случайная матрица char (Matrix mc_1(i_size)):\n" << mc_1;

	//демонстрация вычислений
	cout << "Бесконечная норма (m_1.InfNorm()) = " << m_1.InfNorm() << endl;
	cout << "Первая норма (m_1.FstNorm()) = " << m_1.FstNorm() << endl;
	cout << "Евклидова норма (m_1.EucNorm()) = " << m_1.EucNorm() << endl << endl;
	Matrix<float> m_2 = m_1;
	cout << "Использование конструктора копирования...\n"
		<< "Скопированная матрица(float) (m_2 = m_1):\n" << m_2;
	m_res = m_1 + m_2;
	cout << "Перегрузка оператора сложения...\n"
		<< "(m_res = m_1 + m_2):\n" << m_res;
	m_res = m_1 - m_2;
	cout << "Перегрузка оператора вычитания...\n"
		<< "(m_res = m_1 - m_2):\n" << m_res;
	m_res = m_1 * m_2;
	cout << "Перегрузка оператора умножения...\n"
		<< "(m_res = m_1 * m_2):\n" << m_res;
	m_res = m_1;
	cout << "Перегрузка оператора присваивания...\n"
		<< "(m_res = m_1): \n" << m_res;

	//работа с массивом матриц
	cout << "Создание массива матриц...\n"
		<< "Введите число матриц в массиве (i_quan):";
	cin >> i_quan;
	Matrix<float> *m_p_mas = new Matrix<float>[i_quan];
	PrintMas(i_quan, m_p_mas);
	cout << "Передача массива матриц в функцию возведения в квадрат...\n"
		<< "Введите индекс матрицы для возведения в квадрат:";
	cin >> i_num;
	Pow(i_num, m_p_mas);
	PrintMas(i_quan, m_p_mas);

	delete[] m_p_mas;
	cout << "Массив удален\n" << endl;
	system("@pause");
}