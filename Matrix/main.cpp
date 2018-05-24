#include <vector>
#include <iostream>

namespace COLD
{

	class Matrix
	{
	private:
		unsigned int m_m = 0, m_n = 0;
		bool m_isBadMatrix = false;
		std::vector<double> m_container;

		void update_container();

		double get_value(unsigned int i, unsigned int j);

	public:

		Matrix();
		Matrix(const unsigned int m, const unsigned int n);
		explicit Matrix(const std::vector<double>& init_matrix);
		~Matrix() = default;

		void set_m(unsigned int m);;
		void set_n(unsigned int n);;
		void set(std::vector<double> vect);

		void draw();

		bool operator==(Matrix& a) const;
		Matrix operator+(Matrix& a);
		double operator()(unsigned int i, unsigned int j);
	};

	void Matrix::update_container()
	{
		m_container = std::vector<double>(m_m * m_n);
	}

	double Matrix::get_value(unsigned i, unsigned j)
	{
		return m_container[(i - 1) * m_m + (j - 1)];
	}

	Matrix::Matrix()
	{
		update_container();
	}

	Matrix::Matrix(const unsigned m, const unsigned n): m_m(m), m_n(n)
	{
		update_container();
	}

	Matrix::Matrix(const std::vector<double>& init_matrix)
	{
		int result = init_matrix.size() / 2;
		if (result < 1)
			result = 1;
		m_m = result;
		m_n = result;
		m_container = init_matrix;
	}

	void Matrix::set_m(unsigned m)
	{
		m_m = m;
		update_container();
	}

	void Matrix::set_n(unsigned n)
	{
		m_n = n;
		update_container();
	}

	void Matrix::set(std::vector<double> vect)
	{
		m_container = vect;
	}

	void Matrix::draw()
	{
		for (unsigned int i = 0; i < m_m; i++)
		{
			for (unsigned int j = 0; j < m_n; j++)
			{
				std::cout << get_value(i + 1, j + 1) << ", ";
			}
			std::cout << std::endl;
		}
	}

	bool Matrix::operator==(Matrix& a) const
	{
		if (m_m != a.m_m)
			return false;
		if (m_n != a.m_n)
			return false;
		return true;
	}

	Matrix Matrix::operator+(Matrix& a)
	{
		if (m_m != a.m_m || m_n != a.m_n)
		{
			m_isBadMatrix = true;
			return Matrix(0, 0);
		}

		Matrix result(m_m, m_n);
		for (int i = 0; i < m_m * m_n; i++)
			result.m_container[i] = a.m_container[i] + m_container[i];

		return result;
	}

	double Matrix::operator()(unsigned i, unsigned j)
	{
		return m_container[(i - 1) * m_m + (j - 1)];
	}
}

int main()
{
	COLD::Matrix g( { 2, 0, -1, 1 } );
	COLD::Matrix h( { 0, 0, 5, -5 } );

	auto a = g + h;
	auto b = a + g + h + h;

	b.draw();

	return 0;
}