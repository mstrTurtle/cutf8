#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <exception>
#ifdef _WIN32
#define THROW(str) (throw exception(str))
#else
#define THROW(str) (throw str)
#endif
namespace turtle {

	using std::string;
	using std::string_view;
	using std::vector;
	using std::exception;

	class cutf8 {
		
	public:
		class iterator {
		public:
			iterator(size_t pos, cutf8& cutf8);

			const iterator& operator++() {pos_++;return *this;}

			bool operator!=(const iterator& other) { return (pos_ != other.pos_); }

			string_view operator*();

		protected:
			size_t pos_;

		private:
			cutf8& cutf8_;
		};

		cutf8() = delete;
		cutf8(const string& str) : sv_(str) {
			try {
				build();
			}
			catch (exception& e) {
				throw;
			}
		}

		int build();

		size_t count() { return v_.size() - 1; }

		string_view operator[](size_t ind) {return sv_.substr(v_[ind], v_[ind + 1] - v_[ind]);}

		iterator begin() { return iterator(0, *this); }

		iterator end() { return iterator(v_.size() - 1, *this); }

	private:
		vector<size_t> v_;
		string_view sv_;
	};

}  // namespace turtle

