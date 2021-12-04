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

    class cutf8_iterator {
    public:
        cutf8_iterator(size_t pos, string_view sv, const vector<size_t>& v)
            : pos_(pos), sv_(sv), v_(&v) {
            if (pos<0 || pos > v_->size()-1) THROW("Invalid pos in ctor");
        }

        const cutf8_iterator& operator++() {
            pos_++;
            return *this;
        }

        bool operator!=(const cutf8_iterator& other) { return (pos_ != other.pos_); }
        string_view operator*() { 
            if (pos_ == v_->size() - 1) THROW("Invalid avestar in *it");
            return sv_.substr((*v_)[pos_], (*v_)[pos_ + 1] - (*v_)[pos_]); }

    protected:
        size_t pos_;

    private:
        const vector<size_t>* v_;
        string_view sv_;
    };

    class cutf8 {
    public:
        cutf8() = delete;
        cutf8(const string& str) : sv_(str) {
            try {
                build();
            }
            catch (exception& e) {
                throw;
            }
        }

        int build() {
            const char mask = '\x01';
            const char normal_mask = '\xc0';
            auto beg = sv_.begin();
            for (auto it = sv_.begin(); it != sv_.end();) {
                if ((*it & normal_mask) == '\x80') return -1;
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
                            if (!((*it & normal_mask) == '\x80')) {
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

        size_t count() { return v_.size() - 1; }

        string_view operator[](size_t ind) {
            return sv_.substr(v_[ind], v_[ind + 1] - v_[ind]);
        }

        cutf8_iterator begin() { return cutf8_iterator(0, sv_, v_); }

        cutf8_iterator end() { return cutf8_iterator(v_.size()-1, sv_, v_); }

    private:
        vector<size_t> v_;
        string_view sv_;
    };

}  // namespace turtle

