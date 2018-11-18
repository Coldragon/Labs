#pragma once
#include <vector>

namespace COLD
{
	class matrix
	{
	private:
		unsigned int m_line = 0, m_column = 0;
		std::vector<double> m_container;

		bool m_error = false;

		void update_container();

		double get_value(unsigned int i, unsigned int j);
	
	public:

		matrix();
		matrix(unsigned int m, unsigned int n);
		matrix(const std::vector<double>& init_matrix);

		void set_m(unsigned int m);
		void set_n(unsigned int n);
		void set(const std::vector<double>& vect);
		void set_value(unsigned int line, unsigned int column, double value);

		void draw();

		bool operator== (matrix& a) const;
		matrix operator+ (matrix& a);
		matrix operator- (matrix& a);
		matrix operator* (matrix& a) const;
		double operator() (unsigned int i, unsigned int j);
	};
}

