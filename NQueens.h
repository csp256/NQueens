#pragma once

#include <vector>

namespace NQueens {
	using Index = uint32_t;

	//////////////////////////////////////////////////////////////////////////////

	class Solutions {
		std::vector<Index> _data;
		Index const _n;

	public:
		Solutions(Index const n) : _n{n} {}

		inline size_t count() const { return _n ? _data.size() / _n : 1; }

		inline void append(std::vector<Index> const& solution) 
		{
			if (solution.size() != _n) {
				throw std::runtime_error("solution was the wrong length");
			} else {
				_data.insert(_data.end(), solution.begin(), solution.end());
			}
		}

		inline Index const * solution_ptr(size_t number = 0) const 
		{
			return &_data[_n * number]; 
		}
	}; // class Solutions

	//////////////////////////////////////////////////////////////////////////////

	size_t count_solutions(Index const n = 8);
	
	Solutions all_solutions(Index const n = 8);
	
	void print_solutions(Index const n = 8);

	using SolutionVisitor = void (*)(std::vector<Index> const&);
	void visit_solutions(SolutionVisitor visitor, Index const n = 8);

	//////////////////

	/// http://oeis.org/A000170
	inline std::vector<uint64_t>& hardcoded() 
	{
		static std::vector<uint64_t> answer = {1, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 2279184, 14772512, 95815104, 666090624, 4968057848, 39029188884, 314666222712, 2691008701644, 24233937684440, 227514171973736, 2207893435808352, 22317699616364044, 234907967154122528};
		return answer;
	}

} // namespace NQueens 