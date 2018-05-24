#include "Matrix.h"

namespace COLD
{
	void matrix::update_container()
	{
		m_container = std::vector<double>(m_m * m_n);
	}

	double matrix::get_value(const unsigned int i, const unsigned int j)
	{
		return m_container[(i - 1) * m_m + (j - 1)];
	}

	matrix::matrix()
	{
		update_container();
	}

	matrix::matrix(const unsigned int m, const unsigned int n) : m_m(m), m_n(n)
	{
		update_container();
	}

	matrix::matrix(const std::vector<double>& init_matrix)
	{
		int result = init_matrix.size() / 2;
		if (result < 1)
			result = 1;
		m_m = result;
		m_n = result;
		m_container = init_matrix;
	}

	matrix::~matrix()
	= default;

	void matrix::set_m(const unsigned int m)
	{
		m_m = m;
		update_container();
	}

	void matrix::set_n(const unsigned int n)
	{
		m_n = n;
		update_container();
	}

	void matrix::set(const std::vector<double>& vect)
	{
		m_container = vect;
	}

	void matrix::draw()
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

	bool matrix::operator==(matrix& a) const
	{
		if (m_m != a.m_m)
			return false;
		if (m_n != a.m_n)
			return false;
		return true;
	}

	matrix matrix::operator+(matrix& a)
	{
		if (m_m != a.m_m || m_n != a.m_n)
		{
			m_isBadMatrix = true;
			return matrix(0, 0);
		}

		matrix result(m_m, m_n);
		for (unsigned int i = 0; i < m_m * m_n; i++)
			result.m_container[i] = a.m_container[i] + m_container[i];

		return result;
	}

	double matrix::operator()(const unsigned int i, const unsigned int j)
	{
		return m_container[(i - 1) * m_m + (j - 1)];
	}
}