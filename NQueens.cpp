#include "NQueens.h"

#include <climits>
#include <bit>
#include <iostream>

namespace NQueens {
	using UInt = uint32_t;

	template<class T> 
	const T& min(const T& a, const T& b)
	{
	    return (b < a) ? b : a;
	}

	constexpr UInt first_n_plus_one[] = {
		(1 << 1) - 1,
		(1 << 2) - 1,
		(1 << 3) - 1,
		(1 << 4) - 1,
		(1 << 5) - 1,
		(1 << 6) - 1,
		(1 << 7) - 1,
		(1 << 8) - 1,
		(1 << 9) - 1,
		(1 << 10) - 1,
		(1 << 11) - 1,
		(1 << 12) - 1,
		(1 << 13) - 1,
		(1 << 14) - 1,
		(1 << 15) - 1,
		(1 << 16) - 1,
		(1 << 17) - 1,
		(1 << 18) - 1,
		(1 << 19) - 1,
		(1 << 20) - 1,
		(1 << 21) - 1,
		(1 << 22) - 1,
		(1 << 23) - 1,
		(1 << 24) - 1,
		(1 << 25) - 1,
		(1 << 26) - 1,
		(1 << 27) - 1
	};

	constexpr UInt one_hot[] = {
		1,
		(1 << 1),
		(1 << 2),
		(1 << 3),
		(1 << 4),
		(1 << 5),
		(1 << 6),
		(1 << 7),
		(1 << 8),
		(1 << 9),
		(1 << 10),
		(1 << 11),
		(1 << 12),
		(1 << 13),
		(1 << 14),
		(1 << 15),
		(1 << 16),
		(1 << 17),
		(1 << 18),
		(1 << 19),
		(1 << 20),
		(1 << 21),
		(1 << 22),
		(1 << 23),
		(1 << 24),
		(1 << 25),
		(1 << 26),
		(1 << 27)};

	constexpr UInt relevance[] = {
		1,
		(1 << 1) - 1,
		(1 << 2) - 1,
		(1 << 3) - 1,
		(1 << 4) - 1,
		(1 << 5) - 1,
		(1 << 6) - 1,
		(1 << 7) - 1,
		(1 << 8) - 1,
		(1 << 9) - 1,
		(1 << 10) - 1,
		(1 << 11) - 1,
		(1 << 12) - 1,
		(1 << 13) - 1,
		(1 << 14) - 1,
		(1 << 15) - 1,
		(1 << 16) - 1,
		(1 << 17) - 1,
		(1 << 18) - 1,
		(1 << 19) - 1,
		(1 << 20) - 1,
		(1 << 21) - 1,
		(1 << 22) - 1,
		(1 << 23) - 1,
		(1 << 24) - 1,
		(1 << 25) - 1,
		(1 << 26) - 1,
		(1 << 27) - 1};

	constexpr UInt irrelevance[] = {
		~static_cast<UInt>(1),
		~static_cast<UInt>((1 << 1) - 1),
		~static_cast<UInt>((1 << 2) - 1),
		~static_cast<UInt>((1 << 3) - 1),
		~static_cast<UInt>((1 << 4) - 1),
		~static_cast<UInt>((1 << 5) - 1),
		~static_cast<UInt>((1 << 6) - 1),
		~static_cast<UInt>((1 << 7) - 1),
		~static_cast<UInt>((1 << 8) - 1),
		~static_cast<UInt>((1 << 9) - 1),
		~static_cast<UInt>((1 << 10) - 1),
		~static_cast<UInt>((1 << 11) - 1),
		~static_cast<UInt>((1 << 12) - 1),
		~static_cast<UInt>((1 << 13) - 1),
		~static_cast<UInt>((1 << 14) - 1),
		~static_cast<UInt>((1 << 15) - 1),
		~static_cast<UInt>((1 << 16) - 1),
		~static_cast<UInt>((1 << 17) - 1),
		~static_cast<UInt>((1 << 18) - 1),
		~static_cast<UInt>((1 << 19) - 1),
		~static_cast<UInt>((1 << 20) - 1),
		~static_cast<UInt>((1 << 21) - 1),
		~static_cast<UInt>((1 << 22) - 1),
		~static_cast<UInt>((1 << 23) - 1),
		~static_cast<UInt>((1 << 24) - 1),
		~static_cast<UInt>((1 << 25) - 1),
		~static_cast<UInt>((1 << 26) - 1),
		~static_cast<UInt>((1 << 27) - 1)};

	struct Threats {
		UInt S; /// South
		UInt SW; /// South-west
		UInt SE; /// South-east

