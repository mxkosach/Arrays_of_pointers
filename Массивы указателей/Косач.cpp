#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <fstream>
#include "myfunctions.h"
using namespace std;

void transp(int** M, int nr);
double mdn(int* X, int nx);

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	{
		title(1);
		const int nr = 5, nc = 10;
		int M[nr][nc];
		myrnd(M[0], nr * nc, -99, 99);
		cout << "Исходная матрица:\n";
		for (int i = 0; i < nr; i++)
			myout(M[i], nc);
		int k1 = 1, k2 = 4;
		cout << "Индексы переставляемых строк: " << k1 << " " << k2 << endl;

		//int* p; p = M[k1]; M[k1] = M[k2]; M[k2] = p; //ошибка
		int* P[nr];
		for (int i = 0; i < nr; i++)
			P[i] = M[i];
		int* p; p = P[k1]; P[k1] = P[k2]; P[k2] = p;

		cout << "Итоговая матрица:\n";
		for (int i = 0; i < nr; i++)
			myout(P[i], nc);
	}

	{
		title(2);
		const int nr = 5, nc = 10; int M[nr][nc];
		myrnd(M[0], nr * nc, -99, 99);
		cout << "Исходная матрица:\n";
		for (int i = 0; i < nr; i++)
			myout(M[i], nc);

		int X[nr];
		for (int i = 0; i < nr; i++)
			X[i] = M[i][nc - 1];
		int* P[nr];
		for (int i = 0; i < nr; i++)
			P[i] = M[i];
		mysrt(X, nr, 1, P);
		cout << "Итоговая матрица:\n";
		for (int i = 0; i < nr; i++)
			myout(P[i], nc);
	}

	{
		title(4);
		const int nr = 5; int M[nr][nr];
		myrnd(M[0], nr * nr, -9, 9);
		cout << "Исходная матрица:\n";
		myout(M[0], nr * nr, nr);

		int* A[nr], size[nr];
		for (int i = 0; i < nr; i++)
		{
			size[i] = i + 1;
			A[i] = new int[size[i]];
			for (int j = 0; j <= i; j++)
				A[i][j] = M[i][j];
		}
		cout << "Нижний треугольник матрицы:\n";
		for (int i = 0; i < nr; i++)
			myout(A[i], size[i]);
		for (int i = 0; i < nr; i++)
			delete[] A[i];
	}

	{
		title(5);
		float x = 2.2, * p1 = &x, ** p2 = &p1;
		cout << "Ячейка x  имеет адрес " << &**p2 << " и содержит значение " << **p2 << endl
			<< "Ячейка p1 имеет адрес " << &*p2 << " и содержит значение " << *p2 << endl
			<< "Ячейка p2 имеет адрес " << &p2 << " и содержит значение " << p2 << endl;
	}

	{
		title(6, 'a');
		char* s = new char[128];
		int nedg = myinput(s, "11.6.txt");
		int** edg = new int* [nedg];
		int nver = 0;
		char* p = s;
		for (int i = 0; i < nedg; i++)
		{
			edg[i] = new int[2];
			int beg = atoi(p);
			p += mycspn(p, " ");
			int end = atoi(p);
			if (beg > nver)
				nver = beg;
			if (end > nver)
				nver = end;
			edg[i][0] = beg;
			edg[i][1] = end;
			p += mylen(p) + 1;
		}
		cout << "Количество вершин графа = " << nver << endl;
		cout << "Количество ребер графа = " << nedg << endl;

		title(6, 'b');
		int** N = new int* [nver];
		for (int i = 0; i < nver; i++)
		{
			N[i] = new int[nver];
			for (int j = 0; j < nver; j++)
			{
				N[i][j] = 0;
			}
		}
		for (int i = 0; i < nedg; i++)
		{
			int beg = edg[i][0],
				end = edg[i][1];
			N[beg - 1][end - 1] = 1;
		}
		cout << "Матрица смежности графа:\n";
		for (int i = 0; i < nver; i++)
		{
			myout(N[i], nver, 6, 6);
		}

		title(6, 'c');
		int** E = new int* [nver];
		int* size = new int[nver];
		for (int i = 0; i < nver; i++)
		{
			size[i] = 0;
			for (int j = 0; j < nver; j++)
				size[i] += N[i][j];
			E[i] = new int[size[i]];
		}
		for (int i = 0; i < nver; i++)
			for (int j = 0, n = 0; j < nver; j++)
				if (N[i][j] == 1)
					E[i][n++] = j + 1;
		cout << "Матрица конечных вершин графа:\n";
		//for (int i = 0; i < nver; i++)
		//	if (size[i])
		//		myout(E[i], size[i], size[i], 4);
		//	else
		//		cout << endl;
		myout(E, nver, size); //задание 7

		for (int i = 0; i < nedg; i++)
			delete[]edg[i];
		for (int i = 0; i < nver; i++)
			delete[]N[i];
		for (int i = 0; i < nver; i++)
			delete[]E[i];
		delete[]edg; delete[]N; delete[]E;
		delete[]size;	delete[]s;
	}

	{
		title(8);
		const int nr = 5;
		int M[nr][nr];
		myrnd(M[0], nr * nr, -99, 99);
		cout << "Исходная матрица:\n";
		myout(M[0], nr * nr, nr);

		int* pM[nr];
		for (int i = 0; i < nr; i++)
			pM[i] = M[i];
		for (int i = 0; i < nr; i++)
			transp(pM, nr);
		cout << "Транспонированная матрица:\n";
		myout(M[0], nr * nr, nr);
	}

	{
		title(9, 'b');
		char* tmp = new char[1024];
		int ns = myinput(tmp, "11.9.txt");
		char** S = new char* [ns];
		char* p = tmp;
		for (int i = 0; i < ns; i++)
		{
			S[i] = new char[mylen(p) + 1];
			mycpy(S[i], p);
			p += mylen(p) + 1;
		}
		char** F = new char* [ns];
		for (int i = 0; i < ns; i++)
			F[i] = S[i];
		mysrt(F, ns, 1, S);
		cout << "Список студентов (сортировка по фамилии):\n";
		for (int i = 0; i < ns; i++)
			cout << S[i] << endl;

		title(9, 'c');
		char** G = new char* [ns];
		for (int i = 0; i < ns; i++)
		{
			char* p = S[i];
			for (int j = 0; j < 3; j++)
			{
				p += mycspn(p, " ");
				p += myspn(p, " ");
			}
			G[i] = p;
		}
		mysrt(G, ns, 1, S);
		cout << "Список студентов (сортировка по группе):\n";
		for (int i = 0; i < ns; i++)
			cout << S[i] << endl;

		title(9, 'd');
		int* V = new int[ns];
		for (int i = 0; i < ns; i++)
		{
			char* p = S[i];
			for (int j = 0; j < 4; j++)
			{
				p += mycspn(p, " ");
				p += myspn(p, " ");
			}
			V[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				V[i] += atoi(p);
				p += mycspn(p, " ");
				p += myspn(p, " ");
			}
		}
		mysrt(V, ns, 0, (int**)S);
		cout << "Список студентов (сортировка по оценкам):\n";
		for (int i = 0; i < ns; i++)
			cout << S[i] << endl;

		for (int i = 0; i < ns; i++)
			delete[]S[i];
		delete[]tmp;
		delete[]S;
		delete[]F;
		delete[]G;
		delete[]V;
	}

	{
		title(10);
		cout << "Пример 1:\n";
		char str[16] = "4321";
		int n = atoi(str);
		cout << "str = " << str << endl << "atoi(str) = " << n << endl;

		cout << "\nПример 2:\n";
		n = 1234;
		_itoa(n, str, 10);
		cout << "n = " << n << endl << "itoa(n,str,10) = " << str << endl;

		cout << "\nПример 3:\n";
		mycpy(str, "54,032");
		double d = atof(str);
		cout << "str = " << str << endl << "atof(str) = " << d << endl;

		cout << "\nПример 4:\n";
		d = 71.593267;
		ftoa(d, str, 3);
		cout << "d = " << fixed << d
			<< endl << "ftoa(d, str, 3) = " << str << endl;

		cout << "\nПример 5:\n";
		mycpy(str, "461qwe");
		n = atoi(str);
		cout << "str = " << str << endl
			<< "atoi(str) = " << n << endl;
		mycpy(str, "zxc940");
		n = atoi(str);
		cout << "str = " << str << endl
			<< "atoi(str) = " << n << endl;

		cout << "\nПример 6:\n";
		setlocale(LC_NUMERIC, "C");
		mycpy(str, "54.032");
		d = atof(str);
		cout << "str = " << str << endl
			<< "atof(str) = " << setprecision(3) << d << endl;
		setlocale(LC_ALL, "RUS");
	}

	{
		title(12);
		const int nr = 5, nc = 10; int M[nr][nc];
		myrnd(M[0], nr * nc, -99, 99);
		double X[nr];
		for (int i = 0; i < nr; i++)
			X[i] = mdn(M[i], nr);

		cout << "Исходная матрица и медианы её строк:\n" << setprecision(1);
		for (int i = 0; i < nr; i++)
		{
			myout(M[i], nc, nc + 1);
			cout << " |" << fixed << setw(6) << X[i] << endl;
		}

		int* pM[nr];
		for (int i = 0; i < nr; i++)
			pM[i] = M[i];
		mysrt(X, nr, false, (double**)pM);
		cout << "Итоговая матрица и медианы её строк:\n";
		for (int i = 0; i < nr; i++)
		{
			myout(M[i], nc, nc + 1);
			cout << " |" << fixed << setw(6) << X[i] << endl;
		}
	}

	{
		title(13);
		const int n = 6;
		int M[n][n];
		myrnd(M[0], n * n, -9, 9);
		cout << "Исходная матрица:\n";
		myout(M[0], n * n, n);

		int* A[n], * B[n];
		int* sizeA = new int[n], * sizeB = new int[n];
		for (int i = 0; i < n; i++)
		{
			sizeA[i] = n - i - 1;
			A[i] = new int[sizeA[i]];
			sizeB[i] = i + 1;
			B[i] = new int[sizeB[i]];
		}
		for (int i = 0; i < n; i++)
		{
			int ia = 0, ib = 0;
			for (int j = 0; j < n; j++)
				if (j < n - 1 - i)
					A[i][ia++] = M[i][j];
				else
					if (j > n - 1 - i)
						B[i - 1][ib++] = M[i][j];
		}
		cout << "Элементы над побочной диагональю:\n";
		for (int i = 0; i < n - 1; i++)
			myout(A[i], sizeA[i]);
		cout << "Элементы под побочной диагональю:\n";
		for (int i = 0; i < n - 1; i++)
		{
			cout << setw((n - i - 2) * 4) << "";
			myout(B[i], sizeB[i]);
		}
		for (int i = 0; i < n; i++)
		{
			delete[] A[i];
			delete[] B[i];
		}
		delete[] sizeA;
		delete[] sizeB;
	}

	{
		title(14);
		char* s = new char[64];
		int nr = myinput(s, "11.14.txt");
		int** R = new int* [nr];
		cout << "Рёбра графа:\n";
		char* p = s;
		for (int i = 0; i < nr; i++)
		{
			R[i] = new int[2];
			R[i][0] = atoi(p);
			p = mystr(p, " ");
			R[i][1] = atoi(p);
			cout << R[i][0] << "-->" << R[i][1] << "  ";
			if ((i + 1) % 4 == 0)
				cout << endl;
			p += mylen(p) + 1;
		}

		int nv = 6;
		int* tmp = new int[nv];
		for (int i = 0; i < nv; i++)
			tmp[i] = 0;
		for (int i = 0; i < nr; i++)
			tmp[R[i][1] - 1] = 1;
		cout << "Начальные вершины графа: ";
		for (int i = 0; i < nv; i++)
			if (tmp[i] == 0)
				cout << i + 1 << "  ";

		for (int i = 0; i < nv; i++)
			tmp[i] = 0;
		for (int i = 0; i < nr; i++)
			tmp[R[i][0] - 1] = 1;
		cout << "\nКонечные вершины графа: ";
		for (int i = 0; i < nv; i++)
			if (tmp[i] == 0)
				cout << i + 1 << "  ";
		for (int i = 0; i < nr; i++)
			delete[]R[i];
		delete[]s;	delete[]R;	delete[]tmp;
		cout << endl;
	}

	{
		title(15);
		char* s = new char[2048];
		int ns = myinput(s, "731.txt");

		char** stud = new char* [ns];
		int* numG = new int[ns];

		char* p = s;
		for (int i = 0; i < ns; i++)
		{
			stud[i] = new char[mylen(p) + 1];
			mycpy(stud[i], p);
			for (int j = 0; j < 4; j++)
			{
				p += mycspn(p, " ");
				p += myspn(p, " ");
			}
			numG[i] = atoi(p);
			p += mylen(p) + 1;
		}
		mysrt(numG, ns, 1, (int**)stud);

		char** tel = new char* [ns];
		const int ng = 5;
		int sizeG[ng] = {};
		for (int i = 0; i < ns; i++)
		{
			p = stud[i];
			for (int j = 0; j < 5; j++)
			{
				p += mycspn(p, " ");
				p += myspn(p, " ");
			}
			tel[i] = p;
			sizeG[numG[i] - 1]++;
		}
		int n = 0;
		for (int i = 0; i < ng; i++)
		{
			mysrt(&tel[n], sizeG[i], true, &stud[n]);
			n += sizeG[i];
		}

		cout << "Итоговый список:\n";
		for (int i = 0; i < ns; i++)
		{
			p = mystr(stud[i], "группа") - 1;
			int lenfio = p - stud[i];
			myout(stud[i], lenfio, lenfio + 1);
			cout << setw(33 - lenfio) << ' ' << p << endl;
		}

		for (int i = 0; i < ns; i++)
			delete[]stud[i];
		delete[]stud; delete[]numG; delete[]tel; delete[]s;
	}


	cout << endl; system("pause");
	return 0;
}

void transp(int** M, int nr)
{
	for (int i = 0; i < nr; i++)
		for (int j = i; j < nr; j++)
			swap(M[i][j], M[j][i]);
}

double mdn(int* X, int nx)
{
	int* tmp = new int[nx];
	for (int i = 0; i < nx; i++)
		tmp[i] = X[i];
	mysrt(tmp, nx);
	double res = nx % 2 == 0 ? tmp[nx / 2] : (tmp[nx / 2] + tmp[nx / 2 + 1]) / 2.;
	delete[]tmp;
	return res;
}
