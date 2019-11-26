#pragma once

#include <algorithm>
#include <cassert>

#include "assignable.h"


template <
	typename Container,
	typename Predicate = std::less<>
>
class lower_bound_insert_iterator
{
public:
	using iterator_category = std::output_iterator_tag;
	using value_type = typename Container::value_type;
	using difference_type = void;
	using pointer = void;
	using reference = void;

public:
	explicit lower_bound_insert_iterator(Container& container, Predicate predicate = {})
		: container_(&container)
		, predicate_(std::move(predicate))
	{
		assert(std::is_sorted(container_->begin(), container_->end(), predicate_));
	}

	[[nodiscard]] lower_bound_insert_iterator& operator*() noexcept
	{
		return *this;
	}

	lower_bound_insert_iterator& operator++() noexcept
	{
		return *this;
	}

	lower_bound_insert_iterator operator++(int)
	{
		return *this;
	}

	lower_bound_insert_iterator& operator=(const value_type& value)
	{
		const auto it = std::lower_bound(container_->begin(), container_->end(), value, predicate_);
		container_->insert(it, value);
		return *this;
	}

	lower_bound_insert_iterator& operator=(value_type&& value)
	{
		const auto it = std::lower_bound(container_->begin(), container_->end(), value, predicate_);
		container_->insert(it, std::move(value));
		return *this;
	}

private:
	Container* container_;
	details::assignable<Predicate> predicate_;
};

template <
	typename Container,
	typename Predicate = std::less<>
>
auto lower_bound_inserter(Container& container, Predicate&& predicate = {})
{
	return lower_bound_insert_iterator(container, std::forward<Predicate>(predicate));
}