		UInt all_threats;

	public:
		Threats(UInt S = 0, UInt SW = 0, UInt SE = 0) 
			: S{ S }
			, SW{ SW }
			, SE{ SE }
			, all_threats{ S | SW | SE }
		{}

		inline bool is_safe(UInt const column) const
		{
			return 0 == (all_threats & (1 << column));
		}

		/// Returns the ThreatMasks for next row; doesn't modify this struct
		inline Threats add_queen(Index const n, UInt const column) const 
		{
			UInt const mask = (1 << column);
			return Threats{
				S | mask, 
				((SW | mask) << 1) & relevance[n],
				(SE | mask) >> 1};
		}

		inline Index first_unthreatened() const
		{
			return std::countr_one(all_threats);
		}

		inline Index last_unthreatened(Index const n) const
		{
			constexpr UInt bitwidth = CHAR_BIT * sizeof(decltype(all_threats));
			return min<UInt>(n,
				bitwidth - std::countl_one(all_threats | irrelevance[n]));
		}

		inline void advance_column(Index & column) const
		{
			column = std::countr_one(all_threats | first_n_plus_one[column]);
		}

	}; // class Threats

	//////////////////////////////////////////////////////////////////////////////

	constexpr bool is_odd(Index const x)
	{
		return x & 1;
	}

	//////////////////////////////////////////////////////////////////////////////

	template <int kOddN, typename Function>
	inline void n_queens_search_impl(Index const n, Function&& callback)
	{
		std::vector<Index> solution;
		solution.resize( n );

		if (27 <= n) return; /// I don't think so!

		switch (n) {
		case 0: {
			/// 0 queens on a 0x0 board is a solution: http://oeis.org/A000170
			callback(solution);
			break;
		}
		case 1: {
			solution[0] = 0;
			callback(solution);
			break;
		}
		default: {
			std::vector<Index> mirror;
			mirror.resize( n );

			/// Includes middle column.
			Index const half_of_board = (kOddN) 
				? n / 2 + 1
				: n / 2;

			/// Only used is n is odd.
			Index const middle_of_board = n / 2;

			auto impl = [&](Index const row, Threats const threats, auto& impl) -> void
			{
				if (row == n) {
					callback(solution);
					for (Index i = 0; i < n; i++) {
						mirror[i] = (n - 1) - solution[i];
					}
					callback(mirror);
				} else {
					Index limit;

					if constexpr (kOddN) {
						if (2 <= row) {
							limit = threats.last_unthreatened(n);
						} else {
							if (row == 1) {
								limit = (solution[0] == middle_of_board)
									? half_of_board
									: threats.last_unthreatened(n);
							} else {
								limit = half_of_board;
							}
						}
					} else {
						limit = (row) 
							? threats.last_unthreatened(n)
							: half_of_board;
					}

					for (Index column = threats.first_unthreatened(); column < limit; threats.advance_column(column)) {
						if (threats.is_safe(column)) {
							solution[row] = column;
							// to deduce impl's own type at this location, we pass it as an argument
							impl(row + 1, threats.add_queen(n, column), impl);
						}
					}
				}
			};
			impl(0, Threats{}, impl);
		}
		} // switch
	} // n_queens_search()

	//////////////////////////////////////////////////////////////////////////////

	template <typename Function>
	inline void n_queens_search(Index const n, Function&& callback)
	{
		if (is_odd(n)) {
			n_queens_search_impl<1>(n, callback);
		} else {
			n_queens_search_impl<0>(n, callback);
		}
	} // n_queens_search()

	//////////////////////////////////////////////////////////////////////////////

	size_t count_solutions(Index const n)
	{
		size_t solution_count = 0;
		n_queens_search(n, [&](auto const& /*solution*/) -> void 
			{ 
				solution_count++; 
			});
		return solution_count;
	}

	Solutions all_solutions(Index const n)
	{
		Solutions solutions{ n };
		n_queens_search(n, [&](auto const& solution) -> void 
			{ 
				solutions.append(solution); 
			});
		return solutions;
	}

	void print_solutions(Index const n)
	{
		n_queens_search(n, [&](auto const& solution) -> void 
			{
				std::cout << "[";
				if (solution.size()) {
					for (Index i = 0; i < solution.size() - 1; i++) {
						std::cout << std::to_string(solution[i]) << ",";
					}
					std::cout << std::to_string(solution.back());
				}
				std::cout << "]\n";
			});
	}

	void visit_solutions(SolutionVisitor visitor, Index const n)
	{
		n_queens_search(n, visitor);
	}

} // namespace NQueens