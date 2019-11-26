#pragma once

#include <optional>


namespace details
{

template<typename T>
class assignable
{
public:
	assignable(const assignable& other)
		: value_(other.value_)
	{
	}

	assignable(assignable&& other)
		: value_(std::move(other.value_))
	{
	}

	assignable(const T& value)
		: value_(value)
	{
	}

	assignable(T&& value)
		: value_(std::move(value))
	{
	}

	assignable& operator=(const assignable& other)
	{
		value_.emplace(*other.value_);
		return *this;
	}

	assignable& operator=(assignable&& other)
	{
		value_ = std::move(other.value_);
		return *this;
	}

	template<typename... Args>
	decltype(auto) operator()(Args&&... args)
	{
		return (*value_)(std::forward<Args>(args)...);
	}

private:
	std::optional<T> value_;
};

} // namespace details
