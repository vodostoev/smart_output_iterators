#include <algorithm>
#include <cassert>
#include <deque>
#include <list>
#include <memory>
#include <vector>

#include "lower_bound_insert_iterator.h"
#include "sorted_unique_insert_iterator.h"

int main()
{
	{
		const std::vector source = { 1, 2, 4 };
		std::vector target = { 1, 3, 5 };
		const std::vector expected = { 1, 1, 2, 3, 4, 5 };

		std::copy(begin(source), end(source), lower_bound_inserter(target));

		assert(target == expected);
	}

	{
		const std::vector source = { 1, 2, 4 };
		std::list target = { 5, 3, 1 };
		const std::list expected = { 5, 4, 3, 2, 1, 1 };

		std::copy(begin(source), end(source),
			lower_bound_inserter(target, std::greater{}));

		assert(target == expected);
	}

	{
		const std::vector source = { 1, 2, 4 };
		std::deque target = { 5, 3, 1 };
		const std::deque expected = { 5, 4, 3, 2, 1, 1 };

		std::copy(begin(source), end(source),
			lower_bound_inserter(target, [](auto l, auto r) { return l > r; }));

		assert(target == expected);
	}

	{
		std::vector target = { 1, 2, 3, 5 };
		const std::vector expected = { 1, 2, 3, 4, 5 };

		auto it = sorted_unique_insert_iterator(target);
		*it = 1;
		*it = 2;
		*it = 4;

		assert(target == expected);
	}
}
