#include <iostream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <list>
#include <vector>

template<typename R, typename F>
R Map(R r, F&& fn) {
	std::transform(
			std::begin(r),
			std::end(r),
			std::begin(r),
			std::forward<F>(fn)
	);
	return r;
}

template<typename R, typename F>
R Filter(R r, F&& fn) {
	R ret(r.size());
	auto first = std::begin(r);
	auto const last = std::end(r);
	auto result = std::begin(ret);
	size_t inserted = 0;
	while(first != last) {
		if(fn(*first)) {
			*result = *first;
			++inserted;
			++result;
		}
		++first;
	}
	ret.resize(inserted);
	return ret;
}
