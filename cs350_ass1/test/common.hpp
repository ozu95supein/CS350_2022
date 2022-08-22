#ifndef CS350F21ES_COMMON_HPP
#define CS350F21ES_COMMON_HPP

#include "window.hpp"
#include <gtest/gtest.h>

// Modify this variable if working directory is giving issues
#ifndef WORKDIR
#define WORKDIR "./"
#endif

// GTEST Utilities
inline char const* test_name() { return ::testing::UnitTest::GetInstance()->current_test_info()->name(); }

#endif //CS350F21ES_COMMON_HPP
