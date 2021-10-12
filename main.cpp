#include <set>
#include <list>
#include "gtest/gtest.h"
#include "fmt/format.h"

namespace {
    struct C final {
        C(const char c) : c_ {c} {}
        C(const char c, const std::list<char>::iterator iter) : c_ {c}, iter_{iter} {}
        const char c_{};
        const std::list<char>::iterator iter_{};
        [[nodiscard("do not discard")]]
        bool operator<(const C& c) const noexcept { return c_ < c.c_; }
    };

    [[nodiscard("do not discard")]]
    std::size_t find_max_non_repeating_seq(const std::string_view sv) {
        std::set<C> db;
        std::list<char> buffer;

        // using namespace std::literals; zu
        std::size_t max_so_far = 0;
        //std::size_t idx{};
        fmt::print("sv is {}\n", sv);
        for(const auto c : sv) {
            if (const auto elem = db.find(c); elem != db.end()) {
                fmt::print("found repeating char {}\n", c);
                //max_so_far = std::max(max_so_far, db.size());
                // capture the maximum so far if it's bigger than what we have so far
                max_so_far = std::max(max_so_far, buffer.size());
                fmt::print("max so far {}\n", max_so_far);
                // we need to:
                //  1. delete all nodes from [begin, elem]. So to do so, we need to do something like
                //     [begin, elem+1) since the iterator end is ")" in C++ STL
                //  2. delete all nodes in db from [begin, elem+1)
                const auto end =  std::next((*elem).iter_);
                std::for_each(buffer.begin(), end, [&db](const char c){
                    fmt::print("erasinc char {}\n", c);
                    db.erase(c);
                });
                buffer.erase(buffer.begin(), end);
                fmt::print("buffer size is now {}\n", buffer.size());
                const auto iter = buffer.emplace(buffer.end(), c);
                const auto [_, b] = db.insert(C{c, iter});
                assert(b);                // auto r = db.extract(C{c});
                //auto r = db.extract(c);
                // r.value() = C{c, idx};
                //r.value() = C{c, idx};
                //db.(std::move(r));
                //++idx;
                continue;
            }
            fmt::print("new non-repeat char found {}\n", c);
            const auto iter = buffer.emplace(buffer.end(), c);
            const auto [_, b] = db.insert(C{c, iter});
            assert(b);
            max_so_far = std::max(max_so_far, buffer.size());
            fmt::print("non-repeat max so far {}\n", max_so_far);
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
    ASSERT_EQ(res, 3);
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
