#ifndef LOCAL_BOOST_TEST_INCLUDED_UNIT_TEST_HPP
#define LOCAL_BOOST_TEST_INCLUDED_UNIT_TEST_HPP

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace boost_test_detail {

using TestFn = void (*)();

struct TestCase {
    std::string name;
    TestFn fn;
};

inline std::vector<TestCase> &registry() {
    static std::vector<TestCase> tests;
    return tests;
}

inline int &failureCount() {
    static int failures = 0;
    return failures;
}

struct Registrar {
    Registrar(const char *name, TestFn fn) {
        registry().push_back(TestCase{name, fn});
    }
};

template <typename Left, typename Right>
inline void checkEqual(const Left &left, const Right &right, const char *leftExpr, const char *rightExpr, const char *file, int line) {
    if (!(left == right)) {
        ++failureCount();
        std::cerr << file << ":" << line << ": check failed: "
                  << leftExpr << " == " << rightExpr << std::endl;
    }
}

inline int runAll() {
    for (const TestCase &testCase : registry()) {
        try {
            testCase.fn();
        } catch (const std::exception &exception) {
            ++failureCount();
            std::cerr << "Unhandled exception in " << testCase.name << ": "
                      << exception.what() << std::endl;
        } catch (...) {
            ++failureCount();
            std::cerr << "Unhandled non-standard exception in " << testCase.name
                      << std::endl;
        }
    }

    if (failureCount() != 0) {
        std::cerr << failureCount() << " test check(s) failed" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed" << std::endl;
    return EXIT_SUCCESS;
}

}  // namespace boost_test_detail

#define BOOST_AUTO_TEST_SUITE(name)
#define BOOST_AUTO_TEST_SUITE_END()
#define BOOST_CHECK_EQUAL(left, right) \
    ::boost_test_detail::checkEqual((left), (right), #left, #right, __FILE__, __LINE__)

#define BOOST_AUTO_TEST_CASE(name)                                    \
    static void name();                                               \
    static ::boost_test_detail::Registrar registrar_##name(#name, &name); \
    static void name()

int main() {
    return ::boost_test_detail::runAll();
}

#endif
