#include <set>
#include <list>
#include "gtest/gtest.h"
#include "fmt/format.h"

namespace {
//    struct C final {
//        C(const char c) : c_ {c} {}
//        C(const char c, const std::size_t idx) : c_ {c} {}
//        char c_{};
//        std::size_t idx_{};
//        [[nodiscard("do not discard")]]
//        bool operator<(const char c) const noexcept { return c_ < c; }
//    };

    std::set<char> db;
    std::list<char> buffer;

    [[nodiscard("do not discard")]]
    std::size_t find_max_non_repeating_seq(const std::string_view sv) {
        // using namespace std::literals; zu
        std::size_t max_so_far = 0;
        //std::size_t idx{};
        for(const auto c : sv) {
            if (db.contains(c)) {
                //max_so_far = std::max(max_so_far, db.size());
                max_so_far = std::max(max_so_far, buffer.size());
                //buffer.pop_front();
                // auto r = db.extract(C{c});
                auto r = db.extract(c);
                // r.value() = C{c, idx};
                r.value() = c;
                db.insert(std::move(r));
                //++idx;
                continue;
            }
            db.insert(c);
            //buffer.push_back(c);
            //++idx;
        }
        return max_so_far;
    }
}

TEST(leetcode_max_non_repeating_seq, test0) {
    fmt::print("D\n");
    const auto res = find_max_non_repeating_seq("D");
    ASSERT_EQ(res, 1);
}

TEST(leetcode_max_non_repeating_seq, test1) {
    fmt::print("DVDA\n");
    const auto res = find_max_non_repeating_seq("DVDA");
    ASSERT_EQ(res, 2);
}

TEST(leetcode_max_non_repeating_seq, test2) {
    fmt::print("ABCDEBER\n");
    const auto res = find_max_non_repeating_seq("ABCDEBER");
    ASSERT_EQ(res, 5);
}

TEST(leetcode_max_non_repeating_seq, test3) {
    fmt::print("ABCDEAER\n");
    const auto res = find_max_non_repeating_seq("ABCDEAER");
    ASSERT_EQ(res, 5);
}
