#include "cutf8.h"

namespace turtle {

	int cutf8::build() {
		const char mask = '\x01';
		const char head2_mask = '\xc0';
		const char head2_match = '\x80';
		auto beg = sv_.begin();
		for (auto it = sv_.begin(); it != sv_.end();) {
			if ((*it & head2_mask) == head2_match) return -1;
			v_.emplace_back((size_t)(it - beg));
			if (!(*it & (mask << 7))) {
				it++;
				continue;
			}
			for (int i = 0; i < 6; i++) {
				if (!((mask << (6 - i)) & *it)) {
					int sz = i + 1;
					for (int j = 0; j < sz - 1; j++) {
						it++;
						if (!((*it & head2_mask) == head2_match)) {
							THROW("Invalid UTF8");
						}
					}
					it++;
					break;
				}
			}
		}
		v_.emplace_back((size_t)(sv_.end() - beg));
		return 0;
}

	cutf8::iterator::iterator(size_t pos, cutf8& cutf8)
		: pos_(pos), cutf8_(cutf8) {
		if (pos<0 || pos > cutf8.v_.size() - 1) THROW("Invalid pos in ctor");
	}


	string_view cutf8::iterator::operator*() {
		const auto& v = cutf8_.v_;
		const auto& sv = cutf8_.sv_;
		if (pos_ == v.size() - 1) THROW("Invalid avestar in *it");
		return sv.substr(v[pos_], v[pos_ + 1] - v[pos_]);
	}

}