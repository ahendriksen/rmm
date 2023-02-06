/*
 * Copyright (c) 2020-2021, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// If using GCC, temporary workaround for older libcudacxx defining _LIBCPP_VERSION
// undefine it before including spdlog, due to fmtlib checking if it is defined
// TODO: remove once libcudacxx is on Github and RAPIDS depends on it
#ifdef __GNUG__
#undef _LIBCPP_VERSION
#endif

#include <iostream>
#include <string>

namespace rmm {

namespace detail {

/**
 * @brief Represent a size in number of bytes.
 */
struct bytes {
  std::size_t value;

  friend std::ostream& operator<<(std::ostream& os, bytes const& value)
  {
    static std::array units{"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"};

    int index = 0;
    auto size = static_cast<double>(value.value);
    while (size > 1024) {
      size /= 1024;
      index++;
    }
    return os << size << ' ' << units.at(index);
  }
};

}  // namespace detail


// The default is INFO, but it should be used sparingly, so that by default a log file is only
// output if there is important information, warnings, errors, and critical failures
// Log messages that require computation should only be used at level TRACE and DEBUG
#define RMM_LOG_TRACE(...)
#define RMM_LOG_DEBUG(...)
#define RMM_LOG_INFO(...)
#define RMM_LOG_WARN(...)
#define RMM_LOG_ERROR(...)
#define RMM_LOG_CRITICAL(...)

}  // namespace rmm
