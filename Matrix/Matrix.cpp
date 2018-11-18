#include "Matrix.h"
#include <iostream>

namespace COLD
{
	void matrix::update_container()
	{
		m_container = std::vector<double>(m_line * m_column);
	}

	double matrix::get_value(const unsigned int i, const unsigned int j)
	{
		return m_container[(i - 1) * m_line + (j - 1)];
	}

	matrix::matrix()
	{
		update_container();
	}

	matrix::matrix(const unsigned int m, const unsigned int n) : m_line(m), m_column(n)
	{
		update_container();
	}

	matrix::matrix(const std::vector<double>& init_matrix)
	{
		int result = init_matrix.size() / 2;
		if (result < 1)
			result = 1;
		m_line = result;
		m_column = result;
		m_container = init_matrix;
	}

	void matrix::set_m(const unsigned int m)
	{
		m_line = m;
		update_container();
	}

	void matrix::set_n(const unsigned int n)
	{
		m_column = n;
		update_container();
	}

	void matrix::set(const std::vector<double>& vect)
	{
		m_container = vect;
	}

	void matrix::set_value(const unsigned int line, const unsigned int column, const double value)
	{
		m_container[(line - 1) * m_line + (column - 1)] = value;
	}

	void matrix::draw()
	{
		for (unsigned int i = 0; i < m_line; i++)
		{
			for (unsigned int j = 0; j < m_column; j++)
			{
				std::cout << get_value(i + 1, j + 1) << ", ";
			}
			std::cout << std::endl;
		}
	}

	bool matrix::operator==(matrix& a) const
	{
		if (m_line != a.m_line)
			return false;
		if (m_column != a.m_column)
			return false;
		return true;
	}

	matrix matrix::operator+(matrix& a)
	{
		if (m_line != a.m_line || m_column != a.m_column)
		{
			m_error = true;
			return matrix(0, 0);
		}

		matrix result(m_line, m_column);
		for (unsigned int i = 0; i < m_line * m_column; i++)
			result.m_container[i] = a.m_container[i] + m_container[i];

		return result;
	}

	matrix matrix::operator-(matrix& a)
	{
		if (m_line != a.m_line || m_column != a.m_column)
		{
			m_error = true;
			return matrix(0, 0);
		}

		matrix result(m_line, m_column);
		for (unsigned int i = 0; i < m_line * m_column; i++)
			result.m_container[i] = a.m_container[i] - m_container[i];

		return result;
	}

	matrix matrix::operator*(matrix& a) const
	{
		matrix returned(m_column,a.m_line);
		
		
		
		
		return returned;
	}

	double matrix::operator()(const unsigned int i, const unsigned int j)
	{
		return get_value(i, j);
	}
}
