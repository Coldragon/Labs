#pragma once
#include <iostream>
#include <vector>

namespace COLD
{
	class matrix
	{
	private:
		unsigned int m_m = 0, m_n = 0;
		bool m_isBadMatrix = false;
		std::vector<double> m_container;

		void update_container();

		double get_value(unsigned int i, unsigned int j);

	public:

		matrix();
		matrix(unsigned int m, unsigned int n);
		explicit matrix(const std::vector<double>& init_matrix);
		~matrix();

		void set_m(unsigned int m);
		void set_n(unsigned int n);
		void set(const std::vector<double>& vect);

		void draw();

		bool operator==(matrix& a) const;
		matrix operator+(matrix& a);
		double operator()(unsigned int i, unsigned int j);
	};
}

